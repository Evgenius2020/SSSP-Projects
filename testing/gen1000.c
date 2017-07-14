#include <stdio.h>

int main() {
	FILE* in = fopen("./build/in.txt", "w");
	for (int i = 0; i < 1000 * 1000; i++) {
		fprintf(in,"%d ",i % 2);
	}
	fclose(in);
}
