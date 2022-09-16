def find_last(s, sub): # 사실 rfind()를 쓰면 훤씬 간단하다.
    prevpos = s.find(sub) # 우선 한번 substring를 찾아본다. 존재하면 위치가 prevpos에 저장됨.
    if prevpos == -1: # substring이 발견되지 않았을 때, None을 return하고 끝냄.
        return None
    else:
        pos = prevpos # pos에 prevpos값을 저장함.

    while prevpos != -1: # 더이상 substring가 없을때까지 돌림.
        prevpos = s.find(sub,prevpos + 1) # 찾은 substring 다음 자리부터 검색을 또 시작함. 
        if prevpos == -1: # 검색결과가 없을경우 이전에 저장한 pos를 return.
            return pos
        else: # 검색결과가 있을 경우 그 값을 pos에 저장.
            pos = prevpos


s = "ABCDEFGFEDCBA"
print(find_last(s,"G"))
print(find_last(s,"A"))
print(find_last(s,"AB"))
print(find_last(s,"12345"))
