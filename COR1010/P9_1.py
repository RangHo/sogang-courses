num_str = input("정수를 입력하시오 : ")
total = 0
index = 0
while index < len(num_str):
    total += int(num_str[index])
    index += 1

print("자리수의 합은 {}입니다.".format(total))
