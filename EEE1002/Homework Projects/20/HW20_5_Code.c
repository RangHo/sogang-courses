#include<stdio.h>

#define ROW 5
#define COL 5

/*
    2차원 배열은 길이가 주어지지 않으면 처리를 하는것이 불가능하기 때문에 길이를 직접 입력하셔야 합니다. 
    예를 들어, {1,2,3,4} 면 1x4 배열인지, 2x2 배열인지, 4x1 배열인지 판단할 기준이 없습니다.

    위의 #define 에 행, 열의 크기를 기입해 주십시오.
*/

int add(int arr1[ROW][COL], int arr2[ROW][COL], int sum[ROW][COL]);

int main()
{
    int arr1[ROW][COL] = {{5,4,3,2,1}, {10,9,8,7,6}, {11,12,13,14,15}, {16,17,18,19,20}, {21,22,23,24,25}};
    int arr2[ROW][COL] = {{1,2,3,4,5}, {6,7,8,9,10}, {12,14,13,12,11}, {20,19,18,17,16}, {25,24,23,22,21}};

    int sum[ROW][COL] = {0};
    
    add(arr1, arr2, sum);

    for(int i = 0; i < ROW; i++){
       for(int j = 0; j < COL; j++){
           printf("%d ", *(*(sum + i) + j));
       } 
       printf("\n");
    }
    

    return 0;
}


int add(int arr1[ROW][COL], int arr2[ROW][COL], int sum[ROW][COL]){
    for(int i = 0; i < ROW; i++){
       for(int j = 0; j < COL; j++){
           *(*(sum + i) + j) = *(*(arr1 + i) + j) + *(*(arr2 + i) + j);
       } 
    }
}
