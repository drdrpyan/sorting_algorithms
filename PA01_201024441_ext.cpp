//2014년 2학기 알고리즘 과제2 PA1

//BGM_Sort.h
#ifndef __BGM_SORT_H__
#define __BGM_SORT_H__

#include <fstream>

using std::ifstream;

namespace BGM
{
	template <typename T>
	class Sort
	{
	private:
		static void swap(T& a, T& b);
		static int readFile(ifstream& ifs, T* buffer);
		static void fileMerge(int file1Num, int file2Num, int outFileNum, bool(*compare)(const T&, const T&));
	public:
		static void BubbleSort(T* arr, int length, bool(*compare)(const T&, const T&));
		static void QuickSort(T* arr, int length, bool(*compare)(const T&, const T&));
		static void MergeSort(T* arr, int length, bool(*compare)(const T&, const T&));
		static void RadixSort(T* arr, int length, int maxPower, int radix);
		static void ExternalMergeSort(const char* inFileName, const char* outFileName, bool(*compare)(const T&, const T&));
		static bool outputCheck(const char* outputFile, bool(*compare)(const T&, const T&));
	};
}

#endif

#ifndef __BGM_SORT_CPP__
#define __BGM_SORT_CPP__

#define BUFFER_SIZE 1024

#include <fstream>
#include <stdexcept>
#include <vector>
#include <list>
#include <stdlib.h>

using std::exception;
using std::vector;
using std::list;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::endl;

namespace BGM
{
	template<typename T>
	void Sort<T>::swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	int Sort<T>::readFile(ifstream& ifs, T* buffer)
	{
		int i=0;
		for(i=0; i<BUFFER_SIZE && ifs>>buffer[i]; i++);
		ifs.close();
		
		return i;
	}

	template<>
	int Sort<int>::readFile(ifstream& ifs, int* buffer)
	{
		int i=0, temp=0;
		ifs >> temp;
		for(i=0; i<BUFFER_SIZE && temp!=-1; i++)
		{
			buffer[i] = temp;
			ifs >> temp;
		}
		ifs.close();

		return i;
	}

	template<typename T>
	void Sort<T>::fileMerge(int file1Num, int file2Num, int outFileNum, bool(*compare)(const T&, const T&))
	{
		throw exception("not implemented");
	}

	template<>
	void Sort<int>::fileMerge(int file1Num, int file2Num, int outFileNum, bool(*compare)(const int&, const int&))
	{
		char strbuff[10];
		sprintf(strbuff, "%d", file1Num);
		ifstream ifs1(strbuff);
		sprintf(strbuff, "%d", file2Num);
		ifstream ifs2(strbuff);
		sprintf(strbuff, "%d", outFileNum);
		ofstream ofs(strbuff);

		int buff1[BUFFER_SIZE];
		int buff2[BUFFER_SIZE];

		int buff1Size = Sort<int>::readFile(ifs1, buff1);
		int buff2Size = Sort<int>::readFile(ifs2, buff2);
		int i1=0, i2=0;

		while(buff1Size==0 || buff2Size==0)
		{
			i1=0;
			i2=0;
			while(i1<buff1Size && i2<buff2Size)
			{
				if(compare(buff1[i1], buff2[i2]))
					ofs << buff1[i1++] << endl;
				else
					ofs << buff2[i2++] << endl;
			}
			if(i1==buff1Size)
				buff1Size = Sort<int>::readFile(ifs1, buff1);
			else if(i2==buff2Size)
				buff2Size = Sort<int>::readFile(ifs2, buff2);
		}
		if(buff1Size==0)
			do
			{
				for(int i=0; i<buff2Size; i++)
					ofs << buff2[i] << endl;
			} while((buff2Size=Sort<int>::readFile(ifs2, buff2)) == 0);
		else if(buff2Size==0)
			do
			{
				for(int i=0; i<buff1Size; i++)
					ofs << buff1[i] << endl;
			} while((buff1Size=Sort<int>::readFile(ifs1, buff1)) == 0);

		ofs << -1;

		ifs1.close();
		ifs2.close();
		ofs.close();				
	}

	template<typename T>
	void Sort<T>::BubbleSort(T* arr, int length, bool(*compare)(const T&, const T&))
	{
		for(int i=1; i<length; i++)
			for(int j=0; j<length-1; j++)
				if(!compare(arr[j], arr[j+1]))
					swap(arr[j], arr[j+1]);
	}

