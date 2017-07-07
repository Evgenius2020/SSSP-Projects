int part_reduce(int* mass, int length);
int parts_reduce(int* results, int length);
int total_reduce(int* matrix, int height, int width);

void compute_element(int* matrix, int* buf, int x, int y, int height, int width);
void compute_matrix(int* matrix, int height, int width);

void life_run(int* matrix, int height, int width);