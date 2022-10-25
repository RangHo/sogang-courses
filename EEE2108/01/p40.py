#x = int(input("Enter an integer\n"));
x = 1000;
sum = 0;

for j in range(3,x):
    Status = 1;
    for i in range(2,j):
        if (j % i == 0):
            Status = 0;
    if (Status == 1):
       #print(j);
       sum = sum + j;
print("Sum of primes:",sum);