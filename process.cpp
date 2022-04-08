#ifndef _process_
#define _process_
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "centerheap.h"
using namespace std;
// Handle reservation and cancellation operations
// We will first process the treatment list on that day, that is, we will call the withdraw function to withdraw the patients in the reservation list (at this point, the reservation list is equivalent to today's treatment list) and those waiting in the central queue to be withdrawn
// After that, all the patients in the appointment list before the update were put into the treatment list of the same day, and the appointment list was cleared
// We will update today's appointment list later
// Patients with DDL (date +1) on the next day will be prioritized in the appointment list, and then the remaining capacity will be displayed as the main queue of priority patients
// Capacity_total should be a const global variable that records the total daily capacity of all hospitals added up
//content_total Records how many appointments are made today
/*******************************************************************************************************************/
template<class T> void  centerHeap<T>::appointment_process(int date )
{   extern int capacity_total;
    extern int content_total;
    pop_patient_wrtddl(min,date+10);  // The treatment is scheduled one day before DDL, so an appointment is required the day before
   int rest_capacity = capacity_total - content_total;
    for (int i = 0; i < rest_capacity && min != NULL;i++){ // To prevent exceeding the daily capacity of all hospitals combined on that day
        min->treated_time = date + 5;
        min->treated_location = check_nearest(min);
        //total_appointment_num++;
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
    cout<< "abcdfuckyou" << total_appointment_num << endl;
    return;
}
template<class T> void centerHeap<T>::treatment_process(int date)  // Deal with the treatment, add all the patients in the appointment list of the day before yesterday into the treatment list, and clear the appointment list
{  
    centerNode<T> *temp;
    
    if(last_treatment == NULL){
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
template<class T> void  centerHeap<T>::withdraw(int id) // Cancel designated patients from the appointment list and center queue
{
    centerNode<T> *temp = last_appointment;
    
    if(centerNode<T>* p = search_id(min,id)) {
        remove(p);
        if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
        withdraw_list[id] = 1;
    }else{
        while(temp != NULL){
            if(temp->id == id) {
                temp->child->parent = temp->parent;
                temp->parent->child = temp->child;
                if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
                withdraw_list[id] = 1;
            }
            temp = temp->parent;
        }

    }
    
}
#endif