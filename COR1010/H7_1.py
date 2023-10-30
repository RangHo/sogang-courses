word = input("Enter a word : ")

occurances = {}
for c in word:
    c = c.lower()
    occurances[c] = occurances.get(c, 0) + 1

print(occurances)
