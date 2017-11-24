from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
# Helpers heb ik de ploty html functie geplaatst (chart_html)
from helpers import *
import json
import plotly



# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """
    Maak de index is kort vanwegen de make_portfolio functie die het werk
    doet.
    """

    # Zie fuctie. Data wordt opgehaald en verwerkt en gebracht naar de view
    portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
    id=session["user_id"])

    portfolio = make_portfolio(portfolio_db)
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

    return render_template("index.html", portfolio=portfolio, cash=usd(cash[0]['cash']))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":

        # Kijk of de input voldoet
        if not request.form.get("symbol"):
            return apology("must provide a symbol")
        elif not request.form.get("buy_amount"):
            return apology("you must provide an amout to buy")

        # Zoek de waarde op van het symbol of return als die niet bestaat
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("the symbol was not found")

        # Stel input in op BUY en neem aantal aandelen dat gekocht wordt
        buy_amount = request.form.get("buy_amount")
        type = 'BUY'

        cost = quote["price"] * int(buy_amount)
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # Bereken koste aan de hand van hoeveelheid gekochte producten.
        if cost > rows[0]["cash"]:
            return apology("you dont have the mony")
        else:
            # Als alles klopt dan kan de aankoop gedaan worden.
            # De SQL breekt als die op word gesplitst
            # Update history met nieuwe aankoop
            db.execute("INSERT INTO history ('id', 'type', 'symbol', 'shares', 'price') VALUES (:id, :type, :symbol, :shares, :price)",
            id=session["user_id"], type=type, symbol=quote["symbol"],
            shares=buy_amount, price=quote["price"])

            # Update cahs - nieuw aankoop.
            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id",
            cost=cost, id=session["user_id"])

            # Haal de niewe data op
            portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
            id=session["user_id"])
            portfolio = make_portfolio(portfolio_db)
            cash = db.execute("SELECT cash FROM users WHERE id = :id",
            id=session["user_id"])

            # Geef hier terug de waarden van de nieuwe portfolio in index.html
            return render_template("index.html", portfolio=portfolio,
            cash=usd(cash[0]['cash']))
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    # SQL van history steld wijnig voor, is al op voormaat.
    history = db.execute("SELECT * FROM history WHERE id = :id",
    id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id",
    id=session["user_id"])

    # Haal de geschidenis op en laat deze zien
    for row in history:
        row['price'] = usd(row['price'])

    return render_template("history.html",history=history, cash=usd(cash[0]['cash']))

@app.route("/login", methods=["GET", "POST"])

def login():
    """Log user in."""
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
        username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"),
        rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # In het geval van een post methode laat je de data zien van een lookup
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol")

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # None is de retrun value als de tikker niet te vinden is.
        if quote == None:
            return apology("the symbol was not found")

        else:
            # Wel gevonden mooi:
            return render_template("give_symbol_value.html",name=quote["name"],
            symbol=quote["symbol"], price=quote["price"])

    # anders een form
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])

def register():
    """Register user."""
    if request.method == "POST":
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        elif not request.form.get("password_confirmation"):
            return apology("must enter your pasword twice")

        elif not request.form.get("password") == request.form.get("password_confirmation"):
            return apology("enter the same password twice")

        # Hash (niet rookbaar) de wachtwoorden die binnenkomen
        hash = pwd_context.hash(request.form.get("password"))
        username=request.form.get("username")

        # Zet de data in de database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
        username=username, hash=hash)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
        username=username)

        # return result
        if not result:
            return apology("Username already exists")

        session["user_id"] = rows[0]["id"]

        return render_template("confirm_login.html", user=rows[0]["username"])

    else:
        return render_template("register.html")

@app.route("/chart", methods=["GET", "POST"])
@login_required
def chart():
    """Shows a piechart of the portfolio"""
    # generate chart
    portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
    id=session["user_id"])
    portfolio = make_portfolio(portfolio_db)


    # Initieer de dataobjecten die de pie opmaken en vul ze.
    symbols = []
    values = []
    for rows in portfolio:
        if rows != "Total value portfolio":
            symbols.append(rows)
            values.append(portfolio[rows]['pie_data'])
    chart = chart_html(symbols, values)

    # Ga met behulp van ploty funcite een pie diagram maken.
    return render_template("chart.html", chart=chart)

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        # Is het post, dan kijken of alles klopt:
        if not request.form.get("symbol"):
            return apology("must provide a symbol")
        elif not request.form.get("sell_amount"):
            return apology("you must provide an amout to sell")
        elif int(request.form.get("sell_amount")) < 0:
            return apology("you must provide a positive number of shares to sell")

        # Zet de variablen in objecten.
        symbol = request.form.get("symbol")
        sell_amount = int(request.form.get("sell_amount"))

        # Haal data uit de db en vorm om tot bruikbare dict.
        portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
        id=session["user_id"])
        portfolio = make_portfolio(portfolio_db)

        # Kijk of het aantal aandelen niet te groot is.
        if portfolio[symbol]['shares'] < sell_amount:
            return apology("you dont the shares")

        # Klopt het, mooi dan vullen we de database met nieuwe sell
        # en tellen we de sell op bij cash
        else:
            type = 'SELL'
            price = lookup(symbol)
            cost = price['price'] * sell_amount

            # Nogmaals SQL breekt als die word gesplitst.
            db.execute("INSERT INTO history ('id', 'type', 'symbol', 'shares', 'price') VALUES (:id, :type, :symbol, :shares, :price)",
            id=session["user_id"], type=type, symbol=symbol, shares=sell_amount,
            price=price["price"])

            db.execute("UPDATE users SET cash = cash + :cost WHERE id = :id",
            cost=cost, id=session["user_id"])

            # Weer nieuwe portfolio data ophalen.
            portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
            id=session["user_id"])
            portfolio = make_portfolio(portfolio_db)
            cash = db.execute("SELECT cash FROM users WHERE id = :id",
            id=session["user_id"])

            return render_template("index.html", portfolio=portfolio,
            cash=usd(cash[0]['cash']))
    else:
        portfolio_db = db.execute("SELECT symbol, SUM(shares), type, price FROM history WHERE id = :id GROUP BY symbol, type",
        id=session["user_id"])
        portfolio = make_portfolio(portfolio_db)

        stock = []
        for rows in portfolio:
            if rows != 'Total value portfolio':
                stock.append(rows)

        return render_template("sell.html", portfolio=stock)


def make_portfolio(database):
    """
    Om de portfolio data goed weer te geven heb ik een dict gemaakt.
    deze vul ik met alle data die belangrijk is inc data om de pie te maken
    """

    portfolio = {}
    amount = {}
    # Vul eerst een array met eventuele symbols
    # Maak null zodat we kunnen optellen enz.
    for items in database:
        amount[items['symbol']] = 0

    # Tel buy op trek sell af
    for items in database:
        if items['type'] == 'BUY':
            amount[items['symbol']] += items['SUM(shares)']
        else:
            amount[items['symbol']] -= items['SUM(shares)']

    total_value_portfolio = 0

    # Vul een dict met alles wat je wil weten over een portfolio
    for items in amount:
        if amount[items] > 0:
            temp = lookup(items)
            temp['total'] = temp['price'] * amount[items]
            total_value_portfolio += temp['total']
            portfolio[items] = {'symbol':temp['symbol'],
                                'name':temp['name'],
                                'shares':amount[items],
                                'price':usd(temp['price']),
                                'total':usd(temp['total']),
                                'pie_data':temp['total']}

    portfolio['Total value portfolio'] = {'value':usd(total_value_portfolio)}
    return portfolio