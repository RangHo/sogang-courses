def bisection_solve(x, eval_ans, epsilon, low, high):
    ans = (high + low)/2
    while abs(eval_ans(ans) - x) >= epsilon:
        if eval_ans(ans) < x:
            low = ans
        else:
            high = ans
        ans = (high + low)/2
    return ans

def log(x, base, epsilon):
    def find_log_bounds(x,base):
        upper_bound = 0
        while base**upper_bound < x:
            upper_bound += 1
        return upper_bound -1, upper_bound
    low, high = find_log_bounds(x, base)
    return bisection_solve(x, lambda ans: base**ans, epsilon, low, high)

print (log(8,2,0.001))
