import sys
import cs50

# Kijk of de juiste hoeveelheid argumenten worden gegeven.
if len(sys.argv) == 2:
    plaintext = cs50.get_string()

    key = int(sys.argv[1])

    # Loop over de letters, kijk of het ascii is, zo ja pas aan op hoofdletter
    # en kleiner latter en print, zo nee print teken.
    for letter in plaintext:
        if letter.isalpha():
            if letter.isupper():
                print(chr(((ord(letter) - 65  + key) % 26) + 65), end='')
            else:
                print(chr(((ord(letter) - 97 + key) % 26) + 97), end='')
        else:
            print(letter, end='')

    print('\n')

else:
    print("Not the right amount of arguments.")