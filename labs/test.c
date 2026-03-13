#include <stdio.h>
#include <stdlib.h>

typedef struct Carte {
    char* titlu;
    int nrPagini;
} Carte;

typedef struct Nod Nod;

struct Nod {
    Carte info;
    Nod* next;
};

void adauga(Nod** head, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = NULL;
    if((*head)==NULL) {
        *head = nou;
    } else {
        Nod* aux = *head;
        while (aux->next!=NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
}

void adaugaLaInceput(Nod** head, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = *head;
    *head = nou;//schimba adresa
}

int main() {
    Nod head;
    head.info.nrPagini = 15;
    head.next = malloc(sizeof(Nod));
    head.next->info.nrPagini = 2;
    head.next->next = NULL;
    
    Nod* curr = &head;
    while (curr!=NULL) {
        printf("First: %d\n", curr->info.nrPagini);
        curr = curr->next;
    }
    

    free(head.next);
    


    return 0;

}