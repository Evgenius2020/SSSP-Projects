int partReduce(int* data, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		if (data[i]) {
			res++;
		}
	}
	return res;
}