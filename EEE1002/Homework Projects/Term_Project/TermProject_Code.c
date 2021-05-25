/*
    #
    - 코드의 출력은 각각 result1.txt, result2.txt, result3.txt, result4.txt 로 저장됩니다.
    - 코드는 -------- 또는 ========로 나누었습니다.
    - ======== 는 함수 사이의 경계를 나타냅니다.
    - -------- 는 함수 내 파트의 경계를 나타냅니다.
    - 각 경계선에 각 부분의 역할을 간략하게 적어놓았습니다.
    - 알고리듬, 각 함수의 역할 등 자세한 내용은 보고서에 작성하였습니다.
    - [UK Government Data Standards
   Catalogue](https://webarchive.nationalarchives.gov.uk/20100407173424/http://www.cabinetoffice.gov.uk/govtalk/schemasstandards/e-gif/datastandards.aspx)
     에 의하면, 성, 이름의 크기를 각각 35자로 설정하는것을 추천하기 때문에 이 코드에서도 그렇게
   하였습니다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 35

struct List {
    int hi;
    char First_name[SIZE];
    char Last_name[SIZE];
    int score;
    char grade[2];
    struct List* next;
};
typedef struct List node;

int hicounter = 0;
int maxhi = 0;
int State = 1;
int printstate = 1;

node* head;
node* Temporary;
//-------------Function Declarations----------------
void create(node* p, FILE* fp);
void insert(node* p);
void print(node* p);
void printFile(node* p, FILE* fp);
void pullhi(node* p);
void removetail(node* p);
void sort(node* p, int a);
void swap(node* p, int a, int b);
node* delete (node* p);
node* findname(node* p, char a[SIZE], char b[SIZE]);
node* findval(node* p, int a);
//==================================================

int main(int argc, char* argv[])
{
    FILE* fp;
    char c;
    char filename[100];
    head = (node*)malloc(sizeof(node));

    //--------------Problem 1--------------

    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Error: Could Not Open File.");
        return 1;
    }

    printf("--------------Problem 1--------------\n\n");

    create(head, fp);
    removetail(head);
    print(head);
    maxhi = hicounter;
    // printf("\nTotal No. of Students: %d\n\n", maxhi);
    hicounter = 0;
    fclose(fp);

    // system("PAUSE");
    printf("Press Any Key to Continue to Problem 2:\n>> ");
    getchar();

    fp = fopen("result1.txt", "w");
    printFile(head, fp);
    fclose(fp);

    printf("--------------Problem 2--------------\n\n");

    while ((c = getchar()) != '\n' && c != EOF) { } // Flush input buffer, Just in case.

    //--------------Problem 2--------------

    sort(head, maxhi);
    print(head);
    // printf("Total No. of Students: %d\n\n", maxhi);

    printf("Press Any Key to Continue to Problem 3:\n>> ");
    getchar();

    fp = fopen("result2.txt", "w");
    printFile(head, fp);
    fclose(fp);

    printf("--------------Problem 3--------------\n\n");

    while ((c = getchar()) != '\n' && c != EOF) { }

    //--------------Problem 3--------------

    while (State) {
        head = delete (head);
        if (printstate == 1) {
            print(head);
        }
    }
    // printf("Total No. of Students: %d\n\n", maxhi);

    fp = fopen("result3.txt", "w");
    printFile(head, fp);
    fclose(fp);

    printf("--------------Problem 4--------------\n\n");

    while ((c = getchar()) != '\n' && c != EOF) { }

    //--------------Problem 4--------------

    insert(head);
    sort(head, maxhi);
    print(head);
    // printf("Total No. of Students: %d\n\n", maxhi);

    fp = fopen("result4.txt", "w");
    printFile(head, fp);
    fclose(fp);

    return 0;
}

//==============] Create List and Assign values [==============

void create(node* list, FILE* fp)
{

    char temp1[SIZE]; // For some reason, directly writing to the list caused an error that I could
                      // not debug. This is the reason for the middleman variables.
    char temp2[SIZE];
    char temp3[2];
    int tempint;
    if (fscanf(fp, "%s %s %d[^\n]", temp1, temp2, &tempint) == EOF) {
        tempint = -999;
    }
    //--------------Grade Decision--------------

    if (90 <= tempint) {
        strcpy(list->grade, "A+");
    } else if (80 <= tempint && tempint <= 89) {
        strcpy(list->grade, "A0");
    } else if (70 <= tempint && tempint <= 79) {
        strcpy(list->grade, "B+");
    } else if (60 <= tempint && tempint <= 69) {
        strcpy(list->grade, "B0");
    } else if (50 <= tempint && tempint <= 59) {
        strcpy(list->grade, "C+");
    } else if (40 <= tempint && tempint <= 49) {
        strcpy(list->grade, "C0");
    } else if (30 <= tempint && tempint <= 39) {
        strcpy(list->grade, "D+");
    } else if (20 <= tempint && tempint <= 29) {
        strcpy(list->grade, "D0");
    } else if (0 <= tempint && tempint <= 19) {
        strcpy(list->grade, "F");
    } else {
        strcpy(list->grade, "0");
    }
    //--------------Assign & Create Next List-------------

    strcpy(list->First_name, temp1);
    strcpy(list->Last_name, temp2);
    list->score = tempint;
    list->hi = ++hicounter;

    if (list->score == -999) {
        list->next = NULL;
        hicounter--;
    } else {
        list->next = (node*)malloc(sizeof(node));
        create(list->next, fp);
    }

    return;
}

//==============] Remove the Last Node of a List [==============

void removetail(node* list)
{
    if (list->next->next == NULL) {
        list->next = NULL;
    } else {
        removetail(list->next);
    }
}

//==============] Print the List [==============

void print(node* list)
{

    if (list == NULL) {
        printf("\nError: Could Not Print. List is Empty.\n");
        return;
    }

    if (list->next != NULL) {
        printf("%s %s %d %s\n\n", list->First_name, list->Last_name, list->score, list->grade);
        print(list->next);
    } else {
        printf("%s %s %d %s\n\n", list->First_name, list->Last_name, list->score, list->grade);
    }
    return;
}

//==============] Print the List to File [==============

void printFile(node* list, FILE* fileptr)
{

    if (list == NULL) {
        printf("\nError: Could Not Print. List is Empty.\n");
        return;
    }

    if (list->next != NULL) {
        fprintf(fileptr, "%s %s %d %s\n\n", list->First_name, list->Last_name, list->score,
            list->grade);
        printFile(list->next, fileptr);
    } else {
        fprintf(fileptr, "%s %s %d %s\n\n", list->First_name, list->Last_name, list->score,
            list->grade);
        printf("\nPrinted to File.\n\n");
    }
    return;
}

//==============] Swap Two Nodes [==============

void swap(node* list, int hi1, int hi2)
{

    node* Prev1 = NULL; // Local temporary values.
    node* Prev2 = NULL;
    node* Current1 = head;
    node* Current2 = head;
    node* temp = NULL;
    int tempint;

    //--------------Search for hi1 and hi2 in the list--------------

    while (Current1 != NULL && Current1->hi != hi1) {
        Prev1 = Current1;
        Current1 = Current1->next;
    }

    while (Current2 != NULL && Current2->hi != hi2) {
        Prev2 = Current2;
        Current2 = Current2->next;
    }

    //--------------Swap--------------

    if (Current1 != NULL
        && Current2 != NULL) { // Error handling. Current1/2 is NULL if hi value is invalid.
        if (Prev1 != NULL) {   // If Current1 is not 1st node
            Prev1->next = Current2;
        } else { // If Current1 is 1st node
            head = Current2;
        }

        if (Prev2 != NULL) { // If Current2 is not 1st node
            Prev2->next = Current1;
        } else { // If current2 is 1st node
            head = Current1;
        }

        temp = Current1->next; // Switch the node -> next pointers and hi values
        tempint = Current1->hi;
        Current1->next = Current2->next;
        Current2->next = temp;

        Current1->hi = Current2->hi;
        Current2->hi = tempint;
    } else {
        printf("\n\nError, hi is probably invalid.\n\n");
    }
}

//==============] Find the Pointer of the Node Based on it's Hierarchy [==============

node* findval(node* list, int hi)
{
    if (list->hi == hi) {
        return (list);
    } else {
        findval(list->next, hi);
    }
}

//==============] Find the Pointer of the Node Based on it's Name value [==============

node* findname(node* list, char First[SIZE], char Last[SIZE])
{
    if (strcmp(list->First_name, First) == 0 && strcmp(list->Last_name, Last) == 0) {
        return (list);
    } else {
        if (list->next == NULL) {
            return (NULL);
        } else {
            findname(list->next, First, Last);
        }
    }
}

//==============] Simple Bubble Sort Algorithm [==============

void sort(node* list, int count)
{
    int i, j;
    node *temp1, *temp2;

    for (i = 1; i <= count; i++) {

        for (j = 1; j <= count - i; j++) {
            temp1 = findval(head, j);
            temp2 = findval(head, j + 1);
            if (strcmp(temp1->Last_name, temp2->Last_name) > 0) {
                swap(list, j, j + 1);
            }
        }
    }
}

//==============] Delete Node [==============

node* delete (node* list)
{
    char FirstName[35];
    char LastName[35];
    int temphi;

    if (list == NULL) { // Error if list is empty
        printf("\nError: Pointer is NULL\n");
        State = 0;
        return (list);
    }

    printstate = 1;

    printf("Enter First, Last to Delete\nEnter \"Go Next\" to Skip to Next problem\n>> ");
    scanf("%s %s", FirstName, LastName);

    node* n1;
    node* n2;
    node* n3;

    //--------------If the input is "Go Next"--------------

    if (strcmp("Go", FirstName) == 0 && strcmp("Next", LastName) == 0) {
        State = 0;
        return (list);
    }

    //--------------If the node is the first node--------------

    if (strcmp(list->First_name, FirstName) == 0 && strcmp(list->Last_name, LastName) == 0) {
        n1 = list->next;
        free(list);
        list = n1;
        pullhi(list);
        maxhi--;
        printf("\nDeleted \"%s %s\".\n\n", FirstName, LastName);
        return (list);
    }

    n1 = findname(list, FirstName, LastName);

    //--------------If the node is not on the list-------------

    if (n1 == NULL) {
        while (n1 == NULL) {
            printf("\"%s %s\" is not in the list. Please try again.\n\n", FirstName, LastName);
            printstate = 0;
            return (list);
        }
    }

    //--------------If the node is the last node--------------

    if (n1->next == NULL) {
        temphi = n1->hi;
        n2 = findval(list, temphi - 1);
        free(n1);
        n2->next = NULL;
        maxhi--;
        printf("\nDeleted \"%s %s\".\n\n", FirstName, LastName);
        return (list);
    }

    temphi = n1->hi;

    n2 = findval(list, temphi - 1);
    n3 = findval(list, temphi + 1);
    free(n1);
    n2->next = n3;

    pullhi(n3);

    maxhi--;
    printf("\nDeleted \"%s %s\".\n\n", FirstName, LastName);

    return (list);
}

//==============] Pull Hierarchy Values [==============

void pullhi(node* list)
{
    if (list->next == NULL) {
        list->hi--;
        return;
    } else {
        list->hi--;
        pullhi(list->next);
    }
}

//==============] Insert New Student at the End of the List [==============

void insert(node* list)
{
    node* new;
    char NewFirst[SIZE];
    char NewLast[SIZE];
    char NewGrade[2];
    int Newhi;
    int NewScore;

    if (list->next == NULL) {

        printf("Enter New Student\n>> ");
        scanf("%s %s %d", NewFirst, NewLast, &NewScore);

        //--------------Create node and Assign Values--------------

        new = (node*)malloc(sizeof(node));
        list->next = new;
        new->next = NULL;
        strcpy(new->First_name, NewFirst);
        strcpy(new->Last_name, NewLast);
        new->score = NewScore;
        new->hi = list->hi + 1;

        //--------------Assign Grade--------------

        if (90 <= NewScore && NewScore <= 100) {
            strcpy(new->grade, "A+");
        } else if (80 <= NewScore && NewScore <= 89) {
            strcpy(new->grade, "A0");
        } else if (70 <= NewScore && NewScore <= 79) {
            strcpy(new->grade, "B+");
        } else if (60 <= NewScore && NewScore <= 69) {
            strcpy(new->grade, "B0");
        } else if (50 <= NewScore && NewScore <= 59) {
            strcpy(new->grade, "C+");
        } else if (40 <= NewScore && NewScore <= 49) {
            strcpy(new->grade, "C0");
        } else if (30 <= NewScore && NewScore <= 39) {
            strcpy(new->grade, "D+");
        } else if (20 <= NewScore && NewScore <= 29) {
            strcpy(new->grade, "D0");
        } else if (0 <= NewScore && NewScore <= 19) {
            strcpy(new->grade, "F");
        } else {
            printf("\nWarning: %s %s Has Invalid Score.\n\n", new->First_name, new->Last_name);
            strcpy(new->grade, "0");
        }

        maxhi++;
        return;
    }

    else {
        insert(list->next);
    }
}