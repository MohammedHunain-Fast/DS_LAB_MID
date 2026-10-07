#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int n, int key) {
	int l = 0, h = n - 1;
	
	while(l <= h && key >= arr[l] && key <= arr[h]) {
		if(arr[h] == arr[l]) {
			if(arr[l] == key) return l;
				break;
		}
		int pos = l + (((double)(h - l) / (arr[h] - arr[l])) * (key - arr[l]));
		if(key == arr[pos]) return pos;
		else if(key > arr[pos]) l = pos + 1;
		else h = pos - 1;
	}
	return -1;
	
}


int main() {
	int arr[8] = {1, 2, 3, 4, 5 ,6, 7, 8};
	int n = 8;
	int found = interpolationSearch(arr, n, 1);
	
	if(found != -1) cout << "key found at index " << found << endl;
	else cout << "key not found!\n";
	return 0;
}
