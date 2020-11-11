void swap(int* a, int* b);
int main()
{
	int a = 3;
	int b = 4;
	float c = 3.14;
	b++;
	swap(a,b);
	return 0;
}

void swap(int* a, int* b) {
	int temp = a;
	a = b;
	b = temp;
}


