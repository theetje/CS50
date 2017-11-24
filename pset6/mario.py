import cs50

def mario():
    print("Height: ")


    # Vraag de hoogte
    while True:
        height = cs50.get_int()

        if (height > 0 and height < 23):
            break

    # Pas hoogte
    height += 1;

    # Loop over hoogte en per regel:
    for i in range(1, height ):
        print (' ' * (height - (i + 1)), end='')
        print ('#' * i, end='')
        print (' ', end='')
        print ('#' * i)

mario()