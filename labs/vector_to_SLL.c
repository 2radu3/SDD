#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    struct Node* next;
};

Node* vectorToSLL(int* v, int size) {
    if (size <= 0) return NULL;

    Node* head = (Node*)malloc(sizeof(Node));
    head->data = v[0];
    head->next = NULL;

    Node* curr = head;

    for (int i = 1; i < size; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = v[i];
        newNode->next = NULL;

        curr->next = newNode;
        curr = newNode;
    }
    return head;
}

void addToList(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if ((*head) == NULL) {
        *head = newNode;
    }
    else {
        Node* aux = *head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void print(Node* head) {
    while (head != NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

int main() {
    Node* head = NULL;
    int v[] = { 1, 2, 3 };
    print(vectorToSLL(v, 3));
    return 0;
}