#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "localq.h" 
#include "centerheap.h" 
#include "centerheap.cpp"
#include "localq.cpp"
#include "process.cpp"
#include "report.cpp"
using namespace std;


template <class T>
void centerHeap<T>::build(){ //将本地的队列加入到中央的堆内部
    
    localQueue <patient*> Q1 = build_queue(1); //first build the local queue;
    localQueue<patient*> Q2 = build_queue(2);
    localQueue<patient*> Q3 = build_queue(3);
    int k=0;
    int l1 = Q1.getlength();
    int l2 = Q2.getlength();
    int l3 = Q3.getlength();
    for (int i=1;i<=l1;i++)
    {
        patient p1=Q1.De_queue() ;
        add_patient(p1); //first pop the content of the queue one by one
        

    }
    for (int i=1;i<=l2;i++)
    {   
        patient p2=Q2.De_queue() ;
        add_patient(p2);
    }
    for (int i=1;i<=l3;i++)
    {
        patient p3=Q3.De_queue() ;
        add_patient(p3);
    }

}
template <class T>
void centerHeap<T>::add_patient(patient p) //将本地队列的元素弹出并构建成centerHeap
{
    
    if (p.status==54188)
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