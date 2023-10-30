mul_2 = list(range(2, 31, 2))
mul_5 = list(range(5, 31, 5))

target = int(input("Enter the number : "))

if target in mul_2 and target in mul_5:
    print("2,5,10의 배수")
elif target in mul_2:
    print("2의 배수")
elif target in mul_5:
    print("5의 배수")
else:
    print("배수가 아님")
