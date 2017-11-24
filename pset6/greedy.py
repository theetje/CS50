import cs50

def greedy():
    print("hai! How much change is owed? ")

    # Vraag zolang niet de juiste hoeveelheid geld wordt gegeven.
    while True:
        total_mony = cs50.get_float()

        if (total_mony > 0 and total_mony < 23):
            break

    total_mony = round(total_mony * 100)

    coins = 0;

    # Bereken hoeveel munten er uit komen en pas geld hoeveelheid aan.
    coins += int (total_mony / 25)
    total_mony = (total_mony % 25)

    coins += int (total_mony / 10)
    total_mony = (total_mony % 10)

    coins += int (total_mony / 5)
    total_mony = (total_mony % 5)

    coins += int (total_mony / 1)
    total_mony = (total_mony % 1)

    print("coins: ",coins)

greedy()
