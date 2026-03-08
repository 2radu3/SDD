//tema inserare dupa un crieteriu, in functie dupa un anumit pret etc
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Carte {
    int id;
    char* titlu;
    int nrPagini;
    float pret;
} Carte;

typedef struct Nod Nod;
struct Nod {
    Carte info;
    Nod* next;
};

void inserareLaInceput(Nod** cap, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next = *cap;
    *cap = nou;
}

void inserareDupaPret(Nod** cap, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next=NULL;
    if((*cap) == NULL) {
        *cap = nou;
    }
    else {
        if(c.pret < (*cap)->info.pret) { //(*cap) se afla pe prima pozitie a listei
            nou->next = *cap; //next va fi actualul prim element al listei
            *cap = nou;
        }
        else {
            Nod* aux = *cap;
            while(aux->next!=NULL) {
                aux = aux->next;
            }
            aux->next = nou;
        }
        
    }
}

void inserareLaSfarsit(Nod** cap, Carte c) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c;
    nou->next=NULL;
    if((*cap)==NULL) {
        *cap = nou;
    }
    else {
        Nod* aux = *cap;
        while(aux->next!=NULL) {
            aux = aux->next;
        }
        aux->next = nou;
    }
}

Carte citireCarte(FILE* file) {
    char buffer[30];
    Carte c;
    fscanf(file, "%29s %d %f", buffer, &c.nrPagini, &c.pret);

    c.titlu = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(c.titlu, buffer);
    return c;
}

void afisareCarte(Carte carte) {
    printf("Titlu: %s, nrPagini: %d, pret: %.2f\n", carte.titlu, carte.nrPagini, carte.pret);
}

Nod* citireListaCarti(const char* numeFisier) {
    FILE* file = fopen(numeFisier, "r");
    if(!file) {
        printf("eroare la deschiderea fisierului\n");
        return NULL;
    }

    Nod* cap = NULL;

    inserareDupaPret(&cap, citireCarte(file));
    inserareDupaPret(&cap, citireCarte(file));
    inserareDupaPret(&cap, citireCarte(file));

    fclose(file);
    return cap;

}

void afisareListaCarti(Nod* cap) {
    while(cap!=NULL) {
        afisareCarte(cap->info);
        cap=cap->next;
    }
}

void dezalocare(Nod** cap) {
    while ((*cap)!=NULL) {
        free((*cap)->info.titlu);
        Nod* aux = *cap;
        *cap = (*cap)->next;
        free(aux);
    }
}

float pretMediuCarti(Nod* cap) {
    int nrCarti = 0;
    float sumaPreturi = 0;
    while(cap!=NULL) {
        nrCarti++;
        sumaPreturi += cap->info.pret;
        cap = cap->next;
    }

    if(nrCarti != 0)
    return sumaPreturi/nrCarti;
    else
    return 0;
}

char* afisareTitlu(Nod* cap, float _pret) {
    while(cap!=NULL) {
        if(cap->info.pret == _pret) {
            char* copie = (char*)malloc(sizeof(char) * strlen(cap->info.titlu)+1);
            strcpy(copie,cap->info.titlu);
            return copie;
        }
        
        cap = cap->next;
    }
    return ("\nNot Found\n");
}

int main(){

    Nod* cap = citireListaCarti("carti.txt");
    afisareListaCarti(cap);
    printf("\nPretul mediu pentru o carte este %.2f lei", pretMediuCarti(cap));
    printf(afisareTitlu(cap,46.9));
    dezalocare(&cap);
    
    return 0;
}