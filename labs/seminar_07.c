#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
};

typedef struct Hashtable Hashtable;
struct Hashtable {
	Nod** vector;
	int size;
};

void inserareLaSfarsit(Nod** cap, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = NULL;
	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void afisareCarte(Carte carte) {
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

float pretMediuCarte(Nod* cap) {
	int nrCarti = 0;
	float sumaPreturi = 0;
	while (cap != NULL) {
		sumaPreturi += cap->info.pret;
		nrCarti++;
		cap = cap->next;
	}

	if (nrCarti != 0) {
		return sumaPreturi / nrCarti;
	}
	else {
		return 0;
	}
}

Carte initCarte(const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

Hashtable initTabela(int dim) {
	Hashtable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(dim * sizeof(Nod*));
	for (int i = 0; i < dim; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int nrPagini, int size) {

	return nrPagini % size;
}

//mecanismul de tratare a coliziunilor este chaining
void inserareInTabela(Hashtable table, Carte c) {
	if (table.size > 0) {
		int pozitie = hash(c.nrPagini, table.size);
		if (pozitie >= 0 && pozitie < table.size) {
			inserareLaSfarsit(&(table.vector[pozitie]), c);
		}

	}
}

//parcurgere tabela dispersie pentru mecanismul chain
void parcurgereTabela(Hashtable tabela) {
	for (int i = 0; i < tabela.size; i++) {
		printf("Pozitie: %d\n", i);
		afisareListaCarti(tabela.vector[i]);
	}
}

void dezalocareTabela(Hashtable tabela) {
	for (int i = 0; i < tabela.size; i++) {
		dezalocare(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

//sa calculam pretul mediu pentru toate cartile care au un numar de pagaini dat ca parametru (toate cartile care au 122 de pagini)
float pretMediu(Hashtable table, int nrPag) {
	int poz = hash(nrPag, 6);
	Nod* cap = table.vector[poz];
	int contor = 0;
	float suma = 0;
	while (cap!=NULL) {
		if (cap->info.nrPagini == nrPag) {
			suma += cap->info.pret;
			contor++;
		}
		cap = cap->next;
	}
	return suma / contor;
}

int main() {
	Hashtable tabela = initTabela(6);
	inserareInTabela(tabela, initCarte("Micul Print", 132, 35.2));
	inserareInTabela(tabela, initCarte("Nuntasii", 122, 46.9));
	inserareInTabela(tabela, initCarte("bonus!!", 122, 71.5));
	inserareInTabela(tabela, initCarte("Confess", 126, 34.3));
 	parcurgereTabela(tabela);
	
	printf("%f", pretMediu(tabela, 122));
	dezalocareTabela(tabela);

	return 0;
}