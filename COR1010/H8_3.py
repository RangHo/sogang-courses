def countChars(s):
    occurances = {}
    for c in s:
        c = c.lower()
        occurances[c] = occurances.get(c, 0) + 1

    return occurances

input_str = input("Enter string : ")
occurances = countChars(input_str)

print("=" * 30)

for c, n in occurances.items():
    print("{} : {}번 사용되었습니다.".format(c, n))
