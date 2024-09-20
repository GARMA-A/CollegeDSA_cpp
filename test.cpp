#include <iostream>
using namespace std;

const int MAX_Size = 100;

class Stack {
    int top;
    int s[MAX_Size];

public:
    Stack() {
        top = -1;
    }

    void push(int element) {
        if (top < MAX_Size - 1) {
            top++;
            s[top] = element;
        }
        else {
            cout << "Stack is full" << endl;
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    void pop() {
        if (isEmpty())
            cout << "Stack is Empty" << endl;
        else
            top--;
    }

    int getTop() {
        if (isEmpty()) {
            cout << "Stack is Empty" << endl;
            return -1; 
        }
        else {
            return s[top];
        }
    }
};

void calculateSpan(int price[], int sizeOfPriceArray, int span[]) {
    Stack days;
    days.push(0); 

    span[0] = 1; 

    for (int i = 1; i < sizeOfPriceArray; i++) { 
        while (!days.isEmpty() && price[days.getTop()] <= price[i])
            days.pop();

        if (days.isEmpty()) {
            span[i] = i + 1;
        }
        else {
            span[i] = i - days.getTop();
        }

        days.push(i);
    }
}
void printArray(  int span[] , int sizeOfPriceArray){
   for (int i = 0; i < sizeOfPriceArray; i++){
    cout << span[i] << " ";
   }
         
}

int main() {
    cout << "***********************************************************STOCK SPAN PROBLEM****************************************" << endl;
    int price[] = { 100, 80, 60, 70 , 60 , 75 , 85 };
    int sizeOfPriceArray = sizeof(price) / sizeof(price[0]); 
    int span[MAX_Size];

    calculateSpan(price, sizeOfPriceArray, span);
    printArray(span, sizeOfPriceArray);
  

    return 0;
}

