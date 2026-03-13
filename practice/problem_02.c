//Given the head of singly linked list, find middle node of the linked list.
//- If the number of nodes is odd, return the middle node.
//- If the number of nodes is even, there are two middle nodes, so 
//  return the second middle node.

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
    if((*head) == NULL) {
        *head = nou;
    } else {
        Node *aux = *head;
        while (aux->next!=NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
}

Node* middleNode(Node* head) {
    int count = 0;
    Node* nou = head;
    while(nou != NULL) {
        count++;
        nou = nou->next;
    }
    nou = head;
    for(int i = 0; i < count/2; i++) {
        nou = nou->next;
    }
    return nou;
}

void afisare(Node* head) {
    while(head!=NULL) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

int main() {

    Node* head = NULL; //initializare lista goala
    adaugaLaSfarsit(&head, 10);
    adaugaLaSfarsit(&head, 20);
    adaugaLaSfarsit(&head, 30);
    adaugaLaSfarsit(&head, 40);
    adaugaLaSfarsit(&head, 50);
    adaugaLaSfarsit(&head, 60);
    middleNode(head);

    //int a = 5 / 2;
    //printf("%d", a);

    afisare(head);
    printf("\n");
    Node* mijloc = middleNode(head);
    printf("%d", mijloc->data);

    return 0;
}