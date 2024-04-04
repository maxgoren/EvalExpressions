#include <iostream>
#include <cmath>
#include <vector>
#include "stack.hpp"
#include "lex.hpp"
#include "exprtree.hpp"
#include "shuntingyard.hpp"
using namespace std;


int main(int argc, char* argv[]) {
    string input;
    while (true) {
        cout<<"calc> ";
        getline(cin, input);
        if (input == "exit")
            return 0;

        cout<<eval(buildTree(lex(shuntingYard(input))))<<endl;
        cout<<eval(lex(shuntingYard(input)))<<endl;
    }
    return 0;
}