#ifndef _report_
#define _report_
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "localq.h"
#include "centerheap.h"
using namespace std;

//report出来treated的人
template<class T> void centerHeap<T>:: report_treated(centerNode<T>* head_treatment)
{
    ofstream fout("treated.txt");
    if (head_treatment->parent == NULL)
    {
        fout.close();
        return;
    }
    centerNode<T> *tmp = head_treatment->parent;
    while (tmp != NULL)
    {

        fout<<tmp->id<<","<<tmp->name<<","<<tmp->prof<<","<<tmp->birth<<","<<tmp->risk<<","<<tmp->treated_time-tmp->time<<endl;
        tmp = tmp->parent;
    }
    fout.close();
}



//report出来registered的人
template<class T> void centerHeap<T>:: report_appointment(centerNode<T>* head_appointment)
{
    ofstream fout("appointment.txt");
    if (head_appointment->parent == NULL)
    {
        fout.close();
        return;
    }
    centerNode<T> *tmp = head_appointment->parent;
    while (tmp != NULL)
    {
        fout<<tmp->id<<","<<tmp->name<<","<<tmp->prof<<","<<tmp->birth<<","<<tmp->risk<<","<<tmp->time<<endl;
        tmp = tmp -> parent;
    }
    fout.close();
}

template<class T> void centerHeap<T>:: report_registered(centerNode<T>* head_waiting)
{
    ofstream fout("registered.txt");
    if (head_waiting->parent == NULL || min == NULL)
    {
        fout.close();
        return;
    }
    centerNode<T> *tmp = head_waiting->parent;
    while (tmp != NULL)
    {   extern int date_treat;
        fout<<tmp->id<<","<<tmp->name<<","<<tmp->prof<<","<<tmp->birth<<","<<tmp->risk<<","<<date_treat-tmp->time<<endl;
        tmp = tmp -> parent;
    }
    fout.close();
}

/*每月播报*/
template<class T> void centerHeap<T>:: month_report()
{
    ofstream fout("appointment.txt");
    centerNode<T> *tmp_treatment = last_treatment;
    centerNode<T> *tmp_appointment = last_appointment;
    /*要求print的数据*/
    int registered = 0;     /*多少人registered ---> 治好+预约+排队*/
    int waiting = 0;        /*多少人waiting ---> 排队 */
    int waiting_total = 0;      /*多少人waiting in total ---> 预约+排队*/
    int appointment = 0;        /*多少人appointment ---> 预约*/
    int waiting_time = 0;       /*治好的人的平均等待时间*/
    int withdraw = withdraw_number;          /*多少人withdrew*/
    /*没要求print的数据*/
    int treatment = 0;   /*多少人被治疗好*/

    /*找有多少人被治疗好*/
    while (tmp_treatment != NULL)
    {
        treatment++;
        waiting_time = waiting_time + tmp_treatment->treated_time - tmp_treatment->time;
        tmp_treatment = tmp_treatment->parent;
    }
    waiting_time = waiting_time / treatment;

    /*找有多少人已经预约*/
    while (tmp_appointment != NULL)
    {
        appointment++;
        tmp_appointment = tmp_appointment->parent;
    }
    
    /*找多少人还在排队*/
    centerNode<T> *tmp = min;
    centerNode<T> *tmp_line = min;
    centerNode<T> *tmp_line1 = tmp_line;
    waiting++;
    if (tmp_line->child != NULL)                /*print第一个根节点*/
    {
        tmp_line = tmp->child;
        while (tmp_line != NULL)
        {                                                       
        
            tmp_line1 = tmp_line;
            waiting++;
            while (tmp_line1->left != tmp_line)
            {
                tmp_line1 = tmp_line1->left;
                waiting++;
            }
            
            tmp_line = tmp_line->child;   
        }
    }
    tmp = tmp->left;
    /***************/
    while (tmp != min)         /*print之后的根节点*/
    {   
        waiting++;
        if (tmp_line->child != NULL)
        {
            tmp_line = tmp->child;
            while (tmp_line != NULL)
            {
            
                tmp_line1 = tmp_line;
                waiting++;
                while (tmp_line1->left != tmp_line)
                {
                    tmp_line1 = tmp_line1->left;
                    waiting++;
                }
                
                tmp_line = tmp_line->child;    
            }
        }
        tmp = tmp->left;
    }
    registered = waiting + appointment + treatment;
    waiting_total = appointment + waiting;
    fout<<"The number of people who have registered is "<<registered<<endl;
    fout<<"The number of people who are waiting is "<<waiting<<endl;
    fout<<"The number of people who are waiting in total is "<<waiting_total<<endl;
    fout<<"The number of treatment appointment which have been made is "<<appointment<<endl;
    fout<<"The average waiting time is "<<waiting_time<<endl;
    fout<<"The number of people who withdrew is "<<withdraw<<endl;
    fout.close();
}

