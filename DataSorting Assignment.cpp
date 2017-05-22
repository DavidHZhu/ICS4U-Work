/*****************************************************************************
 *	Name:   David Zhu                                                        *
 *	Course: ICS4U                                                            *  
 *	Date: May 15th 2017  		                                                 * 
 *	                                                                         * 
 *	Purpose: Sort Data using various sort algorithms							         *
 *	                                                                         *
 *	Usage: https://think.cs.vt.edu/corgis/csv/hospitals/hospitals.html									 *
 *	       														     *    
 *	                                                                         *
 *	Revision History:  added partition and quickSort with numbers
 						adding user interface for sort method and category                                                   *  
 *	                                                                         *
 *	Known Issues: Kio							         *
 *	                                                                         *  
 *****************************************************************************/
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
char toSort; 
using namespace std;
 
struct Hydropower {
	
	string county;
	float cElevation;
	float cLength;
	float latitude;
	float longitude;
	string name;
	string organization;
	string state;
	float sHeight;
	string watercourse;
	string year;
	
};


// Reads in an int (overloaded function)
void readNext(ifstream &f, int &s) {
	
	string value;
	getline(f, value, ',' ); 
	s = atoi(value.c_str());	//converts to int
	
}

// Reads in a float (overloaded function)
void readNext(ifstream &f, float &s) {
	
	string value;
	getline(f, value, ',' ); 
	s = atof(value.c_str());	//converts to int
	
}

// Reads in string, check for quotes (overloaded function) 
void readNext(ifstream &f, string &s) {
	
	string s1;
	getline(f, s, ',' );
	if (s[0] == '\"') {
		getline(f, s1, '\"' );
		s = s.substr(1, s.length()) + s1;	// strip of quotations. 
	}
	
}

void printLine(Hydropower h) {
	
	cout << setw(30) << h.county << " | ";
	cout << h.latitude << endl;

}

// Quick sort function
void quickSort(vector<Hydropower> &h, int left, int right) {
      int i = left, j = right;
      Hydropower temp;
      
      // Sorting by Latitude
      if (toSort == 'l' || toSort == 'L'){
     	float pivot = h[(left + right) / 2].latitude;
 
	      // While lower counter is less than upper counter - i starts at bottom and goes up, j starts at top goes down
	    while (i <= j) {
	    	// checks if element is on the left relative to pivot
	        while (h[i].latitude < pivot)
	            i++;
	        // checks if element is on the right relative to pivot    
	        while (h[j].latitude > pivot)
	            j--;
	        // swaps left item with right item    
	        if (i <= j) {
	            temp = h[i];
	            h[i] = h[j];
	            h[j] = temp;
	            i++;
	            j--;
	        }
	    }
	}
	
	// Sorting by county 
	if (toSort == 'c' || toSort == 'C') {
    	string pivot = h[(left + right) / 2].county;
 
	      // While lower counter is less than upper counter - i starts at bottom and goes up, j starts at top goes down
	    while (i <= j) {
	    	// checks if element is on the left relative to pivot
	        while (h[i].county < pivot)
	            i++;
	        // checks if element is on the right relative to pivot    
	        while (h[j].county > pivot)
	            j--;
	            
	        if (i <= j) {
	            temp = h[i];
	            h[i] = h[j];
	            h[j] = temp;
	            i++;
	            j--;
	        }
	    }			
	}
		
      // Recusively solve smaller subarrays within original array (no new memory is allocated)
      if (left < j)
            quickSort(h, left, j);
      if (i < right)
            quickSort(h, i, right);
            
}

// Merges elements for Merge Sort (Divide and Conquer) - requires temporary memory to work
void merge(vector<Hydropower> &h, int left, int right, int mid){
	int i = left;
    int k = left;
    int j = mid + 1;
    Hydropower temp[h.size()];	// Temporary data to contain subarrays

    
    // Sorting county:
    if (toSort == 'c' || toSort == 'C') {
	    while (i <= mid && j <= right) {	// two subarrays, left to mid and mid +1 to right
	        if (h[i].county < h[j].county) 	// compares selected value
	            temp[k++] = h[i++];			// comparing sorted lists(from earlier in the year)
	         else 
	            temp[k++] = h[j++];
		}
		
		// Copy remaining elements from subarray 1
	    while (i <= mid) 
	        temp[k++] = h[i++];
	    // Copy remaining elements from subarray 2  
	    while (j <= right) 
	        temp[k++] = h[j++];
	    // Edit new hydropower 
	    for (i = left; i < k; i++) {
	        h[i] = temp[i];

		}
	}
	
	// Sorting latitude:
	if (toSort == 'l' || toSort == 'L') {
	    while (i <= mid && j <= right) {
	        if (h[i].latitude < h[j].latitude) 
	            temp[k++] = h[i++];
	         else 
	            temp[k++] = h[j++];      
	    }
	    
	    while (i <= mid) 
	        temp[k++] = h[i++];
	    
	    while (j <= right) 
	        temp[k++] = h[j++];
	    
	    for (i = left; i < k; i++){
	        h[i] = temp[i];
	        
		}
	}	
			
}	
		
