// Detect Cycle in Linked List

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

    if(*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        
        Node* temp = *head;
        while(temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void print(Node* head) {
    Node* temp = head;
    do {
        printf("\nData: %d", temp->data);
        temp = temp->next;
    } while(temp != head);
}

void hasCycle(Node** head) {
    Node* slow = *head;
    Node* fast = *head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if(fast == slow) {
            printf("\nHas cycle");
            return;
        }
    }
    printf("\nNo cycle");
    return;
}

int main() {
    
    Node* head = NULL;
    addToList(&head, 1);
    addToList(&head, 2);
    addToList(&head, 3);
    addToList(&head, 4);
    addToList(&head, 5);

    hasCycle(&head);

    print(head);
    
    return 0;
}