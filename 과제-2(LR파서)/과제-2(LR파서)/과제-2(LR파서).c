#include <stdio.h>
#include <stdlib.h>

#define NUMBER 256
#define PLUS 257
#define STAR 258
#define LPAREN 259
#define RPAREN 260
#define END 261
#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define ACC 999

int action[12][6] = {
	{5,0,0,4,0,0}, {0,6,0,0,0,ACC}, {0,-2,7,0,-2,-2},
	{0,-4,-4,0,-4,-4}, {5,0,0,4,0,0}, {0,-6,-6,0,-6,-6},
	{5,0,0,4,0,0}, {5,0,0,4,0,0}, {0,6,0,0,11,0},
	{0,-1,7,0,-1,-1}, {0,-3,-3,0,-3,-3},{0,-5,-5,0,-5,-5}
};

int go_to[12][3] = {
	{1,2,3}, {0,0,0}, {0,0,0}, {0,0,0}, {8,2,3}, {0,0,0},
	{0,9,3}, {0,0,10}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}
};

int prod_left[7] = { 0, EXPRESSION, EXPRESSION, TERM, TERM, FACTOR, FACTOR };
int prod_length[7] = { 0,3,1,3,1,3,1 };

int stack[1000];
int top = -1;
int sym;
int status = -1; // ������ ���¸� ��Ÿ���� ��������
				// -1: ���ۻ���, 0: ������ ����, 1: �Ǽ��� ����, 2: ȥ������
				// ȥ�������� ��� ���� ó���� ������ �Ǽ��� �� �� ������ ���� ��� ǥ���Ѵ�.

double value[1000];
char yytext[32];
double yylval;

void push(int);
void reduce(int);
void yyerror();
void lex_error();
int yylex();
int yyparse();
void shifts(int);

void main() {
	yyparse();
	if (status == 0) {
		printf("���� ��� : %d\n", (int)value[1]);
	}
	else {
		printf("���� ��� : %lf\n", value[1]);
	}
}

int yyparse() {
	int i;
	stack[++top] = 0; // initial state
	sym = yylex();
	do {
		i = action[stack[top]][sym - 256]; // get relation
		if (i == ACC)
			printf("success !\n");
		else if (i > 0)	// shift
			shifts(i);
		else if (i < 0) // reduce
			reduce(-i);
		else
			yyerror();
	} while (i != ACC);
}

void push(int i) {
	top++;
	stack[top] = i;
}

void shifts(int i) {
	push(i);
	value[top] = yylval;
	sym = yylex();
}

void reduce(int i) {
	int old_top;
	top -= prod_length[i];
	old_top = top;
	push(go_to[stack[old_top]][prod_left[i]]);

	switch (i) { // ���� ��Ģ��ȣ�� ���� ���� �� ���
		case 1: value[top] = value[old_top + 1] + value[old_top + 3];
			break;
		case 2: value[top] = value[old_top + 1];
			break;
		case 3: value[top] = value[old_top + 1] * value[old_top + 3];
			break;
		case 4: value[top] = value[old_top + 1];
			break;
		case 5: value[top] = value[old_top + 2];
			break;
		case 6: value[top] = value[old_top + 1];
			break;
		default: yyerror("parsing table error");
			break;
	}
}

void yyerror() {
	printf("syntax error\n");
	exit(1);
}

int yylex() {
	static char ch = ' ';
	int i = 0;
	int sw = 0; // 0�̸� ����, 1�̸� �Ǽ�
	while (ch == ' ' || ch == '\t') ch = getchar();
	if (isdigit(ch)) {
		do {
			yytext[i++] = ch;
			ch = getchar();
		} while (isdigit(ch));

		// �Ǽ���
		if (ch == '.') {
			int p = -1;
			do {
				yytext[i++] = ch;
				ch = getchar();
				p++;
			} while (isdigit(ch));
			if (p == 0) {
				lex_error();
			}
			sw = 1;
		}

		yytext[i] = 0;
		if (sw == 0) {
			yylval = atoi(yytext);
			if (status == -1) {
				status = 0;
			}
			else if (status == 1) {
				printf("���� ��ġ���� ������ �Ǽ��� ȥ�յǾ� ������ �����߽��ϴ�!\n��ġ: %s\n", yytext);
				status = 2;
			}
		}
		else if (sw == 1) {
			yylval = atof(yytext);
			if (status == -1) {
				status = 1;
			}
			else if (status == 0) {
				printf("���� ��ġ���� ������ �Ǽ��� ȥ�յǾ� ������ �����߽��ϴ�!\n��ġ: %s\n", yytext);
				status = 2;
			}
		}
		return (NUMBER);
	}
	else if (ch == '+') {
		ch = getchar();
		return (PLUS);
	}
	else if (ch == '*') {
		ch = getchar();
		return (STAR);
	}
	else if (ch == '(') {
		ch = getchar();
		return (LPAREN);
	}
	else if (ch == ')') {
		ch = getchar();
		return (RPAREN);
	}
	else if (ch == '\n') {
		return (END);
	}
	else
		lex_error();
}

void lex_error() {
	printf("illegal token\n");
	exit(1);
}