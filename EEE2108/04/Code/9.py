# global 변수를 하나 설정하고, 함수가 값을 return할때마다 그 수에 1씩 추가함.

effcounter = 0
def fib_efficient(n, d): 
    global effcounter
    if n in d:
        effcounter = effcounter + 1
        return d[n] 
    else:
        effcounter = effcounter + 1
        ans = fib_efficient(n-1, d) + fib_efficient(n-2, d)
        d[n] = ans
        return ans
d = {1:1, 2:2}
print(fib_efficient(6, d))
print("Function was called",effcounter,"times.")



counter = 0

def fib(n): 
    global counter
    if n == 1:
        counter = counter + 1
        return 1 
    elif n == 2:
        counter = counter +1
        return 2 
    else:
        counter  = counter +1
        return fib(n-1) + fib(n-2)

print(fib(6))
print("Function was called", counter, "times.")