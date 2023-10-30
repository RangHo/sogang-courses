def isSymmetric(word):
    for l, r in zip(word, reversed(word)):
        if l != r:
            return False
    return True

word = input("Enter a word : ")
result = isSymmetric(word)

if result:
    print(f"{word} is symmetric")
else:
    print(f"{word} is asymmetric")
