//
//  main.cpp
//  stack using array
//
//  Created by Haider Ali on 10/7/19.
//  Copyright © 2019 Haider Ali. All rights reserved.
//

#include <iostream>
using namespace std;

class Stack {

private:
    char a[100];
    int t = -1;

public:
    bool isEmpty() {
        return t == -1;
    }
    bool isFull() {
        return t == 9;
    }
    void push(char x) {
        if(isFull()){
            cout<<"stack overflow";
            return;
        }
        t++;
        a[t] = x;
    }
    
    void pop(){
        if(isEmpty()) {
            cout<<"stack underflow";
            return;
        }
        t--;
    }
    
    char top(){
        if(isEmpty()) {
            return NULL;
        }
        return a[t];
    }
};

bool balanceBrackets(string str) {
    
    Stack *a = new Stack();
    long int len = str.length();

    for(int i=0; i<len; i++) {
        
        if(str[i] == '{' || str[i] == '[' || str[i] == '('){
            a->push(str[i]);
        }
        else if(str[i] == '}') {
            if(a->top() == '{') {
                a->pop();
            }
            else return false;
        }
        else if(str[i] == ']') {
            if(a->top() == '[') {
                a->pop();
            }
            else return false;
        }
        else if(str[i] == ')') {
            if(a->top() == '(') {
                a->pop();
            }
            else return false;
        }
        
    }
    return a->isEmpty() ? true : false;
}

void infixToPostfix(string str1) {
    
    if (!balanceBrackets(str1)) {
        cout<<"wrong expression";
        return;
    }
    
    Stack *stack = new Stack();
    char str2[100];
    long int length = str1.length();
    int index = -1;
    
    for(int i=0; i<length; i++) {
        
        if(str1[i] == '{' || str1[i] == '[' || str1[i] == '(') {
            stack->push(str1[i]);
            continue;
        }
        else if(str1[i] == '}' || str1[i] == ']' || str1[i] == ')') {
            while (stack->top() != '{' && stack->top() != '[' && stack->top() != '(') {
                index++;
                str2[index] = stack->top();
                stack->pop();
            }
            stack->pop();
            continue;
        }
        
        if(str1[i] == '^' || str1[i] == '/' || str1[i] == '*' || str1[i] == '+' || str1[i] == '-'){
            
            if(stack->isEmpty()) {
                stack->push(str1[i]);
            }
            else {
                if(stack->top() == '^'){
                    if (str1[i] == '/' || str1[i] == '*' || str1[i] == '+' || str1[i] == '-'){
                        index++;
                        str2[index] = stack->top();
                        stack->pop();
                        stack->push(str1[i]);
                    }
                    else if(str1[i] == '^'){
                        index++;
                        str2[index] = str1[i];
                    }
                }
                else if(stack->top() == '/' || stack->top() == '*') {
                    if (str1[i] == '+' || str1[i] == '-') {
                        index++;
                        str2[index] = stack->top();
                        stack->pop();
                        stack->push(str1[i]);
                    }
                    else if(str1[i] == '^'){
                        stack->push(str1[i]);
                    }
                    else if(str1[i] == '/' || str1[i] == '*') {
                        index++;
                        str2[index] = str1[i];
                    }
                }
                else if(stack->top() == '+' || stack->top() == '-') {
                    if (str1[i] == '^' || str1[i] == '/' || str1[i] == '*') {
                        stack->push(str1[i]);
                    }
                    else if(str1[i] == '+' || str1[i] == '-'){
                        index++;
                        str2[index] = str1[i];
                    }
                }
                else if(stack->top() == '{' || stack->top() == '[' || stack->top() == '(') {
                    stack->push(str1[i]);
                }
            }
        }
        else {
            if (str1[i] != 32) {
                index++;
                str2[index] = str1[i];
            }
        }
    }
    while(!stack->isEmpty()) {
        index++;
        str2[index] = stack->top();
        stack->pop();
    }
    
    
    
    //##########################################
    //update length
    
    float a;
    float b;
    float c = 0;
    
    for(int i=0; i<=index; i++) {
       
        if (!stack->isEmpty() && (str2[i] == '^' || str2[i] == '/' || str2[i] == '*' || str2[i] == '+' || str2[i] == '-')) {
        
            b = stack->top() ;
            stack->pop();
            a = stack->top() ;
            stack->pop();
            
            switch (str2[i]) {
                case '+':
                    c = a+b;
                    break;
                case '-':
                    c = a-b;
                    break;
                case '*':
                    c = a*b;
                    break;
                case '/':
                    c = a/b;
                    break;
                case '^':
                    int b = int(a);
                    int p = int(b);
                    c = b^p;
                    break;
            }
            stack->push(c);
        }
        else{
            // This is due to we use charactor value so it will balanced over double value;
             stack->push(str2[i]-48);
        }
    }
    a = stack->top();
    stack->pop();
    cout<<a<<endl;
    cout<<str2;
}

int main() {
   
    infixToPostfix("2+    (2+3)+ (3)");
    
}
