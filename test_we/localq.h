#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#ifndef localq_h
#define localq_h


class patient;
template<class T> class localQueue
{
	public:
		localQueue(int size = 10);
		T &operator[](int index);
		int getlength(void);
		bool isempty(void);
		T back(void);  
		T front(void); 
		void push(T value);
		T pop(void);
		
    
	private:
		int maxsize, minsize;
		int first, last;
		int numitems;
		T *reprarray;
		
		void allocate(void);
		void deallocate(void);
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
		int near_hospital;    //the closed hospital who can get treated
		
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

#endif

