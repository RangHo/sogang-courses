total = 0
number = 0

while True:
    if total + number < 100:
        total += number
        number += 1
    else:
        break

print("The last number is {} and total is {}".format(number, total))
