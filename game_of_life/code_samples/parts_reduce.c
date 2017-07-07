int parts_reduce(int* results, int length) {
	int res = 0;
	for (int i = 0; i < length; i++) {
		res += results[i];
	}
	return res;
}