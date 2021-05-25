/*20201510 이찬혁
  2.13: D^2 = (x_2 - x_1)^2 + (y_2 - y_1)^2 을 이용해서 두 점 사이의 거리 계산
*/

#include <math.h>
#include <stdio.h>

int main()
{
    double D = 0.0;
    double x1 = 5.0, y1 = 12.0, x2 = 0.0,
           y2 = 0.0; // 2.11 과 마찬가지로 sqrt 가 double 이기 때문에 변수 또한 double 로 정의.

    D = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    printf("Distance D: %.3f", D);

    return 0;
}