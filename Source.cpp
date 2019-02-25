//Author: Ryan Donnohue
//Algorithms Project One

/*
Note to grader: 
The notes in this code are extremely wordy, the reason behind this is so it will be much 
easier to encorporate thoughts and processes of the code into my formal report.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "Sorting.h"
#include <iomanip>
#include <string>
#include <limits>

using namespace std; 

//function to initialize vectors using the respective source files
void readFile(vector<int>& mySource, string fileSourceName); 

//spacing is used mid argument list to allow entirety of the function to remain in focus
//all source vectors are passed as constants to maintain data security
void sumVectors(vector<int>& sum, const vector<int> &one, const vector<int> &two, 
	const vector<int> &three, const vector<int> &four, const vector<int> &five); 

//will take in the vector to be initialized and the size of the data set
void initializeSubVector(vector<int>& myVector, int size); 

//This function will copy the vector to an array
void copyToArray(int[],const vector <int> &myVector); 

//This function is a specific sort created for the sum array
void mergeSortForSum(int[], int[],int l,int r); 

//this is a merge function for the sum array specifically 
void mergeSum(int[], int[], int l, int m, int r);

//Swaps around the values in the sources
void MYswap(vector <int> myVector, int[], int[]); 

//Displays the results
void display(long int[][5]);

int main()
{
	//I will begin by making five different vectors
	//These arrays will contain all the information given by the five different sources
	vector <int> sourceOne; 
	vector <int> sourceTwo;
	vector <int> sourceThree;
	vector <int> sourceFour;
	vector <int> sourceFive;

	//This will be the sum vector, which will hold the sum of the five sources
	vector<int> sum; 

	/*Since we are dealing with a relatively small data set, memory management is not a high priority.
	For that reason, I will be using a series of sub-vectors to keep track of the indexes and how
	they move with respect to the sorted sum vector. In essence, the sub-vectors will be a set of
	{0,1,2,3,...,n} and will mirror all operation taking place on the sum vector*/

	vector<int> subVectorForSum; 
	

	//These will be used in a concatenation in the readFile function
	//The purpose will allow for function reussability 
	string fileNameOne = "One"; 
	string fileNameTwo = "Two"; 
	string fileNameThree = "Three"; 
	string fileNameFour = "Four"; 
	string fileNameFive = "Five"; 

	//Calling the read file function
	//This function will take in a vector and a string as an argument
	readFile(sourceOne, fileNameOne); 
	readFile(sourceTwo, fileNameTwo); 
	readFile(sourceThree, fileNameThree);
	readFile(sourceFour, fileNameFour); 
	readFile(sourceFive, fileNameFive); 

	//sum vector created using the respective sources
	sumVectors(sum, sourceOne, sourceTwo, sourceThree, sourceFour, sourceFive);

	//initializing subVectorForSum
	initializeSubVector(subVectorForSum, (int)sourceOne.size());
	 
	//We will now copy the vector to an array of appropriate size
	int *sumArray = new int[(int)sum.size()]; 
	
	/*I am choosing to copy my vectors to arrays for a short period of this program
	The reason for this is because the technology I am using is relatively old and
	running VS in debugging mode does a ton of bounds checking on vectors, this causes the 
	run-time to increase to lengths of 5-10 minutes, which is very inconvenient when attempting to 
	step into functions after merge sort on the sum array*/

	copyToArray(sumArray, sum); 

	//The same will be done with the sub vector for sum
	int *subArrayForSum = new int[(int)subVectorForSum.size()];
	
	//copying to array
	copyToArray(subArrayForSum, subVectorForSum);

	

	//We will now sort the sum array using the subArrayForSum as a mirror array
	//The mirror array will do as its name suggests, it will copy every single sway that
	//the sumArray does, except it will track index positioning

	mergeSortForSum(sumArray, subArrayForSum, 0, (int)sum.size() - 1);

	

	

	//The SumArray has now been sorted, and the indexes have been kept track of. 
	//Now to convert the sources to the appropriate format
	int* sourceOneArray = new int[(int)sourceOne.size()]; 
	int* sourceTwoArray = new int[(int)sourceTwo.size()];
	int* sourceThreeArray = new int[(int)sourceThree.size()];
	int* sourceFourArray = new int[(int)sourceFour.size()];
	int* sourceFiveArray = new int[(int)sourceFive.size()];



	//swapping the index values (appropriate format)
	MYswap(sourceOne, subArrayForSum, sourceOneArray); 
	MYswap(sourceTwo, subArrayForSum, sourceTwoArray);
	MYswap(sourceThree, subArrayForSum, sourceThreeArray);
	MYswap(sourceFour, subArrayForSum, sourceFourArray);
	MYswap(sourceFive, subArrayForSum, sourceFiveArray);


	//now it is time to count inversions... This is done by using an object in a header file
	//The object will output the number of inversions and the respective sorting algorithm

	//all overloaded with an argument that accepts the size of the source file
	Sorting sourceOneOBJ((int)sourceOne.size()); 
	Sorting sourceTwoOBJ((int)sourceTwo.size()); 
	Sorting sourceThreeOBJ((int)sourceThree.size()); 
	Sorting sourceFourOBJ((int)sourceFour.size()); 
	Sorting sourceFiveOBJ((int)sourceFive.size()); 
	 
	

	//creates a vector in the object... might be necessary to switch to array for sort implementation 
	/*Since I will be running in debugging mode and memory complexity is relatively low for this program
	I will be converting my vectors to arrays in the code, for certain sorting algorithms.
	This will help reduce the time requirements by avoiding bounds checking*/

	 

	sourceOneOBJ.createVector(sourceOneArray); 
	sourceTwoOBJ.createVector(sourceTwoArray); 
	sourceThreeOBJ.createVector(sourceThreeArray); 
	sourceFourOBJ.createVector(sourceFourArray); 
	sourceFiveOBJ.createVector(sourceFiveArray); 
	 
	/*
	A 2-d array that will hold 4 values for the inversions
	row 0: Merge inversions
	row 1: quicksort inversions
	row 2: insertion sort inversions
	row 3: brute for inversions
	
	Column 1: source one
	column 2: source two
	column 3: source three
	column 4: source four
	column 5: source five
	*/
	long int results[4][5]; 

	

	//merge method
	results [0][0] = sourceOneOBJ.getInversionsMerge(); 
	results [0][1] = sourceTwoOBJ.getInversionsMerge(); 
	results [0][2] = sourceThreeOBJ.getInversionsMerge(); 
	results [0][3] = sourceFourOBJ.getInversionsMerge(); 
	results [0][4] = sourceFiveOBJ.getInversionsMerge();

	//quicksort method
	results[1][0] = sourceOneOBJ.getInversionsQuicksort();
	results[1][1] = sourceTwoOBJ.getInversionsQuicksort();
	results[1][2] = sourceThreeOBJ.getInversionsQuicksort();
	results[1][3] = sourceFourOBJ.getInversionsQuicksort();
	results[1][4] = sourceFiveOBJ.getInversionsQuicksort();

	//insertion method
	results[2][0] = sourceOneOBJ.getInversionsInsertionSort();
	results[2][1] = sourceTwoOBJ.getInversionsInsertionSort();
	results[2][2] = sourceThreeOBJ.getInversionsInsertionSort();
	results[2][3] = sourceFourOBJ.getInversionsInsertionSort();
	results[2][4] = sourceFiveOBJ.getInversionsInsertionSort();

	//brute force method O(n^2) method which detects all elements that are greater than the selected element
	//will produce times comparable to insertion sort... considering we have a data set of only 10,000
	//O(n^2) is not that bad (when ran in a release build)
	results[3][0] = sourceOneOBJ.bruteForceInversions();
	results[3][1] = sourceTwoOBJ.bruteForceInversions();
	results[3][2] = sourceThreeOBJ.bruteForceInversions();
	results[3][3] = sourceFourOBJ.bruteForceInversions();
	results[3][4] = sourceFiveOBJ.bruteForceInversions();

	//display results
	display(results);
	
}

