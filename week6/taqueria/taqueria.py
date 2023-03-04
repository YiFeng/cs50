menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}



def get_order():
    total_price = 0
    while True:
        try:
            item = input("Item: ").title()
            if item in menu:
                price = menu[item]
                total_price += price
                print(f"Total: ${total_price:.2f}")
            else:
                continue
        except EOFError:
            break


def main():
    get_order()

if __name__ == "__main__":
    main()