	template<typename T>
	void Sort<T>::QuickSort(T* arr, int length, bool(*compare)(const T&, const T&))
	{
		if(length <= 1)
			return;

		T pivot = arr[0];
		int i,j=0;
		for(i=1; i<length; i++)
			if(compare(arr[i], pivot))
			{
				j++;
				swap(arr[i], arr[j]);
			}
		swap(arr[0], arr[j]);

		QuickSort(arr, j, compare);
		QuickSort(arr+j+1, length-j-1, compare);
	}

	template<typename T>
	void Sort<T>::MergeSort(T* arr, int length, bool(*compare)(const T&, const T&))
	{
		if(length <= 1)
			return;

		MergeSort(arr, length/2, compare);
		MergeSort(arr+length/2, length-length/2, compare);

		T* tempArray = new T[length];
		int tempIdx=0, part1Idx=0, part2Idx=length/2;

		while(part1Idx<length/2 && part2Idx<length)
		{
			if(compare(arr[part1Idx], arr[part2Idx]))
				tempArray[tempIdx++] = arr[part1Idx++];
			else
				tempArray[tempIdx++] = arr[part2Idx++];
		}
		if(part1Idx==length/2)
			while(part2Idx < length)
				tempArray[tempIdx++] = arr[part2Idx++];
		else
			while(part1Idx < length/2)
				tempArray[tempIdx++] = arr[part1Idx++];

		for(int i=0; i<length; i++)
			arr[i] = tempArray[i];
	}

	template<typename T>
	void Sort<T>::RadixSort(T* arr, int length, int maxPower, int radix)
	{
		throw exception("not implemented");
	}

	template<>
	void Sort<int>::RadixSort(int* arr, int length, int maxPower, int radix)
	{
		vector<int>* queues = new vector<int>[radix];
		int currentP, idx;
		
		for(int p=0; p<maxPower; p++)
		{
			currentP=1;
			for(int i=0; i<p; i++)
				currentP *= radix;

			for(int i=0; i<length; i++)
				queues[(arr[i]/currentP)%radix].push_back(arr[i]);

			idx = 0;
			for(int i=0; i<radix; i++)
			{
				for(int j=0; j<(int)queues[i].size(); j++)
					arr[idx++] = queues[i][j];
				queues[i].clear();
			}
		}
	}

	template<typename T>
	void Sort<T>::ExternalMergeSort(const char* inFileName, const char* outFileName, bool(*compare)(const T&, const T&))
	{
		throw exception("not implemented");
	}

	template<>
	void Sort<int>::ExternalMergeSort(const char* inFileName, const char* outFileName, bool(*compare)(const int&, const int&))
	{
		ifstream ifs(inFileName);
		ofstream tempOfs;
		list<int> tempFiles;

		int buffer[BUFFER_SIZE];
		int bufferSize;
		char strbuff[10];

		//split
		int tempFile=0;
		do
		{
			//read to buffer
			bufferSize = Sort<int>::readFile(ifs, buffer);

			//sort buffer
			Sort<int>::QuickSort(buffer, bufferSize, compare);

			//save buffer to file
			sprintf(strbuff, "%d", tempFile);
			tempOfs.open(strbuff, ios::out);
			for(int i=0; i<bufferSize; i++)
				tempOfs << buffer[i] << endl;
			tempOfs << -1;
			tempOfs.close();
			tempOfs.clear();
			tempFiles.push_back(tempFile++);
		} while(bufferSize == 0);

		//merge
		int if1, if2;
		while(tempFiles.size() > 1)
		{
			if1 = tempFiles.front();
			tempFiles.pop_front();
			if2 = tempFiles.front();
			tempFiles.pop_front();
			Sort<int>::fileMerge(if1, if2, tempFile, compare);
			sprintf(strbuff, "%d", tempFile-2);
			remove(strbuff);
			sprintf(strbuff, "%d", tempFile-1);
			remove(strbuff);
			tempFiles.push_back(tempFile++);
		}
		sprintf(strbuff, "%d", tempFile-1);
		rename(strbuff, outFileName);
	}

	template<typename T>
	bool Sort<T>::outputCheck(const char* outputFile, bool(*compare)(const T&, const T&))
	{
		throw exception("not implemented");
	}

	template<>
	bool Sort<int>::outputCheck(const char* outputFile, bool(*compare)(const int&, const int&))
	{
		ifstream ifs(outputFile);
		int temp1=0, temp2=0;

		ifs>>temp1;
		ifs>>temp2;
		while(temp1!=-1 || temp2!=-1)
		{
			if(temp2!=-1 && !compare(temp1, temp2))
				return false;
			temp1 = temp2;
			ifs >> temp2;
		}
		return true;
	}
}


