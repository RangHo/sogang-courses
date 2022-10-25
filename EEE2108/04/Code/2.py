def is_in(str1, str2):
    if str2 in str1 or str1 in str2:
        return True
    else:
        return False

#아래는 결과출력을 위한 코드. 문제의 조건은 아니지만 과제 제출의 동작 사진을 위해 작성하였습니다.

if is_in("Hell", "HellO") == True:
    print("YES.")
else:
    print("No.")

if is_in("asdf", "HellO") == True:
    print("YES.")
else:
    print("No.")