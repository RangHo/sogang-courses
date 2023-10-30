m2 = set()
m3 = set()

for i in range(1, 21):
    if i % 2 == 0:
        m2.add(i)
    if i % 3 == 0:
        m3.add(i)

print("6의 배수 :", m2 & m3)