#endif


//Main.cpp
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <stdlib.h>
//#include "BGM_Sort.h"

using namespace std;
using BGM::Sort;

bool intAscending(const int& a, const int& b)
{
	return a<b;
}

void arrReset(int* arr, const vector<int>& vec)
{
	for(int i=0; i<vec.size(); i++)
		arr[i] = vec[i];
}

void testResult(int* arr, int length, bool(*compare)(const int&, const int&))
{
	int i=0;
	for(i=0; i<length-1 && compare(arr[i],arr[i+1]); i++);

	if(i==length-1)
		cout << "OK" << endl;
	else
		cout << "Error" << endl;
}

int main(int argc, char** argv)
{
	char* inFileName;
	char* outFileName;

	if(argc==5 && !strcmp(argv[1], "-i") && !strcmp(argv[3],"-o"))
	{
		inFileName = argv[2];
		outFileName = argv[4];
	}
	else if(argc==5 && !strcmp(argv[1], "-o") && !strcmp(argv[3], "-i"))
	{
		inFileName = argv[4];
		outFileName = argv[2];
	}
	else
	{
		cout << "-help : help" << endl;
		cout << "-i [input file] -o [output file]" << endl;
		return 1;
	}

	ifstream ifs(inFileName);
	ofstream ofs(outFileName);

	cout << "start" << endl;
	cout << "file read..." << endl;
	vector<int> source;
	int temp;
	ifs>>temp;
	while(temp!=-1)
	{
		source.push_back(temp);
		ifs >> temp;
	}
	cout << "complete" << endl;

	cout << "set array..." << endl;
	int *sourceArray = new int[source.size()];
	arrReset(sourceArray, source);
	cout << "complete" << endl;

	clock_t start, end;

	cout << "Bubble Sorting..." << endl;
	start = clock();
	Sort<int>::BubbleSort(sourceArray, source.size(), intAscending);
	end = clock();
	float bubbleResult = (float)(end-start)/CLOCKS_PER_SEC;
	//testResult(sourceArray, source.size(), intAscending);
	cout << "complete" << endl;
	arrReset(sourceArray, source);

	cout << "Quick Sorting..." << endl;
	start = clock();
	Sort<int>::QuickSort(sourceArray, source.size(), intAscending);
	end = clock();
	float quickResult = (float)(end-start)/CLOCKS_PER_SEC;
	//testResult(sourceArray, source.size(), intAscending);
	cout << "complete" << endl;
	arrReset(sourceArray, source);

	cout << "MergeSorting..." << endl;
	start = clock();
	Sort<int>::MergeSort(sourceArray, source.size(), intAscending);
	end = clock();
	float mergeResult = (float)(end-start)/CLOCKS_PER_SEC;
	//testResult(sourceArray, source.size(), intAscending);
	cout << "complete" << endl;
	arrReset(sourceArray, source);

	cout << "RadixSorting..." << endl;
	start = clock();
	Sort<int>::RadixSort(sourceArray, source.size(), 32, 2);
	end = clock();
	float radixResult = (float)(end-start)/CLOCKS_PER_SEC;
	//testResult(sourceArray, source.size(), intAscending);
	cout << "complete" << endl;
	arrReset(sourceArray, source);

	cout << "ExternalSorting..." << endl;
	start = clock();
	char strbuff[50];
	strcpy(strbuff, outFileName);
	strcat(strbuff, ".result");
	Sort<int>::ExternalMergeSort(inFileName, strbuff, intAscending);
	end = clock();
	float externalResult = (float)(end-start)/CLOCKS_PER_SEC;

	cout << "all complete" << endl;

	
	ofs << "Comparison of sorting" << endl;
	ofs << "======================" << endl;
	ofs << "* No. of items : " << source.size() << endl;
	ofs << "\t\t\t\t\t\tunit:sec" << endl;
	ofs << "---------------------------------------------------------------------------------" << endl;
	ofs << "|Bubble\t\t|Quick\t\t|Merge\t\t|Radix\t\t|External\t|" << endl;
	ofs << "---------------------------------------------------------------------------------" << endl;
	ofs << "|" << bubbleResult << "\t\t|"<< quickResult << "\t\t|" << mergeResult << "\t\t|"
		<< radixResult << "\t\t|" << externalResult << "\t\t|" << endl;
	ofs << "---------------------------------------------------------------------------------" << endl;
	
	return 0;
}

