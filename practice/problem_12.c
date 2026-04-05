// Reverse a Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
    Node* prev;
};

void reverse(Node** head) {
    if (*head == NULL) return;

    Node* prev = NULL;
    Node* curr = *head;

    while(curr != NULL) {
        prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;

        curr = curr->prev;
    }

    if(prev != NULL) {
        *head = prev->prev;
    }   
}

void addToList(Node** head, Node** tail, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
    newNode->prev = *tail;
	if ((*head) == NULL) {
		*head = *tail = newNode;
	}
	else {
		(*tail)->next = newNode;
        *tail = newNode;
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
    Node* tail = NULL;
    addToList(&head, &tail, 1);
    addToList(&head, &tail, 2);
    addToList(&head, &tail, 3);
    addToList(&head, &tail, 4);
    reverse(&head);
    print(head);
    
    return 0;
}