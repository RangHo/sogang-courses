bound = int(input("숫자를 입력하시오 : "))

count = 0
total = 0

while True:
    count += 1

    if count % 2 == 0:
        continue

    if count > bound:
        break

    total += count

print("{}까지 홀수 합은 {}입니다".format(bound, total))
