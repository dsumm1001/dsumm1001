/**
 * @file main.cpp
 * @author Doug Summerlin (dsummerl@umd.edu)
 * @brief This is my first RWA, it is a box sorting program
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//import libaries
#include <iostream> 

/*function prototypes here*/
unsigned int get_total_parts(unsigned int);
void get_total_boxes();
void get_box_capacities();
void fill_boxes();

/*define your data structures here*/

/*struct S {
	unsigned int boxS_qty;
	unsigned int ppS_box;
};
struct M {
	unsigned int boxM_qty;
	unsigned int ppM_box;
};
struct L {
	unsigned int boxL_qty;
	unsigned int ppL_box;
};
struct XL { 
	unsigned int boxXL_qty;
	unsigned int ppXL_box;
};*/

//define struct with uints for qty and parts per box of each size
struct boxstruct {
	unsigned int boxS_qty;
	unsigned int ppS_box;
	unsigned int boxM_qty;
	unsigned int ppM_box;
	unsigned int boxL_qty;
	unsigned int ppL_box;
	unsigned int boxXL_qty;
	unsigned int ppXL_box;
};


/*function definitions here*/

/**
 * * @brief Get the total number of parts to be placed in boxes
 * * @return unsigned Number of parts entered by the user
 */
unsigned int get_total_parts(){
	//define placeholder variable for user input
	int entry;

	//define static uint for final parts value
	static unsigned int parts;

	//prompt user and ask for input
	std::cout << "How many parts in total? ";
	std::cin >> entry;
	//std::cout << "There are " << entry << " parts in total." << '\n';
	
	// while the entry is not a positive integer, prompt the user
	// for a new value that meets the criteria
	while(entry < 1){
		std::cout << "Please enter a real number greater than zero. How many parts in total? ";
		std::cin >> entry;
		//std::cout << "There are " << entry << " parts in total." << '\n';;
	}

	// make parts equal to the user entry and return it
	parts = entry;
	//std::cout << "Type of parts is " << typeid(parts).name() << '\n';
	return parts;
}

/**
 * @brief Get the total number of boxes for each type
 * @param <data_structure> Data structure to hold box/part information
 * @return Void
 */
void get_total_boxes(boxstruct& boxes){
	//define entries array of length 4 (for 4 sizes)
	int entries[4] = {0};

	//calculate length of array using sizeof()
	int len = sizeof(entries)/sizeof(entries[0]);

	//print prompt for user to terminal
	std::cout << "Enter the number of each box from S/M/L/XL (separated by a space): ";
	//loop to fill array, iterated as many times as array variables
	for (int i =0; i < len; i++){
		std::cin >> entries[i];
	}
	//std::cout << "No. of M boxes: " << entries[1] << '\n';

	/*this loop has lots of criteria; if any value is not a
	  positive integer, then prompt the
	  user for new values until the critera are met.
	*/
	while(entries[0]<1 || entries[1]<1 || entries[2]<1 || entries[3]<1){
		std::cout << "Only positive integers. Enter the type of each box from S/M/L/XL (separated by a space): ";
		
		for (int i =0; i < len; i++){
			std::cin >> entries[i];
		}
	}

	//fill struct with values from array
	boxes.boxS_qty = entries[0];
	boxes.boxM_qty = entries[1];
	boxes.boxL_qty = entries[2];
	boxes.boxXL_qty = entries[3];

	//print entered values to terminal
	std::cout << "No. of S/M/L/XL boxes: " << boxes.boxS_qty << "/" << boxes.boxM_qty << "/" << boxes.boxL_qty << "/" << boxes.boxXL_qty << '\n';
	std::cout << "\n";

	return;
}

/**
 * @brief Get the number of parts for each box type
 * @param <data_structure> Data structure to hold box/part information
 * @return Void
 */
void get_box_capacities(boxstruct& boxes){
	//define entries array of length 4 (for 4 sizes)
	int entries[4] = {0};

	//calculate length of array using sizeof()
	int len = sizeof(entries)/sizeof(entries[0]);

	//print prompt for user to terminal
	std::cout << "Enter the no. of parts each box can hold from S/M/L/XL (separated by a space): ";
	//loop to fill array, iterated as many times as array variables
	for (int i =0; i < len; i++){
		std::cin >> entries[i];
	}
	//std::cout << "No. of M boxes: " << entries[1] << '\n';

	/*this loop has lots of criteria; if any value is larger than
	  the successive value or is not a positive integer, then prompt the
	  user for new values until the critera are met.
	*/
	while(entries[0]<1 || entries[1]<1 || entries[2]<1 || entries[3]<1 || entries[0] >= entries[1] || entries[1] >= entries[2] || entries[2] >= entries[3]){
		
		std::cout << "Positive real values only, with larger boxes holding more parts than the previous size. Enter the no. of parts each box can hold from S/M/L/XL (separated by a space): ";
		for (int i =0; i < len; i++){
			std::cin >> entries[i];
		}
	
	}

	/*while(entries[0] >= entries[1] || entries[1] >= entries[2] || entries[2] >= entries[3]){
		std::cout << "Larger boxes must hold more parts than the previous size. Enter the no. of parts each box can hold from S/M/L/XL (separated by a space): ";
		for (int i =0; i < len; i++){
			std::cin >> entries[i];
		}
	}*/
	
	//fill struct with values from array
	boxes.ppS_box = entries[0];
	boxes.ppM_box = entries[1];
	boxes.ppL_box = entries[2];
	boxes.ppXL_box = entries[3];

	//print entered values to terminal
	std::cout << "No. of parts contained in S/M/L/XL boxes: " << boxes.ppS_box << "/" << boxes.ppM_box << "/" << boxes.ppL_box << "/" << boxes.ppXL_box << '\n';
	std::cout << "\n";

	return;

}

