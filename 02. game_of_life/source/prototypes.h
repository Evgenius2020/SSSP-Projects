void compute_square(int* matrix, int* buf, int x, int y);
void compute_matrix(int* matrix, int height, int width, int threads);
int part_reduce(int* mass, int length);
int parts_reduce(int* results, int length);
int total_reduce(int* matrix, int height, int width, int threads);
void life_run(int* matrix, int height, int width, int threads);