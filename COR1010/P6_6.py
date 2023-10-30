first_name = input("Enter your first name : ")
last_name = input("Enter your last name : ")
id = first_name.lower() + last_name[0].upper()
print("Your id is \"{}\"".format(id))

password = input("Input password : ")
if len(password) >= 12:
    if password.isascii() and password.isalnum():
        print("Valid password")
    else:
        print("Invalid character is included")
else:
    print("Must be at least 12 letters")
