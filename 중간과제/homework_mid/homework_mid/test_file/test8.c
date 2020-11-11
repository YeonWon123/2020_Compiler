int fun(float *p, int** pp)
{
	return 1;
}

float (*arr[10]) (int *);

void main()
{
	int x;
	int i;
	float y;
	x = 1;
	y = 3.14;

	while(x<10) x = x + 1;
	for (i = 0; i < 10; i++)
		x = x + i;

	if (x > 10 && y < 5)
		x = 20;
	else
		x = 30;
	
	switch(x + 10)
	{
		case 1:
			x = 40;
			break;
		case 0:
			x = 60;
			break;
		default:
			x = 30;
			break;
	}
}
	
