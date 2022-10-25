def is_in(str1, str2):
    if str2 in str1 or str1 in str2:
        return True
    else:
        return False
#---------------------------------------- 위는 is_in function

def test_is_in(str1, str2):
    if is_in(str1, str2) == True:
        print("Output is True.")
    else:
        print("Output is False.")

#---------------------------------------- 아래는 테스트 함수를 테스트하기 위한 코드.
test_is_in("Hell", "Hello")
test_is_in("asdf", "Hello")