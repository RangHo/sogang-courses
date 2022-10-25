def f(L1, L2):
    if(len(L1) != len(L2)):
        print ("Error: L1 and L2 are not the same length!")
        return None
    length = len(L1)
    i = 0
    sum = 0
    while i < length:
        sum = sum + (L1[i]**L2[i])
        i = i + 1
    return sum

print(f([1,2],[2,3]))
print(f([1,2,3,4,5],[1,2,3,4,5]))