//Count Occurrences in a Linked List
//Given a singly linked list and a key, the task is to count 
//the number of occurrences of the given key in the linked list.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    int data;
    Node* next;
};

void adaugareLaSfarsit (Node** head, int data) {
    Node* nou = (Node*)malloc(sizeof(Node));
    nou->data = data;
    nou->next = NULL;
    if((*head) == NULL) {
        *head = nou;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
    
}

void afisare(Node* head) {
    while(head!=NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

void occurrences(Node* head, int key) {
    int count = 0;
    while(head!=NULL) {
        if(head->data == key) {
            count++;
        }
        head = head->next;
    }
    printf("\nOccurrences: %d", count);
}

int count(Node* head, int key) { //using recursion
    if (head == NULL) {
        return 0;
    }

    int contor = count(head->next, key);

    if(head->data == key) {
        contor++;
    }

    return contor;

}

int main () {

    Node* head = NULL;
    adaugareLaSfarsit(&head, 1);
    adaugareLaSfarsit(&head, 2);
    adaugareLaSfarsit(&head, 1);
    adaugareLaSfarsit(&head, 2);
    adaugareLaSfarsit(&head, 1);
    adaugareLaSfarsit(&head, 3);
    adaugareLaSfarsit(&head, 1);
    afisare(head);
    occurrences(head, 1);
    printf("\nOccurrences (recursion): %d", count(head,1));


    return 0;
}