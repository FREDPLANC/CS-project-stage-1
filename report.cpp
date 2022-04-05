#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "localq.h"
#include "centerheap.h"
using namespace std;

//report出来treated的人
template<class T> void centerHeap<T>:: report_treated()
{
    ofstream fout("treated.txt");
    centerNode<T> *tmp = last_treatment;
    while (tmp != NULL)
    {

        fout<<tmp->prof<<","<<tmp->aging<<","<<tmp->risk<<","<<tmp->treated_time-tmp->time<<endl;
        tmp = tmp->parent;
    }
    fout.close();
}



//report出来registered的人
template<class T> void centerHeap<T>:: report_appointment()
{
    ofstream fout("appointment.txt");
    centerNode<T> *tmp = last_appointment;
    while (tmp != NULL)
    {
        fout<<tmp->prof<<","<<tmp->aging<<","<<tmp->risk<<","<<tmp->time<<endl;
        tmp = tmp -> parent;
    }
    fout.close();
}



//report出来queueing的人
template<class T> void centerHeap<T>:: report_registered()
{
    ofstream fout("registered.txt");
    centerNode<T> *tmp = min;
    centerNode<T> *tmp_line = min;
    centerNode<T> *tmp_line1 = tmp_line;
    extern int date_treat;
    fout<<tmp->prof<<","<<tmp->aging<<","<<tmp->risk<<","<<date_treat-tmp->time<<endl;
    if (tmp_line->child != NULL)                /*print第一个根节点*/
    {
        tmp_line = tmp->child;
        while (tmp_line != NULL)
        {                                                       
        
            tmp_line1 = tmp_line;
            fout<<tmp_line->prof<<","<<tmp_line->aging<<","<<tmp_line->risk<<","<<date_treat-tmp_line->time<<endl;
            while (tmp_line1->left != tmp_line)
            {
                tmp_line1 = tmp_line1->left;
                fout<<tmp_line1->prof<<","<<tmp_line1->aging<<","<<tmp_line1->risk<<","<<date_treat-tmp_line1->time<<endl;
            }
            
            tmp_line = tmp_line->child;   
        }
    }
    tmp = tmp->left;
    /*************************************************************************************/
    while (tmp != min)         /*print之后的根节点*/
    {   
        fout<<tmp->prof<<","<<tmp->aging<<","<<tmp->risk<<","<<date_treat-tmp->time<<endl;
        if (tmp_line->child != NULL)
        {
            tmp_line = tmp->child;
            while (tmp_line != NULL)
            {
            
                tmp_line1 = tmp_line;
                fout<<tmp_line->prof<<","<<tmp_line->aging<<","<<tmp_line->risk<<","<<date_treat-tmp_line->time<<endl;
                while (tmp_line1->left != tmp_line)
                {
                    tmp_line1 = tmp_line1->left;
                    fout<<tmp_line1->prof<<","<<tmp_line1->aging<<","<<tmp_line1->risk<<","<<date_treat-tmp_line1->time<<endl;
                }
                
                tmp_line = tmp_line->child;    
            }
        }
        tmp = tmp->left;
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
        tmp_treatment = tmp_treatment->left;
    }
    waiting_time = waiting_time / treatment;

    /*找有多少人已经预约*/
    while (tmp_appointment != NULL)
    {
        appointment++;
        tmp_appointment = tmp_appointment->left;
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


template<class T> void centerHeap<T>:: week_report()
{
    report_appointment();
    report_treated();
    report_registered();
}