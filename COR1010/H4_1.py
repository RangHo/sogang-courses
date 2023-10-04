word = list(input("단어를 입력하시오 : "))

print(word)

if word[0].lower() not in "aeiou":
    piglatin = word[1:] + word[0:1]
else:
    piglatin = word.copy()

piglatin.extend(list("ay"))

print(piglatin)

print(f"{''.join(word)} ==> {''.join(piglatin)}")