void readFile(vector<int> &mySource, string fileSourceName)
{
	//a will be used to store values while the file is being read from
	int a; 
	ifstream myFile; 

	myFile.open("file" + fileSourceName + ".txt");//opening with a concatenation argument 

	while (myFile >> a)//simple condition (reading)
	{
		mySource.push_back(a);//pushing back
	}

	return; 
}

void sumVectors
(vector<int>& sum, const vector<int> &one, const vector<int> &two,
const vector<int> &three, const vector<int> &four, const vector<int> &five)
{
	int a; 
	for (int i = 0; i < (int)one.size(); i++)
	{
		a = one[i] + two[i] + three[i] + four[i] + five[i]; 
		sum.push_back(a); 
	}

	return; 
}

void initializeSubVector(vector<int>& myVector, int size)
{
	for (int i = 0; i < size; i++)
	{
		myVector.push_back(i); 
	}
	return;
}

void copyToArray(int myArray[],const vector <int> &myVector)
{
	for (int i = 0; i < (int)myVector.size(); i++)
	{
		myArray[i] = myVector[i]; 
	}
	return; 
}

void mergeSortForSum(int sumArray[], int subArray[], int l, int r)
{
	 
	//base case
	if (l >= r)
	{
		return; 
	}
	//general case
	else
	{
		int mid = (r + l) / 2; 

		mergeSortForSum(sumArray, subArray, l, mid); 
		mergeSortForSum(sumArray, subArray, mid + 1, r);
		mergeSum(sumArray, subArray, l, mid, r); 
	}
	return; 
}

