#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Nod Nod;
typedef struct Persoana{
    int id;
    char* nume;
    int varsta;
    float inaltime;
} Persoana;


struct Nod {
    Persoana info;
    Nod* stanga;
    Nod* dreapta;
};

Persoana initPersoana(int id, const char* nume, int varsta, float inaltime) {
    Persoana p;
    p.id = id;
    p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(p.nume, nume);
    p.varsta = varsta;
    p.inaltime = inaltime;
    return p;
}

void afisarePersoana(Persoana p) {
    printf("\n%d, Nume: %s, Varsta: %d, Inaltime: %.2f", p.id, p.nume, p.varsta, p.inaltime);
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

int maxim (int a, int b) {
    return (a > b ? a : b);
}

int calculInaltimeArbore(Nod* rad) {
    if(rad) {
        return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) + 1;
    }
    return 0;
}

int diferentaInaltimeSubarbori(Nod* rad) {
    if(rad) {
        return calculInaltimeArbore(rad->stanga) - calculInaltimeArbore(rad->dreapta);
    } else {
        return 0;
    }
}

void inserareInBST (Nod** rad, Persoana p) {
    if(*rad == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = p;
        nou->dreapta = NULL;
        nou->stanga = NULL;
        *rad = nou;
    } else if(p.id < (*rad)->info.id) {
        inserareInBST(&(*rad)->stanga, p);
    } else {
        inserareInBST(&(*rad)->dreapta, p);
    }

    int difH = diferentaInaltimeSubarbori(*rad);

    if(difH == 2) {
        //dezechilibreu pe partea stanga
        if(diferentaInaltimeSubarbori((*rad)->stanga) == -1) {
            rotireLaStanga(&(*rad)->stanga);
        }
        rotireLaDreapta(rad);
    }

    if(difH == -2) {
        //dezechilibru pe partea dreapta
        if(diferentaInaltimeSubarbori((*rad)->dreapta) == 1) {
            rotireLaDreapta(&(*rad)->dreapta);
        }
        rotireLaStanga(rad);
    }
}

void inordine(Nod* rad) {
    if(rad) {
        inordine(rad->stanga);
        afisarePersoana(rad->info);
        inordine(rad->dreapta);
    }
}

void preordine(Nod* rad) {
    if(rad) {
        afisarePersoana(rad->info);
        preordine(rad->stanga);
        preordine(rad->dreapta);
    }
}

void postordine(Nod* rad) {
    if(rad) {
        postordine(rad->stanga);
        postordine(rad->dreapta);
        afisarePersoana(rad->info);
    }
}

Persoana cautareByID(Nod* rad, int id) {
    if(rad == NULL) {
        return initPersoana(-1, "", 0, 0);
    } else if(id == rad->info.id) {
        return initPersoana(rad->info.id, rad->info.nume, rad->info.varsta, rad->info.inaltime);
    } else if(id < rad->info.id) {
        return cautareByID(rad->stanga, id);
    } else {
        return cautareByID(rad->dreapta, id);
    }
}

void dezalocare(Nod** rad) {
    if(*rad) {
        dezalocare(&(*rad)->stanga);
        dezalocare(&(*rad)->dreapta);
        free((*rad)->info.nume);
        free(*rad);
    }
}

int main() {
    Nod* rad = NULL;
	inserareInBST(&rad, initPersoana(7, "Tudor", 20, 1.85));
	inserareInBST(&rad, initPersoana(5, "Vlad", 21, 1.80));
	inserareInBST(&rad, initPersoana(9, "Mihai", 22, 1.81));
	inserareInBST(&rad, initPersoana(3, "Ionut", 19, 1.82));
	inserareInBST(&rad, initPersoana(6, "Gabriel", 23, 1.83));
	inserareInBST(&rad, initPersoana(8, "Mihnea", 20, 1.79));
	inserareInBST(&rad, initPersoana(11, "Ana", 21, 1.80));
	inserareInBST(&rad, initPersoana(12, "Maria", 22, 1.70));
	inserareInBST(&rad, initPersoana(13, "Andreea", 20, 1.71));

    inordine(rad);

    Persoana persCautata = cautareByID(rad, 9);
    afisarePersoana(persCautata);
    free(persCautata.nume);
    printf("\nInaltime arbore: %d", calculInaltimeArbore(rad));

    dezalocare(&rad);

    return 0;
}