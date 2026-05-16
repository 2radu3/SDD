#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte {
    int id;
    char* titlu;
    int nrPagini;
    float pret;
    //int prioritate;
} Carte;

typedef struct Nod Nod;
struct Nod {
    Carte info;
    Nod* next;
    Nod* stanga;
    Nod* dreapta;
};

typedef struct HashTable {
    Nod** vector;
    int size;
} HashTable;

typedef struct MaxHeap MaxHeap;
struct MaxHeap {
    Carte* vectorC;
    int size;
};

Carte initCarte(const char* titlu, int nrPagini, float pret) {
    Carte c;
    c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);
    c.nrPagini = nrPagini;
    c.pret = pret;
    return c;
}

Carte initCarte2(int id, const char* titlu, int nrPagini, float pret) {
    Carte c;
    c.id = id;
    c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);
    c.nrPagini = nrPagini;
    c.pret = pret;
    return c;
}

void afisareCarte(Carte c) {
    printf("\nTitlu: %s, NrPagini: %d, Pret: %.2f", c.titlu, c.nrPagini, c.pret);
}

void afisareListaCarti(Nod* cap) {
    while(cap != NULL){
        afisareCarte(cap->info);
        cap = cap->next;
    }
}

void inserareLaSfarsit(Nod** cap, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = NULL;
    if(*cap == NULL) {
        *cap = nou;
    } else {
        Nod* aux = *cap;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
}

void dezalocare(Nod** cap) {
    while((*cap) != NULL) {
        free((*cap)->info.titlu);
        Nod* aux = *cap;
        *cap = (*cap)->next;
        free(aux);
    }
}

HashTable initTabela(int dim) {
    HashTable tabela;
    tabela.size = dim;
    tabela.vector = (Nod**)malloc(dim * sizeof(Nod*));
    for(int i = 0; i < dim; i++) {
        tabela.vector[i] = NULL;
    }
    return tabela;
}

int hash(int nrPagini, int size) {
    return nrPagini % size;
}

void inserareInTabela(HashTable tabela, Carte c) {
    if(tabela.size > 0) {
        int poz = hash(c.nrPagini, tabela.size);
        if(poz > 0 && poz <= tabela.size) {
            inserareLaSfarsit(&(tabela.vector[poz]), c);
        }
    }
}

void parcurgereTabela(HashTable tabela) {
    for(int i = 0; i < tabela.size; i++) {
        printf("\nPozitie: %d", i);
        afisareListaCarti(tabela.vector[i]);
    }
}

void dezalocareTabela(HashTable tabela) {
    for(int i = 0; i < tabela.size; i++) {
        dezalocare(&(tabela.vector[i]));
    }
    free(tabela.vector);
}

float calculPretMediuDupaNrPagini(HashTable tabela, int nrPagini) {
    int poz = hash(nrPagini, tabela.size);
    Nod* cap = tabela.vector[poz];
    float suma = 0;
    int nrCarti = 0;
    while(cap != NULL) {
        if(cap->info.nrPagini == nrPagini) {
            suma += cap->info.pret;
            nrCarti++;
        }
        cap = cap->next;
    }
    return suma / nrCarti;
}


//conversie HashTable la Binary Search Tree (AVL)
int maxim(int a, int b) {
    return (a > b ? a : b);
}

int calculInaltime(Nod* rad) {
    if (rad == NULL) return 0;
    return maxim(calculInaltime(rad->stanga), calculInaltime(rad->dreapta)) + 1;
}

int diferentaNivel(Nod* rad) {
    if (rad) {
        return calculInaltime(rad->stanga) - calculInaltime(rad->dreapta);
    }
    return 0;
}

void rotireLaStanga(Nod** rad) {
    Nod* aux = (*rad)->dreapta;
    (*rad)->dreapta = aux->stanga;
    aux->stanga = *rad;
    *rad = aux;
}

void rotireLaDreapta(Nod** rad) {
    Nod* aux = (*rad)->stanga;
    (*rad)->stanga = aux->dreapta;
    aux->dreapta = *rad;
    *rad = aux;
}

void inserareInBST(Nod** rad, Carte c) {
    if(*rad == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = c;
        nou->dreapta = NULL;
        nou->stanga = NULL;
        *rad = nou;
    } else if (c.id < (*rad)->info.id) {
        inserareInBST(&(*rad)->stanga, c);
    } else {
        inserareInBST(&(*rad)->dreapta, c);
    }

    int diffH = diferentaNivel(*rad);

    if (diffH == 2) {
        if (diferentaNivel((*rad)->stanga) == -1) {
            rotireLaStanga(&(*rad)->stanga);
        }
        rotireLaDreapta(rad);
    }

    if (diffH == -2) {
        if(diferentaNivel((*rad)->dreapta) == 1) {
            rotireLaDreapta(&(*rad)->dreapta);
        }
        rotireLaStanga(rad);
    }
}

void conversieAVL(HashTable tabela, Nod** radArbore) {
    for (int i = 0; i < tabela.size; i++) {
        Nod* cap = tabela.vector[i];
        while(cap) {
            inserareInBST(radArbore, cap->info);
            cap = cap->next;
        }
    }
}

//conversie HashTable la ABC
void inserareInABC(Nod** rad, Carte c) {
    if (*rad == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->dreapta = NULL;
        nou->stanga = NULL;
        nou->info = c;
        *rad = nou;
    } else if (c.id < (*rad)->info.id) {
        inserareInABC(&(*rad)->stanga, c);
    } else {
        inserareInABC(&(*rad)->dreapta, c);
    }
}

void conversieABC (HashTable tabela, Nod** rad) {
    for (int i = 0; i < tabela.size; i++) {
        Nod* cap = tabela.vector[i];
        while (cap != NULL) {
            inserareInABC(rad, tabela.vector[i]->info);
            cap = cap->next;
        }
    }
}

void inordine(Nod* rad) {
    if(rad) {
        inordine(rad->stanga);
        afisareCarte(rad->info);
        inordine(rad->dreapta);
    }
}

//conversie HashTable la MaxHeap
void heapify(MaxHeap heap, int index) {
    if (heap.size > 0) {
        int pozMax = index;
        int pozSt = 2 * index + 1;
        int pozDr = 2 * index + 2;

        if (pozSt < heap.size && heap.vectorC[pozMax].id < heap.vectorC[pozSt].id) {
            pozMax = pozSt;
        }

        if (pozDr < heap.size && heap.vectorC[pozMax].id < heap.vectorC[pozDr].id) {
            pozMax = pozDr;
        }

        if (pozMax != index) {
            Carte aux = heap.vectorC[pozMax];
            heap.vectorC[pozMax] = heap.vectorC[index];
            heap.vectorC[index] = aux;

            if (pozMax <= heap.size / 2 - 1) {
                heapify(heap, pozMax);
            }
        }
    }
}

void conversieMaxHeap(HashTable tabela, MaxHeap* heap) {
    int contor = 0;
    for (int i = 0; i < tabela.size; i++) {
        Nod* cap = tabela.vector[i];
        while (cap) {
            heap->vectorC[contor] = cap->info;
            contor++;
            cap = cap->next;
        }
    }

    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        heapify(*heap, i);
    }
}

