# 기초빅데이터프로그래밍 중간고사

중간고사는 2개의 세션에 걸쳐 14 문제를 풀었습니다.

## 세션 1: 필기 시험

필기 시험은 첫 30분간 진행됩니다.
주어진 코드를 보고 출력 결과를 예상하거나, 빈 칸을 채워 넣는 문제가 많습니다.

### 문제 1. 실행 결과 예측 (1)

아래 script 실행 결과를 적으시오.

```python
import copy
x = [1, 2, 3]
L1 = [1, 2, x]
L2 = L1[:]
print(id(L1) == id(L2))
L1[2][1] = 3
print(L1)
print(L2)
```

#### 정답

```
False
[1, 2, [1, 3, 3]]
[1, 2, [1, 3, 3]]
```

#### 해설

### 문제 2. 실행 결과 예측 (2)

아래 script 실행 결과를 적으시오.

```python
class MyClass:
    def __init__(self, value):
        self.Value = value
        print("Class is created! Value =", value)

    def __del__(self):
        print("Class is deleted!")

def choi():
    d = MyClass(10)

choi()
d = MyClass(8)
d_cp = d
del d
```

#### 정답

```
Class is created! Value = 10
Class is deleted!
Class is created! Value = 8
```

#### 해설

### 문제 3. 상속 순서

`Liger.__mro__`의 결과가 아래와 같을 때, 다음 프로그램의 실행 결과를 적으시오.

```python
(__main__.Liger, __main__.Tiger, __main__.Lion, __main__.Animal, object)
```

```python
class Animal:
    def __init__(self):
        print("Animal 생성")


class Tiger(Animal):
    def __init__(self):
        super().__init__()
        print("Tiger 생성")

    def jump(self):
        print("멀리 점프하기")

    def cry(self):
        print("어흥")


class Lion(Animal):
    def __init__(self):
        super().__init__()
        print("Lion 생성")

    def bite(self):
        print("한입에 꿀꺽하기")

    def cry(self):
        print("으르렁")


class Liger(Tiger, Lion):
    def __init__(self):
        super().__init__()
        print("Liger 생성")

    def play(self):
        print("사육사와 놀기")


m = Liger()
m.cry()
```

#### 정답

```
Animal 생성
Lion 생성
Tiger 생성
Liger 생성
어흥
```

#### 해설

### 문제 4. 리스트 필터링

다음 리스트 `a`에서 리스트 `b`를 구하는 아래 구문을 완성하시오.

```python
a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
b = [5, 10, 15]

list(______(____________________, a))
```

#### 정답

```python
list(filter(lambda x: x % 5 == 0, a))
```

#### 해설

### 문제 5. 전역 vs. 클래스 vs. 인스턴스 변수

아래 script를 실행시킨 결과를 적으시오.

```python
str = "NOT Class Member"


class GString:
    str = ":"

    def Set(self, msg):
        self.str = msg

    def Print(self):
        print(self.str)


g = GString()
g.Print()
```

#### 정답

```
:
```

#### 해설

### 문제 6. 제너레이터 함수 사용법

아래와 같은 출력을 보이도록 script의 빈칸을 채우시오.

```python
def lineUp(data):
    for index in range(_________):
        yield data[index]


for j in ___________________________:
    print(j)


# ---- Output ----
# (0, 'S')
# (1, 'o')
# (2, 'g')
# (3, 'a')
# (4, 'n')
# (5, 'g')
```

#### 정답

```python
def lineUp(data):
    for index in range(len(data)):
        yield data[index]


for j in enumerate(lineUp("Sogang")):
    print(j)
```

#### 해설

### 문제 7. 필요한 모듈 `import`

아래와 같은 실행 결과를 얻기 위해, 다음 Python script의 `(    )` 안에 들어갈 구문을 적으시오.

```python
(                )
pt1 = 22
pt2 = 42
pt3 = 42
avg = (pt1 + pt2 + pt3) / 3
print("average :", round(avg))
print("average :", m.trunc(avg))


# ---- Output ----
# average : 39
# average : 38
```

#### 정답

```python
import math as m
```

#### 해설

### 문제 8. `for` 루프와 제너레이터 함수

아래 script를 실행시켰을 때 화면에 나오는 결과를 적으시오.

```python
def cube_numbers(nums):
    for i in nums:
        yield i ** 3


my_nums = cube_numbers([-3, -2, -1, 0, 1, 2, 3])

for i in my_nums:
    print(next(my_nums), end=" || ")
```

#### 정답

```
StopIteration
-8 || 0 || 8 || 
```

#### 해설

### 문제 9. 내장 메서드 사용법

아래 코드에서 표시한 부분의 `if` 구문을 method를 사용해서 하나의 문장으로 바꾸시오.

```python
def char_freq(s):
    """
    input: a string s
    output: a dictionary consists of char: count
    """
    D = {}
    for c in s:
        if c.isspace():
            continue
        c = c.lower()
        # ---- begin  ----
        if c in D:
            D[c] += 1
        else:
            D[c] = 1
        # ---- end ----
        return D
```

#### 정답

```python
D[c] = D.get(c, 0) + 1
```

#### 해설

### 문제 10. 클래스 "메서드"?

아래 script를 실행시킨 결과를 적으시오.

```python
class Magr:
    insCnt = 0

    def __init__(self):
        Magr.insCnt += 1

    def printInsCount():
        print("Count: ", Magr.insCnt, end=" || ")


x, y, z = Magr(), Magr(), Magr()
Magr.printInsCount()
z.printInsCount()
```

#### 정답

```
Count: 3 || 
TypeError
```

#### 해설

### 문제 11. 상속받은 속성과 메서드

아래 script를 실행시킨 결과를 적으시오.

```python
class Times(object):
    factor = 1

    def mul(self, x):
        return self.factor * x


class TwoTimes(Times):
    factor = 2


x = TwoTimes()
print(x.mul(4))
```

#### 정답

```
8
```

#### 해설

### 문제 12. 람다 함수 고급

`a = [1, 2, 3, 4, 5]` 원소의 합을 구하는 statement를 Lambda 함수를 이용하여 작성하시오.

#### 정답

```python
from functools import reduce

a = [1, 2, 3, 4, 5]
reduce(lambda x, y: x + y, a)
```

#### 해설

### 문제 13. 제너레이터 함수 실습

아래 실행 예와 같이 입력을 거꾸로 출력하는 코드를 `yield`를 사용하여 작성하시오.

```
input:SogangUniv
S
oS
goS
agoS
nagoS
gnagoS
UgnagoS
nUgnagoS
inUgnagoS
vinUgnagoS
```

#### 정답

```python
def reverse_generator(target):
    for i in range(len(target)):
        yield data[i::-1]


target = input("input:")
for content in reverse_generator(target):
    print(content)
```

#### 해설

## 세션 2. 실기 시험

실기 시험은 필기 시험이 끝나자마자 1시간동안 진행됩니다.
실기 시험 중에는 강의자료를 다운로드 받아서 보면서 코딩할 수 있습니다.

실제 문제와 풀이는 [해당 파일](CodingTest.ipynb)에서 확인하세요.