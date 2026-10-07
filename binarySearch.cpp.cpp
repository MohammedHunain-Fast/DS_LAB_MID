#include <iostream>
using namespace std;

int binarySearch(int arr[], int n, int key) {
	int l = 0,  h = n - 1;
	
	while(l <= h) {
		int mid = (l + h) / 2;
		if(key == arr[mid]) return mid;
		else if(key > arr[mid]) l = mid + 1;
		else h = mid - 1;
	}
	return -1;
}


int main() {
	int arr[8] = {1, 2, 3, 4, 5 ,6, 7, 8};
	int n = 8;
	int found = binarySearch(arr, n, 2);
	
	if(found != -1) cout << "key found at index " << found << endl;
	else cout << "key not found!\n";
	return 0;
}
