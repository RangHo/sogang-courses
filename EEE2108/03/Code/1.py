def lyrics_to_frequencies(lyrics):
    myDict = {}
    for word in lyrics:
        if word in myDict:
            myDict[word] += 1
        else:
            myDict[word] = 1
    return myDict
    
    
she_loves_you = ['she','she','A'
]

beatles = lyrics_to_frequencies(she_loves_you)


def most_common_words(freqs):
    values = freqs.values()
    best = max(freqs.values())
    words = []
    for k in freqs:
        if freqs[k] == best:
            words.append(k)
    return (words, best)
    
def words_often(freqs, minTimes):
    result = []
    done = False
    while not done:
        temp = most_common_words(freqs)
        if temp[1] >= minTimes:
            result.append(temp)
            for w in temp[0]:
                del(freqs[w])  
                if bool(freqs) == False: # freqs 안에 남아있는게 없을 경우, most_common_words를 
                                         #한번 더 돌릴 경우 에러가 난다. 그러나 freqs 안에 남아있는것이 
                                         # 없을 경우, 횟수가 1인 단어들까지 모두 eval이 끝났기 때문에 
                                         # 굳이 한번 더 돌릴 필요 없이 그냥 여기서 done 을 True로 설정해서 
                                         # 강제로 끝낸다.
                    done = True
        else:
            done = True
    return result

print(words_often(beatles,1))