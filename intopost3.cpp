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
	if(c == '+' || c ==  '-' || c == '*' || c == '/' || c == '^' || c == '!' || c ==  '(' || c == ')') return false;
	 return true;
}
bool isBalanced(char exp[]) {
	int i;
	Stack s;
	for(i = 0; exp[i] != '\0' ;i++) {
		if(exp[i] == '(') {
			s.push(exp[i]);
		}
		else if(exp[i] == ')') {
			if(s.isEmpty()) return false;
			s.pop();
		}
	}
	return s.isEmpty();
	}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int evaluatePostfix(char postfix[]) {
    Stack s;
    for (int i = 0; postfix[i] != '\0'; i++) {
        // If it's a number, convert char to int and push to stack
        if (isDigit(postfix[i])) {
            s.push(postfix[i] - '0'); 
        } 
        // If it's an operator, pop two elements and apply it
        else {
            int val2 = s.pop(); // Second operand (top of stack)
            int val1 = s.pop(); // First operand

            switch (postfix[i]) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.pop(); // The final remaining element is the answer
}
	
int prec(char c) {
	if(c == '^') return 3;
	if(c == '*' || c == '/') return 2;
	if(c == '+' || c == '-') return 1;
	return 0;	
}

char* inToPost(char infix[]) {
	int i = 0, j = 0;
	char* postfix = new char[strlen(infix) + 1];
	Stack s;
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
				s.pop();
			}
			i++;
		}
		else {
			while(!s.isEmpty() && prec(infix[i]) <= prec(s.stackTop())) {
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
	char* postfix = inToPost(infix);
	
	for(size_t i = 0; i < strlen(postfix); i++) {
		cout << postfix[i];
	} 
	cout << endl;
	
	delete[] postfix;
	return 0;
}
