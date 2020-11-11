#include <stdio.h>
#include <stdlib.h>
#include "type.h"
extern int syntax_err;
extern A_NODE *root;
FILE *fout;
void initialize();
void print_ast();

void main(int argc, char *argv[])
{
	if ((fout=fopen(argv[argc-1], "r"))==NULL) {
		printf("can not open input file: %s\n", argv[argc-1]);
		exit(1);
	}
	initialize();
	yyparse();
	if (syntax_err) 
		exit(1);
	print_ast(root);
	exit(0);
}
