ns = [int(n) for n in input("Enter two numbers : ").split()]

is_mutual_prime = True
min_n = min(ns)

i = 2
while i <= min_n:
    if ns[0] % i == 0 and ns[1] % i == 0:
        is_mutual_prime = False
        break
    i += 1

if is_mutual_prime:
    print("They are mutually prime.")
else:
    print("They are not mutually prime.")
