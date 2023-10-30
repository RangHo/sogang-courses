score1 = int(input("필기시험 점수는? "))
score2 = int(input("실기시험 점수는? "))

if score1 >= 60 and score2 >= 80:
    print("축하합니다. 2종 면허를 취득하셨습니다.")
if score1 < 60 or score2 < 80:
    print("수고하셨습니다. 다음에 다시 시도해주세요.")
