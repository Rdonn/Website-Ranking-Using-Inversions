#ifndef sort_H
#define sort_H

#include <vector>

using namespace std; 

class Sorting
{
public:
	int numberOfInversions;
	int arraySize; 
	 


	Sorting();
	Sorting(int);

	int getVectorSizeTest(); 
	long int getInversionsMerge(); 
	void createVector(int[]); 
	long int bruteForceInversions(); 

	long int getInversionsQuicksort(); 
	long int getInversionsInsertionSort(); 
private:
	vector<int> myVector;
	

};

#endif 
