def align_center(text: str, width: int) -> str:
    space_count = width - len(text)
    space_left = space_count // 2
    space_right = space_count - space_left
    result = ' ' * space_left + text + ' ' * space_right
    return result


def align_right(text: str, width: int) -> str:
    space_count = width - len(text)
    result = ' ' * space_count + text
    return result


sentence = input("문장을 입력하시오 : ")
width = int(input("폭을 입력하시오 : "))
align_type = int(input("정렬 방식을 선택하시오(center:1, left:2, right:3) : "))

if align_type == 1:
    print(align_center(sentence, width))
elif align_type == 2:
    print(sentence)
elif align_type == 3:
    print(align_right(sentence, width))
else:
    print("지원되지 않는 정렬 방식입니다.")
