#ifndef _process_
#define _process_
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "centerheap.h"
using namespace std;
//处理预约和撤销操作
//当天首先处理治疗名单, 即首先调用withdraw 函数撤销在预约名单里(此时预约名单相当于今日的治疗名单)和中心队列等待中的待撤销病人
//之后,把当天更新前的预约名单里的病人全部放在当天治疗名单中, 预约名单清零
//之后再更新今日的预约名单

//预约名单中优先安排下一天是ddl(date +1)的病人, 之后再按照剩下容量弹出主队列优先病人
//capacity_total 应该为const全局变量, 记录所有医院加起来的每日总容量
//content_total 记录目前今日有多少病人已经预约
/*******************************************************************************************************************/
template<class T> void  centerHeap<T>::appointment_process(int date )
{   extern int capacity_total;
    extern int content_total;
    pop_patient_wrtddl(min,date+10);  // 在ddl之前一天就要进行治疗,因此前第二天需要预约
   
    for (int i = 0; i < capacity_total-content_total && min != NULL;i++){ //防止超出当日所有医院加起来的每日总容量
        min->treated_time = date + 5;
        min->treated_location = check_nearest(min);
        total_appointment_num++;
        if(last_appointment == NULL) {
            last_appointment = min;
            removeMin();
            total_appointment_num++;
        }
        else{
            last_appointment->child = min;
            removeMin();
            last_appointment->child->parent = last_appointment;
            last_appointment = last_appointment->child;
            last_appointment->child = NULL;
            total_appointment_num++;
        }
    }
    return;
}
template<class T> void centerHeap<T>::treatment_process(int date)  // 处理治疗, 把前天的预约名单里的病人全部倒入治疗名单,预约名单清零
{  
    centerNode<T> *temp;
    
    if(last_treatment = NULL){
        last_treatment = last_appointment;
        last_appointment = NULL;
    }else{
        while(last_appointment!=NULL){
            last_treatment->child = last_appointment;
            last_appointment = last_appointment->parent;
            last_treatment->child->parent = last_treatment;
            last_treatment = last_treatment->child;
        }
            last_appointment = NULL;
    }
    return;

}  
template<class T> void  centerHeap<T>::withdraw(int id) //撤销在预约名单和中心队列里的指定病人
{
    centerNode<T> *temp = last_appointment;
    
    if(centerNode<T>* p = search_id(min,id)) {
        remove(p);
        if(withdraw_list[id] == 0) withdraw_number++;
        withdraw_list[id] = 1;
    }else{
        while(temp != NULL){
            if(temp->id == id) {
                temp->child->parent = temp->parent;
                temp->parent->child = temp->child;
                if(withdraw_list[id] == 0) withdraw_number++; //若此人没有撤销过, 则撤销人数加一
                withdraw_list[id] = 1;
            }
            temp = temp->parent;
        }

    }
    
}
#endif