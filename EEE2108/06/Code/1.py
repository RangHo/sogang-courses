import timeit

def search(L,e):
    Length = len(L) - 1
    LeftSide = 0
    RightSide = Length
    Mid = 0

    while LeftSide <= RightSide:
        Mid = (LeftSide + RightSide) // 2

        if L[Mid] < e:
            LeftSide = Mid + 1
        
        elif L[Mid] > e:
            RightSide = Mid - 1
        
        else:
            return Mid

    raise ValueError('Number was not found in list.')
    
i = 1000
while i < 1000000000:
    List = []
    List.extend(range(1,i))


    t1 = timeit.timeit(lambda: print(search(List, 40)), number=1)

    print("List of", i, "numbers.")
    print("Time:",t1,"s")
    i = i * 10
