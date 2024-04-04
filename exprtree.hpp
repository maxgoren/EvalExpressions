/*
MIT License

Copyright (c) 2023 Max Goren, maxgoren@gmail.com http://www.maxgcoding.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef exprtree_hpp
#define exprtree_hpp
#include <cmath>
#include <vector>
#include "stack.hpp"
#include "lex.hpp"
using namespace std;

struct node {
    Token token;
    node* left;
    node* right;
    node(Token tok) : token(tok), left(nullptr), right(nullptr) { }
};

//builds expression tree from a postfix expression
node* buildTree(vector<Token> tokens) {
    stack<node*> sf;
    for (int i = 0; i < tokens.size(); i++) {
        Token c = tokens[i];
        if (c.type == 1) {
            node* x = new node(c);
            x->right = sf.pop();
            x->left = sf.pop();
            sf.push(x);
            cout<<"Push: "<<sf.top()->token.op<<endl;
        } else
        if (c.type == 0) {
            sf.push(new node(c));
            cout<<"Push: "<<c.num<<endl;
            continue;
        }
    }
    return sf.top();
}

double eval(node* x) {
    if (x == nullptr)
        return 0;
    if (x->token.type == 0)
        return x->token.num;
    if (x->token.type == 1) {
        double lhs = eval(x->left);
        double rhs = eval(x->right);
        switch (x->token.op) {
            case '^': return pow(lhs, rhs);
            case '*': return lhs*rhs;
            case '/': 
                if (rhs == 0) {
                    cout<<"Error: divide by zero."<<endl;
                } else 
                    return lhs/rhs;
            case '+': return lhs+rhs;
            case '-': return lhs-rhs;
            default:
            break;
        }
    }
    return 0;
}


int d = 0;
void dfs(node* h) {
    d++;
    if (h != nullptr) {
        dfs(h->left);
        for (int i = 0; i < d; i++) cout<<"  ";
        if (h->token.type == 0) {
            cout<<h->token.num<<endl;
        } else {
            cout<<h->token.op<<endl;
        }    
        dfs(h->right);
    }
    d--;
}

#endif