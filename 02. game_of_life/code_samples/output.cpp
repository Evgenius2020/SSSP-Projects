
int F(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int sum = 0;
	if(a!=0) sum++;
	if(b!=0) sum++;
	if(c!=0) sum++;
	if(d!=0) sum++;
	if(e!=0) sum++;
	if(f!=0) sum++;
	if(g!=0) sum++;
	if(h!=0) sum++;
	if(sum>=3) return 1;
	return 0;
}


void compute_square(int *matrix, int *buf, int x, int y, int m, int n)
{
	int rez=0;
	int a, b, c, d, e, f, g ,h;

	if((y==0)||(x==0)) a=0; else a=matrix[(x-1)*n+y-1];
	if(x==0) b=0; else b=matrix[(x-1)*n+y];
	if((y==n-1)||(x==0)) c=0; else c=matrix[(x-1)*n+y+1];

	if((y==0)) d=0; else d=matrix[x*n+y-1];
	if((y==n-1)) e=0; else e=matrix[x*n+y+1];

	if((y==0)||(x==m-1)) f=0; else f=matrix[(x+1)*n+y-1];
	if(x==m-1) g=0; else g=matrix[(x+1)*n+y];
	if((y==n-1)||(x==m-1)) h=0; else h=matrix[(x+1)*n+y+1];
	rez=F(a, b, c, d, e, f, g ,h);
	buf[x*n+y]=rez;
}

void step(int *matrix, int m, int n)
{
	int *bufer = (int*)malloc(sizeof(int)*size*size);
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			compute_square(matrix, bufer, i, j, m, n);
	}
	for(int i = 0; i < size * size; i++) matrix[i]=bufer[i];
	free(bufer);
}
