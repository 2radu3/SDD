//Deletion in a Doubly Linked List
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
    newNode->prev = *tail;
	if ((*head) == NULL) {
		*head = *tail = newNode;
	}
	else {
		(*tail)->next = newNode;
        *tail = newNode;
	}
}

void afisare(Node* head) {
	while (head != NULL) {
		printf("\nData: %d", head->data);
		head = head->next;
	}
}

//Deletion of the first node
void deleteFirstNode (Node** head) {
    if(*head == NULL) return;
    Node* temp = *head;
    *head = (*head)->next;
    if(*head != NULL) (*head)->prev = NULL;
    free (temp);
}

//Deletion after a given node
void deleteAfterGivenNode (Node** head, int key) {

	Node* curr = *head;
	while(curr != NULL) {
		if(curr->data == key) {
			break;
		}
		curr = curr->next;
	}

	if(curr == NULL || curr->next == NULL) {
		return;
	}

	Node* delNode = curr->next;
	curr->next = delNode->next;

	if (delNode->next != NULL) {
		delNode->next->prev = curr;
	}

	free (delNode);
}

int main() {
	Node* head = NULL, *prev = NULL;
	addToList(&head, &prev, 1);
	addToList(&head, &prev, 2);
	addToList(&head, &prev, 3);
	addToList(&head, &prev, 4);
	addToList(&head, &prev, 5);
	addToList(&head, &prev, 6);
    //deleteFirstNode(&head);
	deleteAfterGivenNode(&head, 3);
	afisare(head);

	return 0;
}