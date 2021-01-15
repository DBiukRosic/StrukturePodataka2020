#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 10

typedef struct cvor *ptr;
typedef struct cvor {
	int el;
	ptr left;
	ptr right;
} cvor;


ptr napravi_cvor(int);
void dodaj_cvor(ptr, int);
void ispis(ptr, int);
int is_number(char);
int input(void);
ptr find(ptr, int, int*);
int delete(ptr, int);


int main()
{
	int x, y = 0, z = 1, i = 0, del = 0;
	char c, in[100];
	ptr head, found;


	printf("\nEnter head val: ");
	while (!(x = input()))
		printf("Please enter a valid integer...\n");
	head = napravi_cvor(x);


	do {
		printf("\nA - Add element\tC - Clear terminal\tD - Delete element\nF - Find element    P - Print tree\tQ - quit\n\n");
		scanf(" %[^\n]", in);
		if (strlen(in) != 1) {
			printf("Invalid input...\n");
			continue;
		}
		c = tolower(in[0]);
		if (c == 'a') {
			printf("enter val: ");
			while (!(x = input()))
				printf("Please enter a valid integer...\n");
			dodaj_cvor(head, x);
		}
		else if (c == 'p')
			ispis(head, 0);
		else if (c == 'f') {
			printf("Enter element you would like to find: ");
			while (!(x = input()))
				printf("Please enter a valid integer...\n");
			found = find(head, x, &y);
			if (y)
				printf("Found %d under node: %d\n", x, found->el);
			else
				printf("Element not in tree\n");
		}
		else if (c == 'd') {
			printf("Enter element you would like to delete: ");
			while (!(x = input()))
				printf("Please enter a valid integer...\n");
			if ((del = delete(head, x)) == -1)
				printf("Don't delete head element while rest of tree is empty...\n");
			else if (del)
				printf("Element deleted\n");
			else
				printf("Element not in tree\n");
		}
		else if (c == 'c')
			system("clear");
		else if (c == 'q')
			z = 0;
		else
			printf("Invalid input...\n");
	} while (z);

	return 0;
}


ptr napravi_cvor(int x)
{
	ptr temp = malloc(sizeof(cvor));
	temp->el = x;
	temp->right = temp->left = NULL;
	return temp;
}


void dodaj_cvor(ptr head, int x)
{
	ptr new = napravi_cvor(x);
	ptr current = head;
	while (current != NULL) {
		if (new->el >= current->el) {
			if (current->right == NULL) {
				current->right = new;
				break;
			}
			current = current->right;
		}
		else {
			if (current->left == NULL) {
				current->left = new;
				break;
			}
			current = current->left;
		}
	}
}


void ispis(ptr current, int space)
{
	if (current == NULL)
		return;
	space += N;
	if (current->right != NULL)
		ispis(current->right, space);
	printf("\n");
	for (int i = N; i < space; i++)
		printf(" ");
	printf("%d\n", current->el);
	if (current->left != NULL)
		ispis(current->left, space);
}


int input()
{
	int x = 0, prev = 0;
	char *c = malloc(20);
	scanf(" %[^\n]", c);
	while (*c != '\n') {
		if ((x = is_number(*c)) && prev) {
			prev *= 10;
			prev += x;
		}
		else if (x)
			prev = x;
		else if (*c == '0')
			prev *= 10;
		else if (prev)
			return prev;
		else
			return 0;
		c++;
	}
	return 0;
}


int is_number(char x)
{
	return (x < 58 && x > 47) ? (x - 48) : 0;
}


ptr find(ptr current, int el, int *found)
{
	ptr parent = current;
	while (current != NULL) {
		if (el == current->el) {
			*found = 1;
			return parent;
		}
		else if (el < current->el) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}
	}
	*found = 0;
	return 0;
}


int delete(ptr current, int el)
{
	int x = 0;
	ptr delete = find(current, el, &x);
	ptr delete_free;
	if (el == current->el && (current->left == current->right))
		return -1;
	if (!x)
		return 0;
	if (delete->left != NULL && delete->right != NULL) {
		if (delete->left->el == el) {
			delete_free = delete->left;
			if (delete->left->right != NULL)
				delete->left = delete->left->right;
			else if (delete->left->left != NULL)
				delete->left = delete->left->left;
			else
				delete->left = NULL;
		}
		else if (delete->right->el == el) {
			delete_free = delete->right;
			if (delete->right->right != NULL)
				delete->right = delete->right->right;
			else if (delete->right->left != NULL)
				delete->right = delete->right->left;
			else
				delete->right = NULL;
		}
		else
			delete_free = current;
	}
	else if (delete->left == NULL) {
		delete_free = delete->right;
		if (delete->right->right != NULL)
			delete->right = delete->right->right;
		else if (delete->right->left != NULL)
			delete->right = delete->right->left;
		else
			delete->right = NULL;
	}
	else if (delete->right == NULL) {
		delete_free = delete->left;
		if (delete->left->right != NULL)
			delete->left = delete->right->right;
		else if (delete->left->left != NULL)
			delete->left = delete->right->left;
		else
			delete->left = NULL;
	}
	free(delete_free);
	return 1;
}