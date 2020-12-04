#define _CRT_SECURE_NO_WARNINGS
#pragma warning(4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD 256

typedef struct list *list_p;
typedef struct list {
	int broj;
	list_p next;
} list;

list read_file(list_p, char *);
list unija(list_p, list_p, list_p);
list presjek(list_p, list_p, list_p);
int sort(list_p);
int swap(list_p, list_p);
int combine(list_p);
int printlist(list_p);

int main(void)
{
	char dat_1[MAX_WORD] = "lista1.txt";
	char dat_2[MAX_WORD] = "lista2.txt";
	list l1, l2, uni, inter;
	l1.next = NULL, l2.next = NULL, uni.next = NULL, inter.next = NULL;

	read_file(&l1, dat_1);
	read_file(&l2, dat_2);

	inter = presjek(&l1, &l2, &inter);
	uni = unija(&l1, &l2, &uni);

	printf("\n Unija: \n");
	printlist(&uni);

	printf("\n Presjek: \n");
	printlist(&inter);

	return 0;
}
list read_file(list_p pok, char *dat)
{
	FILE *p = fopen(dat, "r");
	list_p temp;

	while (!feof(p)) {
		temp = (list_p)malloc(sizeof(list));
		fscanf(p, " %d", &temp->broj);
		temp->next = pok->next;
		pok->next = temp;
	}

	fclose(p);
	return *pok;
}
list unija(list_p l1, list_p l2, list_p unija)
{
	unija = l1;

	while (l1->next != NULL)
		l1 = l1->next;

	l1->next = l2->next;

	if (unija->next == NULL) {
		list_p temp = malloc(sizeof(list));
		temp->broj = 0;
		temp->next = unija->next;
		unija->next = temp;
	}

	sort(unija);
	combine(unija);
	return *unija;
}
list presjek(list_p l1, list_p l2, list_p presjek)
{
	list_p temp, l2_head = l2;

	while (l1->next != NULL) {
		while (l2->next != NULL) {
			if (l1->next->broj == l2->next->broj) {
				temp = (list_p)malloc(sizeof(list));
				temp->broj = l1->next->broj;
				temp->next = presjek->next;
				presjek->next = temp;
			}
			l2 = l2->next;
		}
		l1 = l1->next;
		l2 = l2_head;
	}

	if (presjek->next == NULL) {
		temp = (list_p)malloc(sizeof(list));
		temp->broj = 0;
		temp->next = presjek->next;
		presjek->next = temp;
	}

	sort(presjek);
	combine(presjek);
	return *presjek;
}
int sort(list_p sorted)
{
	list_p temp = malloc(sizeof(list));
	temp = sorted;
	list_p temp_head = temp;

	while (sorted->next != NULL) {
		while (temp->next != NULL) {
			if (sorted->next->broj < temp->next->broj)
				swap(temp->next, sorted->next);
			temp = temp->next;
		}
		temp = temp_head;
		sorted = sorted->next;
	}

	return 0;
}
int swap(list_p a, list_p b)
{
	int temp = 0;

	temp = a->broj;
	a->broj = b->broj;
	b->broj = temp;

	return 0;
}
int combine(list_p pok)
{
	pok = pok->next;
	list_p pok_free;

	while (pok->next != NULL) {
		if (pok->broj == pok->next->broj) {
			pok_free = pok->next;
			pok->next = pok->next->next;
			free(pok_free);
		}
		else
			pok = pok->next;
	}
	return 0;
}
int printlist(list_p pok)
{
	while (pok->next != NULL) {
		printf("%d\t", pok->next->broj);
		pok = pok->next;
	}
	printf("\n");

	return 0;
}