int global_b = 12;
int global_a;

int main()
{
	int  a = 0;
	char c[267] ;
	while ( 1 ) {
		a++;
		if (a > 2) break;
	}
	global_a += a;
	return 0;
}
