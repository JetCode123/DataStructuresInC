/**
 *  ''单链表实现:'' + @。time:2022.9.22 (周3) 01:05 👌🏻
 */

#include <stdio.h>
#include <stdlib.h> 

#include "LinkedList.h"

#define N 10

// /* ''声明''结构体类型:
//  */
// struct Node {
//     int data;
//     struct Node* next;
// };
// struct Node* head; struct Node* tail; /* 定义头结点+尾结点 结构体变量:*/

// typedef struct Node* linkedlist; /* 声明指向struct Node的''结构体指针''代表链表结构:*/
// // 当然其实，''head头结点指针''就already可以代表链表结构了: identical 👌🏻

// int main(int argc, char* argv[]) {
//     return 0;
// }

// /* 定义链表操作的ADT: */

void printArray(int* a,int len) {
    printf("Array's contents: [");
    for (int i = 0; i < len; i++) {
        if (i != len - 1) {
            printf("%d ",a[i]);
        } else { printf("%d", a[i]); }
    }
    printf("]\n");
}

int main(void) {
    /*
    bool a = 1;
    printf("a = %d\n", a); */
void printArray(int* a,int len);

    int* arr = (int*) malloc(sizeof(int) * N);
    for (int i = 0, x = 10; i < N; i++, x -= 1) {
        arr[i] = x;
    }
    printArray(arr, N);
    
    getchar();

    LinkedList list = Build(arr, N);
    Print(head);

    printf("FindElem(9): %d\n", Find(list, 9));
    printf("ListLength(): %d\n", Length(list));

    Item v = Get(list, 3);
    printf("The 3th element is %d\n", v);

    Insertion(100);
    printf("After insertion: ");
    Print(head);

    // 删除结点：
    Deletion(list, 100); Print(head);

    Deletion(list, 10); Print(head);

    //Trash(list);
    //ListPrint(list);
}