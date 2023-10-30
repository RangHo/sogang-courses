import random

def password(length):
    lowercase = "abcdefghijklmnopqrstuvwxyz"
    uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    numbers = "0123456789"
    symbols = "!@#$%^&*"
    all = lowercase + uppercase + numbers + symbols

    selected = random.choice(uppercase)
    for i in range(length-1):
        selected += random.choice(all)

    return selected

length = int(input("Enter the length of password : "))
print("Password is", password(length))
