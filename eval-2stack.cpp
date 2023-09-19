#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct Stack : public stack<T> {
    T pop() {
        T ret = stack<T>::top();
        stack<T>::pop();
        return ret;
    }
};

int applyOper(char op, int a, int b) {
        switch (op) {
            case '+':
                cout<<a<<" + "<<b<<" = "<<(a +b )<<endl;
                return (a +b );
            case '*':
                cout<<a<<" * "<<b<<" = "<<(a * b)<<endl;
                return (a * b);
            case '/':
                cout<<a<<" / "<<b<<" = "<<(a / b)<<endl;
                return (a / b);
            case '-':
                cout<<a<<" - "<<b<<" = "<<(a - b)<<endl;
                return (a - b);
        }
    return 0;
}

void handleScope(Stack<char>& ops, Stack<int>& vals) {
    int a, b; char op;
    while (!ops.empty()) {
        b = vals.pop();
        a = vals.pop();
        op = ops.pop();
        vals.push(applyOper(op, a, b));
        cout<<"push: "<<vals.top()<<endl;
    }
}

//Dijkstra's two stack algorithm for evaluating
//infix expressions
int eval(string str) {
    cout<<"-----------------"<<endl;
    int x, a, b;
    char op;
    Stack<int> vals;
    Stack<char> ops;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(' || str[i] == ' ') {
            continue;
        } else if (str[i] == '+' || str[i] == '*' ||str[i] == '-' || str[i] == '/' ) { 
            //push valid operators to stack.
            cout<<"push: "<<str[i]<<endl;
            ops.push(str[i]);
        } else if (str[i] == ')') { 
            //replace expression in paren's with its value.
            b = vals.pop();
            a = vals.pop();
            vals.push(applyOper(ops.pop(), a, b));
        } else if (isdigit(str[i])) {
            //convert string to digit and push to value stack.
            int e = i;
            while (isdigit(str[++e]));
            x = atoi(str.substr(i, e).c_str());
            vals.push(x);
            cout<<"push: "<<x<<endl;
            i = e-1;
        } 
    }
    while (!ops.empty()) {
        b = vals.pop();
        a = vals.pop();
        op = ops.pop();
        vals.push(applyOper(op, a, b));
        cout<<"push: "<<vals.top()<<endl;
    }
    cout<<"answer: "<<vals.top()<<endl;
    return vals.pop();
}

int main() {
    cout<<eval("10 + 2 * 6")<<endl;
    cout<<eval("(10+2)*6")<<endl;
    cout<<eval("(100 * 2) + 12")<<endl;
    cout<<eval("((100/2)-(25/3))+85")<<endl;
}