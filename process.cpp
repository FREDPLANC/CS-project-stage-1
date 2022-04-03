#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "centerq.h"
using namespace std;
//处理预约和撤销操作
template<class T> void  centerHeap<T>::appointment_process(int date )
{
    pop_patient_wrtddl(min,date);
    for (int i = 0; i < capacitor_total;i++){
        min->treated_time = ddl + 1;
        min->treated_location = check_nearest(centerNode* min);
        removeMin();
    }
    return;
}

template<class T> void  centerHeap<T>::withdraw(int id)
{
    centerNode<T>* p = search_id(id);
    remove(p);
    withdraw_list[id] = 1;
}
