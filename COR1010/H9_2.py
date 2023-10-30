input_file = open("word_game.txt", "r")

for line in input_file:
    word = line.strip()

    guess_history = ["*"] * len(word)

    found_attempts = failed_attempts = 0
    while found_attampts < len(word):
        guess_char = input("추측하는 문자 하나를 입력 {}----> ".format(guess_history))

        if guess_char in guess_history:
            print("{}은(는) 이미 찾은 문자입니다.".format(guess_char))
        elif word.find(guess_char) < 0:
            print("{}은(는) 존재하지 않는 문자입니다.".format(guess_char))
            failed_attempts += 1
        else:
            i = word.find(guess_char)
            while i >= 0:
                guess_history[i] = guess_char
                found_attempts += 1
                i = word.find(guess_char, i + 1)

    print("찾는 단어는 {}입니다.".format(word))
    print("{}번 찾기 실패하였습니다.".format(failed_attempts))
    should_continue = input("단어 맞추기를 계속하시겠습니까? ")

    if should_continue.lower() == "n":
        break

    print()

input_file.close()
