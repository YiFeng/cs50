import pyfiglet
import sys
import random

valid_inputs = ['-f', '--font']

def is_valid_arg(argv, available_fonts):
    return argv[1] in valid_inputs and argv[2] in available_fonts

def print_message(message: str, font: str):
    fig = pyfiglet.Figlet(font=font)
    print(fig.renderText(message))

def main():
    n = len(sys.argv) - 1
    available_fonts = pyfiglet.FigletFont.getFonts()
    if n == 2 and is_valid_arg(sys.argv, available_fonts):
        font = sys.argv[2]
    elif n == 0:
        # Choose a random font
        font = random.choice(available_fonts)
    else:
        print("Invalid usage")
        sys.exit(1)

    #get user input
    text = input("Please input a text: ")
    print_message(text, font)

if __name__ == "__main__":
    main()