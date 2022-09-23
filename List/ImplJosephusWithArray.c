/** ''约瑟夫问题的数组实现:''
 * @.time: 2022.9.23 周5 02:22
 * */

#include <stdio.h>
#include <stdlib.h>

#define N 9
#define K 3
typedef int Circle[N];

/* 🙄 perplexed design:*/
#define true 1
#define false 0
typedef int boolean;
struct Node {   /* 定义''Node''代表Solider，id表示序号，flag用来标识是否被killed:*/
    int id;
    boolean flag;
};

int killed[N];

int main(void) {
    int josephusFinalID(int n,int k);
    int* josephusExitSeries(int n,int k);

    /* FinalID测试:*/
    printf("f(n=9,k=2): %d\n", josephusFinalID(9, 2));
    printf("f(8,3): %d\n", josephusFinalID(8,3));

/*    
    Circle c = {1,2,3,4,5,6,7,8,9,10};
    printf("circle(5): %d\n",c[5]); */
    
    // 初始化killed标记数据:
    for (int i = 0; i < N; i++) { killed[i] = false; }

    /* josephus序列测试: */
    int* outcome = josephusExitSeries(N, K);
    int* p = outcome;
    printf("josephus序列: C(N=9,k=3) = [ ");
    while (p++ < outcome+N) {
        printf("%d ", *p);
    }
    printf("]\n");

    printf("@killed标记数组: [ ");
    for (int i = 0; i < N; i++) {
        printf("%d ", killed[i]);
    }
    printf("]\n\n");

    free(outcome);  //@.🤔()这个地方不释放的话，结束life-cycle之后会memory-leaks吗?
    return 0;
}
                                                                      
/* 得到约瑟夫环的''出环顺序'':*/ 
//int* josephusExitSeries(int* origin,int n,int k) {
int* josephusExitSeries(int n,int k) {    
    /** 因为只是得到killed顺序，因此可以不涉及存储。只返回出circle的索引值序列就可以了!
     * @.tips: _ 然后针对扩展，拿着这个int indices[]到Origin数组中去索引值就可以了! 👌🏻
     */
    
    int* indices = (int*)calloc(n,sizeof(int));  //indices[0] = 1;
    //int c = 1;  

    /** @.thoughts: 代码要想写出来，思维捋顺是必要的。否则，一切都是一头雾水的感觉，非常低效。是没有办法把事情作好的。
     * 思维捋顺之后，writing code 就是''把你脑海中的思路用code表达出来的过程''。naturally procedure!! 🤔 
     * @.time:2022.9.23 周5 01:49
     */
    int start; int halt;
    for (int c = 1; c <= N; c++) { //变量c控制迭代次数:
        /* @.tips; 一次迭代过程确定一个halt，killed编号*/
        if (c == 1) {
            start = 0;
            halt = start + k - 1;
        } else {
            start = (halt + 1) % N; // (2 + 1) % 9 = 3
            //int start0 = start - 1; //对应到array中的索引下标:
            
            // step1: 确定start0,即从1开始数的元素:
            while (killed[start] != false) {
                start = (start + 1) % N;
            }
            // step2: 确定halt元素的位置:
            int start0 = start;
            for (int m = 0; m < k - 1; m++) { //迭代k-1次，For k=3, iter.times=2
                start0 = (start0+1)%N;
                while (killed[start0] != false) {
                    start0 = (start0 + 1) % N;
                }                
            }
            halt = start0;
        }

        killed[halt] = true; //确定被killed元素，更新flag标记:
        indices[c] = halt + 1;
    }
    return indices;
} //🙄 Not that difficult than you think. @.time:02:22 @豫A


/* 根据递推公式计算得到最后survive的ID:(with recursion Impl:)*/ 
/**  @.warnings: ''编号''从1开始，对应Array从0开始的需要注意下转换: 👌🏻
 * */
int josephusFinalID(int n,int k) {
    if (n == 1) {
        return 1;
    }
    int ID = josephusFinalID(n-1, k) + k;
    ID = (ID > n) ? ID - n : ID;
    return ID;
}
