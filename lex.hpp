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
#ifndef lex_hpp
#define lex_hpp
#include <iostream>
#include <vector>
using namespace std;

struct Token {
    int type;
    union {
        double num;
        char op;
    };
    Token(double n) : type(0), num(n)  { }
    Token(char c) : type(1), op(c) { }
};

vector<Token> lex(string pfExpr) {
    vector<Token> tokens;
    for (int i = 0; i < pfExpr.size(); i++) {
        char c = pfExpr[i];
        if (isdigit(c)) {
            string num;
            do {
                num.push_back(c);
                c = pfExpr[++i];
            } while (i < pfExpr.size() && isdigit(c));
            tokens.push_back(Token(stof(num)));
            i--;
            continue;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
            tokens.push_back(Token(c));
    }
    return tokens;
}

#endif