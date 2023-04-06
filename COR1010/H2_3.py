first = input("First Name : ")
last = input("Last Name : ")
year = int(input("Year of birth : "))

login_id = last.title() + str(year)[:1:-1] + first[::-1].upper()

print("Login ID :", login_id)
