#define CRT_SECURE_NO_WARNING
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct list *pok;
typedef struct list {
	int el;
	char oper;
	pok next;
}list;

void pop_stog(pok);
void pop_to_postfix(pok, pok, int);
void postfix(pok, pok, int);
void pop(pok, int);
void push_int(pok, int, int*);
void push_char(pok, int);
void push_end(pok, pok);
void reverse_print(pok);
void zagrade(pok, pok);
int izracun(pok, pok);
int racun(char, int, int);
int znak_operatora(int);
int znak_broja(int);
int ispis(pok);

int main(void)
{
	int c, a = 0, b = 0; 
	list stack1, stack2, postfixIzraz;
	stack1.next = NULL; 
	stack2.next = NULL; 
	postfixIzraz.next = NULL;

	FILE* fp = fopen("izraz.txt", "r+");

	while (!(feof(fp))) {
		c = fgetc(fp);
		if (znak_broja(c)) {
			push_int(&postfixIzraz, c - 48, &a); 
			a = 1;
		}
		else if (znak_operatora(c)) {
			a = 0;
			push_char(&stack1, c); 
			postfix(&postfixIzraz, &stack1, c); 
		}
		else
			a = 0;
	}

	push_end(&postfixIzraz, &stack1); 
	printf("\nPostfix izraz: ");
	reverse_print(postfixIzraz.next);
	printf("\n");

	printf("\nRezultat: %d\n", izracun(postfixIzraz.next, &stack2)); 
	fclose(fp);

	return 0;

}
void pop_stog(pok ptr)
{
	pok temp = ptr->next;
	ptr->next = ptr->next->next;
	free(temp);
}
int izracun(pok post, pok stog)
{
	int el = 0;
	pok temp, stog_p, p = post;
	if (p == NULL)
		return el;
	izracun(p->next, stog);
	if (p->oper == '\0') {
		temp = malloc(sizeof(list));
		temp->el = p->el;
		temp->oper = '\0';
		temp->next = stog->next;
		stog->next = temp;
	}
	else {
		if (stog->next != NULL) {
			stog_p = stog->next;
			if (stog_p->next != NULL) {
				el = racun(p->oper, stog->next->el, stog->next->next->el);
				stog->next->next->el = el;
				pop_stog(stog);
			}
			else
				return el;
		}
		else
			return el;
	}
	return el;
}
void reverse_print(pok p)
{
	if (p == NULL)
		return;
	reverse_print(p->next);
	if (p->oper != '\0')
		printf("%c  ", p->oper);
	else
		printf("%d ", p->el);
}
int racun(char c, int y, int x)
{
	switch (c) {
	case '*':
		return(x*y);
		break;
	case '/':
		return(x / y);
		break;
	case '+':
		return(x + y);
		break;
	case '-':
		return(x - y);
		break;
	default:
		return -1;
	}
}
void postfix(pok post, pok stack, int x)
{
	pok temp = stack->next;
	if (temp->next == NULL)
		return;
	int el = temp->el;
	if (el == 3) {
		zagrade(stack, post);
		return;
	}
	else if (el == 2)
		return;

	while (temp->next != NULL) {
		if (el <= temp->next->el && temp->next->el < 2)
			pop_to_postfix(post, stack, temp->next->oper);
		else
			return;
		temp = temp->next;
	}
}
void zagrade(pok stack, pok post)
{
	pok temp, stack_free;
	pok head_free = stack->next;
	stack->next = stack->next->next;
	free(head_free);
	while (stack->next->el != 2) {
		temp = (pok)malloc(sizeof(list));
		temp->next = post->next;
		post->next = temp;
		temp->oper = stack->next->oper;
		temp->el = 0;

		stack_free = stack->next;
		stack->next = stack->next->next;
		free(stack_free);
	}
	stack_free = stack->next;
	stack->next = stack->next->next;
	free(stack_free);
}
void pop_to_postfix(pok post, pok stack, int x)
{
	pok temp = malloc(sizeof(list));
	temp->oper = x;
	temp->next = post->next;
	post->next = temp;
	pok temp_free = stack->next;
	temp_free->next->oper = temp_free->oper;
	temp_free->next->el = temp_free->el;
	stack->next = temp_free->next;
	free(temp_free);
}
int ispis(pok p)
{
	if (p->next == NULL)
		return 0;
	while (p->next != NULL) {
		if (p->next->oper != '\0')
			printf("%c ", p->next->oper);
		else
			printf("%d ", p->next->el);
		p = p->next;
	}
	printf("\n");
	return 0;
}
int znak_broja(int x)
{
	return (x < 58 && x > 47) ? 1 : 0;
}
int znak_operatora(int c)
{
	return ((c < 48 && c > 39 && c != 44 && c != 46) || (c == 92)) ? 1 : 0;
}
void push_int(pok p, int x, int *y)
{
	if (*y) {
		p->next->el = (p->next->el * 10) + x;
	}
	else {
		pok temp = malloc(sizeof(list));
		temp->next = p->next;
		p->next = temp;
		temp->el = x;
		temp->oper = '\0';
	}
}
void push_char(pok p, int x)
{
	pok temp = malloc(sizeof(list));
	temp->next = p->next;
	p->next = temp;
	temp->oper = x;
	if (x == 43 || x == 45)
		temp->el = 0;
	else if (x == 42 || x == 47)
		temp->el = 1;
	else if (x == 40)
		temp->el = 2;
	else if (x == 41)
		temp->el = 3;
	else
		printf("ERROR\n");
}
void pop(pok p, int x)
{
	pok temp, temp_free;
	temp_free = p->next;
	temp = p->next->next;
	temp->el += temp_free->el;
	free(temp_free);
}
void push_end(pok post, pok stack)
{
	pok temp_free = NULL;
	while (stack->next != NULL) {
		pok temp = malloc(sizeof(list));
		temp->oper = stack->next->oper;
		temp->next = post->next;
		post->next = temp;
		stack = stack->next;
		if (temp_free != NULL)
			free(temp_free);
		temp_free = stack;
	}
}