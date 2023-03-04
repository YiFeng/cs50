import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    recent2weeks_cases = {}
    previous_cases = {}
    for row in reader:
        state = row['state']
        num_case = int(row['cases'])

        if state not in recent2weeks_cases:
            recent2weeks_cases[state] = []
        if len(recent2weeks_cases[state]) >= 14:
            recent2weeks_cases[state].pop(0)

        if state in previous_cases:
            recent2weeks_cases[state].append(num_case - previous_cases[state])
        else:
            recent2weeks_cases[state].append(num_case)
        previous_cases[state] = num_case
    return recent2weeks_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        this_week = sum(new_cases[state][7:14]) / 7
        last_week = sum(new_cases[state][0:7]) / 7

        try:
            change = (this_week - last_week)/last_week * 100
            if change > 0:
                print(f"{state} had a 7-day average of {this_week:.0f} and an increase of {change:.0f}%")
            elif change < 0:
                print(f"{state} had a 7-day average of {this_week:.0f} and an decrease of {-change:.0f}%")
            else:
                print(f"{state} had a 7-day average of {this_week:.0f} and same as last week")
        except ZeroDivisionError:
            print("last week has 0 cases")



main()
