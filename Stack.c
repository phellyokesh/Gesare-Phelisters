#include<stdio.h>
#define SIZE 6

int stack[SIZE];
int top = -1;

void push(int value) 
   {
    if (top == SIZE -1)
    printf("Stack Overflow!\n");
    else
    {
        stack[++top] = value;
        printf("%d pushed into stack.\n", value);
    }
}
 void pop() 
 {
    if (top == -1)
        printf("Stack underflow\n!");
    else
        printf("%d popped from stack.\n", stack [top--]);
 }
            void display()
            {
                if (top == -1)
                     printf("Stack is empty.\n");
                     else
                        {
                            printf("Stack elements: ");
                             for (int i = top; i >= 0; i--)
                            printf("%d ", stack[i]);
                            printf("\n");
    }
}
							
            int main() {
            push(11);
            push(22);push(33);
            display();
            pop();
            display();
            return 0;
        }
