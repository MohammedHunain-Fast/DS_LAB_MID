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
		return top == -1;
	}
	char stackTop() {
		if(top == -1) return '\0';
		return arr[top]; 
	}
};

bool isOperand(char c) {
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') return false;
	return true;
}

int pre(char c) {
	if(c == '+' || c == '-') return 1;
	if(c == '*' || c == '/') return 2;
	if(c == '^') return 3;
	return 0; // '(' drops here, returning 0 precedence
}

char* infixToPostfix(char *infix) {
	Stack s;
	int i = 0, j = 0;
	char* postfix = new char[strlen(infix) + 1];
	
	while(infix[i] != '\0') {
		if(isOperand(infix[i])) {
			postfix[j++] = infix[i++];
		}
		else if(infix[i] == '(') {
			s.push(infix[i++]);
		}
		else if(infix[i] == ')') {
			while(!s.isEmpty() && s.stackTop() != '(') {
				postfix[j++] = s.pop();
			}
			if(s.stackTop() == '(') {
				s.pop(); // Pop out the opening bracket
			}
			i++; // FIX 1: Advance 'i' so it doesn't get stuck on ')' infinitely!
		}
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
	char infix[] = "a/(b+c)";
	char* postfix = infixToPostfix(infix);
	
	for(size_t i = 0; i < strlen(postfix); i++) {
		cout << postfix[i];
	} 
	cout << endl;
	
	delete[] postfix; // Clean up memory allocation
	return 0;
}
