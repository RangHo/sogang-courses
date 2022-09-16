x = int(input("Enter an integer greater than 2:"));
smallest_divisor = None;
for guess in range(2,x):
    if x % guess == 0:
        smallest_divisor = guess;
        break;
if smallest_divisor != None:
    #print("Smallest divisor of", x, "is", smallest_divisor);
    largest_divisor = int(x / smallest_divisor);
    print("Largest dividor of", x , "is", largest_divisor);
else:
    print(x, "Is a prime number.");