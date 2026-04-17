import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:  # Verifica que hayan los siguientes argumentos de entrada "python dna.py data.csv sequence.txt"
        print("Faltan argumentos de entrada")
        sys.exit(1)

   # TODO: Read database file into a variable
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # TODO: Read DNA sequence file into a variable
    try:
        with open(database_file, "r") as file:
            reader = csv.DictReader(file)  # Convierte cada fila en un diccionario
            database = list(reader)  # Lista de diccionarios que representan personas
    except FileNotFoundError:
        print(f"Error: File '{database_file}' no encontrado.")
        sys.exit(1)

    try:
        with open(sequence_file, "r") as file:
            dna_sequence = file.read()  # Lee todo el contenido del archivo de ADN
    except FileNotFoundError:
        print(f"Error: File '{sequence_file}' no encontrado.")
        sys.exit(1)

    # TODO: Find longest match of each STR in DNA sequence
    strs = database[0].keys() - {"name"}  # Obtén los STRs desde el encabezado del CSV
    str_counts = {str_: longest_match(dna_sequence, str_) for str_ in strs}

    # TODO: Check database for matching profiles
    for person in database:
        if all(int(person[str_]) == str_counts[str_] for str_ in strs):
            print(person["name"])
            return

    print("No match")
    return


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


main()
