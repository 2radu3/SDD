//Lista Dublu Inlantuita
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte {
    char* titlu;
    int nrPagini;
    float pret;
} Carte;

typedef struct Node Node;
struct Node {
    Carte info;
    Node* next;
    Node* prev;
};

//-inserareInceput
void inserareLaInceput(Node** head, Node** tail, Carte c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = *head;
    newNode->prev = NULL;

    if(*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*head)->prev = newNode;
        *head = newNode;
    }
}

//-inserarareLaSfarsit
void inserareLaSfarsit(Node** head, Node** tail, Carte c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = NULL;
    newNode->prev = *tail;

    if(*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void afisareCarte(Carte c) {
    printf("Titlu: %s, NrPagini: %d, Pret: %.2f\n", c.titlu, c.nrPagini, c.pret);
}

//-cautareNod / Informatie utila dupa criterii
Carte cautareDupaTitlu(Node* head, Node* tail, char* titlu) {
    while(head != NULL) {
        if(strcmp(head->info.titlu, titlu) == 0) {
            afisareCarte(head->info);
        }
        head = head->next;
    }
}

Carte citireCarte(FILE* file) {
    char buffer[30];
    Carte c;
    fscanf(file, "%s %d %f", buffer, &c.nrPagini, &c.pret);

    c.titlu = (char*)malloc(strlen(buffer + 1) * sizeof(char));
    strcpy(c.titlu, buffer);
    return c;
}

Node* citireListaCarti(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    if(!file) {
        printf("\neroare la deschiderea fisierului");
        return NULL;
    }

    Node* head = NULL;
    Node* coada = NULL;
    while(!feof(file)) {
        inserareLaSfarsit(&head, &coada, citireCarte(file));
    }

    fclose(file);
    return head;
}

void afisareListaCarti(Node* head) {
    while(head != NULL) {
        afisareCarte(head->info);
        head = head->next;
    }
}

//-stergere Noduri dupa criterii
void stergereDupaPret(Node** head, Node** tail, float pret) {
    if(*head == NULL) return;

    Node *aux = head;
    while(aux != NULL) {
        if(aux->info.pret == pret) {
            Node* deSters = aux;

            if(aux->prev != NULL) {
                aux->prev->next = aux->next;
            } else {
                *head = aux->next;
            }
            
            if(aux->next != NULL) {
                aux->next->prev = aux->prev;
            } else {
                *tail = aux->prev;
            }
            aux = aux->next;
            free(deSters->info.titlu);
            free(deSters);
        } else {
            aux = aux->next;
        }
    }
}

//-conversie la alta structura invatata la seminar (inclusiv la vector)
//-traversare in ambele sensuri
void traversareCapCoada(Node* head) {
    while(head != NULL) {
        head = head->next;
    }
}

void traversareCoadaCap(Node* tail) {
    while(tail != NULL) {
        tail = tail->prev;
    }
}

//-dezalocare
void dezalocare(Node** head, Node** tail) {
    while(*head != NULL) {
        free((*head)->info.titlu);
        Node* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
    *tail = NULL;
}

int main() {
    Node* tail = NULL;
    Node* head = citireListaCarti("carti.txt");
    afisareListaCarti(head);
    cautareDupaTitlu(head, tail, "MiculPrint");

    return 0;
}