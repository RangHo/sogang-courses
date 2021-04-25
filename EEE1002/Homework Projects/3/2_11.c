/*20201510 이찬혁
  2.11: A = sqrt(S(S-a)(S-b)(S-c)) 를 이용해서 삼각형의 넓이를 계산.
*/

#include <stdio.h>
#include <math.h>

int main(){
    double A = 0.0; // sqrt 데이터타입이 double 이기 때문에 타이프캐스팅을 피하기 위해 변수도 double로 정의.
    double a = 5.0, b = 12.0, c = 13.0; // 변수 정의.
    double S = (a + b + c)/2;

    A = sqrt(S*(S - a)*(S - b)*(S - c));
    printf("Area A: %.3f", A);

    return 0;
}