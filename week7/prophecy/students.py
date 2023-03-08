import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

db.execute('CREATE TABLE IF NOT EXISTS students_new (id INTEGER PRIMARY KEY, student_name TEXT)')
db.execute('CREATE TABLE IF NOT EXISTS houses (house TEXT UNIQUE PRIMARY KEY, head TEXT)')
# db.execute('CREATE TABLE IF NOT EXISTS house_assign (student_id INTEGER PRIMARY KEY, house TEXT, FOREIGN KEY(house) REFERENCES houses(house)')

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        id = row['id']
        name = row['student_name']
        house = row['house']
        head = row['head']
        db.execute("INSERT INTO students_new (id) VALUES (?)", id)
        db.execute("INSERT INTO students_new (student_name) VALUES (?)", name)
        db.execute("INSERT INTO houses (house) VALUES (?)", house)
        db.execute("INSERT INTO houses (head) VALUES (?)", head)
        # db.execute("INSERT INTO house_assign (student_id) VALUES (?)", id)
        # db.execute("INSERT INTO house_assign (house) VALUES (?)", house)


