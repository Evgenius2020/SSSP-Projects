int squareCompute(int *matrix, int x, int y, int lineSize) {
	int dirx[8] = { 0,  1,  1,  1,  0, -1, -1,  -1 };
	int diry[8] = { -1, -1,  0,  1,  1,  1,  0,  -1 };
	int neighbours = 0;
	for (int i = 0; i < 8; i++) {
		int neighbourX = x + dirx[i];
		int neighbourY = y + diry[i];
		if ((neighbourX >= 0) && (neighbourX < lineSize)
			&& (neighbourY >= 0) && (neighbourY < lineSize)) {
			if (matrix[neighbourY * lineSize + neighbourX]) {
				neighbours++;
			}
		}
	}

	// Game specific.
	if (matrix[y * lineSize + x]) {
		return ((neighbours == 2) || (neighbours == 3)) ? 1 : 0;
	}
	else {
		return (neighbours == 3) ? 1 : 0;
	}
}