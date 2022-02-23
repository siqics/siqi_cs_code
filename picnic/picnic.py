# The host of the picnic game.
# Siqi Wen 2021

# Create a variable which takes an input for the number of players.
player_number = int(input("How many players: "))

# Create a list.
player_names = []

# Use the for loop to fulfill the list with the names that user will type in one by one.
for i in range(player_number):
    name = input("Player " + str(i + 1) + " name: ")
    player_names.append(name)

# Create a while loop.
while player_number > 0:

    # For loop that iterates over player_names list and asks each player_name what they will bring.
    for player_name in player_names:

        # Create a variable and assign it with the answer each player_name types in each time.
        answer = input("\nHi " + player_name + "\nWe're going on a picnic! What will you bring: ")

        # Give out the corresponding response by checking if the
        # answer has the same first letter as the player_name.
        if answer[0].upper() == player_name[0].upper():
            print("\nYou can come!")
        else:
            print("\nSorry, you can't come.")

    # Create a variable and set it equal to False initially.
    stop_question = False

    # While loop that runs until it reaches to a specific condition.
    while not stop_question:

        # Create a variable that takes an input from user claiming if they want to try more or not.
        more_rounds = input("\ntry again?(yes/no): ")

        # Set variable stop_question equal to True to stop this while loop when user wants to try more.
        if more_rounds == "yes":
            stop_question = True

        # Exit the program when user wants no more rounds.
        elif more_rounds == "no":
            exit(0)

        # Prompt user to type in yes/or when they didn't.
        else:
            print("Please enter yes/no.")