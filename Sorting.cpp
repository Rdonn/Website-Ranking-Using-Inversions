#include "Sorting.h"
#include <vector>
#include <iostream>

using namespace std; 

//MergeSort function: O(nlogn)
long int sort(vector<int>&  bar);
long int mergeSort(vector<int>&left, vector<int>& right, vector<int>& bars);

//quicksort function
long int quicksort(vector<int> myVector);

//insertion sort function
long int insertionSort(vector<int> myVector, int size);


Sorting::Sorting()
{
	numberOfInversions = 0;
	arraySize = 0;
}

//Overloaded Sorting constructor
Sorting::Sorting(int arraySize)
{
	
	this->arraySize = arraySize;
	numberOfInversions = 0;
}

//accepts an array from a declared object and creates a vector using the public var "arraySize"
void Sorting :: createVector(int myArray[])
{

	for (int i = 0; i < arraySize; i++)
	{
		myVector.push_back(myArray[i]); 
	}

	return; 
}

//In case further implementation is required, allows the user to retrieve obj vector size
int Sorting::getVectorSizeTest()
{
	return (int)myVector.size(); 
}

long int Sorting::getInversionsMerge()
{
	long int numberOfInversions = 0; 
	vector<int> tempVector; 
	
	//the recursive call in sort in passed to by reference, so I will be making  a temp array.
	for (int i = 0; i < (int)myVector.size(); i++)
	{
		tempVector.push_back(myVector[i]); 
	}

	numberOfInversions = sort(tempVector);

	return numberOfInversions; 
}

//gets the number of inversions in the obj vector by brute force (for target results)
long int Sorting::bruteForceInversions()
{
	long int count = 0;

	for (int i = 0; i < (int)myVector.size(); ++i)
		for (int j = i + 1; j < (int)myVector.size(); ++j)
		{
			if (myVector[i] > myVector[j])
			{

				++count;
			}
		}


	return count; 
}

//quicksort(inversion #)
long int Sorting::getInversionsQuicksort()
{

	numberOfInversions = quicksort(myVector);

	return numberOfInversions; 
}

//Insertion sort (inversion #)
long int Sorting::getInversionsInsertionSort()
{
	numberOfInversions = insertionSort(myVector, myVector.size());
	return numberOfInversions;
}

//beginning function declaration for Sorting.cpp
long int sort(vector<int>& myVector)
{
	long int numInversions = 0; 
	//Base case
	if ((int)myVector.size() <= 1)
		return 0; 
	int mid = (int)myVector.size() / 2; 
	vector <int> left, right; 

	for (int i = 0; i < mid; i++)
	{
		left.push_back(myVector[i]); 
	}
	for (int i = 0; i < (int)myVector.size() - mid; i++)
	{
		right.push_back(myVector[i + mid]); 
	}
	//general cases
	numInversions = sort(left); 
	numInversions += sort(right); 
	numInversions += mergeSort(left, right, myVector); 

	//returns number of inversions 
	//(accumulated via) number = sort(left) + sort(right) + merge(left, right)
	return numInversions; 
}

long int mergeSort(vector<int>&left, vector<int>& right, vector<int>& myVector)
{
	long int inversions = 0; 
	//contains left and right sizes
	int n1 = (int)left.size(); 
	int n2 = (int)right.size(); 

	int i = 0; 
	int j = 0; 
	int k = 0; 
	//will run until either i or j are out of bounds. 
	while (i < n1 && j < n2)
	{
		if (left[i] < right[j])
		{
			myVector[k] = left[i]; 
			i++;
		}
		else if (left[i] == right[j])
		{
			myVector[k] = left[i]; 
			i++;
		}
		else
		{

			myVector[k] = right[j];
			j++;
			//if (left[i] > right[j] then everything in the left vector in front of I must
			//must be greater than the element right[j], thus: left.size() - i
			inversions = inversions + (n1 - i);
			
		}
		k++; 
	}

	//if I < left.size() (this fills out the rest of the myVector vector)
	while (i < n1)
	{
		myVector[k] = left[i]; 
		k++; 
		i++; 
	}

	//if j < right.size() (this fills out the rest of the myVector vector)
	while (j < n2)
	{
		myVector[k] = right[j]; 
		k++; 
		j++; 
	}


	return inversions; 
}

long int quicksort(vector<int> myVector)
{
	//base case
	if (myVector.size() <= 1)
	{
		return 0;
	}

	
	long int numberOfInversions = 0;
	//L will contain elements less than M
	//M will contain elements equal to the pivot
	//R will contain elements greater than the pivot
	vector<int> L, M, R;
	M.push_back(myVector[0]);
	int pivot = M[0];

	


	for (int i = 1; i < myVector.size(); i++)
	{
		if (myVector[i] == pivot)
		{
			M.push_back(myVector[i]);
			//must be less than all elements held in the right vector thus far
			//so they would all invert with it
			numberOfInversions += R.size();
		}

		else if (myVector[i] < pivot)
		{
			L.push_back(myVector[i]);
			//Must be less than all elements in right and middle, so they would invert with it
			numberOfInversions += (R.size() + M.size());
		}

		else if (myVector[i] > pivot)
		{
			//adds no inversions, and is appended to R
			R.push_back(myVector[i]);
		}
	}

	//general cases
	numberOfInversions += quicksort(L);
	numberOfInversions += quicksort(R);

	//returns a long int
	return numberOfInversions;
}

long int insertionSort(vector<int> myVector, int size)
{
	long int numberOfInsertions = 0; 
	int i = 0, comparisonNumber = 0, j = 0;

	for (i = 1; i < size; i++)
	{
		comparisonNumber =myVector[i];
		j = i -1;

		while (j >= 0 && myVector[j] > comparisonNumber)
		{
			myVector[j + 1] = myVector[j];
			j--;
			//will count how many unsorted numbers (that are also greater than it) passes
			numberOfInsertions++; 
		}
		myVector[j + 1] = comparisonNumber;
	}
	
	return numberOfInsertions;
}