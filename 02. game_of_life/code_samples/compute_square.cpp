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