// merge sort recursive algorighthm		
void mergeSort(vector<Hydropower> &h, int left, int right){
	
	int pivot; // the pivot
    if (left < right ){
        pivot = (left + right) / 2;		// finds center, changes every call
        mergeSort(h, left, pivot);		// divide - left subarray
        mergeSort(h, pivot+1, right);	// divide - right subarray
        merge(h, left, right, pivot);	// conquer - merges sorted arrays
    }
    
    return;
	
}

// insertion sort
void insertionSort(vector<Hydropower> &h){
	
	int i, j;
	int moves = 0;
	
	// Sort by latitude:
	if (toSort == 'l' || toSort == 'L') {
		for (i = 1; i < h.size(); i++){
			// Current element:
			float current = h[i].latitude;
			Hydropower cur_location = h[i];
			
			// Find where j should be located in the first i-1 elements:
			for (j = 0; j < i; j++)
				if (h[j].latitude >= current)
					break;
			
			
			// Shift elements down 
			for (int k = i - 1; k >= j; k--)
				h[k + 1] = h[k];
			
			h[j] = cur_location;
			moves++;
		}
		
	}
	
	// Sort by county:
	if (toSort == 'c' || toSort == 'C') {
		for (i = 1; i < h.size(); i++){
			// Current element:
			string current = h[i].county;
			Hydropower cur_location = h[i];
			
			// Find where j should be located in the first i-1 elements:
			for (j = 0; j < i; j++)
				if (h[j].county >= current)
					break;
			
			
			// Shift elements down 
			for (int k = i - 1; k >= j; k--)
				h[k + 1] = h[k];
			
			h[j] = cur_location;
			moves++;
		}
		
	}
	
	cout << "Insertion Sorted in " << moves << " moves" << endl;		
			
}
/************************************** MAIN PROGRAM ***************************************************************************************************************************/

int main(){
	
	// Read in CSV
	vector<Hydropower> hydropower;
	Hydropower h;
	ifstream fin("hydropower.csv");
	if (!fin){
		cerr << "File not found; Check directories!" << endl;
		return -1;
	}
	
	// Throw Away for Headers
	string value;
	char ch;
	getline(fin, value);
	
	int count = 0;
	char method;
	bool isValid = false;
	
	while (fin.good()) {
		count++;
		readNext(fin, h.county);
		readNext(fin, h.cElevation);
		readNext(fin, h.cLength);
		readNext(fin, h.latitude);
		readNext(fin, h.longitude);
		readNext(fin, h.name);
		readNext(fin, h.organization);
		readNext(fin, h.state);
		readNext(fin, h.sHeight);
		readNext(fin, h.watercourse);
		
		// last item read to end of line, rather than comma
		getline(fin, h.year);
		if (fin.good())  {
			hydropower.push_back(h);
		}
	}
	
	// Takes in input and decides which method to use
	cout << "Sort by: County(C) or Latitude(L): ";
	cin >> toSort;
	
	//Category:
	switch(toSort){
		case 'C':
		case 'c':
			isValid = true;
			cout << "Sort by County:" << endl;
			break;
		case 'L':
		case 'l':
			isValid = true;
			cout << "Sort by Latitude:" << endl;
			break;
		default:
			cout << "Invalid Input";
			isValid = false;	
	}
	
	// Continues onto Sort method:
	if (isValid) {
		cout << "Method: Quicksort(Q), Mergesort(M), or Insertion(I): ";
		cin >> method;
		switch(method){
			case 'Q':
			case 'q':
				quickSort(hydropower, 0, hydropower.size()-1);
				break;
			case 'M':
			case 'm':
				mergeSort(hydropower, 0, hydropower.size()-1);
				break;	
			case 'I':
			case 'i':
				insertionSort(hydropower);
				break;
			default:
				cout << "Invalid Method";
				isValid = false;		
		}
	}
		
	

	if (isValid) {
		cout << "County " << setw(10) << "| Latitude" << endl;
		for (int n = 0; n < hydropower.size(); n ++)	
			printLine(hydropower[n]);

	}
	 fin.close();
	
}


