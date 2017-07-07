#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Wrong number of arguments\n");
		return 0;
	}
	FILE* in1 = fopen (argv[1], "r");
	FILE* in2 = fopen (argv[2], "r");
	if (!in1 || !in2) {
		printf("I/O Failure!\n");
		return 1;
	}
	short curr1, curr2;
	while(1) {
		curr1 = fgetc(in1);
		curr2 = fgetc(in2);
		if ((curr1 == EOF) && (curr2 == EOF)) {
			printf("Files are matches!\n");
			return 1;
		}
		if (curr1 != curr2) {	
			printf("Files are different!\n");
			return 0;
		}
	}
}

