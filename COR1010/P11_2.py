def is_prime(number: int) -> bool:
    if number <= 1:
        return False
    for i in range(2, number):
        if number % i == 0:
            return False
    return True


number = int(input("소수인지 확인할 숫자를 입력하시오 : "))
if is_prime(number):
    print("{}은(는) 소수입니다".format(number))
else:
    print("{}은(는) 소수가 아닙니다".format(number))
