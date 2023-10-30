scores = {}

with open("score.txt", "r") as f:
    for line in f:
        course, score = line.split()
        course = int(course)
        score = int(score)

        if course not in scores or scores[course] < score:
            scores[course] = score

for course, score in scores.items():
    print("{} 번 : {} 점".format(course, score))
