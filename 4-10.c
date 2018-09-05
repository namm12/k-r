#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

int getline(char[]);
char getop(char[], char[]);
void push(double);
double pop(void);
int line_i;

int main(){
	char type, s[MAXOP], num[MAXOP];
	double temp, temp2;
	extern int sp;

	while(getline(s)>0){
		line_i = 0;
		while((type=getop(s, num))!='\0'){
			switch(type){
			case NUMBER:
				push(atof(num));
				break;
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '-':
				temp = pop();
				push(pop()-temp);
				break;
			case '/':
				temp = pop();
				push(pop()/temp);
				break;
			case '%':
				temp =  pop();
				push((int) pop() % (int) temp);
				break;
			case 'p':		// prints the top element
				push(pop());
				break;
			case 'd':		// duplicates the top element
				temp = pop();
				push(temp);
				push(temp);
				break;
			case 's':		// swaps top two elements
				temp =  pop();
				temp2 = pop();
				push(temp);
				push(temp2);
				break;
			case 'c':		// clears the stack
				while(sp>0)
					pop();
				break;
			case '\n':
				printf("%g\n", pop());
				break;
			default:
				printf("error: unknown command\n");
				break;
			}
		}
	}

	return 0;
}

int getline(char s[]){
	char c;
	int i;

	for(i=0; i<MAXOP && (c=getchar())!=EOF && c!='\n'; i++){
		s[i] = c;
	}
	if(c=='\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

char getop(char s[], char num[]){
	int j = 0;

	while(s[line_i]==' ' || s[line_i]=='\t')	//- skips white spaces
		line_i++;								//- and tabs
	if(!isdigit(s[line_i]) && !isdigit(s[line_i+1])){		//- two consecutive nondigits
		num[j] = '\0';										//- means special character,
		return s[line_i++];									//- therefore returned
	}
	while(isdigit(s[line_i]) || s[line_i]=='.' || s[line_i]=='-')		//- captures number, both positive
		num[j++] = s[line_i++];											//- and negative, both integer and float
	num[j] = '\0';

	return NUMBER;
}

#define MAXVAL 100

double val[MAXVAL];		// creates stack called val[]
int sp = 0;				// next free position in val[]

void push(double f){
	if(sp>=MAXVAL){
		printf("push(): cannot push, stack full\n");
		return;
	}
	else{
		val[sp++] = f;
	}
}

double pop(){
	if(sp>0){
		return val[--sp];
	}
	else{
		printf("pop(): cannot pop, stack empty\n");
		return 0.0;
	}
}
