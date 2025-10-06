#include<iostream>
using namespace std;

class Queue
{
    int arr[5];
    int front, rear,count;
public:
    Queue()
    {
        front = 0;
        rear = -1;
        count=0;
    }
    void enqueue(int value)
    {
        if (count==6)
        {
            cout << "Queue is full" << endl;
        }
        else
        {
            rear=(rear+1)%5;
            arr[rear]=value;
            count++;
            cout<< value <<" enqueued"<<endl;
        }
    }
    void dequeue()
    {
        if (count==0)
            cout << "Queue is empty" << endl;
        else
        {
            cout<< arr[front]<<" dequeued"<<endl;
            front=(front+1)%5;
            count--;
        }
    }
    void display()
    {
        if (count==0)
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            cout << "Queue:";
            for (int i = 0; i < count; i++)
            {
                cout << arr[(front + i) % 5] << " ";
            }
            cout << endl;
        }
        
        }
    };
    
    int main()
    {
        Queue q;
        q.enqueue(4);
        q.enqueue(8);
        q.enqueue(12);
        q.display();
        q.dequeue();
        q.display();
    }
