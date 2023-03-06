import csv
import sys

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

def find_pattern(dna_sequence: str, dna_database, STR_pattern) -> dict:
    dna_type = {}
    for pattern in STR_pattern:
        dna_type[pattern] = longest_match(dna_sequence, pattern)
    return dna_type

def check_match(dna_database, dna_type, STR_pattern):
    result = "No match"
    for row in dna_database:
        count_match = sum(1 if int(row[pattern]) == dna_type[pattern] else 0 for pattern in STR_pattern)
        if count_match == len(STR_pattern):
            result = row['name']
            break
    return result

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Please input two file names")

    # TODO: Read database file into a variable
    database_file = open(sys.argv[1], "r")
    dna_database = csv.DictReader(database_file)
    STR_pattern = list(dna_database.fieldnames)
    STR_pattern.remove("name")

    # TODO: Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], "r")
    dna_sequence = sequence_file.read()
    sequence_file.close()

    # TODO: Find longest match of each STR in DNA sequence
    # read STR pattern in DNA database
    dna_type = find_pattern(dna_sequence, dna_database, STR_pattern)

    # TODO: Check database for matching profiles
    print(check_match(dna_database, dna_type, STR_pattern))
    database_file.close()
    return


if __name__ == "__main__":
    main()
