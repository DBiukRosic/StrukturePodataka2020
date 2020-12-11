#define CRT_SECURE_NO_WARNING
#pragma warning(4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 10
#define MAX 100


typedef struct list *pok;
typedef struct list {
	int el;
	pok next;
}list;



void pushStog(int*, pok);
void pushRed(int*, pok);
int pop(pok);
int ispis(pok);
int random(void);

int main() {
	int br;
	int i;
	srand((unsigned int)time(NULL));
	list stack, red;
	stack.next = NULL;
	red.next = NULL;
	for (i = 0; i < 10; i++) {
		br = random();
		pushStog(&br, &stack);
		pushRed(&br, &red);
	}
	printf("Ispis stacka: \n");
	ispis(&stack);
	printf("Ispis reda: \n");
	ispis(&red);
	printf("Prvi element izbacen iz stacka: %d\n Prvi element izbacen iz reda: %d\n", pop(&stack), pop(&red));
	
	return 0;
}

int ispis(pok s)
{
	pok p = NULL;

	printf("\n");
	if (s->next == NULL) {
		return 0;
	}
	for (p = s->next; p != NULL; p = p->next) {
		printf("\t %d \n", p->el);
	}
	printf("\r\n");
}

int random(void) {
	int rnd;
	rnd = (MIN + (rand() / (RAND_MAX / (MAX - MIN + 1) + 1)));
	return rnd;
}

void pushStog(int *br, pok stack) {
	pok temp = malloc(sizeof(list));
	temp->el = *br;
	temp->next = stack->next;
	stack->next = temp;
}
void pushRed(int *br, pok p) {
	while (p->next != NULL) {
		p = p->next;
	}
	pok temp = malloc(sizeof(list));
	p->next = temp;
	temp->next = NULL;
	temp->el = *br;

}

int pop(pok p) {
	int br;
	if (p->next == NULL) {
		return -1;
	}
	pok temp = p->next;
	br = p->next->el;
	p->next = p->next->next;
	free(temp);
	return br;
}
