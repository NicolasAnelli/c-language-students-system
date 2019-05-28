/*
 * layout.h
 *
 *  Created on: Aug 18, 2018
 *      Author: nicolasanelli
 */

#ifndef LAYOUT_H_
#define LAYOUT_H_

#define WIDTH 80

char simbol = '*';

void filledLine();
void line(char *content, char align);
void emptyLine();
void clearScreen();


void filledLine() {
	for (int i = 0; i<WIDTH; i++){
		printf("%c", simbol);
	}
	printf("\n");
}
void line(char *content, char align) {
	int size;
	int rest = WIDTH - 1;
	int writed = 0;
	int aux = 0;
	int i;
	size = strlen(content);

	switch (align) {
		case 'L':
		default:
			printf("%c ", simbol);
			writed += 2;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("%c", simbol);
			break;
		case 'R':
			printf("=  ");
			writed += 3;
			aux = (WIDTH - 3) - (size + 2);
			for (i = 0; i < aux; i++) {
				printf(" ");
			}
			writed += aux;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("%c", simbol);
			break;
		case 'C':
			printf("%c  ", simbol);
			writed += 3;
			aux = ((WIDTH/2) - 3) - size/2;
			for (i = 0; i < aux; i++) {
				printf(" ");
			}
			writed += aux;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("%c", simbol);
			break;
	}
	printf("\n");
}
void emptyLine() {
	line("",'C');
}
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
#if defined(__unix__) || defined(__APPLE__) || defined(__linux__)
	printf("\e[1;1H\e[2J");
#endif
}

#endif /* LAYOUT_H_ */
