# 기초인공지능프로그래밍 조교용 유틸리티

실습 및 과제 채점에 도움이 되는 유틸리티입니다.

## `grader.py` 자동 채점 유틸리티

학생의 코드를 주어진 정답 코드와 비교해서 채점하는 커맨드라인 유틸리티입니다.
정답 코드의 출력과 학생 코드의 출력을 비교하여 채점 결과를 출력하거나 파일로
내보낼 수 있습니다. 사용 방법은 아래를 참고하세요.

### TL;DR

표준 입력이 필요 없을 때:

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --filter '채점 대상 파일명' \
    --csv-out \
    --json-out \
    --diff-out
```

표준 입력이 필요할 때:

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --filter '채점 대상 파일명' \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --csv-out \
    --json-out \
    --diff-out
```

### 기본적인 사용법

이 유틸리티는 학생 코드가 모인 디렉토리를 필수 인자로 받습니다. 이 디렉퇴리 안에
있는 파일 중, `.py`로 끝나는 모든 파일을 대상으로 채점을 진행합니다. 채점을 할
파일은 이후 설명할 `--filter` 옵션으로 조정할 수 있습니다. 또, 커맨드라인 옵션을
통해 채점 전략을 설정할 수 있습니다. 현재 지원하는 4개의 채점 전략은 아래와
같습니다.

1. 정답 코드와 비교하기
1. 정답 출력 텍스트 파일과 비교하기
1. 정답 코드와 여러 개의 테스트케이스 파일로 비교하기
1. 정답 출력 텍스트 파일 여러 개와 같은 개수의 테스트케이스 파일로 비교하기

여기서 가장 범용적으로 쓸 수 있는 방법은 정답 코드와 비교하는 방법으로, 이
문서에서는 정답 코드와 비교하는 방법만 서술합니다.

#### 정답 코드와 비교하기

`--answer-code` 커맨드라인 옵션을 이용하여 정답 코드를 지정할 수 있습니다. 정답
코드를 지정하면 이 스크립트는 정답 코드의 출력 결과를 저장한 후, 각 학생 코드의
출력과 정답 코드의 출력을 비교하여 정답 여부를 판정합니다. 이는 채점할 코드가
사용자의 입력을 받을 필요가 없을 때 사용합니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py
```

위 스크립트를 실행하면 터미널 화면에 각 파일의 채점 결과가 표시됩니다.

#### 정답 코드와 테스트케이스 파일로 비교하기

위에서 작성한 코드에 `--testcase` 옵션을 추가하여 채점할 코드를 테스트할 수
있습니다. 각 테스트케이스는 일반적인 텍스트 파일이며, 줄바꿈 문자가 엔터 키를
누르는 것과 같은 역할을 합니다. 테스트케이스는 여러 개 추가할 수 있으며, 각
테스트케이스에 대해 정답 코드의 출력을 저장한 후, 모든 테스트케이스에 대하여
학생의 코드를 검증합니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ...
```

위 스크립트를 실행하면 위와 같이 각 파일의 채점 결과가 표시되지만, 학생이 제출한
코드 하나당 모든 테스트케이스를 수행한 결과가 나오므로 훨씬 출력 양이 많습니다.

### 학생 코드 필터링하기

하나의 디렉토리 안에 여러 문제 코드가 함께 들어 있는 경우도 많습니다. 이럴 때는
필터를 이용하여 채점할 파일을 걸러낼 수 있습니다. `--filter` 옵션을 이용하면
특정 패턴이 파일명에 포함되어 있는 파일만을 대상으로 채점을 진행할 수 있습니다.
예를 들어, 이름에 `P1_1`이 포함된 파일만 채점하려면 아래와 같이 작성할 수
있습니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter 'P1_1'
```

반대로 `--exclude` 옵션을 이용하면 특정 패턴이 파일명에 포함되어 있는 파일을
제외하고 채점합니다. 이 옵션은 `--filter` 옵션돠 함께 사용할 수 있습니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter 'P1_1'
    --exclude '20231234'
```

