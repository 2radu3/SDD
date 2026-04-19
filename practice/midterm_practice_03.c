//Coada si Stiva
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
};

Carte initCarte(const char* titlu, int nrPagini, float pret) {
    Carte c;
    c.nrPagini = nrPagini;
    c.pret = pret;
    c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);

    return c;
}

//-inserare la inceput pentru stiva
void push(Node** head, Carte c) { 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = *head;
    *head = newNode;
}

//-pop pentru stiva si coada
Carte pop(Node** stiva) { 
    if(*stiva == NULL) {
        return initCarte(NULL, 0, 0);
    }
    Carte c = (*stiva)->info;
    Node* aux = *stiva;
    *stiva=(*stiva)->next;
    free(aux);

    return c;
}

//-inserare la sfarsit pentru coada
void put(Node** head, Carte c) { 
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = NULL;
    if(*head == NULL) {
        *head = newNode;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

//-scoatere nod dupa criteriu (nu este posibila la stive, doar prin parcurgerea listei)
void scoatereDupaNume(Node** head, char* nume) {
    Node* aux = *head;
    Node* prev = NULL;

    if(strcmp(aux->info.titlu, nume) == 0) {
        *head = aux->next;
        free(aux);
        return;
    }

    while(aux != NULL) {
        if(strcmp(aux->info.titlu, nume) == 0) {
            prev->next = aux->next;
            free(aux);
            return;
        }

        prev = aux;
        aux = aux->next;   
    }
}

//-conversie la alta structura invatata la seminar (inclusiv la vector)
void conversieCoadaVector (Node** coada, Carte** vectorCarti, int nrCarti) { //se poate folosi si pentru stiva
    *vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
    int i = 0;
    while(*coada != NULL) {
        (*vectorCarti)[i] = pop(coada);
        i++;
    }
}

//-afisare
void afisareCarte(Carte c) {
    printf("Titlu: %s, nrPagini: %d, Pret: %.2f\n", c.titlu, c.nrPagini, c.pret);
}

void afisare(Node* head) {
    while (head != NULL) {
        Carte c = pop(&head);
        afisareCarte(c);
    }
}

//-dezalocare
void dezalocare(Node** head) {
    Node* aux;
    while(*head != NULL) {
        aux = *head;
        *head = (*head)->next;
        free(aux->info.titlu);
        free(aux);
    }   
}

int main() {
    Node* stiva = NULL;
    push(&stiva, initCarte("Don Quijote", 250, 45));
    push(&stiva, initCarte("Macbeth", 320, 62.5));
    scoatereDupaNume(&stiva, "Macbeth");
    afisare(stiva);
    
    return 0;
}