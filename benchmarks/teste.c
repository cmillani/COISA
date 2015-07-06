int *c ;
int foo(int a, int *b)
{
	return (*b)*a;
}

int main()
{
	return foo(4,c);
}