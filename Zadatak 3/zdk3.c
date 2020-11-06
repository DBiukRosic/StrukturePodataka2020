#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 256

struct person;
typedef struct person* Position;
typedef struct person {
	char ime[M];
	char prezime[M];
	int godina;
	Position next;
}Person;

Position noviStudent(char*, char*, int);
void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
Position pronalazak(Position, char*);
Position pronalazakPret(Position, char*);
void brisi(Position, char*);

void dodaj_posli(Position, Position);
void dodaj_prije(Position, Position, Position);
void sortirja(Position);
Position procitaj(char*);
void ispisi_file(Position, char*);
void sortiraj_listu(Position);
Position upisi_iz_filea(char*, int);
int broj_linija(char*);


int main() {
	Position head = (Position)malloc(sizeof(Person));
	head->next = NULL;


	Position s1 = noviStudent("Denis", "Tenis", 2001);
	Position s2 = noviStudent("Spomenka", "Bovan", 1950);
	Position s3 = noviStudent("Duje", "Senta", 2000);
	Position s4 = noviStudent("Ivan", "Skalic", 1991);

	unosPocetak(head, s1);
	unosKraj(head, s2);
	dodaj_prije(head, s3, s2);


	Ispis(head);

	ispisi_file(head, "test.txt");

	int linije = broj_linija("test2.txt");
	printf("Broj linija %d \n", linije);

	Position head2 = upisi_iz_filea("test2.txt", linije);
	printf("\n\n\n");
	Ispis(head2);
	printf("\n\n\n");

	sortiraj_listu(head2);
	Ispis(head2);

	return 0;
}

Position noviStudent(char* Ime, char* Prezime, int god)
{
	Position p;

	p = (Position)malloc(sizeof(struct person));

	p->godina = god;
	strcpy(p->ime, Ime);
	strcpy(p->prezime, Prezime);
	p->next = NULL;

	return p;
}

void Ispis(Position head)
{
	Position p = NULL;

	printf("ISPIS LISTE: \n\n");
	for (p = head->next; p != NULL; p = p->next) {
		printf("\t %s %s %d \n", p->ime, p->prezime, p->godina);
	}
	printf("\r\n");
}

void unosPocetak(Position head, Position p)
{
	p->next = head->next;
	head->next = p;
}

void unosKraj(Position q, Position p)
{
	while (q->next != NULL) {
		q = q->next;
	}
	unosPocetak(q, p);
}

Position pronalazak(Position q, char* prez) {
	while (q->next != NULL && strcmp(q->prezime, prez))
		q = q->next;
	return q;
}

Position pronalazakPret(Position p, char* prezimee) {
	Position pret = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->prezime, prezimee)) {
		pret = p;
		p = p->next;
	}
	if (p == NULL) {
		printf("ne postoji!\n");
		return NULL;
	}
	return pret;
}

void brisi(Position p, char* prezimee) {
	Position prev;
	prev = pronalazakPret(p, prezimee);

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}



void dodaj_posli(Position new, Position where) {
	Position temp = where->next;
	where->next = new;
	new->next = temp;
}


void dodaj_prije(Position head, Position new, Position where) {
	Position prethodni = pronalazakPret(head, where->prezime);

	prethodni->next = new;
	new->next = where;
}


void ispisi_file(Position head, char* filename) {
	FILE* file = fopen(filename, "w");

	Position p = NULL;

	for (p = head->next; p != NULL; p = p->next) {
		fprintf(file, "%s %s %d \n", p->ime, p->prezime, p->godina);
	}

	fclose(file);
}


Position upisi_iz_filea(char* filename, int linije) {
	FILE* file = fopen(filename, "r");
	int i;

	Position head = (Position)malloc(sizeof(Person));
	head->next = NULL;

	char ime[M], prezime[M];
	int godina;

	for (i = 0; i < linije; i++) {
		fscanf(file, "%s %s %d", ime, prezime, &godina);

		Position new = noviStudent(ime, prezime, godina);
		unosKraj(head, new);
	}

	fclose(file);

	return head;
}


int broj_linija(char* filename) {
	FILE* file = fopen(filename, "r");
	char slovo;
	int brojac = 0;

	while (!feof(file)) {
		slovo = fgetc(file);

		if (slovo == '\n') {
			brojac += 1;
		}
	}

	fclose(file);

	return brojac;

}


void sortiraj_listu(Position head) {
	Position temp1, temp2, swap1, swap2;


	for (temp1 = head->next; temp1 != NULL; temp1 = temp1->next) {
		for (temp2 = head->next; temp2->next != NULL; temp2 = temp2->next) {

			char* p1_val = temp2->prezime;
			char* p2_val = temp2->next->prezime;

			if (strcmp(p1_val, p2_val) > 0) {
				swap1 = temp2;
				swap2 = temp2->next;

				Position prethodni = pronalazakPret(head, swap1->prezime);

				prethodni->next = swap2;
				Position temp_swap = swap2->next;
				swap2->next = swap1;
				swap1->next = temp_swap;
				break;
			}
		}
	}
}