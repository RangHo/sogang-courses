num_strs = input("Enter numbers : ").split()

primes = []
for num_str in num_strs:
    num = int(num_str)

    # Check if num is prime
    is_prime = True
    for n in range(2, int(num**0.5) + 1):
        if num % n == 0:
            is_prime = False
            break

    if is_prime:
        primes.append(num)

print("Prime number :", primes)
