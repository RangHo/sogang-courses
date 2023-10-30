def replace(l: list, d: dict):
    for i, value in enumerate(l):
        if value in d:
            l[i] = d[value]

l = [2, 7, 5]
d = {1: 5, 2: 7, 3: 3, 5: 20}
replace(l, d)
print(l)
