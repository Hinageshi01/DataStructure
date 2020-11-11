#include <iostream>
#include<bits/stdc++.h> 

using namespace std;

void operate(stack<int> &num, stack<char> &opr) {
    if (num.size() > 1) {
        int tmp = num.top() , ans;
        num.pop();
        if (opr.top() == '+') 
            ans = num.top() + tmp;
        if (opr.top() == '-') 
            ans = num.top() - tmp;
        if (opr.top() == '*') 
            ans = num.top() * tmp;
        if (opr.top() == '/') 
            ans = num.top() / tmp;
        num.pop();
        num.push(ans);
        opr.pop();
    }
}

void calculator()
{
    stack<int> num;
    stack<char> opr;
    double tmp,ans;
    char x;
    while (cin >> x && x != '#') {
        if (x >= '0' && x <= '9') 
            num.push(x - '0');
        else {
            if (opr.empty()) 
                opr.push(x);
            else {
                if ((x == '+' || x == '-') && (opr.top() == '*' || opr.top() == '/')) {
                    while (!opr.empty() && opr.top() != '(') 
                        operate(num, opr);
                    opr.push(x);
                }
                else if (x != ')')
                    opr.push(x);
                else{
                    while (opr.top() != '(') 
                        operate(num, opr);
                    opr.pop();
                }
            }
        }
    }
    while (!opr.empty()) 
        operate(num, opr);
    cout << num.top();
}