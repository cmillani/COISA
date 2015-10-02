char c = 'c';
char ah = 'a';
int main()
{
	register int a = 0;
	while (a < 20)
	{
		if (ah == c) ah++;
		ah++;
	}
	if (c == 'a') return 0;
	return 1;
}