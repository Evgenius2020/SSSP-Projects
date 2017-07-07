int compute_square(int *matrix, int *buf, int x, int y, int width, int height)
{
	int dirx[8] = { 0,  1,  1,  1,  0, -1, -1,  -1 };
	int diry[8] = { -1, -1,  0,  1,  1,  1,  0,  -1 };
	int neighbours = 0;
	for (int i = 0; i < 8; i++) {
		int neighbourX = x + dirx[i];
		int neighbourY = y + diry[i];
		if ((neighbourX >= 0) && (neighbourX < width) 
			&& (neighbourY >= 0) && (neighbourY < height)) {
			if (matrix[neighbourY * width + neighbourX]) {
				neighbours++;
			}
		}
	}
	return (neighbours >= 3) ? 1 : 0;
}
