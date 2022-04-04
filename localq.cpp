#include <cstdio>
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "localq.h"
#include "centerq.h"
using namespace std;

void daily_hosp_setZero(void){
    for(int i = 0; i < 3;i++){
        H[i]->content = 0;
    }
}

template <class T>
int centerHeap<T>::check_nearest(centerNode<T> *node)
{   
    

    int result = 0;
    int best = 100;
    int choice = 0;
    int loc_pat = node->loc;
    for(int i == 0; i < 3; i++){
        if(H[i]->content >= capacity){
            continue;
        }
        result = loc_pat - H[i]->loc;
        if(result < 0){
            result = -result;
        } 
        result = result % 10;
        if(result < best){
            best = result;
            choice = i;
        }

    }
    H[choice]->content++;
    return choice;
    
}



inline localQueue<patient*> build_queue(int i){
    localQueue<patient*> palist;
    char filename[256];
    cout<<"请输入文件名"<<endl;
    cin>>filename;
    int omitline = 0; // the line to be neglected
    ifstream infile(filename);
    while(infile.good()){
        //.csv文件用","作为分隔符
        if(omitline == 0){
            char omitting[256];
            infile.getline(omitting,256);
            omitline++;
            continue;
        }
        //patient* ill = new patient();
        int item;
        item = 0;
        while(item >= 0){
            char buffer[64]; // the size of each item;
            infile.getline(buffer,64,',');
            while(buffer[0] == '\n'){
                strcpy(buffer,buffer + 1);
            }
            item++;
            patient* pat = new patient();
            switch (item) {  // You can refer to the order in the sample csv.
					case 1:
						/*ill->id=(int)strtol(buf,NULL,10);*/
						if (buffer[0]=='\0') {
							delete pat;
							pat = nullptr; 
							item=-1;
							break;
						}
						//pat->id=len_N;  // Set the id as the index of the array N.
                        pat->id = (int)strtol(buffer,NULL,10);
						break;
					case 2:
						strcpy(pat->name,buffer);
						break;
					case 3:
						pat->prof=(int)strtol(buffer,NULL,10);
						break;
					case 4:
						pat->time=(int)strtol(buffer,NULL,10);
						break; 
                    case 5:
                        pat->risk=(int)strtol(buffer,NULL,10);
                        break;
                    case 6:
                        strcpy(pat->contact,buffer);
                        break;
                    case 7:
                        pat->treat_ddl=(int)strtol(buffer,NULL,10);
                        break;
                    case 8:
                        pat->loc=(int)strtol(buffer,NULL,10);
						break;
                    case 9:
                        pat->birth=(int)strtol(buffer,NULL,10);
                        (*pat).age_rank();
                        break;
                    case 10:
                        strcpy(pat->status,buffer);
                        item = -2;
                        break;
                        
                    default:
                        cout << "exit with case in reading the file\n";      
            }
            if(item == -2){
                N[len_N++]=pat; 
                palist.En_queue(pat);  // This pointer to this patient is stored to the vector palist.    
            }   
        }   
    }
    infile.close();
	return palist;
}

template<class T> localQueue<T>::localQueue(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
        maxsize = 20;
    else
        minsize = 20;
    numitems = 0;
    first = 0;
    last = 0;
    reprarray = new T[maxsize];
}

template<class T>bool localQueue<T>::isNull(void)
{
    if (numitems == 0)
	{
		return true;  //队头等于队尾，为空
	}
	return false;
}

template<class T> T &localQueue<T>::operator[](int index)
{
    if ((0 <= index) && (index <= numitems))
    {
        int dirindex = (index + first -1) % maxsize;
        return reprarray[dirindex];
    }
    else
    {
        cout << "Error: index out of range.\n";
        exit(EXIT_FAILURE);
    }
}   

template<class T> int localQueue<T>::getlength(void)
{
    return numitems;
}

template<class T> T localQueue<T>::front(void)
{
    if (isNull())
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
    else{
        return reprarray[first];
    }
}

template<class T> T localQueue<T>::rear(void)
{
    if (isNull())
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        int dirindex = (first + numitems - 1) % maxsize;
        return reprarray[dirindex];
    }
}

template<class T> T localQueue<T>::De_queue(void){ // let a element go out a queue
    if (isNull())
	{
		cout<<"The queue is empty~";
		exit(EXIT_FAILURE);
	}
    if(((numitems -1) <= maxsize * 0.25) && (2*minsize < maxsize)){
        deallocate();
    }
    T ele_out = reprarray[first];  // the element to be out;
	first += 1;
	first = first % maxsize;
    numitems--;
    return ele_out;
}

template<class T> void localQueue<T>::En_queue(T element){ // let a element go into a queue
    if ( numitems >= maxsize * 0.75)
        allocate();
	last += 1;
    last = last % maxsize;
	reprarray[last] = element;
    numitems++;
    return;
}

template<class T> void localQueue<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
        newarray[i] = reprarray[(i + first) % maxsize];
    first = 0;
    last = numitems -1;
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    
    return;
}

template<class T> void localQueue<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[(i + first) % maxsize];
    }
    first = 0;
    last = numitems -1;
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

void patient::age_rank() {  // for aged < 12, we use 1 to represent the age group;And the same for others
	int age_diff = 2022 - this->birth;
	if (age_diff <= 12) {
        this->aging = 1;
    }
	else if (age_diff <= 18) {
        this->aging = 2;
    }
	else if (age_diff <= 35) {
        this->aging = 3;
    }
	else if (age_diff <= 50) {
        this->aging = 4;
    }
	else if (age_diff <= 65) {
        this->aging = 5;
    }
	else if (age_diff <= 75) {
        this->aging = 6;
    }
	else{
        this->aging = 7;
    }  
}
