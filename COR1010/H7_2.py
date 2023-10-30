oct_attend = {
    'Peter' :[3, 5, 10, 12, 17, 19, 24, 26, 31],
    'Lidia' :[5, 12, 19, 24, 26, 31],
    'Ken' :[5, 10, 12, 19, 24, 26],
    'Andy' :[5, 10, 12, 19, 24, 26, 31],
    'Erin' :[10, 12, 19, 24, 26],
    'Jay' :[5, 12, 19, 24, 26],
    'Ceci' :[3, 5, 12, 17, 26, 31],
    'Michael' :[3, 5, 12, 19, 24, 26, 31]
}

day_attend = {}

for name, days in oct_attend.items():
    for day in days:
        if day_attend.get(day, False):
            day_attend[day].append(name)
        else:
            day_attend[day] = [name]

for day, names in day_attend.items():
    print('{:2} : {}'.format(day, names))
