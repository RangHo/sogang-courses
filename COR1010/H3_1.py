n = int(input("Etnter the number : "))

if n > 0:
    if n % 3 == 0:
        if n % 4 == 0:
            print(n, "is divided by both 3 and 4")
        else:
            print(n, "is divided by 3")
    elif n % 4 == 0:
        print(n, "is divided by 4")
    else:
        print(n, "is not divided by any number")
else:
    print(n, "is not valid input")
