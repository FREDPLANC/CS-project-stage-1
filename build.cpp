#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "localq.h" 
#include "centerq.h" 
#include "centerheap.cpp"
#include "localq.cpp"
#include "process.cpp"
#include "report.cpp"
using namespace std;

template <class T>
centerNode<T>::centerNode(patient value): degree(0), marked(false), 
    left(NULL),right(NULL),child(NULL),parent(NULL) 
    {
        key    = value.prof * 1000000 + value.aging * 100000 + value.time;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = NULL;
        child  = NULL;
    }

template <class T>
void centerHeap<T>::build(){ //将本地的队列加入到中央的堆内部
    
    localQueue<int> *Q1=build_queue(1); //first build the local queue;
    localQueue<int> *Q2=build_queue(2);
    localQueue<int> *Q3=build_queue(3);
    centerHeap<int>  tmp;
    int k=0;
    for (int i=1;i<=Q1.getlength();i++)
    {
        
        add_patient(Q1); //first pop the content of the queue one by one
        

    }
    for (int i=1;i<=Q2.getlength();i++)
    {
        add_patient(Q2);
    }
    for (int i=1;i<=Q2.getlength();i++)
    {
        add_patient(Q3);
    }

}
template <class T>
void centerHeap<T>::add_patient(localQueue* Q) //将本地队列的元素弹出并构建成centerHeap
{
    patient p=Q.De_queue() ;
    if (p.status==withdraw)
    {
        withdraw(p.id);
    }
    else{
        insert(p);
    }  
    
}
template <class T>
void centerHeap<T>::insert(patient p)
{
    centerNode<T> *node;
    node = new centerNode<T>(p);
    if (node == NULL) return ;
    insert(node);
    
}

