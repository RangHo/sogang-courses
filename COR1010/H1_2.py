import math

a = 5
c = 8
B = 60

area = 0.5 * a * c * math.sin(math.radians(B))
print("a :", a, "c :", c, "B(각도) :", B)
print("삼각형의 넓이 :", round(area, 2))
