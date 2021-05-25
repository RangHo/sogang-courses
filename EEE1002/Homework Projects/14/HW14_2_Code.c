#include <stdio.h>

void sort(int array[][4], int, int);

int main()
{

    /*바로 아래의 어레이에 데이터 넣으시면 됩니다.
    Input data in the array below.*/

    int Please_Stop_Changing_The_Conditions_For_This_Question_TT_TT[]
        = { 45, 36, 24, 12, 18, 60, 80, 11, 67, 79, 69, 11, 65, 14, 22 };

    //=================== 입력 처리 ===========================
    int maxroll = 0;
    int totaldata = 0;

    totaldata = sizeof Please_Stop_Changing_The_Conditions_For_This_Question_TT_TT
        / sizeof Please_Stop_Changing_The_Conditions_For_This_Question_TT_TT[0];
    maxroll = totaldata / 3;

    int data[maxroll][4];

    for (int i = 0; i < maxroll; i++) {
        data[i][0] = i + 1;
        for (int j = 1; j < 4; j++) {
            data[i][j] = Please_Stop_Changing_The_Conditions_For_This_Question_TT_TT[3 * i + j - 1];
        }
    }
    printf("\n");

    //=========== a) 각 학생의 총점은 net 에 저장됨. ===================

    int net[maxroll][4];

    for (int i = 0; i < maxroll; i++) {
        net[i][0] = data[i][0];
        net[i][1] = data[i][1] + data[i][2] + data[i][3];
        net[i][2] = 0;
        net[i][3] = 0;

        printf("Student %d Total: %d \n", net[i][0], net[i][1]);
    }
    printf("\n");

    //=========== b) 각 과목의 점수를 바탕으로 한 분류 결과는 A,B,C에 저장됨. ===========

    int A[maxroll][4];
    int B[maxroll][4];
    int C[maxroll][4];

    for (int i = 0; i < maxroll; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = data[i][j];
        }
    }
    for (int i = 0; i < maxroll; i++) {
        for (int j = 0; j < 4; j++) {
            B[i][j] = data[i][j];
        }
    }
    for (int i = 0; i < maxroll; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = data[i][j];
        }
    }

    printf("Subject A:\n");
    sort(A, 1, maxroll);
    printf("Subject B:\n");
    sort(B, 2, maxroll);
    printf("Subject C:\n");
    sort(C, 3, maxroll);

    //=========== c) 종합적 점수를 바탕으로 한 분류 결과는 net에 저장됨. ===========

    printf("Total:\n");
    sort(net, 1, maxroll);

    return 0;
}

//============================================================================

void sort(int array[][4], int num, int maxroll)
{

    int temp = 0;
    int index = 0;

    for (int i = 0; i < maxroll; i++) {
        index = i;
        for (int j = i; j < maxroll; j++) {
            if (array[index][num] < array[j][num]) {
                index = j;
            }
        }
        temp = array[index][0];
        array[index][0] = array[i][0];
        array[i][0] = temp;

        temp = array[index][num];
        array[index][num] = array[i][num];
        array[i][num] = temp;
    }

    //----------------------------- 출력 -----------------------------------
    //전체 명단 출력
    /*
       for(int i = 0; i < maxroll; i++){
           printf("Rank %d: No.%d at %d\n", i+1 ,array[i][0], array[i][num]);
       }
   */
    printf("Top rank: No.%d", array[0][0]);

    //-------------------- 여기서부터는 동점자 처리 ------------------------------

    int check = 0;
    int SameScore = 0;
    while (check < maxroll) {
        if (array[check][num] == array[check + 1][num]) {
            printf(", No.%d ", array[check + 1][0]);
            check++;
            SameScore = 1;
        } else {
            check = check + maxroll + 100;
        }
    }

    printf(" with a score of %d", array[0][num]);

    if (SameScore) {
        printf(".\nStudents with the same score exist");
    }
    printf(".\n\n");
}