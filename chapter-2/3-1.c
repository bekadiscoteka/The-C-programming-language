#include <stdio.h>
int binary_search(int x, int arr[], int size);
#define SIZE 97 
int main() {
	int arr[SIZE];
	// fill up
	int search_value = 3;
	for (int i=0; i<SIZE; ++i) 
		arr[i] = i;
	
	//print out
	printf("result %d", binary_search(search_value, arr, SIZE));

}

int binary_search(int x, int arr[], int size) {
	int low = 0;
	int high = size-1;
	int mid;
	while (low < high) {
		mid = (high + low) / 2;	
		if (x <= arr[mid])	high = mid;
		else				low = mid+1;
	}

	if (x == arr[high] || x == arr[low]) {
		printf("high %d; low %d", high, low);
		return high;
	}
	else 
		return -1;
}
