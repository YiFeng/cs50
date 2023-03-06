# This program is to output grade level of a text
# formula: index = 0.0588 * L - 0.296 * S - 15.8
# letter is a to z or A to Z
# word is seperated by space
# sentence is seperated by . ! ?

sentence_mark = [".", "!", "?"]

def cal_coleLiau_index(text: str) -> int:
    letter_num =  sum(c.isalpha() for c in text)
    sentence_num = sum(c in sentence_mark for c in text)
    word_num = len(text.split())
    l = letter_num / word_num * 100
    s = sentence_num / word_num * 100
    return round(0.0588 * l - 0.296 * s - 15.8)

def grade_level(result: int):
    if result < 1:
        return "Before Grade 1"
    elif result >= 16:
        return "Grade 16+"
    else:
        return f"Grade {result}"


def main():
    text = input("Text: ")
    result = cal_coleLiau_index(text)
    print(grade_level(result))

if __name__ == "__main__":
    main()
