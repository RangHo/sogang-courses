usage = int(input("전기사용량(kWh)은? : "))

base1 = 910
base2 = 1600
base3 = 7300
rate1 = 93.3
rate2 = 187.9
rate3 = 280.6

if usage <= 200:
    total = int(base1 + usage * rate1)
elif usage <= 400:
    total = int(base2 + (usage - 200) * rate2 + 200 * rate1)
else:
    total = int(base3 + (usage - 400) * rate3 + 200 * rate2 + 200 * rate1)

# 부가가치세
total += (total * 0.1)

#전력산업기반기금
total += total * 0.037

print("게산된 금액은 {:,}원 입니다.".format(int(total)))

