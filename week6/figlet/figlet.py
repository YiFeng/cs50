import pyfiglet
import sys
from sys import argv
import random

n = len(argv) - 1
# Get a list of all available fonts
fonts = pyfiglet.FigletFont.getFonts()
valid_inputs = ['-f', '--font']

def is_valid_argum(argv):
    if argv[1] in valid_inputs and argv[2] in fonts:
        return True
    else:
        print("Invalid usage")
        sys.exit(1)

if n == 0:
    # Get a list of all available fonts
    fonts = pyfiglet.FigletFont.getFonts()
    # Choose a random font
    font = random.choice(fonts)
    # Create a Figlet object with the chosen font
    fig = pyfiglet.Figlet(font=font)
elif n == 2:
    if is_valid_argum(argv):
        fig = pyfiglet.Figlet(font=argv[2])
else:
    print("Invalid usage")
    sys.exit(1)

#get user input
text = input("Please input a text: ")

print(fig.renderText(text))



