#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 64

typedef struct directory *ptr;
typedef struct directory {
	char name[M];
	ptr child;
	ptr next;
} directory;

typedef struct stack *stack_ptr;
typedef struct stack {
	ptr address;
	stack_ptr next;
} stack;

int Input(char*);
int make_dir(ptr, char*);
int make_child(ptr, char*);
int exists(ptr, char*);
int empty_dir(ptr);
int empty_stack(stack_ptr);
int print(ptr);
void print_stack(stack_ptr);
void push(stack_ptr, ptr);
ptr pop(stack_ptr);

int main()
{
	directory dir;
	dir.next = NULL; 
	dir.child = NULL; 
	strcpy(dir.name, "~");
	ptr current = &dir;
	stack stog; stog.next = NULL;
	char c[M], ime[M];
	int d = 1, i = 0, empty;

	do {
		if (strcmp(current->name, "~"))
			printf("\n%s: ", current->name);
		else
			printf("\n%s ", current->name);


		if (Input(c)) {
			Input(ime);
			empty = 0;
		}

		else {
			ime[0] = '\0';
			empty = 1;
		}

		if (!strcmp(c, "mkdir")) {
			if (empty)
				printf("\nDirectory must have a name\n");
			else if (empty_dir(current))
				make_child(current, ime);
			else if (exists(current, ime))
				printf("\nA directory with that name already exists in current directory\n");
			else
				make_dir(current, ime);
		}

		else if (!strcmp(c, "ls")) {
			if (empty_dir(current))
				printf("\nempty...\n");
			else
				print(current);
		}

		else if ((!strcmp(c, "cd")) && (!empty)) {
			if (!exists(current, ime))
				printf("\nNo such file or directory\n");
			else {
				push(&stog, current);
				current = current->child;
				while (strcmp(current->name, ime))
					current = current->next;
			}
		}

		else if ((!strcmp(c, "cd")) && empty) {
			if (empty_stack(&stog)) {
				printf("\nin head directory\n");
			}
			else
				current = pop(&stog);
		}

		else if ((!strcmp(c, "clear")) || (!strcmp(c, "c"))) {
			system("clear");
		}

		else if (!strcmp(c, "pwd")) {
			print_stack(&stog);
			printf("%s\n", current->name);
		}

		else if (!strcmp(c, "q"))
			d = 0;

		else
			printf("command not found\n");

	} while (d);

	return 0;
}

int Input(char* string)
{
	char c; int i = 0;
	while ((c = fgetc(stdin)) != '\n' && c != ' ') {
		string[i] = c;
		i++;
	}
	string[i] = '\0';
	if (c == '\n')
		i = 0;
	return i;
}
int make_child(ptr dir, char* ime)
{
	ptr kid = malloc(sizeof(directory));
	strcpy(kid->name, ime);
	kid->next = NULL;
	kid->child = NULL;
	dir->child = kid;
	return 0;
}

int make_dir(ptr root, char* ime)
{
	root = root->child;
	ptr dir = malloc(sizeof(directory));
	strcpy(dir->name, ime);
	dir->next = root->next;
	root->next = dir;
	dir->child = NULL;
	return 0;
}

int print(ptr p)
{
	ptr dir = p->child;
	while (dir != NULL) {
		printf("\n%s\n", dir->name);
		dir = dir->next;
	}
	return 0;
}

int exists(ptr ptr, char* ime)
{
	ptr = ptr->child;
	while (ptr != NULL) {
		if (!strcmp(ptr->name, ime))
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

int empty_dir(ptr ptr)
{
	if (ptr->child == NULL)
		return 1;
	return 0;
}

int empty_stack(stack_ptr ptr)
{
	return (ptr->next == NULL) ? 1 : 0;
}

void push(stack_ptr stack, ptr dir)
{
	stack_ptr temp = malloc(sizeof(stack));
	temp->address = dir;
	temp->next = stack->next;
	stack->next = temp;
}

ptr pop(stack_ptr stack)
{
	ptr dir = stack->next->address;
	stack_ptr stack_free = stack->next;
	stack->next = stack->next->next;
	free(stack_free);
	return dir;
}

void print_stack(stack_ptr ptr)
{
	if (ptr == NULL)
		return;
	print_stack(ptr->next);
	if (strlen(ptr->address->name))
		printf("%s/", ptr->address->name);
}