# 기초인공지능프로그래밍 중간고사

중간고사는 2개의 세션에 걸쳐 8개의 문제를 풀었습니다.

## 세션 1: 출력 예측

첫 7개 문제는 주어진 Python 코드를 읽고 출력되는 값을 수기로 적는 문제입니다.
여기까지가 세션 1이고, 35분간 진행됩니다. 이번 시험에서는 `while` 반복문이
실수로 문제에 포함되어 문제 3번과 4번에 변동이 생겼습니다.

### 문제 1. 연산자 우선순위와 문자열 포맷팅

```python
a = 7; b = 1.7; c = 2; d = -5

x = a - 2 * b + b < c * 2 / 3
y = c < a or b <= c and d % 2 == 1

b = a % d**c / 3
c = d // c
a -= d

print(x, y)
print("{:3d},{:.2f},{:+f}".format(a, b, c))

# -- Output --
# False True
# 12,2.33,-3.000000
```

각 연산자의 우선순위와 `str#format()` 메서드를 사용한 포맷팅 방법을 알고 있어야
풀 수 있는 문제입니다. Python에서의 연산자 우선순위는 [공식 문서][1]를 참고해
주세요.

[1]: https://docs.python.org/3/reference/expressions.html#operator-precedence

### 문제 2. 리스트 조작

```python
A = [1, 3]; B = [2, 4, 6, 8]
B.extend(A * 2)
B.remove(8)
B.append(5)
B.insert(3, len(B))
print(B)
print(B[1], B[5], B.index(3))

# -- Output --
# [2, 4, 6, 8, 1, 3, 1, 3, 5]
# 4 3 5
```

Python의 `list` 자료형에 수행 가능한 연산이나 메서드를 묻는 문제입니다. B에 대한
수정만 있기 때문에, 각 메서드를 실행한 후의 B의 상태를 메모해 두면 실수 없이 풀
수 있습니다.

### 문제 3. ~~`while`~~ `for` 반복문 기본

```python
# -- Original code --
# a = 1; b = 0
# while a <= 3:
#     while b <= 4:
#         b += 1
#         print(a * b, end=' ')
#     a += 1
#     print()
# print(a + b)

a = 1; b = 0

for a in range(1, 4):
    for b in range(0, 5):
        print(a * b, end=' ')
    print()

print(a + b)

# -- Output --
# 0 1 2 3 4
# 0 2 4 6 8
# 0 3 6 9 12
# 7
```

이 문제는 시험 중 `while` 반복문을 사용하는 문제에서 `for` 반복문을 사용하는
문제로 대체되었습니다.

`for` 반복문과 `range()` 내장 함수의 기능을 알고 있어야 풀 수 있는 문제입니다.
여기서 `print(..., end=' ')` 함수는 한 줄을 출력한 뒤 줄바꿈 문자를 출력하지
않는다는 점 주의하세요.

### 문제 4. ~~`while` 반복문과 실행 제어~~

```python
# Not available.
```

이 문제는 시험범위에 포함되지 않은 `while` 반복문이 등장하여 시험 중
폐기되었습니다.

### 문제 5. 중첩된 `if-elif-else`

```python
x = 15; y = 5
if x > y:
    if x % 3 == 0 and y % 5 == 0: print('AA')
    if x % 2: print('BB')
    elif y < 10: print('CC')
    if x < 10: print('DD')
    else: print('EE')
    print('FF')
else:
    print('GG')
    if x != 10: print('HH')
    if y == 5: print('II')

# -- Output --
# AA
# BB
# EE
# FF
```

`if`와 `elif`, `else`의 관계를 알고 있으면 쉽게 풀 수 있습니다. 먼저 제일 바깥의
`else` 문은 항상 실행되지 않으니 무시하고, 각 `if` 문을 차례대로 비교해보면
간단히 출력을 예측할 수 있습니다.

### 문제 6. `for` 반복문과 2차원 배열

```python
M = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
x = 0

for i in range(len(M)):
    for j in range(i):
        x += M[j][i]
    print(x)

# -- Output --
# 0
# 2
# 11
```

2차원 배열의 인덱싱 순서를 알고 있으면 풀 수 있는 문제입니다. 내부에 있는 `for`
루프의 실행 횟수가 `i`에 달려 있기 때문에 실행할 때마다 실행 횟수가 달라진다는
점을 주의하세요.

### 문제 7. 문자열 슬라이싱

```python
# Not available.
```

문자열 슬라이싱에 관하여 묻는 문제입니다. 슬라이싱을 할 때, 대괄호 안의 숫자가
각각 어떤 역할을 하는지 잘 숙지하고 있으면 쉽게 풀 수 있는 문제입니다.

## 세션 2: 코딩 테스트

마지막 문제는 코딩 테스트입니다. 문자열 하나를 표준 입력으로 받아서 "압축을
해제"한 후, 결과 문자열을 출력합니다. 예를 들어, 입력으로 `s8^4t2`가 주어진 경우
출력 결과는 `ssssssss^^^^tt`가 되어야 합니다.

```python
# See M_8.py file.
```
