#include <stdio.h>
#include <stdlib.h>

struct node {
    int num;
    node* next, *prev;
} *head = NULL, *tail = NULL;

node* createNode(int num) {
    node* newNode = (node *) malloc(sizeof(node));
    newNode->num = num;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void pushHead(int num) {
    node* newNode = createNode(num);
    if (head == NULL) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void pushTail(int num) {
    node* newNode = createNode(num);
    if (head == NULL) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void pushMid(int num) {
    if (head == NULL) {
        pushHead(num);
    }
    else if (num <= head->num) {
        pushHead(num);
    }
    else if (num >= tail->num) {
        pushTail(num);
    }
    else {
        node* newNode = createNode(num);
        node* curr = head;
        while (curr && curr->num < num) {
            curr = curr->next;
        }
        curr->prev->next = newNode;
        newNode->prev = curr->prev;
        curr->prev = newNode;
        newNode->next = curr;
    }
}

void printList() {
    for (node* curr = head;curr;curr = curr->next) {
        printf("%d ", curr->num);
    }
    printf("\n");
}

int checkSorted(int* arrSorted, int numCount) {
    node* curr = head;
    for (int i = 0;i<numCount;i++) {
        if (*(arrSorted+i) != curr->num) {
            return 0;
        }
        curr = curr->next;
    }
    return 1;
}
//Automatically sorted list using priority queue
int main() {
    int numCount;
    printf("Input the amount of number you want to insert: ");
    scanf("%d", &numCount);
    int arrSort[100] = {0};
    printf("Input all the num: ");
    for (int i = 0;i<numCount;i++) {
        int temp =0;
        scanf("%d", &temp);
        pushMid(temp);
        arrSort[i] = temp;
    }
    //sort array
    for (int i = 0;i<numCount;i++) {
        for (int j = i+1;j<numCount;j++) {
            if (arrSort[i] > arrSort[j]) {
                int temp = arrSort[j];
                arrSort[j] = arrSort[i];
                arrSort[i] = temp;
            }
        }
    }
    printf("Linked List: ");
    printList();
    printf("Sorted Arr: ");
    for (int i = 0;i<numCount;i++) {
        printf("%d ", arrSort[i]);
    }
    printf("\n");
    if (checkSorted(arrSort, numCount) == 1) {
        puts("Linked List is sorted!");
    }
    else {
        puts("Linked list is not sorted!");
    }
    return 0;
}