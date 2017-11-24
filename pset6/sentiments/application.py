from flask import Flask, redirect, render_template, request, url_for

import plotly
import helpers
import nltk
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    total_tweets = helpers.get_user_timeline(screen_name)

    # Initializeer de nltk class, Analyzer en variabelen.
    tokenizer = nltk.tokenize.TweetTokenizer()
    analyzer = Analyzer('positive-words.txt', 'negative-words.txt')
    positive, negative, neutral = 0.0, 0.0, 100.0

    # Analyzeer de tweets woord voor woord
    for array in total_tweets:
        tweet = tokenizer.tokenize(array)
        for words in tweet:
            if analyzer.analyze(words) > 0.0:
                positive += 1
                neutral -= 1
            elif analyzer.analyze(words) < 0.0:
                negative += 1
                neutral -= 1


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)


def chart(positive, negative, neutral):
    """Return a pie chart for specified sentiments as HTML."""

    # offline plot
    # https://plot.ly/python/pie-charts/
    # https://plot.ly/python/reference/#pie
    figure = {
        "data": [
            {
                "labels": ["positive", "negative", "neutral"],
                "hoverinfo": "none",
                "marker": {
                    "colors": [
                        "rgb(0,255,00)",
                        "rgb(255,0,0)",
                        "rgb(255,255,0)"
                    ]
                },
                "type": "pie",
                "values": [positive, negative, neutral]
            }
        ],
        "layout": {
            "showlegend": True
            }
    }
    return plotly.offline.plot(figure, output_type="div", show_link=False, link_text=False)