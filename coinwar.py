# Play the Coin War game after taking input from a file named on the command line.
# Siqi Wen 2021

# To access the random module and sys module.
from random import *
import sys


# Read the file that is named on the command line and return a list of two strings.
# The sequence of the letters in each string will be either random or set based
# on what the first line says in the file.
def read_list(filename):

    # Read the contents in the file and convert the contents into a list called "result".
    contents = filename.read()
    result = contents.split()

    # If the first element in the "result" list is "random", then this line will be executed.
    if result[0] == "random":

        # Create an empty list.
        combined_ar = []

        # Use for loop to repeat this procedure for ten times, in each
        # round, a random letter will be appended to the "combined_ar" list.
        # At the end, "combined_ar" will be a list of ten letters.
        for i in range(10):
            random_number = randrange(2)
            if random_number == 0:
                side = "H"
            else:
                side = "T"
            combined_ar.append(side)

        # Separate the "combined_ar" list. The first five letters will be the
        # army for player1; the last five will be the army for player2. Convert
        # each army list into a string, and put these two strings into a list which
        # will be the return value.
        army1_list = combined_ar[:5]
        army2_list = combined_ar[5:]
        army1_string = "".join(army1_list)
        army2_string = "".join(army2_list)
        combined_random_strings_list = [army1_string, army2_string]
        return combined_random_strings_list

    # If the first element in the "result" list is "position", then this line will be
    # executed instead.
    elif result[0] == "position":

        # The return value is a list of two elements which were the last two elements in
        # the "result" list.
        combined_position_strings_list = result[1:]
        return combined_position_strings_list


# Taking player1's army and player2's army as arguments and play the game by
# following the rules, then return 1 if player1 wins, 2 if player2 wins, or 0 if
# there is a tie.
def coin_war(player1, player2):

    # Create two empty lists for prisoners for player1 and player2.
    prisoner1 = []
    prisoner2 = []

    # All these lines in the while loop will only be executed when both
    # player1 and player2 have armies.
    while len(player1) > 0 and len(player2) > 0:

        # If the first elements in player1's army and player2's army are different
        if player1[0] != player2[0]:

            # Whoever has "H" as the first element in their army captures the coin of
            # the player with "T", and puts the "T" and "H" at the end of their army in
            # that order, and then captures any prisoners of the player with "T", and
            # places the opposing prisoners and then their own prisoners in order at
            # the end of their army.
            if player1[0] == "H":
                x = player2.pop(0)
                player1.append(x)
                y = player1.pop(0)
                player1.append(y)
                player1.extend(prisoner2)
                player1.extend(prisoner1)

                # Delete all the elements in prisoner1 and prisoner2 after moving them
                # into the army of player with "H".
                del prisoner1[:]
                del prisoner2[:]
            elif player2[0] == "H":
                x = player1.pop(0)
                player2.append(x)
                y = player2.pop(0)
                player2.append(y)
                player2.extend(prisoner1)
                player2.extend(prisoner2)
                del prisoner1[:]
                del prisoner2[:]

        # If the first elements in player1's army and player2's army are same
        elif player1[0] == player2[0]:

            # Each player puts their first coin at the end of their prisoners.
            x = player1.pop(0)
            prisoner1.append(x)
            y = player2.pop(0)
            prisoner2.append(y)

            # This will only be executed when both players have armies.
            if len(player1) > 0 and len(player2) > 0:

                # Players then put the first remaining coin in their armies at
                # the end of their prisoners.
                a = player1.pop(0)
                prisoner1.append(a)
                b = player2.pop(0)
                prisoner2.append(b)

    # The game will be immediately over when either player has no army.
    # If player1 still has army, then the return value is "1"; if player2
    # still has army, then "2" will be returned.
    if len(player1) > 0:
        return 1
    elif len(player2) > 0:
        return 2

    # If player1 and player2 both don't have army, whoever has more "H" in
    # their prisoners will be the winner. Otherwise, it will be a tie,
    # and "0" will be the return value when it's a tie.
    else:
        count1 = 0
        for i in prisoner1:
            if i == "H":
                count1 += 1
        count2 = 0
        for j in prisoner2:
            if j == "H":
                count2 += 1
        if count1 > count2:
            return 1
        elif count1 < count2:
            return 2
        else:
            return 0


# Set a variable called "armies" and assign it with the value that will
# be returned from function "read_list" when it takes the filename which
# will be typed on the command line as the argument.
armies = read_list(sys.stdin)

# The variable "armies" would be a list of two strings, take the first
# element in "armies" and convert it into a list of five letters, then
# assign it to the variable "player1_army"; take the second element
# in "armies" and convert it into another list of five letters, then
# assign it to another variable "player2_army".
player1_army = list(armies[0])
player2_army = list(armies[1])

# Take "player1_army" and "player2_army" as arguments in the function "coin_war",
# the return value will be assigned to the variable "winner".
winner = coin_war(player1_army, player2_army)

# Print out the two armies, and then print out the game result.
print("\n".join(armies))
print(winner)