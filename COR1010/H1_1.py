total = 3890
coin500 = total // 500; total = total % 500
coin100 = total // 100; total = total % 100
coin50 = total // 50; total = total % 50
coin10 = total // 10

print("500원짜리 :", coin500)
print("100원짜리 :", coin100)
print("50원짜리 :", coin50)
print("10원짜리 :", coin10)
