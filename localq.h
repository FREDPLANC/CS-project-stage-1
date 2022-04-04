#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#ifndef localq_h
#define localq_h

void daily_hosp_setZero(void);

class hospital;
class patient;
template<class T> class localQueue
{
	public:
		localQueue(int size = 10);
		T &operator[](int index);
		int getlength(void);
		bool isNull(void);
		T rear(void);  
		T front(void); 
		void En_queue(T value);
		T De_queue(void);
		
    
	private:
		int maxsize, minsize;
		int first, last;
		int numitems;
		T *reprarray;
		
		void allocate(void);
		void deallocate(void);
};

class hospital{
	public:
		int hosp_id;
		int capacity;
		int loc;
		int content;

		hospital(){
			hosp_id = 0;
			capacity = 0;
			loc = 0;
			content = 0;
		}
		
		
};

class patient {
	public:
		int id;
		char name[30];
		char contact[11]; //number digit of 11
		char address[10]; //the address, not know how to use
		int prof; 
		int birth;  
		int risk;  
		int time;  // when he is registed
		int aging;   // the age group he is in
		char status[10]; // whether he is in waiting , appointed, or else
		
		int treat_ddl;  //the deadline of the treated date
		int loc;    //the location of the patient
		
		/* Class Functions */
		patient();
		patient(int nid, char nam[30], int pro, int tim, int ris, int phone, int bir, char state[10]);
		  //~patient();
		void age_rank(); // judge which age group he is in
		bool marked;
		int degree;
};

// Global variables
patient* N[1000];  // where patient are stored
int len_N=0;   // the number of patient
hospital* H[3]; //three hospital
#endif

