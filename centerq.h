#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
using namespace std;

template<class T> class centerNode  
{
    public:
    T key;    //键值
    int degree;            // 度数
    centerNode<T> *left;    // 左兄弟
    centerNode<T> *right;    // 右兄弟
    centerNode<T> *child;    // 第一个孩子节点
    centerNode<T> *parent;    // 父节点
    bool marked;        // 是否被删除第一个孩子
    int id;
	char name[30];
	char contact[11]; //number digit of 11
	char address[10]; //the address, not know how to use
	int prof; 
	int birth;  
	int risk;  
	int time;  // when he is registed
	int aging;   // the age group he is in
	char status[10]; // whether he is in waiting , appointed, or else
		
	int treat_ddl;  //the deadline of the treated date
	int near_hospital;    //the closed hospital who can get treated
		
	/* Class Functions */
	centerNode();
	  //~patient();
	void age_rank(); // judge which age group he is in




    centerNode(patient value):key(value), degree(0), marked(false), 
    left(NULL),right(NULL),child(NULL),parent(NULL) 
    {
        key    = *************************************;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = NULL;
        child  = NULL;
    }


};


template<class T> class centerQueue
{
	private:
        int totalnum;         // 堆中节点的总数
        int maxdegree;      // 最大度
        centerNode<T> *min;    // 最小节点(某个最小堆的根节点)
        centerNode<T> **cons;    // 最大度的内存区域*******************************************************************************

    public:
        centerHeap();  //*********************************************************************************************
        ~centerHeap();  //***********************************************************************************************
       
        void insert(T key);   // 新建key对应的节点，并将其插入到斐波那契堆中
       
        void removeMin();    // 移除斐波那契堆中的最小节点
        
        void combine(FibHeap<T> *other);  // 将other合并到当前堆中
        
        bool minimum(T *pkey);  // 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
       
        void update(T oldkey, T newkey);   // 将斐波那契堆中键值oldkey更新为newkey
       
        void remove(T key);   // 删除键值为key的节点
        
        void destroy();  // 销毁


    private:
        void addNode(centerNode<T> *node, centerNode<T> *root);  // 将node堆结点加入root结点之前(循环链表中)
        void insert(centerNode<T> *node);  // 将节点node插入到斐波那契堆中


};


