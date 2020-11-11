int a = 5;
char b = 'a';
char* c = "Compiler";

void print() {
	printf("%d %c %s\n", a, b, c);
}

int main()
{
	int i;

	for (i = 0; i < 5; i++) {
		print();
	}

	return 0;
}
