Non_Primes = []

for x in range(2, 100):
    is_prime = True
    for y in range(2, x):
        if x%y == 0:
            is_prime = False
    if is_prime == False:
        Non_Primes.append(x)

print(Non_Primes)