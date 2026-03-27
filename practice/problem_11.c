//Reverse a Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* next;
};

void reverseList(Node** head) {
	Node* curr = *head, * prev = NULL, * next;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
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
	addToList(&head, 1);
	addToList(&head, 2);
	addToList(&head, 3);
	addToList(&head, 4);
	addToList(&head, 5);
	reverseList(&head);
	print(head);
	
	return 0;
}