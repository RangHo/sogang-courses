filename = input("Enter filename : ")

with open(filename, 'w') as f:
    for i in range(3):
        score = input("Enter score : ")
        print(score, file=f)
