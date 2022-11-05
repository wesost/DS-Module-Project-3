// Wes Ostlund
// MP3
// CS273-2


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sorts.h>
#include <fstream>
#include "..\headers\sortFunctors.h"
using std::ifstream;

template <typename T> 
unsigned int sortFunc<T>::idPool = 0; // initialize idpool so that each functor has its own ID

// main() takes in a .txt file of random numbers, and prompts the user to pit different sorting functions 
// (which have been implemented as functors) against each other in a race to see which sorts the file fastest.
// NOTE: I was unable to get my own quicksort implemented as a functor, so everything having to do with 
// my quicksort functor in sortFunctors.h and main.cpp has been commented out. Instead I used matt's bubblesort from
// the example seed code so that I would have at least 3 sorts.
int main()
{
	std::vector<int> sortme; // create a vector to hold randomnumbers.txt
	ifstream randoms; // create an ifstream object 
	randoms.open("random numbers.txt"); // open .txt file
	int holder; // 
	while (randoms >> holder) // read numbers into vector
	{
		sortme.push_back(holder);
	}

	std::vector<int> sortme2; // create  more vectors to sort
	std::vector<int> sortme3;
	// std::vector<int> sortme4; // only need 3 vectors to sort due to quicksort not working
	sortme2 = sortme; // make a copy from the first vector so we have identical vectors to sort with different algorithms
	sortme3 = sortme; 
	//sortme4 = sortme; // would be used to give 4 separate unsorted arrays so that 4 sorts could be used, however, quick sort doesn't work so only 3 are needed

	std::list<sortFunc<int> *> sortList; // initialize linked list of functors - this code is reused from MTB's seed code

	int steeringWheel = 0; // stores user input to "steer" the program

	// Loop starts
	do
	{
		std::cout << "**** Sorting functor race! ****" << std::endl << " Enter -1- to add sort, -2- to display the sorts you've chosen, or -3- to run the race." << std::endl;
		std::cin >> steeringWheel; // see what the user wants to do

		switch (steeringWheel) // proceed depending on user input. the number entered will correspond to a case
		{
		case (1): // add a sort
		{
			int sortNum = 0; // like steeringWheel, this will store input for a nested switch statement
			std::cout << "Enter -1- for insertion sort, -2- for selection sort, -3- for bubble sort \n";
			std::cin >> sortNum; // here we grab which sort the user wants to add to the race

			switch (sortNum) 
			{
			case (1): // for each case corresponding to a different sort, a new functor of the desired sort type is added to the list
			{
				sortList.push_back(new insertionSort<int>("Insertion sort")); // user input of 1 means an insertion sort functor will be added 
				std::cout << "-----Insertion sort has been added----- " << std::endl;
				break; // it is then safe to break back to the starting menu
			}

			case (2): // subsequent cases follow same formula as case(1), with different sorts
			{
				sortList.push_back(new selectionSort<int>("Selection sort"));
				std::cout << "-----Selection sort has been added----- " << std::endl;
				break;
			}

			case (3):
			{
				sortList.push_back(new bubbleSort<int>("Bubble sort"));
				std::cout << "-----Bubble sort has been added----- " << std::endl;
				break;
			}

			// case (4):
			// {
			// 	sortList.push_back(new quickSort<int>("Quick sort"));
			// 	std::cout << "-----Quick sort has been added----- " << std::endl; 
			// 	break;
			// }

			default: // if user enters an invalid number they also return to the main menu to restart and give a valid input
			{
				std::cout << "Please enter a valid number. " << std::endl;
				break;
			}
			}

			break;
		}

		case (2): // display all sorts in list
		{
			if (sortList.empty()){
					std::cout << "Add sorts to the race to see them here " << std::endl; // if nothing's been added let user know list is still empty
			}

			std::list<sortFunc<int> *>::iterator mit; // initialize an iterator to go through the list
			for (mit = sortList.begin(); mit != sortList.end(); ++mit)
			{
				std::cout << "Sort " << (*mit)->getID() << ": " << (*mit)->getName() << "." << std::endl; // grab relevant data from each functor object and display
			}

			break; // return to main menu
		}

		case (3): // run race
		{
			if (sortList.empty()){
				std::cout << "Pick some sorts to race before starting the race! " << std::endl; // if no sorts have been picked, let user know
			}

			std::list<sortFunc<int> *>::iterator lit; // initialize an iterator 
			for (lit = sortList.begin(); lit != sortList.end(); ++lit) // go through the list and feed the unsorted vector to each sort functor 
			{
				switch ((*lit)->getID()) // the id number corresponds to each functor's position in the list
				{
				case (1): // so depending on if it is the first second third or fourth sort added, it will sort the first second or third unsorted vector (see lines 34-38)
				{
					(*(*lit))(sortme); // this way each functor gets an unsorted vector...
					break;
					//(*(*lit))(sortme); -> this is Matt's code for accessing functor objects out of the linked list. 
									   //*lit derefrences the iterator, leaving you with a pointer to the functor. 
									   //(*(*lit)) dereferences the pointer to the functor, giving the actual functor object we're after,
									   // which sortme is passed to
				}

				case (2):
				{
					(*(*lit))(sortme2); //... avoiding a case where the same vector is sorted by separate functors, in which case only the first functor would actally have to deal with an unsorted vector
					break;
				}
				case (3):
				{
					(*(*lit))(sortme3); // case 1-4 do the same thing with a different copy of the unsorted vector
					break;
				}

				// case (4):
				// {
				// 	(*(*lit))(sortme4); // only need 3 
				// 	break;
				// }

				
				default: // if sorts >= idnum 3 are added, they will show how that sort does with an already sorted vector.
				{
					std::cout << "Any sort functors beyond the first 3 won't sort a new vector, but you can see how long they take to sort an already sorted one! " << std::endl;
					(*(*lit))(sortme);
					break;
				}
				}

				std::cout << "How many microseconds did functor " << (*lit)->getID() << ": " << (*lit)->getName() << " take?" << std::endl;
				std::cout << (*lit)->LRT() << std::endl; // display how much time it took for each functor to sort the vector
			}

			for (lit = sortList.begin(); lit != sortList.end(); ++lit) // delete any functor objects we created using dynamic memory allocation
				delete (*lit);
			break;
		}

		default:
		{
			std::cout << "Please enter a valid number. " << std::endl; // default covers the possibility of a number entered outside the range of 1-3
			break;
		}
		}

	} while (steeringWheel != 3); // the loop exits when the user decides to run the race

	std::cout << "Race over! " << std::endl;

	randoms.close(); // close the file we worked with
	return 0;
}