필터링 패턴은 내부적으로 정규표현식 검색을 거치게 되므로, 정규표현식을 사용해서
더 상세하게 필터링이 가능합니다. 위 예시에서 소문자 P도 허용하고 언더바(`_`)
대신 하이픈(`-`)도 허용하려면 아래와 같이 필터링 패턴을 변경하면 됩니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter '[Pp]1[_-]1'
```

### 결과 출력하기

터미널에서는 각 학생의 정답 여부를 눈으로 보기 힘들기 때문에, 이 유틸리티는 채점
결과를 여러 형식의 파일로 출력할 수 있는 기능을 가지고 있습니다. 출력 설정은
마찬가지로 커맨드라인 옵션을 이용해서 조정 가능합니다.

#### CSV 형식으로 출력하기

채점 결과를 엑셀에서 열어볼 수 있도록 CSV 파일로 출력하는 기능을 지원합니다.
엑셀과의 호환성을 위해 CSV 포맷은 플랫폼에 관계없이 BOM이 추가된 UTF-8
인코딩으로 저장됩니다. `--csv-out` 옵션을 통해 이 기능을 켤 수 있으며, 출력 CSV
파일 이름도 지정할 수 있습니다. 파일 이름을 지정하지 않으면 기본 파일명은
`output.csv`입니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter '[Pp]1[_-]1' \
    --csv-out result.csv
```

#### JSON 형식으로 출력하기

`jq`와 같은 검색 유틸리티를 활용할 수 있도록 JSON으로 내보낼 수 있습니다. 사용
방법은 위 CSV 출력 방식과 비슷합니다. CSV 출력과 함께 동시에 사용할 수도 있으니
참고하세요. 이 기능은 `--json-out` 옵션을 통해 켤 수 있습니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter '[Pp]1[_-]1' \
    --json-out result.json
```

#### Diff 결과 출력하기

정답 코드의 출력 결과와 학생이 제출한 코드의 diff 결과도 확인할 수 있습니다.
Diff 결과는 오답인 경우에만 생성되므로, 왜 틀렸는지 빠르게 확인하고 싶을 때 주로
사용합니다. `bat`처럼 신택스 하이라이팅을 지원하는 프로그램으로 열면 직관적으로
틀린 부분을 확인할 수 있습니다.

여기서 `a` 파일은 정답 출력, `b` 파일은 학생 출력입니다. 즉, 오답이 있는 줄에서
`-`로 표시된 부분이 올바른 출력, `+`로 표시된 부분이 학생이 제출한 답안입니다.

이 기능은 `--diff-out` 옵션을 통해 켤 수 있습니다. 다른 출력 옵션과 달리, 이
옵션은 diff 파일을 출력할 디렉토리 이름을 입력받습니다. 기본값은 `./diff`입니다.
이 디렉토리 안에 제출물 실행 결과가 학생별로 저장됩니다. 파일명은 학생 코드에서
추출한 학번으로 통일되어 있습니다.

```shell
python grader.py /path/to/student/codes \
    --answer-code /path/to/answer/code.py \
    --testcase /path/to/testcase1.txt /path/to/testcase2.txt ... \
    --filter '[Pp]1[_-]1' \
    --json-out result.json
    --diff-out diff1
```

### 기타 기능

이 아래는 자주 사용하지는 않지만 있으면 편리한 기능을 모았습니다.

#### 공백 문자 채점

학생의 계산 결과는 완벽하지만 공백 문자 하나 때문에 오답으로 판정되어 하나하나
직접 비교해야 하는 경우가 있습니다. 이를 보조하기 위해 정답 비교 시 공백을
어떻게 처리할지 정할 수 있습니다.

`--strip-whitespace` 옵션을 추가하면 정답 판정 시 정답 코드와 학생 코드 결과의
각 행 양 끝에 있는 공백을 무시하고 채점합니다. 즉, `␣␣output`과 `output␣␣`이
같다고 판정하게 됩니다.

`--ignore-whitespace` 옵션은 공백 문자를 전부 무시합니다. 여기서 공백 문자는
스페이스 문자(` `)만 해당되며, 탭 문자나 개행 문자는 해당되지 않습니다.

#### 스크립트 입마개 하기

`-v/--verbose`와 `-q/--quiet` 옵션을 조합해서 이 유틸리티가 터미널에 쓰는 텍스트
양을 조절할 수 있습니다. `-v` 옵션은 코드 실행과 관련한 더 많은 정보를 출력하고,
반대로 `-q` 옵션은 꼭 필요한 정보만 출력합니다. 두 옵션을 모두 적용하면 서로
상쇄하여 원래 상태로 돌아갑니다.
