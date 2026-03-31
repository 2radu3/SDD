#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* vectorToDLL(int* v, int size) {
    if (size <= 0) return NULL;

    Node* head = (Node*)malloc(sizeof(Node));
    head->data = v[0];
    head->next = NULL;
    head->prev = NULL;

    Node* curr = head;

    for (int i = 1; i < size; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = v[i];
        newNode->next = NULL;
        newNode->prev = v[i - 1];

        curr->next = newNode;
        curr = newNode;
        curr->prev = newNode->prev;
    }
    return head;
}

void print(Node* head) {
    while (head != NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

int main() {
    Node* head = NULL;
    int v[] = { 1, 2, 3, 4 };
    print(vectorToDLL(v, 4));
    return 0;
}