#include<iostream>
using namespace std;

class Stack 
{
    int arr[6];
    int top;
public:
    Stack() { top = -1; }
    
    void push(int val)
    {
        if (top == 5) {
            cout << "Stack Overflow" << endl;
        }
            else {
            arr[++top] = val;
            cout << val << " pushed to stack" << endl;
        }
            
    }
        void pop()
        {
            if (top == -1) {
                cout << "Stack Underflow" << endl;
            }
                else {
                cout << arr[top--] << " popped from stack" << endl;
            }
        }

    void display()
    {
        if (top == -1)
            cout << "Stack is empty" << endl;
        else {
            cout << "Stack elements: ";
            for (int i = top; i >= 0; i--)
                cout << arr[i] << " ";
            cout << endl;
        }
    }
};

int main() 
{
    Stack s;
    s.push(9);
    s.push(16);
    s.push(23);
    s.display();
    s.pop();
    s.display();
}