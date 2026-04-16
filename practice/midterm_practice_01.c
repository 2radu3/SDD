//Lista Simplu Inlantuita
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//typedef struct Carte Carte;
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

typedef struct NodeDublu NodeDublu;
struct NodeDublu {
    Carte info;
    NodeDublu* next;
    NodeDublu* prev;
};

//-inserareLaInceput
void inserareLaInceput(Node** head, Carte c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = NULL;
    if((*head) == NULL) {
        newNode = *head;
    } else {
        Node* aux = *head;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

//-inserarareLaSfarsit
void inserareLaSfarsit(Node** head, Carte c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = c;
    newNode->next = *head;
    *head = newNode;
}

void afisareCarte(Carte c) {
    printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", c.titlu, c.nrPagini, c.pret);
}

//-cautare Nod / Informatie utila dupa criterii
Node pretPar(Node* head) {
    Node* aux = head;
    while(head != NULL) {
        if((int)head->info.pret % 2 == 0){
            afisareCarte(head->info);
        }
        head = head->next;
    }
}

Carte citireCarte(FILE* file) {
    char buffer[30];
	Carte c;
	fscanf(file, "%s %d %f", buffer, &c.nrPagini, &c.pret);

	c.titlu = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(c.titlu, buffer);

	return c;
}

Node* citireListaCarti (const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    if(!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return NULL;
    }
    Node* head = NULL;
    while(!feof(file)) {
        inserareLaSfarsit(&head, citireCarte(file));
    }
    
    fclose (file);
    return head;
}

void afisareListaCarti(Node* head) {
    while(head != NULL) {
        afisareCarte(head->info);
        head = head->next;
    }
}

//-dezalocare structura
void dezalocare(Node** head) {
    while((*head) != NULL) {
        free((*head)->info.titlu);
        Node* aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}

//-stergere Noduri dupa criterii
void stergePretPar(Node** head) {
    if (*head == NULL) return;

    Node* aux = *head;
    Node* prev = NULL;

    while (aux != NULL) {
        if((int)aux->info.pret % 2 == 0) {
            Node* deSters = aux;

            if(prev == NULL) {
                *head = aux->next;
                aux = *head;
            } else {
                prev->next = aux->next;
                aux = aux->next;
            }

            free(deSters->info.titlu);
            free(deSters);
        } else {
            prev = aux;
            aux = aux->next;
        }
    }
}

//-conversie la alta structura invatata la seminar (inclusiv la vector)
//lista simplu inlantuita -> vector
void conversieVector (Node* head, int* nrElemente) {
    if (head == NULL) {
        *nrElemente = 0;
        return NULL;
    }

    int contor = 0;
    Node* aux = head;
    while(aux != NULL) {
        contor++;
        aux = aux->next;
    }

    Carte* vector = (Carte*)malloc(contor * sizeof(Carte));
    if (vector == NULL) return NULL;

    aux = head;
    for(int i = 0; i < contor; i++) {
        vector[i].nrPagini = aux->info.nrPagini;
        vector[i].pret = aux->info.pret;
        vector[i].titlu = (char*)malloc(strlen(aux->info.titlu) + 1);
        strcpy(vector[i].titlu, aux->info.titlu);

        aux = aux->next;
    }
    *nrElemente = contor;
    return vector;
}

NodeDublu* conversieListaDubluInlantuita(Node* head) {
    if(head == NULL) return NULL;
    
    NodeDublu* headNou = NULL;
    NodeDublu* tailNou = NULL;
    NodeDublu* aux = head;

    while(aux != NULL) {
        NodeDublu* nou = (Node*)malloc(sizeof(Node));
        nou->info.nrPagini = aux->info.nrPagini;
        nou->info.pret = aux->info.pret;
        nou->info.titlu = (char*)malloc(strlen(aux->info.titlu) * sizeof(char));
        strcpy(nou->info.titlu, aux->info.titlu);

        if(headNou == NULL) {
            nou->prev = NULL;
            headNou = nou;
            tailNou = nou;
        } else {
            nou->prev = tailNou;
            tailNou->next = nou;
            tailNou = nou;
        }

        aux = aux->next;
    }
    return headNou;
}

void conversieCoada(Node* head, Node** front, Node** rear) {
    *front = head;

    if(head == NULL) {
        *rear = NULL;
        return;
    }

    Node* aux = head;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    *rear = aux;    
}

Node* conversieStiva(Node* head) {
    return head;
}

//-traversare
void traversare(Node* head) {
    if(head == NULL) {
        printf("\nLista este goala");
        return;
    }
    
    while(head != NULL) {
        head = head->next;
    }
}

int main() {
    Node* head = citireListaCarti("carti.txt");
    stergePretPar(&head);
    afisareListaCarti(head);

    
    return 0;
}