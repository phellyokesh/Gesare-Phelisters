#include<stdio.h>
#define SIZE 6

int queue [SIZE];
int front = 0, rear = -1, count =0;

void enqueue(int value)
{if (count == SIZE)
    printf("Queue Overflow!\n");
else
   {rear=(rear + 1) % SIZE;
queue[rear]=value;
count++;
printf("%d enqueued.\n", value);
   }
}

void dequeue()
{
    if (count == 0)
        printf("Queue Underflow!\n");
    else
    {
        printf("%d dequeued.\n", value);
        front = (front + 1) % SIZE;
        count--;
    }

}

void display() 
{
    if (count == 0)
        printf("Queue is empty.\n");
    else {
        printf("Queue elements: ");
        for (int i = 0; i < count; i++)
            printf("%d ", queue[(front + i) % SIZE]);
        printf("\n");
    }
}
int main() {
    enqueue(5);
    enqueue(10);
    enqueue(15);
    display();
    dequeue();
    display();
    return 0;
}
