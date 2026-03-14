//Check if a linked list is a Circular Linked List
//Given the head of a singly linked list, the task is to find if 
//given linked list is circular or not. 
//A linked list is called circular if 
//its last node points back to its first node.

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
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = new;    
    }
}

void afisare(Node* head) {
    while(head != NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

void checkLinked(Node* head) {
    Node* aux = head;
    while(aux != NULL) {
        if(aux->next == NULL) {
            printf("\nNot circular");
        }
        if(aux->next == head) {
            printf("\nIt's circular");
            break;  
        }
        aux = aux->next;
    }
}

int checkLinked2(Node* head) {
    if (!head) return 1;

    Node* temp = head;
    while(head && head->next != temp)
        head = head->next;
    
    if(!head || !head->next) return 0;
    
    return 1;
}

int main() {
    Node* head;
    addToList(&head, 2);
    addToList(&head, 4);
    addToList(&head, 6);
    addToList(&head, 7);
    addToList(&head, 5);
    afisare(head);

    //converting to a circular linked list
    Node* aux = head;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = head;

    checkLinked(head);

    checkLinked2(head)?printf("\nCircular"):printf("\nNot circular");

    return 0;
}
