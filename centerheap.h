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
	int time;  // when he is register
    int treated_time;  //被治好的时间
    int treated_location;   //被治好的地点
	int aging;   // the age group he is in
	char status[10]; // whether he is in waiting , appointed, or else
		
	int treat_ddl;  //the deadline of the treated date
	int near_hospital;    //the closed hospital who can get treated
	int loc;
    
	/* Class Functions */
	centerNode();
	  //~patient();
	void age_rank(); // judge which age group he is in




    centerNode(patient value):key(value), degree(0), marked(false), 
    left(NULL),right(NULL),child(NULL),parent(NULL) 
    {
        key    = prof * 1000000 + age * 100000 + time;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = NULL;
        child  = NULL;
    }


};


template<class T> class centerHeap
{     
      
    public:
        int totalnum;         // 堆中节点的总数
        int maxdegree;      // 最大度
        int withdrew_list[1000];
        centerNode<T> *min;    // 最小节点(某个最小堆的根节点)
        centerNode<T> **cons;    // 最大度的内存区域

        centerHeap();  //*********************************************************************************************
        ~centerHeap();  //***********************************************************************************************
        void insert(T key);   // 新建key对应的节点，并将其插入到斐波那契堆中
        void removeMin();    // 移除斐波那契堆中的最小节点
        void combine(centerHeap<T> *other);  // 将other合并到当前堆中
        bool minimum(T *pkey);  // 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
        void update(T oldkey, T newkey);   // 将斐波那契堆中键值oldkey更新为newkey
        void remove(T key);   // 删除键值为key的节点
        void destroy();  // 销毁
        centerHeap<T> search_id(centerNode<T> *root, T key);
        centerHeap<T> pop_patient_wrtddl(centerNode<T> *root, int ddl);
        centerHeap<T> withdrew(int id);
        int check_nearest(centerNode<T> *node);

    private:
        
        void removeNode(centerNode<T> *node);  // 将node从双链表移除
        
        void addNode(centerNode<T> *node, centerNode<T> *root);  // 将node堆结点加入root结点之前(循环链表中)
        
        void catList(centerNode<T> *a, centerNode<T> *b);  // 将双向链表b链接到双向链表a的后面
        
        void insert(centerNode<T> *node);  // 将节点node插入到斐波那契堆中
        
        centerNode<T>* extractMin();  // 将"堆的最小结点"从根链表中移除，
        
        void link(centerNode<T>* node, centerNode<T>* root);  // 将node链接到root根结点
        
        void makeCons();  // 创建consolidate所需空间
        
        void consolidate();  // 合并斐波那契堆的根链表中左右相同度数的树
        
        void renewDegree(centerNode<T> *parent, int degree);  // 修改度数
        
        void cut(centerNode<T> *node, centerNode<T> *parent);  // 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
        
        void cascadingCut(centerNode<T> *node) ;  // 对节点node进行"级联剪切"
        
        void decrease(centerNode<T> *node, T key);  // 将斐波那契堆中节点node的值减少为key
        
        void increase(centerNode<T> *node, T key);  // 将斐波那契堆中节点node的值增加为key
        
        void update(centerNode<T> *node, T key);  // 更新斐波那契堆的节点node的键值为key
        
        centerNode<T>* search(centerNode<T> *root, T key);  // 在最小堆root中查找键值为key的节点
        
        centerNode<T>* search(T key);  // 在斐波那契堆中查找键值为key的节点
        
        void remove(centerNode<T> *node);  // 删除结点node
        
        void destroyNode(centerNode<T> *node);  // 销毁斐波那契堆
        
        void print(centerNode<T> *node, centerNode<T> *prev, int direction);  // 打印"斐波那契堆"


};


