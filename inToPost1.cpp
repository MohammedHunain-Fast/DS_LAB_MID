#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define MAX 15

class Stack {
	public:
	char arr[MAX];
	int top;
	Stack() : top(-1) {
	}
	
	void push(char data) {
		if(top == MAX - 1) return;
		arr[++top] = data;
	}
	char pop() {
		if(top == -1) return '\0';
		char val = arr[top];
		top--;
		return val;
	}
	
	bool isEmpty() {
		if(top == -1) {
			return true;
		}
		else return false;
	}
	char stackTop() {
		if(top == -1) return '\0';
		char val = arr[top];
		return val; 
	}
};

bool isOperand(char c) {
	if(c == '+' || c == '-' || c == '*' || c == '/') return false;
	else return true;
}

int pre(char c) {
	if(c == '+' || c == '-') return 1;
	else if(c == '*' || c == '/') return 2;
	else return 0;
}

char* infixToPostfix(char *infix) {
	Stack s;
	int i = 0, j = 0;
	char* postfix = new char[strlen(infix) + 1];
	while(infix[i] != '\0') {
		if(isOperand(infix[i])) postfix[j++] = infix[i++];
		else {
			while(!s.isEmpty() && pre(infix[i]) <= pre(s.stackTop())) {
				postfix[j++] = s.pop();
				}
			s.push(infix[i++]);
		}
	}
	while(!s.isEmpty()) {
		postfix[j++] = s.pop();
	}
	postfix[j] = '\0';
	
	return postfix;
}

int main() {
	char infix[] = "a/b+c";
	char* postfix = infixToPostfix(infix);
	for(size_t i = 0; i < strlen(postfix); i++) {
		cout << postfix[i];
	} 
	
	return 0;
}
