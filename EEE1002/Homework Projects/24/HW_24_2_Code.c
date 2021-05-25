#include <stdio.h>
#include <stdlib.h>

struct linked_list {
    int number;
    struct linked_list* next;
};
typedef struct linked_list
    node; // typedef 를 통해서 'node' 라고 치면 linked_list 라 치는거랑 똑같이 함.

node* insert(node* head);
node* delete (node* head);

int main()
{
    node* head;
    void create(node * p);
    int count(node * p);
    void print(node * p);
    head = (node*)malloc(sizeof(node));
    create(head);
    printf("\n");
    print(head);
    printf("\n");
    printf("\nNumber of items: %d\n", count(head));
    insert(head);
    printf("\n");
    print(head);
    delete (head);
    printf("\n");
    print(head);

    return 0;
}

void create(node* list)
{
    printf("Input a number. Type \"-999\" to end.\n>>");
    scanf("%d", &list->number);

    if (list->number == -999) {
        list->next = NULL;
    } else {
        list->next = (node*)malloc(sizeof(node));
        create(list->next);
    }

    return;
}

void print(node* list)
{
    if (list->next != NULL) {
        printf("%d --> ", list->number);
        if (list->next->next == NULL) {
            printf("%d", list->next->number);
        }
        print(list->next);
    }
    return;
}

int count(node* list)
{
    if (list->next == NULL) {
        return 0;
    } else {
        return (1 + count(list->next));
    }
}

node* insert(node* head)
{
    node* find(node * p, int a);
    node* new;
    node* n1;
    int key, x;

    printf("Value of new item?\n>>");
    scanf("%d", &x);
    printf("Vale of key? Type \"-999\" if last\n>>");
    scanf("%d", &key);

    if (head->number == key) {
        new = (node*)malloc(sizeof(node));
        new->number = x;
        new->next = head;
        head = new;
    } else {
        n1 = find(head, key);
        if (n1 == NULL) {
            printf("\nKey not found.\n");
        } else {
            new = (node*)malloc(sizeof(node));
            new->number = x;
            new->next = n1->next;
            n1->next = new;
        }
    }
    return (head);
}

node* delete (node* head)
{
    node* find(node * p, int a);
    int key;
    node* n1;
    node* p;

    printf("\nEnter number to be deleted\n>>");
    scanf("%d", &key);

    if (head->number == key) {
        p = head->next;
        free(head);
        head = p;
    } else {
        n1 = find(head, key);
        if (n1 == NULL) {
            printf("\nKey not found.\n");
        } else {
            p = n1->next->next;

            free(n1->next);
            n1->next = p;
        }
    }

    return (head);
}

node* find(node* list, int key)
{
    if (list->next->number == key) {
        return (list);
    } else {
        if (list->next->next == NULL) {
            return (NULL);
        } else {
            find(list->next, key);
        }
    }
}