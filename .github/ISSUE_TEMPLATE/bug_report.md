---
name: 버그 리포트
about: 코드에 문제가 있거나 잘 작동하지 않을 때
title: "[과목코드] 이슈 제목"
labels: ":bug: 버그"
assignees: ''

---

## 문제가 있는 코드 정보
> 아래에 문제가 있는 코드가 속한 과목과 파일명을 알려주세요.

**과목명**: ex) 기초공학설계
**코드 파일명**: ex) helloworld.c

## 문제 설명
> 정확히 어떤 문제가 있는지 설명해 주세요.

ex) helloworld.c를 컴파일하면 `Hello, world!`를 출력해야 하는데 `hello world`를 출력합니다.
ex) sort.c를 사용하면 200ms 안에 작업이 끝나야 하는데 너무 오래 걸립니다.

### 문제를 재현하는 방법
> 발생한 문제를 재현하려면 어떻게 해야 하는지 알려주세요. 다른 사람이 재현할 수 없는 문제라면 직접 문제 원인을 찾은 뒤 수정해서 공유해 주세요.

ex)
1. [이 파일](https://pastebin.com/yKHJAPyq)을 `sortme.txt`라는 이름으로 다운로드합니다.
2. 코드를 컴파일한 뒤 `./a.out sortme.txt`를 실행합니다.
3. 2초 이상 걸린 뒤 코드 실행이 완료됩니다.

### 일어나야 하는 일
> 이 코드를 실행하면 일어나야 하는 일을 적어 주세요.

ex) 코드가 0.2초 안에 실행이 완료되어야 합니다.

### 실제 일어나는 일
> 이 코드를 실행했더니 실제로 일어나는 일을 적어 주세요.

ex) 코드가 2초 이상 걸려 시간 초과로 점수가 깎입니다.
