# print pyramids
def get_height():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                return height
        except ValueError:
            print("Please Enter a positive integer")

def print_pyramids(height):
    for i in range(height):
        n_blank = height - i - 1
        line = n_blank * " " + (i+1) * "#" + 2 * " " + (i+1) * "#"
        print(line)

def main():
    height = get_height()
    print_pyramids(height)

if __name__ == "__main__":
    main()

