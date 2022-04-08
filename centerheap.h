#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
using namespace std;
#ifndef  centerheap_h
#define centerheap_h

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
	int status; // whether he is in waiting , appointed, or else
		
	int treat_ddl;  //the deadline of the treated date
	int near_hospital;    //the closed hospital who can get treated
	int loc;
    
	/* Class Functions */
	centerNode(){
        
    };
    centerNode(centerNode<T>* N){
    
    left   = this;
    right  = this;
    parent = NULL;
    child  = NULL;
    key=N->key;
    degree=N->degree;
    id=N->id;
    
    prof=N->prof;
    birth=N->birth;
    risk=N->risk;
    time=N->time;
    treated_time=N->treated_time;
    treated_location=N->treated_location;
    aging=N->aging;
    
    treat_ddl=N->treat_ddl;
    near_hospital=N->near_hospital;
    loc=N->loc;
    strcpy(name,N->name);
    strcpy(contact,N->contact);
    strcpy(address,N->address);
    status =  N->status;
    
    }
	  //~patient();
	void age_rank(); // judge which age group he is in




    centerNode(patient value): degree(0), marked(false), 
    left(NULL),right(NULL),child(NULL),parent(NULL) 
    {
        if(value.risk == 0 || 1)
        key    = value.prof * 100000 + value.aging * 10000 + value.time;
        else{
            key = value.prof * 100000 + value.aging * 10000 + value.time + value.risk *1000000;
        }
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = NULL;
        child  = NULL;
        id=value.id;//
    
        prof=value.prof;//
        birth=value.birth;//
        risk=value.risk;//
        time=value.time;//
        
        aging=value.aging;//
    
        treat_ddl=value.treat_ddl;//
        loc=value.loc;//
        strcpy(name,value.name);//
        strcpy(contact,value.contact);//
        strcpy(address,value.address);//
        status = value.status;
    }

};


template<class T> class centerHeap
{     
      
    public:
        int keyNum;         // 堆中当前节点的总数(不只是key的数量, key可能重复)
        int total_appointment_num;       // 一共从开始到现在有多少病人被安排了appointment
        int maxDegree;      // 最大度
        int withdraw_list[1000]; //查询是否该id曾经撤销过预约或等待
        int withdraw_number;     //记录已经撤销的人数
        int list_numb = 0;
        centerNode<T> *min;    // 最小节点(某个最小堆的根节点)
        centerNode<T> **cons;    // 最大度的内存区域
        centerNode<T> *last_appointment; //储存每日预约名单的双链表, last_appointment指向今日最后一个预约的病人
        centerNode<T> *last_treatment;   //储存总治疗名单的双链表
        centerNode<T> *last_waiting;   //储存排队的人的双链表（斐波那契堆中的每个元素）
        centerNode<T> *head_treatment;
        centerNode<T> *head_appointment;
        centerNode<T> *head_registered;

        centerHeap();  //*********************************************************************************************
        ~centerHeap();  //***********************************************************************************************
        void insert(T key);   // 新建key对应的节点，并将其插入到斐波那契堆中
        void removeMin();    // 移除斐波那契堆中的最小节点
        void combine(centerHeap<T> *other);  // 将other合并到当前堆中
        bool minimum(T *pkey);  // 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
        void update(T oldkey, T newkey);   // 将斐波那契堆中键值oldkey更新为newkey
        void remove(T key);   // 删除键值为key的节点
        void destroy();  // 销毁
        centerNode<T>* search_id(centerNode<T> *root, int id);
        void appointment_process(int date );// 处理预约
        void treatment_process(int date );  // 处理治疗
        void pop_patient_wrtddl(centerNode<T> *root, int ddl);
        void withdraw(int id);
        int check_nearest(centerNode<T> *node);
        void build(); //读取医院普通队列
        void add_patient(patient p);
        void insert(patient p);
        void report_treated(centerNode<T>* head_treatment);
        void report_appointment(centerNode<T>* head_appointment);
        void report_registered(centerNode<T>* head_waiting);

        void Listsort_prof(centerNode<T>* head);
        void Listsort_aging(centerNode<T>*  head);
        void Listsort_name(centerNode<T>* head);
        void List_registered();
        void listmake(centerNode<T> *N);
        centerNode<T> *copy(centerNode<T> *N);
        void set_head(centerNode<T>* head_appointment,centerNode<T>* head_treatment,centerNode<T>* head_waiting);
        void add_head(centerNode<T> *N,centerNode<T> *H);
        int count_list(centerNode<T> *head);
        
        void week_report();
        void month_report();
        void print(centerNode<T> *node, centerNode<T> *prev, int direction);  // 打印"斐波那契堆"

        void print();
        void iteregister(centerNode<T> *node, centerNode<T> *prev, int direction);
        int go(int waiting,centerNode<T> *node, centerNode<T> *prev, int direction);
    private:
        
        void removeNode(centerNode<T> *node);  // 将node从双链表移除(不是完整的删除操作)
        
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
        
       
        
        bool contains(T key); //在斐波那契堆中是否存在键值为key的节点。存在返回true，否则返回false。


};
 #endif