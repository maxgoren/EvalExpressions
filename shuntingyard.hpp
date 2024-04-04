#ifndef shuntingyard_hpp
#define shuntingyard_hpp
#include <iostream>
#include <vector>
#include "stack.hpp"
using namespace std;

bool leftAssociate(char c) {
    switch (c) {
        case '^': return false;
        case '*': return true;
        case '/': return true;
        case '+': return true;
        case '-': return true;
        default:
            break;
    }
    return false;
}

int precedence(char c) {
    switch (c) {
        case '^': return 7;
        case '*': return 5;
        case '/': return 5;
        case '+': return 3;
        case '-': return 3;
        default:
            break;
    }
    return 0; 
}

int cache = 0;

string shuntingYard(string expr) {
    stack<char> ops;
    string output;
    for (char c : expr) {
        if (c == '(') {
            ops.push(c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                if (precedence(c) < precedence(ops.top()) || 
                   (precedence(c) == precedence(ops.top()) && leftAssociate(c))) {
                    output.push_back(' ');
                    output.push_back(ops.pop());
                    output.push_back(' ');
                    ops.push(c);
                } else {
                    ops.push(c);
                    output.push_back(' ');
                }
        } else if (c == ')') {
            while (!ops.empty()) {
                if (ops.top() != '(') {
                    output.push_back(ops.pop());
                } else {
                    ops.pop();
                    break;
                }
            }
        } else if (c == 'M') {
            output += to_string(cache);
        } else {
            output.push_back(c);
        }
    }
    while (!ops.empty()) 
        if (ops.top() != '(')
            output.push_back(ops.pop());
        else ops.pop();
    return output;
}

double eval(vector<Token> codePage) {
    stack<double> es;
    for (int pc = 0; pc < codePage.size(); pc++) {
        Token token = codePage[pc];
        if (token.type == 0) {
            es.push(token.num);
        }
        if (token.type == 1) {
            char c = token.op;
            double rhs = es.pop();
            double lhs = es.pop();
            cout<<lhs<<" "<<c<<" "<<rhs<<endl;
            switch (c) {
                case '+': 
                    es.push(lhs+rhs); 
                    break;
                case '-': 
                    es.push(lhs-rhs); 
                    break;
                case '*': 
                    es.push(lhs*rhs); 
                    break;
                case '/': 
                    es.push(lhs/rhs); 
                    break;
                case '^': 
                    es.push(pow(lhs,rhs)); 
                    break;
                default:
                    break;
            }
        } 
    }
    return es.pop();
}


#endif