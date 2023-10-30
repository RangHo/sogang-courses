vowels = "AEIOU"
c = input("영문자를 하나 입력하시오 : ").upper()

if c in vowels:
    print("%s은(는) 모음입니다." % c)
else:
    print("%s은(는) 자음입니다." % c)
