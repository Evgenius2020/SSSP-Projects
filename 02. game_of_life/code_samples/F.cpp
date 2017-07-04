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