void mergeSum(int sumArray[], int subArray[], int l, int m, int r)
{
	int n1 = m - l + 1; 
	int n2 = r - m; 

	int *L1 = new int[n1]; 
	int *R1 = new int[n2];

	int *L2 = new int[n1];
	int *R2 = new int[n2];
	
	for (int i = 0; i < n1; i++)
	{
		L1[i] = sumArray[l + i]; 
		L2[i] = subArray[l + i];
	}

	for (int i = 0; i < n2; i++)
	{
		R1[i] = sumArray[m + 1 + i]; 
		R2[i] = subArray[m + 1 + i];

	}

	int i = 0; 
	int j = 0; 
	int k = l; 

	while (i < n1 && j < n2)
	{
		if (L1[i] < R1[j])
		{
			sumArray[k] = L1[i]; 
			subArray[k] = L2[i]; 
			i++; 
		}

		else
		{
			sumArray[k] = R1[j];
			subArray[k] = R2[j];
			j++; 
		}

		k++; 
	}

	while (i < n1)
	{
		sumArray[k] = L1[i]; 
		subArray[k] = L2[i]; 
		i++; 
		k++; 
	}

	while (j < n2)
	{
		sumArray[k] = R1[j]; 
		subArray[k] = R2[j]; 

		j++; 
		k++; 

	}

	return; 
}

void MYswap(vector <int> myVector,int myTrackingArray[], int myArray [])
{
	//myArray will hold the values from the vector
	//myVector contains the values of the sum of the sources
	//myTrackingArray contains the values of the indexes required to swap to the myArray
	for (int i = 0; i < (int)myVector.size(); i++)
	{
		myArray[i] = myVector[myTrackingArray[i]]; 
	}
}

//complete output function. Very modular for later revision.
void display(long int a[][5])
{

	string b[5] = { "One","Two","Three","Four" , "Five" }; 

	cout << "Number Of Inversions" << endl << endl; 
	
	cout << "source:" <<setw(22);

	for (int i = 0; i < 5; i++)
	{
		cout << b[i] << "       ";
	}

	cout << endl; 

	cout << "Merge sort results:" << setw(14);

	for (int i = 0; i < 5; i++)
	{
		cout << a[0][i] << "   ";
	}
	cout << endl; 
	cout << "Quicksort results: " << setw(14);

	for (int i = 0; i < 5; i++)
	{
		cout << a[1][i] << "   ";
	}

	cout << endl; 
	cout << "Insertion sort results:" << setw(10);

	for (int i = 0; i < 5; i++)
	{
		cout << a[2][i] << "   ";
	}

	cout << endl; 
	cout << "Brute force comparison:" << setw(10);

	for (int i = 0; i < 5; i++)
	{
		cout << a[3][i] << "   ";
	}
	
	cout << endl <<endl;

	long int max = 0, min = numeric_limits<long int> :: max(); 
	int sourceBad, sourceGood; 

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (max < a[3][(long int)j])
			{
				max = a[3][(long int)j];
				sourceBad = j + 1; 
			}
			else if (min > a[3][(long int)j])
			{
				min = a[3][(long int)j];
				sourceGood = j + 1; 
			}

		}
	}

	cout << "Source " << sourceBad << " was the worst with " << max << " inversions." << endl; 
	cout << "Source " << sourceGood << "  was the best with " << min << " inversions." << endl; 
}
