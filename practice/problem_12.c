// Reverse a Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* reverse(Node *head) {
  
    if (head == NULL) return NULL;

    Node *temp = head->prev;
    head->prev = head->next;
    head->next = temp;

    if (head->prev == NULL) return head;

    return reverse(head->prev);
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
    head = reverse(head);
    print(head);
    
    return 0;
}