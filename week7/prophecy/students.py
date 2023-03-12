import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

db.execute('CREATE TABLE IF NOT EXISTS students_new (id INTEGER PRIMARY KEY, student_name TEXT)')
db.execute('CREATE TABLE IF NOT EXISTS houses (id INTEGER PRIMARY KEY, house TEXTs, head TEXT)')
db.execute('CREATE TABLE IF NOT EXISTS house_assign (id INTEGER PRIMARY KEY, student_name TEXT, house TEXT)')

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        id = row['id']
        name = row['student_name']
        house = row['house']
        head = row['head']
        db.execute("INSERT INTO students_new (student_name) VALUES (?)", name)
        db.execute("INSERT INTO houses (house, head) VALUES (?,?)", house, head)
        db.execute("INSERT INTO house_assign (student_name, house) VALUES (?, ?)", name, house)


