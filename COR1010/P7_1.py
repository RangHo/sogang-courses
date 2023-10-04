date = input("날짜를 입력하시오(예:10/1) : ").split('/')
day = int(date[1])

week = ['월', '화', '수', '목', '금', '토', '일']

# 10/1 is a Thursday, so offset is 3
offset = 3
week_index = (day - 1 + offset) % 7

print("{}월 {}일은 {}요일이다".format(date[0], date[1], week[week_index]))
