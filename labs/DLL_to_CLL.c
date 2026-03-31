#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* next;
	Node* prev;
};

void addToList(Node** head, Node** tail, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	if (*head == NULL) {
		*head = *tail = newNode;
	}
	else {
		(*tail)->next = newNode;
		*tail = newNode;
	}
}

void makeCircular(Node** head) {
	Node* tail = *head;
	
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = *head;
	(*head)->prev = tail;
}

void print(Node* head) {
	while (head != NULL) {
		printf("\nData: %d", head->data);
		head = head->next;
	}
}

void circularPrint(Node* head) {
	Node* temp = head;
	do {
		printf("\nData: %d", temp->data);
		temp = temp->next;
	} while (temp != head);
}

int main() {
	Node* head = NULL;
	Node* tail = NULL;
	addToList(&head, &tail, 1);
	addToList(&head, &tail, 2);
	addToList(&head, &tail, 3);
	addToList(&head, &tail, 4);
	makeCircular(&head);
	circularPrint(head);
	
	return 0;
}