/**
 * @brief Fill up boxes using values from user inputs
 * @param boxstruct Data structure to hold box/part information
 * @param num_parts previously user defined total number of parts
 * @return void
 */
void fill_boxes(const boxstruct& boxes, unsigned int num_parts){
	//fill new int with num_parts int
	unsigned int parts_left = num_parts;  

	//fill new variables with data from boxstruct "boxes". Cap == capacity
	unsigned int fullS = 0;
	unsigned int qtyS = boxes.boxS_qty;
	unsigned int capS = boxes.ppS_box;

	unsigned int fullM = 0;
	unsigned int qtyM = boxes.boxM_qty;
	unsigned int capM = boxes.ppM_box;

	unsigned int fullL = 0;
	unsigned int qtyL = boxes.boxL_qty;
	unsigned int capL = boxes.ppL_box;

	unsigned int fullXL = 0;
	unsigned int qtyXL = boxes.boxXL_qty;
	unsigned int capXL = boxes.ppXL_box;
 
	//display initial unaltered number of parts in beginning
	std::cout << "No. of Parts: " << num_parts << '\n';

	//display message with Qty and Capacity
	std::cout << "XL box (" << boxes.boxXL_qty << " x " << boxes.ppXL_box << " MAX): ";
	/* If there are more remaining parts than there are able
	   to be filled by current box size, use all available boxes
	   and subtract from current part total...
	*/
	if (parts_left > qtyXL * capXL){
		parts_left = parts_left - qtyXL*capXL;
		fullXL = qtyXL;
	} else {
		/* If there are less remaining parts than can be filled
		   by the current box size, use modulus to find whole remainder,
		   then subtract mod from parts left to find whole number 
		   (full boxes) divisible by cap size without remainder. 
		   Remainder becomes parts left.
		*/
		int mod = parts_left % capXL;
		fullXL = (parts_left - mod)/capXL;
		parts_left = mod;
	}
	//finish message displaying parts left and full boxes
	std::cout << fullXL << " -- remaining parts: " << parts_left << '\n';


	std::cout << "L box (" << boxes.boxL_qty << " x " << boxes.ppL_box << " MAX): ";
	if (parts_left >= qtyL * capL){
		parts_left = parts_left - qtyL*capL;
		fullL = qtyL;

	} else {
		int mod = parts_left % capL;
		fullL = (parts_left - mod)/capL;
		parts_left = mod;
	}
	std::cout << fullL << " -- remaining parts: " << parts_left << '\n';


	std::cout << "M box (" << boxes.boxM_qty << " x " << boxes.ppM_box << " MAX): ";
	if (parts_left > qtyM * capM){
		parts_left = parts_left - qtyM*capM;
		fullM = qtyM;
	} else {
		int mod = parts_left % capM;
		fullM = (parts_left - mod)/capM;
		parts_left = mod;
	}
	std::cout << fullM << " -- remaining parts: " << parts_left << '\n';


	std::cout << "S box (" << boxes.boxS_qty << " x " << boxes.ppS_box << " MAX): ";
	if (parts_left > qtyS * capS){
		parts_left = parts_left - qtyS*capS;
		fullS = qtyS;
	} else {
		int mod = parts_left % capS;
		fullS = (parts_left - mod)/capS;
		parts_left = mod;
	}
	std::cout << fullS << " -- remaining parts: " << parts_left << '\n';

	//print remaining parts after all possible boxes filled
	std::cout << "Remaining parts, not in boxes: " << parts_left << "\n";
	std::cout << "\n";
	return;
}

/**
 * @brief This is the main function
 * 
 * @return int
 */
int main(){

	//launch message
	std::cout << "\n";
	std::cout << "Hello world, This is Doug's RWA1" << '\n';
	std::cout << "\n";

	//initialize "boxes" struct and "num_parts" int
	static unsigned int num_parts{};
	boxstruct boxes{0,0,0,0,0,0,0,0};

	//call function to get total number of parts
	num_parts = get_total_parts();
	std::cout << "So there are " << num_parts << " total parts..." << '\n';
	std::cout << "\n"; 

	//call function to get total number of boxes of each type
	get_total_boxes(boxes);
		
	//call function to get the max number of parts per box type
	get_box_capacities(boxes);

	//call function to fill up boxes and to display result
	std::cout << "----------------------------------------" << "\n";
	std::cout << "Boxes that can be built with " << num_parts << " parts..." << '\n';
	fill_boxes(boxes, num_parts);

}