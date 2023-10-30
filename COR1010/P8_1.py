sentence = input("문자열을 입력하시오 :\n")

alphabets = digits = 0
for ch in sentence:
    if ch.isascii() and ch.isalpha():
        alphabets += 1
    elif ch.isdigit():
        digits += 1

print("알파벳의 개수 :", alphabets)
print("숫자의 개수 :", digits)
