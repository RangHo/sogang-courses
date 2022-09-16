###############################
## EXERCISE: Test yourself by predicting what the output is and 
##           what gets mutated then check with the Python Tutor
###############################
# 출력이 무엇인지 예상해보고 Python Tutor 에서 확인해보라는 주석 내용.

cool = ['blue', 'green'] # cool 이라는 list를 생성하고 그 안에 'blue', 'green' 이라는 항목을 넣음. 

warm = ['red', 'yellow', 'orange'] # warm 이라는 list를 생성하고 그 안에 'red','yellow','orange' 항목을 넣음.

print(cool) # cool 리스트를 출력.

print(warm) # warm 리스트를 출력.

 

colors1 = [cool] #colors1 이라는 리스트를 생성. colors1 리스트의 첫번째이자 하나뿐인 항목은 cool, 즉 ['blue', 'green'] 이 된다.

print(colors1) # colors1 리스트를 출력.

colors1.append(warm) #colors1 항목에  warm을 append함. colors1 의 두번째 항목은 warm, 즉 ['red', 'wellow', 'orange'] 가 된다.

print('colors1 = ', colors1) #colors1을 출력.

 

colors2 = [['blue', 'green'], # colors2 리스트를 생성, 이 리스트의 첫번째 항목은 ['blue', 'green']이고, 

          ['red', 'yellow', 'orange']] #리스트의 두번째 항목은 ['red', 'yellow', 'orange'] 가 된다.

print('colors2 =', colors2) # colors2를 출력. 이때 결과는 line 22 (colors1을 출력하느 코드) 와 동일하다.

 

warm.remove('red') # warm 리스트의  첫번째 항목인 'red'를 warm 에서 제거.

print('colors1 = ', colors1) # colors1 리스트를 출력. colors1 의 두번째 항목은 warm 인데, 여기에서 'red' 항목이 빠졌기 때문에 이전과 결과가 달라진다. 

print('colors2 =', colors2) # colors2 리스트를 출력. warm 리스트는 colors2 와 관계가 없기 때문에 결과는 이전과 동일하다.

 

for e in colors1: # e는 colors1 의 각 항목이 됨. 처음에는 cool, 즉 ['blue', 'green] 이 되고, 그 다음은 warm, 즉 ['yellow','orange'] 가 된다.

    print('e =', e) # 현재 e를 출력

 

for e in colors1: # e는 colors1의 항목이 됨.

    if type(e) == list: # e가 list일 경우:

        for e1 in e: # e1 은 e 리스트의 항목이 됨.

            print(e1) #e1을 출력.

    else:

        print(e) # e 가 list가 아닐 경우, e를 출력.

 

flat = cool + warm # flat 리스트를 생성, 그 리스트는 cool 과 warm을 합한게 됨. 즉, flat = ['blue', 'green', 'yellow', 'orange']가 됨.

print('flat =', flat) # flat를 출력.

 

print(flat.sort()) # flat 를 오름차순으로 정렬하고 return value를 출력. 이 경우, sort는 flat에 영향을 주지만 return 하는 값이 없기 때문에 출력은 None 가 된다.

print('flat =', flat) # 정렬된 flat를 출력.

 

new_flat = sorted(flat, reverse = True) # new_flat 리스트를 생성. 이는 flat를 역순으로 정렬한것이 됨.

print('flat =', flat) # flat를 출력.

print('new_flat =', new_flat) # new_flat를 출력.

 

cool[1] = 'black' #cool 의 2번째 항목, 즉 'green' 을 'black' 으로 대체함.

print(cool) # cool을 출력. 항목이 바뀐것을 볼 수 있다.

print(colors1) # colors1 을 출력. 역시 항목이 바뀌었다.