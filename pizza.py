# Calculate the cost per square inch of the pizza
# Siqi Wen 2021

# To access the accurate version of π in the math library.
from math import *

# Take input from user for the pizza size and store it as an integer.
diameter = int(input("Enter the pizza size in inches: "))

# Take input from user for the pizza price and store it as a float.
price = float(input("Enter the pizza price: "))

# Find the radius from the diameter.
# https://sciencing.com/radius-diameter-7254718.html
radius = diameter / 2

# Find the area from the radius.
# https://en.wikipedia.org/wiki/Area_of_a_circle
area = pi * radius ** 2

# Calculate the pizza value and round it to two decimal places.
result = round(price / area, 2)

# Output the cost of the given pizza price and size in dollars per
# square inch by using the f-strings feature.
print(f"${result} per square inch")