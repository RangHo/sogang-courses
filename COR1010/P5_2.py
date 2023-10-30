korean, english, math = input("과목별 점수를 입력하시오(예:80.3 95.7 73.2):").split()
korean = float(korean)
english = float(english)
math = float(math)

total = korean + english + math
average = total / 3

print("과목    점수")
print("------------")
print("국어: {:6.2f}".format(korean))
print("영어: {:6.2f}".format(english))
print("수학: {:6.2f}".format(math))
print("총점: {:6.2f}".format(total))
print("평균: {:8.4f}".format(average))
