student_dict = {}

with open('students.txt', 'r') as f:
    for line in f:
        students = line.split()
        student_dict[students[0]] = students[1:]

print(student_dict)
