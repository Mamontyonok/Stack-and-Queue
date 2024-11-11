#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include "stack_queue.h"

using namespace std;

bool IsOpenBracket(char c) {
    if ((c == '(') || (c == '[') || (c == '{'))
        return 1;
    return 0;
}

bool IsCloseBracket(char c) {
    if ((c == ')') || (c == ']') || (c == '}'))
        return 1;
    return 0;
}

char GetOpenBracket(char c) {
    if (c == ')')
        return '(';
    if (c == ']')
        return '[';
    if (c == '}')
        return '{';
    return 0;
}

static const int n = 100;

int main()
{
    string Expression;
    getline(cin, Expression);
    
    Stack<char> st;
    bool flag = false;
    
    for (int i = 0 ; i < Expression.length(); i++){
        if (IsOpenBracket(Expression[i]))
            st.push_back(Expression[i]);
        if(IsCloseBracket(Expression[i])){
            if (st.IsEmpty())
                flag = true;
            else{
                if (st.back() != GetOpenBracket(Expression[i]))
                    flag = true;
                else
                    st.pop_back();
            }
        }
    }
    
    if(st.IsEmpty() != 1)
        flag = true;
    if (flag == false)
        cout<< "\nSUPER!" << endl;
    else cout<<"\nIEROGLIFS" << endl;

  return 0;
}
