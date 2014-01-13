#ifndef PRINTUTILITIES_H
#define	PRINTUTILITIES_H

#include <iostream>
//#include <sys/stat.h> //http://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
//#include <vector>

using namespace std;

void printDoubleArray(double *arr, int arrleng){

  for(int i = 0; i < arrleng; i++){
  //for(int i = 0; i < darray.size(); i++){
    cout << i+1 << " " << arr[i] << endl;
  }
}

void printIntArray(int *arr, int arrleng){

  for(int i = 0; i < arrleng; i++){
  //for(int i = 0; i < darray.size(); i++){
    cout << i+1 << " " << arr[i] << endl;
  }
}

template <typename T> void printArray(T &arr, int arrleng) {

  for(int i = 0; i < arrleng; i++){
  //for(int i = 0; i < darray.size(); i++){
    cout << i+1 << " " << arr[i] << endl;
  }
  
}

#endif
