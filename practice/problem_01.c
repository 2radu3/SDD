// C program to delete every k-th Node of
// a singly linked list.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	int data;
	Node* next;
};

void adaugaLaSfarsit(Node** head, int data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->data = data;
	nou->next = NULL;
	if ((*head) == NULL) {
		*head = nou;
	}
	else {
		Node* aux = *head;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Node* removeKthNode(Node* head, int k) {
	if (head == NULL || k <= 0) {
		return head;
	}
	Node* curr = head;
	Node* prev = NULL;
	int count = 0;
	while (curr != NULL) {
		count++;
		if (count % k == 0) { //if count is a multiple of k, remove the current node
			if (prev != NULL) {
				prev->next = curr->next;//skips the current node and points to the one
			}							//which is 2 indexes further
			else {
				head = curr->next;
			}
			free(curr);
			curr = prev != NULL ? prev->next : head;
		}
		else { //update previous node pointer only if we do not skip the node
			prev = curr;
			curr = curr->next;
		}
	}
	return head;
}

void afisare(Node* head) {
	while (head != NULL) {
		printf("\nData: %d", head->data);
		head = head->next;
	}
}

int main() {
	Node* head = NULL;
	adaugaLaSfarsit(&head, 1);
	adaugaLaSfarsit(&head, 2);
	adaugaLaSfarsit(&head, 3);
	adaugaLaSfarsit(&head, 4);
	adaugaLaSfarsit(&head, 5);
	adaugaLaSfarsit(&head, 6);
	removeKthNode(head, 2);
	afisare(head);

	return 0;
}