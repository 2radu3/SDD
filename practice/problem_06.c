//Count nodes in Circular linked list
//Given a circular linked list. The task is to find the 
//length of the linked list, where length is defined as 
//the number of nodes in the linked list.

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
    if((*head) == NULL) {
        *head = new;
        new->next = *head;
    } else {
        Node* aux = *head;
        while(aux->next != *head) {
            aux = aux->next;
        }
        aux->next = new;
        new->next = *head;
    }
    
}

void print(Node* head) {
    if(head == NULL) return;
    printf("\nData: %d", head->data);
    Node* temp = head->next;
    while(temp != head) {
        printf("\nData: %d", temp->data);
        temp = temp->next;
    }
}

int countNodes(Node* head) {
    if(head == NULL) return 0;
    Node* temp = head->next;
    int counter = 1;
    while(temp != head) {
        temp = temp->next;
        counter++;
    }
    return counter;
}

//OR

int countNodes2(Node* head) {
    if(head == NULL) return 0;

    Node* temp = head;
    int counter = 0;
    do {
        temp = temp->next;
        counter++;
    } while(temp != head);

    return counter;
}




int main() {
    Node* head;
    addToList(&head, 1);
    addToList(&head, 2);
    addToList(&head, 3);
    addToList(&head, 4);
    addToList(&head, 5);
    print(head);
    printf("\n%d", countNodes(head));
    //printf("\n%d", countNodes2(head));
    
    return 0;
}