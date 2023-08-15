#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

//implement for hash table

struct DataItem {
    int data;
    int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    return key % SIZE;
}

    
struct DataItem* search(int key) {
    //get the hash 
    int hashIndex = hashCode(key);

    //move in array until an empty 
    while (hashArray[hashIndex] != NULL) {

        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}

void insert(int key, int data) {

    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    //get the hash 
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

struct DataItem* deletee(struct DataItem* item) {
    int key = item->key;

    //get the hash 
    int hashIndex = hashCode(key);

    //move in array until an empty
    while (hashArray[hashIndex] != NULL) {

        if (hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];

            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return temp;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}

void display() {
    int i = 0;

    for (i = 0; i < SIZE; i++) {

        if (hashArray[i] != NULL)
            printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}

//implement for linked list

typedef struct node
{
    int data;
    struct node* next;
}Node;

Node* createList(int* arr, int n)
{
    Node* head = NULL, * last = NULL;

    for (int i = 0; i < n; i++)
    {
        if (head == NULL) // first time
        {
            last = head = (Node*)malloc(sizeof(Node));
            last->data = head->data = arr[i];
            last->next = head->next = NULL;
        }
        else
        {
            last->next = (Node*)malloc(sizeof(Node));
            last = last->next;
            last->data = arr[i];
            last->next = NULL;
        }
    }
    last->next = NULL;
    return head;
}

// print the linked list value
void printLinkedlist(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}


//1
Node* removeDuplicates(Node* head) {
    int key = 0;
    Node* p = head;

    insert(key, head->data);//for the first element

    while (head->next != NULL) {
        if (search(head->next->data) == NULL) {//if its not a duplicate value
            insert(key, head->next->data);
            key++;
        }
        else {//we have to remove
            head->next = head->next->next;
            continue;
        }
        head = head->next;
    }
    return p;
}


//2
int lenOfList(Node* head) {//length
    Node* p = head;
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}
Node* findTheLastKTH(Node* head, int kth) {

    int length = lenOfList(head);
    Node* p = head;//ponter for the list
    for (int i = 0; i < length - kth ; i++)
    {
        p = p->next;
    }
    return p;
}

//3
void deleteMiddleNode(Node* middle) {
    if (middle == NULL || middle == NULL)
        return;
    Node* midd = middle->next;
    middle->data = midd->data;
    middle->next = midd->next;
}
//4
void changeGreaterSmaller(Node* head, int x) {

    int arr[] = { head->data };
    Node* newList = createList(arr, 1);
    Node* pEndNewList = newList;
    Node* p = head;

    while (p != NULL) {

        if (p->data < x) {
            // Move the node to the start
            Node* newNode  = (Node*)malloc(sizeof(Node));
            newNode->data = p->data;
            newNode->next = newList;
            newList = newNode;
        }
        else {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = p->data;
            pEndNewList->next = newNode;
            pEndNewList = pEndNewList->next;
        }
        p = p->next;
    }

    // Update the head pointer to the rearranged list
    //head = originalList;
    pEndNewList->next = NULL;
    printLinkedlist(newList);
}

//5
Node* summaryLists(Node* head1, Node* head2) {
    Node* sum = (Node*)malloc(sizeof(Node));
    Node* pSum = sum;
    int rest = 0;
    Node* pointer1 = head1;
    Node* pointer2 = head2;
    while (pointer1 != NULL && pointer2 != NULL) {
        int plus = pointer1->data + pointer2->data + rest;
        if (plus > 9) {
            rest = plus / 10;
        }
        else {
            rest = 0;
        }
        pSum->data = plus % 10;
        pSum->next = (Node*)malloc(sizeof(Node));
        pSum = pSum->next;
        pSum->next = NULL;
        pointer1 = pointer1->next;
        pointer2 = pointer2->next;
    }
    if (pointer1 != NULL) {
        while (pointer1 != NULL) {
            int plus = pointer1->data + rest;
            if (plus > 9) {
                rest = plus / 10;
            }
            else {
                rest = 0;
            }
            pSum->data = plus % 10;
            pSum = pSum->next;
            pointer1 = pointer1->next;
        }
    }
    else if (pointer2 != NULL) {
        while (pointer2 != NULL) {
            int plus = pointer2->data + rest;
            if (plus > 9) {
                rest = plus / 10;
            }
            else {
                rest = 0;
            }
            pSum->data = plus % 10;
            pSum = pSum->next;
            pointer2 = pointer2->next;
        }
    }
    return sum;
}

//6
int isPalindrom(Node* head) {
    int length = lenOfList(head);
    if (length == 1)//one element is palindrom too
        return 1;
    Node* pointer1 = head;
    int helper[] = { 1, 2, 3, 5, 8 };
    for (int i = 0; i < (length / 2); i++)
    {
        helper[i] = pointer1->data;
        pointer1 = pointer1->next;
    }
    if (length % 2 != 0) {//if its odd
        pointer1 = pointer1->next;
    }
    int i = (length / 2) - 1;
    while (pointer1 != NULL) {
        if (pointer1->data != helper[i])//if they are not equals its not polindrom
            return 0;
        pointer1 = pointer1->next;
        i--;
    }
    return 1;
}

int main() {


    int arr[] = { 3 , 5 , 8 , 5 , 10 , 2 , 1 ,5, 4};
    Node* head = createList(arr, 9);
    printf("\n---------------1-------------\n");
    head = removeDuplicates(head);
    printLinkedlist(head);   
    printf("\n---------------2-------------\n");
    printf("the 3 element from the end: %d \n", findTheLastKTH(head, 3)->data);
    printf("\n---------------3-------------\n");
    Node* p = head->next->next;
    deleteMiddleNode(p);
    printLinkedlist(head);
    printf("\n---------------4-------------\n");
    changeGreaterSmaller(head, 5);
    printf("\n---------------5-------------\n");
    int arr1[] = { 8,7,9,6 };
    int arr2[] = { 1,7,3 };
    Node* list1 = createList(arr1, 4);
    Node* list2 = createList(arr2, 3);
    Node* summary = summaryLists(list1, list2);
    printLinkedlist(summary);
    printf("\n");
    printf("---------------6-------------\n");
    int arr3[] = { 3, 3, 5 };
    Node* palindrom = createList(arr3, 3);
    if (isPalindrom(palindrom) == 1)
        printf("yes, its palindrom");
    else
        printf("no, its not palindrom");

}