void traversareHeap(MaxHeap heap) {
    for (int i = 0; i < heap.size; i++) {
        afisareCarte(heap.vectorC[i]);
    }
}




int main() {
    HashTable tabela = initTabela(6);
    inserareInTabela(tabela, initCarte2(7, "Carte1", 122, 55));
    inserareInTabela(tabela, initCarte2(4, "Carte2", 100, 55));
    inserareInTabela(tabela, initCarte2(10, "Carte3", 100, 55));
    inserareInTabela(tabela, initCarte2(2, "Carte4", 100, 55));
    inserareInTabela(tabela, initCarte2(6, "Carte5", 100, 55));
    inserareInTabela(tabela, initCarte2(8, "Carte6", 100, 55));
    inserareInTabela(tabela, initCarte2(11, "Carte7", 100, 55));

    //parcurgereTabela(tabela);

    printf("\nPretul mediu este: %.2f lei!", calculPretMediuDupaNrPagini(tabela, 122));

    //dezalocareTabela(tabela);

    Nod* rad = NULL;
    MaxHeap heap;
    heap.vectorC = (Carte*)malloc(sizeof(Carte) * heap.size);
    heap.size = 7;
    
    conversieMaxHeap(tabela, &heap);
    traversareHeap(heap);
    
    //printf("\n");
    //inordine(rad);

    return 0;
}