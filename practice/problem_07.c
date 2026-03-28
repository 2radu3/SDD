//Deletion from a Circular Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

void addToList(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = data;
    if ((*head == NULL)) {
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
    printf("\nData: %d", head->data);
    head = head->next;
    while (head != temp) {
        printf("\nData: %d", head->data);
        head = head->next;
    }
}

void deleteFirstNode(Node** head) { //must ask which one its better
    if ((*head) == NULL) return;    // --both works

    Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }

    if ((*head) == temp) {
        free(*head);
        *head = NULL;
    }
    else {
        Node* aux = *head;
        temp->next = (*head)->next;
        *head = (*head)->next;
        free(aux);
    }
}

Node* deleteFirstNode2(struct Node* last) {
    if (last == NULL) return NULL;

    struct Node* head = last->next;

    if (head == last) {
        free(head);
        last = NULL;
    }
    else {
        last->next = head->next;
        free(head);
    }
    return last;
}

void deleteSpecificNode(Node** head, int key) {
    //check if the list is empty
    if ((*head) == NULL) return;

    //if the first node matches the key
    Node* curr = *head;
    if (curr->data == key) {
        //if it is the only node in the list
        if (curr->next == *head) {
            free(curr);
            *head = NULL;
            return;
        }

        //if it has more nodes we must find the last node
        Node* last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        last->next = curr->next;
        *head = curr->next;
        free(curr);
        return;
    }

    //if the node is last or in the middle
    Node* prev = *head;
    curr = (*head)->next;
    while (curr != *head) {
        if (curr->data == key) {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main() {
    Node* head = NULL;
    addToList(&head, 1);
    addToList(&head, 2);
    addToList(&head, 3);
    addToList(&head, 4);
    deleteFirstNode(&head);
    //print(head);

    //Node* last = head;
    //while (last->next != head) {
        //last = last->next;
    //}
    //last = deleteFirstNode2(last);
    //print(last);

    deleteSpecificNode(&head, 2);
    print(head);

    return 0;
}