/*每周播报*/
template<class T> void centerHeap<T>:: week_report()
{
    List_registered();
    centerNode<T> *head_appointment = new centerNode<T>(last_treatment);
    centerNode<T> *head_treatment = new centerNode<T>(last_treatment);
    centerNode<T> *head_waiting = new centerNode<T>(last_treatment);
    set_head(head_appointment,head_treatment,head_waiting);
    /*按照年龄排序*/
    Listsort_aging(last_appointment);
    Listsort_aging(last_treatment);
    Listsort_aging(last_waiting);

    /*按照职业排序
    Listsort_prof(last_appointment);
    Listsort_prof(last_treatment);
    Listsort_prof(last_waiting);
    */

    /*按照名字排序
    Listsort_name(last_appointment);
    Listsort_name(last_treatment);
    Listsort_name(last_waiting);
    */

    report_appointment(head_appointment);
    report_treated(head_treatment);
    report_registered(head_waiting);
}


/*数出来一个链表里元素的个数*/
template<class T> int centerHeap<T>:: count_list(centerNode<T> *head)
{
    int counter = 0;
    centerNode<T> *tmp = head;
    while (tmp != NULL && tmp->parent != NULL)
    {
        counter++;
        tmp = tmp->parent;
    }
    return counter;
}

/*为list添加头节点*/
template<class T> void centerHeap<T>:: set_head(centerNode<T>* head_appointment,centerNode<T>* head_treatment,centerNode<T>* head_waiting)
{
    /*centerNode<T> *head_appointment = new centerNode<T>(last_treatment);
    centerNode<T> *head_treatment = new centerNode<T>(last_treatment);
    centerNode<T> *head_waiting = new centerNode<T>(last_treatment);
    */
    add_head(last_appointment,head_appointment);
    add_head(last_treatment,head_treatment);
    add_head(last_waiting,head_waiting);

}
template<class T> void centerHeap<T>:: add_head(centerNode<T> *N,centerNode<T> *H)
{
    if (N == NULL)
    {
        H = NULL;
    }
    else
    {
        N->child = H;
        H->parent = N;
    }
   
}



//线性表的排序,采用冒泡排序,直接遍历链表**********用职业排序
template<class T> void centerHeap<T>:: Listsort_prof(centerNode<T>*   head) 
{
    int number = count_list(head);
    int i = 0;
    int j = 0;
    //用于变量链表
    centerNode<T> * L = head;
    //作为一个临时量
    centerNode<T> * p;
    centerNode<T> * p1;
    //如果链表为空直接返回
    if (head==NULL)
    {
        return;
    }
    
    for (i = 0; i < number - 1; i++) 
    {
        L = head->parent;
        for (j = 0; j < number - i - 2; j++) 
        {
            //得到两个值
            p = L;
            p1 = L->parent;
            //如果前面的那个比后面的那个大，就交换它们之间的是数据域
            if (p->prof > p1->prof) 
            {
                centerNode<T>* temp = p;
                if (p1->parent != NULL)
                {
                    p1->parent->child = p;
                    p->child->parent = p1;
                    p1->child = p->child;
                    p->parent = p1->parent;
                    p1->parent = p;
                    p->child = p1;
                }
                else
                {
                    p->child->parnet = p1;
                    p1->child = p->child;
                    p->child = p1;
                    p->parent = NULL;
                    p1->parent = p;

                }
            }
            else
            {
                L = L->parent;
            }
            
        }
    }
}


//线性表的排序,采用冒泡排序,直接遍历链表**********用年龄排序
template<class T> void centerHeap<T>:: Listsort_aging(centerNode<T>*  head) 
{
    int number = count_list(head);
    int i = 0;
    int j = 0;
    //用于变量链表
    
    centerNode<T> * L = head;
    //作为一个临时量
    centerNode<T> * p;
    centerNode<T> * p1;
    //如果链表为空直接返回
    if (head==NULL)
    {
        return;
    }
    
    for (i = 0; i < number + 1 ; i++) 
    {
        L = head->parent;
        for (j = 0; j < number - i - 2; j++) 
        {
            //得到两个值
            p = L;
            p1 = L->parent;
            //如果前面的那个比后面的那个大，就交换它们之间的是数据域
            if (p->birth > p1->birth) 
            {
                centerNode<T> * temp = p;
                if (p1->parent != NULL)
                {
                    p1->parent->child = p;
                    p->child->parent = p1;
                    p1->child = p->child;
                    p->parent = p1->parent;
                    p1->parent = p;
                    p->child = p1;
                }
                else
                {
                    p->child->parent = p1;
                    p1->child = p->child;
                    p->child = p1;
                    p->parent = NULL;
                    p1->parent = p;

                }
                
            }
            else
            {
                L = L->parent;
            }
           
        }
    }
}

