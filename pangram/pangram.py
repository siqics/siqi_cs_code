# Given a sentence, outputs whether or not it is a pangram.
# Siqi Wen 2021

# Strip all non-alphabetic characters out of the given
# string, convert alphabetic characters to codes and return
# the list containing all the codes.
def code(string):

    # Create an empty list.
    code_list = []

    # Look at each character of the string.
    for c in string:

        # Ignore all the non-alphabetic characters.
        if c.isalpha():

            # Convert each alphabetic character to a specific code.
            code_number = ord(c.lower()) - ord("a")

            # Append the code to the list.
            code_list.append(code_number)

    # Return the list.
    return code_list


# Return True if and only if the given string is a
# pangram (a phrase or sentence that uses every letter
# of the alphabet at least once).
def ispangram(codes):

    # Iterate from 0 to 25, check if every number is in the list.
    # Stop on first failure.
    for i in range(26):
        if i not in codes:
            return False

    # Return True when no failure was found.
    return True


# Prompt user for a string, use the functions to check and report the result.
sentence = str(input("Please enter a word or phrase: "))
pan = ispangram(code(sentence))

# If ispangram function returns True, which means pan is True, then the program executes this line.
if pan:
    print(f"** {sentence} ** is a pangram.\nIt contains all the letters of the alphabet!")

# If ispangram function returns False, then the program executes this line instead.
else:
    print(f"** {sentence} ** is not a pangram.\nIt does not contain all the letters of the alphabet.")