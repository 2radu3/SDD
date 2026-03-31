#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
    Node* prev; //we need to add this
};

void addToList(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if((*head) == NULL) {
        *head = newNode;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void addToListDLL(Node** head, Node** tail, int data) { // O(1)
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = *tail;
    if((*head) == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void addToList2(Node** head, int data) { // O(n) but no tail
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(*head == NULL) {
        *head = newNode;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
        newNode->prev = aux;
    }

}

void print(Node* head) {
    while(head != NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

void sllToDll(Node** head) { //if we use addToList() we need to call this again everytime
    if(*head == NULL) return;
    Node* tail = *head;
    tail->prev = NULL;
    while(tail->next != NULL) {
        tail->next->prev = tail;
        tail = tail->next;
    }
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    sllToDll(&head);
    addToList2(&head, 1);
    addToList2(&head, 2);
    addToList2(&head, 3);
    addToList2(&head, 4);
    addToList2(&head, 5);
    addToList2(&head, 6);
    print(head);

    return 0;
}