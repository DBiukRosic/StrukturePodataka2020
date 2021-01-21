#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)

typedef struct node *pok;
typedef struct stack *stack_pok;
typedef struct node {
	int num;
	char operand, operator;
	pok right, left;
}node;
typedef struct stack {
	pok address;
	stack_pok next;
}stack;

int infix_izraz(pok);
int ispis_stabla(pok, int);
int read_from_file(char**);
void ispis(stack_pok);
void push(pok, stack_pok);
pok pop(pok, stack_pok);
pok create_node(char, char, int);
pok create_tree(char*);

int main(void)
{
	pok root;

	char *dat = malloc(1024);
	strcpy(dat, "postfix.txt");

	if (!read_from_file(&dat)) {
		printf("Nema trazenog dokumenta. \n");
	}

	root = create_tree(dat);
	ispis_stabla(root, 0);
	infix_izraz(root);
	printf("\n");

	return 0;
}

int read_from_file(char **input)
{
	FILE *p = fopen(*input, "r");
	if (p == NULL)
		return 0;
	**input = '\0';
	fscanf(p, "%[^\n]", *input);
	fclose(p);
	return 1;
}

pok create_node(char oprand, char oprator, int num)
{
	pok cvor = malloc(sizeof(node));
	cvor->operand = oprand;
	cvor->operator = oprator;
	cvor->num = num;
	cvor->left = cvor->right = NULL;
	return cvor;
}

pok create_tree(char *input)
{
	stack stog;
	stog.next = NULL;
	stack_pok stog_pok = &stog;
	pok root;
	int i = 0, prev = 0, x = 0;
	while (input[i++] != '\0')
		if (input[i - 1] == ' ' && prev) {
			push(create_node('\0', '\0', x), stog_pok);
			prev = 0;
		}
		else if (isalpha(input[i - 1]))
			push(create_node(input[i - 1], '\0', 0), stog_pok);
		else if (isdigit(input[i - 1])) {
			if (!prev) {
				x = input[i - 1] - 48;
				prev = 1;
			}
			else {
				x *= 10;
				x += (input[i - 1] - 48);
			}
		}
		else if (input[i - 1] != ' ')
			root = pop(create_node('\0', input[i - 1], 0), stog_pok);
	return root;
}

void push(pok node, stack_pok stack)
{
	stack_pok temp = malloc(sizeof(stack));
	temp->address = node;
	temp->next = stack->next;
	stack->next = temp;
}

pok pop(pok cvor, stack_pok stack)
{
	int i = 0;
	stack_pok stack_free;

	cvor->right = stack->next->address;

	cvor->left = stack->next->next->address;

	while (i++ != 2) {
		stack_free = stack->next;
		stack->next = stack->next->next;
		free(stack_free);
	}
	stack_pok temp = malloc(sizeof(stack));
	temp->address = cvor;
	temp->next = stack->next;
	stack->next = temp;

	return cvor;
}

void ispis(stack_pok ptr)
{
	while (ptr->next != NULL) {
		if (ptr->next->address->operand != '\0')
			printf("%c\n", ptr->next->address->operand);
		else if (ptr->next->address->operator != '\0')
			printf("%c\n", ptr->next->address->operator);
		else
			printf("%d\n", ptr->next->address->num);
		ptr = ptr->next;
	}
}

int infix_izraz(pok current)
{
	if (current == NULL)
		return 1;
	if (current->left)
		infix_izraz(current->left);
	if (current->operand != '\0')
		printf("%c ", current->operand);
	else if (current->operator != '\0')
		printf("%c ", current->operator);
	else
		printf("%d ", current->num);
	if (current->right)
		infix_izraz(current->right);
	return 0;
}

int ispis_stabla(pok current, int space)
{
	if (current == NULL)
		return 0;
	space += 10;
	if (current->right != NULL)
		ispis_stabla(current->right, space);
	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	if (current->operand != '\0')
		printf("%c\n", current->operand);
	else if (current->operator != '\0')
		printf("%c\n", current->operator);
	else
		printf("%d\n", current->num);
	if (current->left != NULL)
		ispis_stabla(current->left, space);
	return 1;
}