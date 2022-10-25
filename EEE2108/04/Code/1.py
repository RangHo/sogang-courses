def find_root(x, power, epsilon):
    #find interval containing answer
    if x < 0 and power%2 == 0:
        return None #Negative number has no even-powered roots
    low = min(-1, x)
    high = max(1, x)
    #use bisection search
    ans = (high + low)/2
    while abs(ans**power - x) >= epsilon:
        if ans**power < x:
            low = ans
        else:
            high = ans
        ans = (high + low)/2
    return ans

print("Square root of 25: ",find_root(25,2,0.001))
print("Cube root of -8: ",find_root(-8,3,0.001))
print("Fourth root of 16: ",find_root(16,4,0.001))