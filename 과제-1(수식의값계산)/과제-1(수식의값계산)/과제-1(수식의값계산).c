#include <stdio.h>
enum {NULLS, PLUS, STAR, NUMBER, LPAREN, RPAREN, POINT, END} token;

void get_token();
void error(int i);
double factor();
double term();
double expression();

int sw = 0; // 실수형이 등장할 경우 sw = 1;
int num;
double f_num;
char ch = ' ';
void get_token() {
	ch = getchar();	

	// next token --> token
	if (ch >= '0' && ch <= '9') {
		token = NUMBER;
	}
	else if (ch == '+') {
		token = PLUS;
	}
	else if (ch == '*') {
		token = STAR;
	}
	else if (ch == '(') {
		token = LPAREN;
	}
	else if (ch == ')') {
		token = RPAREN;
	}
	else if (ch == EOF || ch == '\n') {
		token = END;
	}
	else if (ch == '.') {
		token = POINT;
		sw = 1;
	}
	else {
		token = NULLS;
	}

	// number value --> num
	if (token == NUMBER) {
		num = (int)(ch - '0');
	}
}

double expression() {
	double result;
	result = term();
	while (token == PLUS) {
		get_token();
		result = result + term();
	}
	return (result);
}

double term() {
	double result;
	result = factor();
	while (token == STAR) {
		get_token();
		result = result * factor();
	}
	return (result);
}

double factor() {
	double result = 0;
	int sw1 = 1;
	if (token == NUMBER) {
		while (token == NUMBER) {
			result *= 10;
			result += num;
			get_token();
		}

		if (token == POINT) {
			get_token();
			if (token != NUMBER) {
				error(4);
			}
			while (token == NUMBER) {
				f_num = num;
				for (int i = 0; i < sw1; i++) {
					f_num /= 10;
				}
				result += f_num;
				sw1++;
				get_token();
			}
		}

	}
	else if (token == LPAREN) {
		get_token();
		result = expression();
		if (token == RPAREN) {
			get_token();
		}
		else {
			error(2);
		}
	}
	else error(1);
	return (result);
}

void error(int i) {
	switch (i) {
	case 1: printf("error: number or '(' expected\n"); break;
	case 2: printf("error: ')' expected\n"); break;
	case 3: printf("error: EOF expected\n"); break;
	case 4: printf("error: number expected\n"); break;
	}
	exit(1);
}

void main(void)
{
	double result;
	get_token();
	result = expression();
	if (token != END) {
		error(3);
	}
	else {
		if (sw == 0)
			printf("%d\n", (int)result);
		else
			printf("%lf\n", result);
	}
}