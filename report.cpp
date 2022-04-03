#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "localq.h"
#include "centerq.h"
using namespace std;





//report出来treated的人
void report_treated(centerNode<T> *report,centerHeap<T> *centerq)
{
    ofstream fout("treated.txt");
    while (report->left != centerq->min)
    {
        if (report->status == "treated")
        {
            fout<<report->prof<<","<<report->aging<<","<<report->risk<<","<<report->treated_time-report->time<<endl;
        }
        report = report -> left;
    }
    fout.close();
}
//report出来registered的人
void report_registered(centerNode<T> *report,centerHeap<T> *centerq)
{
    ofstream fout("registered.txt");
    while (report->left != centerq->min)
    {
        if (report->status == "regeditered")
        {
            fout<<report->prof<<","<<report->aging<<","<<report->risk<<","<<当前の时间-report->time<<endl;
        }
        report = report -> left;
    }
    fout.close();
}
//report出来queueing的人
void report_queueing(centerNode<T> *report,centerHeap<T> *centerq)
{
    ofstream fout("queuening.txt");
    while (report->left != centerq->min)
    {
        if (report->status == "queueing")
        {
            fout<<report->prof<<","<<report->aging<<","<<report->risk<<","<<当前の时间-report->time<<endl;
        }
        report = report -> left;
    }
    fout.close();
}
