int part_reduce(int* mass, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		if (mass[i]) {
			res++;
		}
	}

int parts_reduce(int* results, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		res += results[i];
	}

int total_reduce(int* matrix, int height, int width) {
	int* rez = (int*)malloc(sizeof(int)*height);
	for (int i = 0; i < height; i++) {
		rez[i] = part_reduce(matrix + (i * width), width);
	}
	return parts_reduce(rez, height);
}

