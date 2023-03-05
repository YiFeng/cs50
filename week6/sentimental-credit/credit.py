# check credit card
import re
import traceback

Digits_pattern = r"^\d+$"
Amex_pattern = r"^3[47]\d{13}$"
Master_pattern = r"^5[1-5]\d{14}$"
Visa_pattern =r"^4(\d{12}|\d{15})$"

def get_card() -> str:
    while True:
        card_number = input("Number: ")
        if re.match(Digits_pattern, card_number):
            return card_number

def is_valid_card(card_number: str) -> bool:
    n = len(card_number)
    total_sum = 0
    for i in range(n):
        number = int(card_number[i])
        if (n - 1 - i) % 2 == 0:
            total_sum += number
            continue
        product = number * 2
        if product > 9:
            target_digit = product % 10 + int(product/10)
        else:
            target_digit = product
        total_sum += target_digit
    return total_sum % 10 == 0


def which_bank(card_number: str) -> str:
    if re.match(Amex_pattern, card_number):
        return "AMEX"
    if re.match(Master_pattern, card_number):
        return "MASTERCARD"
    if re.match(Visa_pattern, card_number):
        return "VISA"
    else:
        raise ValueError("Unknown card type")

def main():
    card_number = get_card()
    result = ""
    try:
        if not is_valid_card(card_number):
            raise ValueError("Invalid card number")
        result = which_bank(card_number)
    except Exception as e:
        # print(f"got an error: {e}")
        result = "INVALID"
    finally:
        print(result)

if __name__ == "__main__":
    main()