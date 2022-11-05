// Wes Ostlund 
// MP3
// Library of sort functions implemented as functor objects, reusing sort function code from MP1 which was updated to support vectors
// Citation: seed code from Matthew Bell used as a crutch for sortFunc class, also using his bubblesort code

#include <string>
#include <vector>
#include <chrono> // for recording how long each functor takes to run

#ifndef SORTFUNC_H
#define SORTFUNC_H

//sortFunc is the base class
template <typename T>
class sortFunc { // Citation: MTB
private:
	int idNum; // holds id number of functor
	std::string name; // holds name of functor
protected:
	double lastRunTime; // stores how many microseconds it took for functor to run
public:
	static unsigned int idPool; // For assigning an ID to each sort class
	sortFunc(std::string name = "None assigned") :
		idNum(++idPool), // increase total number of functors in idpool
		name(name), // name will be assigned the given name
		lastRunTime(-1.0) {}
	//Default polymorphic function, purely virtual
	virtual void operator()(std::vector<T>& unsorted) = 0;

	int getID() const { return idNum; } // returns id number
	std::string getName() const { return name; } // returns functor name

	double LRT() {
		return lastRunTime; // returns time in microseconds
	}
	
};

// classes for sort functors are child classes of the sortFunc class
template <typename T> 
class bubbleSort : public sortFunc<T> { // bubblesort functor
public:
	bubbleSort(std::string name = "None assigned") : sortFunc<T>(name) {} // functor constructor that takes in a name
		
	void operator()(std::vector<T>& unsorted); // overloaded () operator, implemented later, which will run the actual sort on the vector "unsorted"
};

template <typename T>
class insertionSort : public sortFunc<T> {
public:
	insertionSort(std::string name = "None assigned") : sortFunc<T>(name) {}
		
	void operator()(std::vector<T>& unsorted); // () operator overloading, implemented later
};

template <typename T>
class selectionSort : public sortFunc<T> { // same formula as before
public:
	selectionSort(std::string name = "None assigned") : sortFunc<T>(name) {}
		
	void operator()(std::vector<T>& unsorted);
};

// quicksort commented out
// template <typename T>
// class quickSort : public sortFunc<T> { // QUICKSORT NOT WORKING AS A FUNCTOR
// private:
//  int partition(vector<T>& sortThis, int start, int end){
//  int pivot = sortThis[end]; // arbitrarily set pivot to be end value of vector
//     int pivotIndex = start; // initialize pivot index as the start index, value will be incremented each time a value smaller than pivot is found

//     for (int i = start; i < end; i++) // loop through vector
//     { 
//         if (sortThis[i] < pivot) // if current vector value is less than pivot
//         {
//             swap(sortThis[i], sortThis[pivotIndex]); // we know to swap that value with the pivot index, as i will be to the left of pivot
//             pivotIndex++; // and increment pivot index to keep moving up
//         }
//     }
//     swap(sortThis[end], sortThis[pivotIndex]); // once complete, use pivot index value to put pivot in its final place

//     return pivotIndex; // return the index of pivot element in its final position
//  }

// public:
// 	quickSort(std::string name = "None assigned") : sortFunc<T>(name) {}
		
// 	void operator()(std::vector<T>& unsorted, int abegin, int finish);
// };


#endif

// template<typename T>
// inline void quickSort<T>::operator()(std::vector<T>& unsorted, int abegin, int finish){ // having more than one argument for the overloaded () causes problems  
// 	auto start = std::chrono::high_resolution_clock::now(); // start count

// 	if (abegin < finish) // base case when start and end overlap 
//     {
//         int index = partition(unsorted, abegin, finish); // partition returns the index to use in dividing the vector into upper and lower halves
//         (unsorted, abegin, (index-1)); // sort left half
//         (unsorted, (index+1), finish);   // sort right half
//     }
// 	auto end = std::chrono::high_resolution_clock::now(); // end count
// 	this->lastRunTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count();
// }



template<typename T>
inline void selectionSort<T>::operator()(std::vector<T>& unsorted){ // () operator overloading for selection sort
	auto start = std::chrono::high_resolution_clock::now(); // start count
	//
	for (int i = 0; i < unsorted.size(); i++) // loop through the vector from start to end
    {
        int smallest = i; // index of the smallest element in the unsorted vector is set to i. value at this index will be compared and the index will be updated if a smaller value is found. At the completion of each iteration of the loop, the smallest value of the remaining unsorted values will be in its correct position. initially it is just the first element because nothing else has been compared
        for (int j = (i + 1); j < unsorted.size(); j++) // start at one element higher than current smallest value's index to start comparisons
        {
            if (unsorted[j] < unsorted[smallest]){ // if the element at index j somewhere later in the vector is less than the current smallest value
                smallest = j; // indexes swapped
            swap(unsorted[i], unsorted[smallest]); // values swapped
        }
    }
}
	auto end = std::chrono::high_resolution_clock::now(); // end count
	this->lastRunTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count(); // the current selection sort functor's runtime is recorded
}

template<typename T>
inline void insertionSort<T>::operator()(std::vector<T>& unsorted){  // () operator overload implementation for insertion sort
	auto start = std::chrono::high_resolution_clock::now(); // start timer
	//
	for(int i = 0; i < unsorted.size(); i++){ // loop through the array
        for(int j = i; j >= 1 && unsorted[j] < unsorted[j-1]; j--){ // if there are two or more elements in the array and the element at i is less than the element before
            swap(unsorted[j], unsorted[j-1]); // then swap those elements, loop continues to run via decrementing j.
        }
    }
	//
	auto end = std::chrono::high_resolution_clock::now(); // end timer
	this->lastRunTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count(); // assign last run time for this functor
}

template<typename T>
inline void bubbleSort<T>::operator()(std::vector<T>& unsorted) // Citation: the code for bubblesort is entirely Matt's, I included it just to have an extra sort which ended up being helpful since i was unable to get quicksort working as a functor
{
	auto start = std::chrono::high_resolution_clock::now();
	bool swapped = true;
	int last = unsorted.size();
	while (swapped) {
		swapped = false;
		for (int i = 0; i < last - 1; i++) {
			if (unsorted[i] > unsorted[i + 1]) {
				T temp = unsorted[i];
				unsorted[i] = unsorted[i + 1];
				unsorted[i + 1] = temp;
				swapped = true;
			}
		}
		last--;
	}
	auto end = std::chrono::high_resolution_clock::now();
	this->lastRunTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count();
}
