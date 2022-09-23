/*
 * @file: 'singleLinkedList.h'
 * @author Robin Lu
 * @brief
 * @version: 1.0
 * @date 2022.9.21 
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int boolean;   /* 定义函数返回值的状态码:*/

// 声明 链表节点类型 + 链表类型
typedef int Item;
struct Node {
    Item value;
    struct Node* next;
};
typedef struct Node* LinkedList; /* 声明指向struct Node的''结构体指针''代表链表结构:*/
// 当然其实，''head头结点指针''就already可以代表链表结构了: identical 👌🏻
//typedef struct Node Node;

struct Node* head; struct Node* tail;   /* 定义头结点+尾结点 结构体指针:*/


/***************************************************************************************/
/**
 * 链表结构的操作方法 ADT: */
struct Node* Build(Item* data,int len);         // 1.构建链表
boolean Insertion(int val);                     // 2. 插入元素
boolean Deletion(struct Node* list,int value);  //3.删除元素
Item Get(struct Node* head,int k);              //4.获取第ith位置的元素:
boolean Find(LinkedList list,Item value);       //5.查找是否存在特定元素:
int Length(struct Node* list);                  //6.获取链表长度:
void Print(LinkedList head);                    //7.打印链表元素输出
boolean Trash(LinkedList list);                 //8.清空链表:(还原到原始状态:)

/***************************************************************************************/

boolean Insertion(Item val) { //2.插入元素
    /* 构造新节点:*/
    struct Node* newed = (struct Node*)malloc(sizeof(struct Node));
    newed -> value = val;
    newed -> next = NULL;

    if (head == NULL) {
        head = newed;
    } 
    if (tail == NULL) {
        tail = newed;
    } 
    tail -> next = newed;
    tail = newed;
    return OK;
}

struct Node* Build(Item* data,int len) { //1.整体构造链表:
    Item* p = data;
    while (p < data + len) {
        Insertion(*p++);
    }
    return head;
}

boolean Deletion(struct Node* list,Item value) {     //3.删除元素:
    /* 删除specified元素: e.g. 7*/
    struct Node* prior = 0;
    struct Node* deleted = NULL;

/* To find 待删除元素，同时定位到它的前驱节点:*/
    struct Node* cur = head; 
    while (cur != NULL && cur -> value != value) {
        prior = cur;
        cur = cur -> next;
    }
    deleted = cur;

    if (deleted != head) {
        /* !head结点:*/
        prior -> next = deleted -> next;
        if (deleted == tail) {  /*  Del(tail):更新tail结点!*/
            tail = prior;
        }    
    } else {  /* 删除头结点:*/
        head = deleted -> next;
    }
    free(deleted);
    return OK;
}

Item Get(struct Node* head,int k) {              //4.获取第ith位置的元素:
    if (k < 0 || k > Length(head)) {
        printf("throws IndexOutOfRangeException!\n");
        return ERROR;
    }
    int i = 0;
    struct Node* cur = head;
    while (i < k) {
        cur = cur -> next;
        i++;
    }
    return cur -> value;
}

int Length(struct Node* list) { //6.获取链表长度
    if (!list) {
        return 0;
    }
    int len = 0;
    struct Node* cur = list;
    while (cur != NULL) {
        len++;
        cur = cur -> next;
    }
    return len;
}

void Print(LinkedList head) {     //7.打印链表元素:
    if (!head) {
        printf("@.warning:empty-list!\n");
        return;
    }
    printf("LinkedList: [");
    struct Node* cur = head;
    while (cur != NULL) {
        if (cur != tail) {
            printf("%d ", cur -> value);
        } else {
            printf("%d", cur -> value);
        }
        cur = cur -> next;
    }
    printf("] ");
    printf("[head:%d, tail:%d] size:%d\n", head -> value, tail -> value, Length(head));
}

boolean Find(LinkedList list,Item value) {  //5.
    struct Node* cur = list;
    while (cur != NULL && cur -> value != value) {
        cur = cur -> next;
    }
    return !cur ? FALSE : TRUE;     //如果cur迭代到tail.next表示查找失败，否则找到value!
}

boolean Trash(LinkedList list) {
    struct Node* temp = NULL;

    while (Length(list) > 0) {
        temp = head;
        head = head -> next;
        list = head;
        free(temp);
    }
    /* assert head != (!NULL)*/
    tail = NULL;
    return OK;
}
