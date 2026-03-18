//Convert singly linked list into circular linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* next;
};

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

void printCircular(Node* head) {
	if (head == NULL) return;
	Node* temp = head;
	do {
		printf("\nData: %d", temp->data);
		temp = temp->next;
	} while (temp != head);
}

void singlyToCircular(Node** head) { //O(n) time and O(1) space
	Node* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = *head;
}

//OR

void circular(Node* curr, Node* head) { //O(n) time and O(n) space
	if (curr->next == NULL) {
		curr->next = head;
		return;
	}

	circular(curr->next, head);
}


int main() {
	Node* head = NULL;
	addToList(&head, 1);
	addToList(&head, 2);
	addToList(&head, 3);
	addToList(&head, 4);
	//print(head);
	
	//singlyToCircular(&head);
	circular(head, head);
	printCircular(head);

	return 0;
}