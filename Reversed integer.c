#include <stdio.h>
int reverseInteger(int n)
{
int reversed =0;
    while (n !=0);
{
    int digit = n % 10;
    reversed =reversed *10 + digit;
    n /=10;
}
return reversed;
}
int main() 
{
int num;
printf("Enter an integer:");
scanf("%d" , &num);

int reversed = reverseInteger(num);
printf("Reversed integer: %d\n", reversed);
return 0;
}
