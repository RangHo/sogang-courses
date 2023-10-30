numbers = input("세 개의 정수를 입력하시오 : ").split()
numbers = [int(i) for i in numbers]

if numbers[0] < numbers[1]:
    numbers[0], numbers[1] = numbers[1], numbers[0]
if numbers[1] < numbers[2]:
    numbers[1], numbers[2] = numbers[2], numbers[1]
if numbers[0] < numbers[1]:
    numbers[0], numbers[1] = numbers[1], numbers[0]

print("내림차순 :", numbers[0], numbers[1], numbers[2])
