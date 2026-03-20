//Exchange first and last nodes in Circular Linked List
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
	if ((*head) == NULL) {
		*head = newNode;
        newNode->next = *head;
	}
	else {
		Node* aux = *head;
		while (aux->next != *head) {
			aux = aux->next;
		}
		aux->next = newNode;
        newNode->next = *head;
	}
}

void print(Node* head) {
    Node* temp = head;
    do{
        printf("\nData: %d", temp->data);
		temp = temp->next;
    } while (temp != head);
}

void exchangeNodes(Node** head) {
    struct Node* prev = *head;
    while (prev->next->next != *head){
        prev = prev->next;
    }
        
    prev->next->next = (*head)->next;
    (*head)->next = prev->next;
    prev->next = *head;
    *head = (*head)->next;
}


int main() {
	Node* head = NULL;
	addToList(&head, 1);
	addToList(&head, 2);
	addToList(&head, 3);
	addToList(&head, 4);	
    addToList(&head, 5);
    exchangeNodes(&head);
    print(head);


	return 0;
}