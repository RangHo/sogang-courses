base10 = int(input("Enter the number : "))

base8 = base10
base8_str = ""
while base8 > 0:
    rem = base8 % 8
    base8 = base8 // 8
    base8_str = str(rem) + base8_str

print(f"{base10} is {base8_str} in oct")
