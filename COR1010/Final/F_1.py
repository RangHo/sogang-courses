def get_LCM(x: int, y: int) -> int:
    """Calculate the least common multiple of two integers.

    :param int x: The first integer.
    :param int y: The second integer.
    :return: The least common multiple of x and y.
    :rtype: int
    """

    # Find the bigger and the smaller number
    t_max = max(x, y)

    t_current = t_max
    while True:
        # If the target is divisible by both numbers, return it
        if t_current % x == 0 and t_current % y == 0:
            return t_current

        # Otherwise, find the next target
        t_current += t_max


n, b, x, y = map(int, input("n,b,x,y : ").split(','))

# Make sure that input is sane
if n < 1 or x < 1 or y < 1:
    print("Invalid input")
    exit()

# Find the least common multiple of x and y
lcm = get_LCM(x, y)

# If b is less than zero, start from the first one
if b < 0:
    start = 1
else:
    start = b // lcm + 1

# Print n common multiples
while n > 0:
    print(lcm * start, end=' ')
    start += 1
    n -= 1
