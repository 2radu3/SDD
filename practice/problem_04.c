//Traversal of Circular Linked List
//Given a circular linked list, print all the elements 
//of this circular linked list.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node* next;
};

void addToList(Node** head, int data) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;

    if((*head) == NULL) {
        *head = new;
    } else {
        Node* aux = *head;
        while (aux->next!=NULL) {
            aux = aux->next;
        }
        aux->next = new;
        //new->next = *head;
    }

}

void printList(Node* curr, Node* head) {
    if(head == NULL) return; //return if list is empty
    printf("%d ", curr->data);

    if (curr->next == head) {
        return;
    }

    printList(curr->next, head);
}


int main() {
    Node* head;
    addToList(&head, 1);
    addToList(&head, 2);
    addToList(&head, 3);
    addToList(&head, 4);
    addToList(&head, 5);
    addToList(&head, 6);
    //head->next->next->next->next->next->next = head;
    Node* aux = head;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = head;
    printList(head, head);

    return 0;
}