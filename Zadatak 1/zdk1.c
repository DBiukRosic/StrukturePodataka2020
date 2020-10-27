#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define UKUPNO_BODOVA 200

struct Student {
	char ime[50];
	char prezime[50];
	int rez;
};

typedef struct Student Student;

int get_lines_count() {
	FILE *file = fopen("studenti.txt", "r");

	if (file == NULL) {
		printf("Could not open file !");
		return 0;
	}

	char c_buffer;
	int line_counter = 0;
	while (!feof(file)) {
		c_buffer = fgetc(file);
		if (c_buffer == '\n') {
			line_counter += 1;
		}
	}

	rewind(file);
	return line_counter;
}


int read_students(int size, Student *studenti) {
	FILE *file = fopen("studenti.txt", "r");

	if (file == NULL) {
		printf("Could not open file !");
		return 1;
	}

	int i;

	for (i = 0; i < size; i++) {
		fscanf(
			file,
			"%s %s %d",
			studenti[i].ime,
			studenti[i].prezime,
			&studenti[i].rez
		);
	}

	fclose(file);

	return 0;
}


int main() {
	Student *studenti;
	int line_number;
	int i;


	line_number = get_lines_count();
	studenti = (Student *)malloc(sizeof(Student) * line_number);
	read_students(line_number, studenti);


	float rel_rez;

	printf("Ime\tPrezime\tPostotak\tBodovi\n");
	for (i = 0; i < line_number; i++) {
		rel_rez = (float)studenti[i].rez / (float)UKUPNO_BODOVA;
		printf(
			"%s\t%s\t%.2f\t%d\n",
			studenti[i].ime,
			studenti[i].prezime,
			rel_rez * 100,
			studenti[i].rez
		);
	}

	return 0;
}