//线性表的排序,采用冒泡排序,直接遍历链表**********用姓名排序
template<class T> void centerHeap<T>:: Listsort_name(centerNode<T>*   head) 
{
    int number = count_list(head);
    int i = 0;
    int j = 0;
    //用于变量链表
    centerNode<T> * L = head;
    //作为一个临时量
    centerNode<T> * p;
    centerNode<T> * p1;
    //如果链表为空直接返回
    if (head==NULL)
    {
        return;
    }
    for (i = 0; i < number - 1; i++) 
    {
        L = head->parent;
        for (j = 0; j < number - i - 2; j++) 
        {
            //得到两个值
            p = L;
            p1 = L->parent;
            //如果前面的那个比后面的那个大，就交换它们之间的是数据域
            if ((p->name).compare(p1->name) == 1) 
            {
                centerNode<T> * temp = p;
                if (p1->parent != NULL)
                {
                    p1->parent->child = p;
                    p->child->parent = p1;
                    p1->child = p->child;
                    p->parent = p1->parent;
                    p1->parent = p;
                    p->child = p1;
                }
                else
                {
                    p->child->parnet = p1;
                    p1->child = p->child;
                    p->child = p1;
                    p->parent = NULL;
                    p1->parent = p;

                }
            }
            else
            {
                L = L->parent;
            }
            
        }
    }
}

//queueing的人形成一个list
template<class T> void centerHeap<T>:: List_registered()
{
    if (min == NULL)
    {
        last_waiting = NULL;
    }
    else
    {
        centerNode<T> *tmp = min;
        centerNode<T> *tmp_line = min;
        centerNode<T> *tmp_line1 = tmp_line;
        extern int date_treat;
        last_waiting = new centerNode<T>(min);
        if (tmp_line->child != NULL)                /*print第一个根节点*/
        {
            listmake(tmp);
            tmp_line = tmp->child;
            while (tmp_line != NULL)
            {                                                       
            
                tmp_line1 = tmp_line;
                listmake(tmp_line);
                while (tmp_line1->left != tmp_line)
                {
                    tmp_line1 = tmp_line1->left;
                    listmake(tmp_line1);
                }
                
                tmp_line = tmp_line->child;   
            }
        }
        tmp = tmp->left;
        tmp_line = tmp;
        /*************************************************************************************/
        while (tmp != min)         /*print之后的根节点*/
        {   
            listmake(tmp);
            if (tmp->child != NULL)
            {
                tmp_line = tmp->child;
                while (tmp_line != NULL)
                {
                
                    tmp_line1 = tmp_line;
                    listmake(tmp_line);
                    while (tmp_line1->left != tmp_line)
                    {
                        tmp_line1 = tmp_line1->left;
                        listmake(tmp_line1);
                    }
                    
                    tmp_line = tmp_line->child;    
                }
            }
            tmp = tmp->left;
        }
    }
    
    
}

template <class T>
void centerHeap<T>::listmake(centerNode<T>* N)
{
    centerNode<T>* node = new centerNode<T>(N);
    //node=copy(N);
    last_waiting->child=node;
    node->parent=last_waiting;
    last_waiting=node;


}
/*template <class T>
centerNode<T>* centerHeap<T>::copy(centerNode<T>* N)
{
    centerNode<T>* node = new centerNode<T>() ;
    node->key=N->key;
    node->degree=N->degree;
    node->id=N->id;
    
    node->prof=N->prof;
    node->birth=N->birth;
    node->risk=N->risk;
    node->time=N->time;
    node->treated_time=N->treated_time;
    node->treated_location=N->treated_location;
    node->aging=N->aging;
    
    node->treat_ddl=N->treat_ddl;
    node->near_hospital=N->near_hospital;
    node->loc=N->loc;
    strcpy(node->name,N->name);
    strcpy(node->contact,N->contact);
    strcpy(node->address,N->address);
    node->status =  N->status;
    
    return node;
}*/
#endif