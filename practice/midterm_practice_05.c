#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Carte {
    int id;
    char* titlu;
    int nrPagini;
    float pret;
} Carte;

struct Nod {
    Carte info;
    Nod* stanga;
    Nod* dreapta;
};

Carte initCarte (int id, const char* titlu, int nrPagini, float pret) {
    Carte c;
    c.id = id;
    c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
    strcpy(c.titlu, titlu);
    c.nrPagini = nrPagini;
    c.pret = pret;

    return c;
}

void afisareCarte(Carte c) {
    printf("\n%d. Titlu: %s, Nr Pagini: %d, Pret: %.2f", c.id, c.titlu, c.nrPagini, c.pret);
}

void inserareInABC(Nod** radacina, Carte c) {
    if(*radacina == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->dreapta = NULL;
        nou->stanga = NULL;
        nou->info = c;
        *radacina = nou;
    } else if (c.id < (*radacina)->info.id) {
        inserareInABC(&(*radacina)->stanga, c);
    } else {
        inserareInABC(&(*radacina)->dreapta, c);
    }
}

void inordine(Nod* rad) {
    if(rad) {
        inordine(rad->stanga);
        afisareCarte(rad->info);
        inordine(rad->dreapta);
    }
}

void preordine(Nod* rad) {
    if(rad) {
        afisareCarte(rad->info);
        preordine(rad->stanga);
        preordine(rad->dreapta);
    }
}

void postordine(Nod* rad) {
    if(rad) {
    postordine(rad->stanga);
    postordine(rad->dreapta);
    afisareCarte(rad->info);
    }
}

Carte cautareDupaID(Nod* radacina, int id) {
    if (radacina == NULL) {
        return initCarte(-1, "Necunoscut", 0, 0);
    } else if(id == radacina->info.id) {
        return initCarte(radacina->info.id, radacina->info.titlu, radacina->info.nrPagini, radacina->info.pret);
    } else if (id < radacina->info.id) {
        return cautareDupaID(radacina->stanga, id);
    } else {
        return cautareDupaID(radacina->dreapta, id);
    }
}

void dezalocare(Nod** rad) {
    if(*rad) {
        dezalocare(&(*rad)->stanga);
        dezalocare(&(*rad)->dreapta);
        free((*rad)->info.titlu);
        free(*rad);
    }
}

int maxim(int a, int b) {
    return (a > b ? a : b);
}

int calculInaltimeArbore(Nod* rad) {
    if(rad) {
        return maxim(calculInaltimeArbore(rad->stanga), calculInaltimeArbore(rad->dreapta)) + 1;
    } else {
        return 0;
    }
}

void main() {
    Nod* rad = NULL;
    inserareInABC(&rad, initCarte(7, "Carte1", 100, 55));
    inserareInABC(&rad, initCarte(4, "Carte2", 100, 55));
    inserareInABC(&rad, initCarte(10, "Carte3", 100, 55));
    inserareInABC(&rad, initCarte(2, "Carte4", 100, 55));
    inserareInABC(&rad, initCarte(6, "Carte5", 100, 55));
    inserareInABC(&rad, initCarte(8, "Carte6", 100, 55));
    inserareInABC(&rad, initCarte(11, "Carte7", 100, 55));

    printf("Parcurgere inordine: \n");
    postordine(rad);

    Carte carteCautata = cautareDupaID(rad, 8);
    printf("Carte cautata: \n");
    afisareCarte(carteCautata);
    free(carteCautata.titlu);

    printf("\nInaltime arbore: %d", calculInaltimeArbore(rad));

    dezalocare(&rad);
}