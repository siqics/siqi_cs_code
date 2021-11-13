# Reply to any yes or no question with a randomly chosen answer
# Siqi Wen 2021

# To access the random module.
from random import *

# Assign variable random_prompt with a random number.
random_prompt = randrange(3) + 1

# Assign another variable random_answer with a random number.
random_answer = randrange(4) + 1

# Assign those four answers to four variables.
answer1 = "As I see it, yes."
answer2 = "Most likely not."
answer3 = "Better not tell you now."
answer4 = "Reply hazy, try again later."

# Selection of choices from 3 prompts based on what the random number is.
# And it will prompt the user to ask a yes or no question.
if random_prompt == 1:
    input("What question do you ask of me?\n")
elif random_prompt == 2:
    input("What is that you want now?\n")
else:
    input("What do you need to know?\n")

# Output one message to the user from those four answers based on what
# the random number is.
if random_answer == 1:
    print(answer1)
elif random_answer == 2:
    print(answer2)
elif random_answer == 3:
    print(answer3)
else:
    print(answer4)

