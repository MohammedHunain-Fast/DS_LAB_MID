#include <iostream>
#include <string>
using namespace std;

class Node {
	public:
		int song;
		Node* next;
		Node* prev;
		
		Node(int song, Node* n = NULL, Node* p = NULL) : song(song), next(n), prev(p) {
		} 
};

class Playlist {
	public:
		Node* head = NULL;
		Node* tail = NULL;
		Node* current = NULL;
		
		void create(int arr[], int n) {
			if (n <= 0) return;
			Node* firstNode = new Node(arr[0]);
			head = firstNode;
			tail = firstNode;
			head -> prev = tail;
			tail -> next = head;
			int i;
			for(i = 1; i < n; i++) {
				Node* newNode = new Node(arr[i]);
				tail -> next = newNode;
				newNode -> prev = tail;
				tail = newNode;
				tail -> next = head;
				head -> prev = tail;
			}
			current = head;
		}

		void moveForward(int steps) {
			if(!current) return;
			// FIXED: Update current directly inside the loop to avoid over-stepping by +1
			for(int i = 0; i < steps; i++) {
				current = current -> next;
			}
		}

		void moveBackward(int steps) {
			if(!current) return;
			// FIXED: Update current directly inside the loop to avoid over-stepping by +1
			for(int i = 0; i < steps; i++) {
				current = current -> prev;
			}
		}

		void shiftSong(int key) {
			if(!head || head == tail || !current) return;
			
			// FIXED: Circular-safe loop that targets the actual node to move
			Node* toShift = NULL;
			Node* temp = head;
			do {
				if(temp->song == key) {
					toShift = temp;
					break;
				}
				temp = temp->next;
			} while(temp != head);
			
			// If the song wasn't found or is already the current playing song, do nothing
			if(!toShift || toShift == current) return;
			
			// FIXED: Safely adjust head/tail tracking before pulling the node out
			if(toShift == head) head = head->next;
			if(toShift == tail) tail = tail->prev;
			
			// Bypass/unlink toShift from its current position
			toShift->prev->next = toShift->next;
			toShift->next->prev = toShift->prev;
			
			// Re-insert toShift directly right after current
			Node* nextNode = current->next;
			current->next = toShift;
			toShift->prev = current;
			toShift->next = nextNode;
			nextNode->prev = toShift;
			
			// If current was the tail, our shifted song is now the new tail
			if(current == tail) {
				tail = toShift;
			}
		}
		
		void remove() {
			if(!head || !current) return;
			if(head == tail) {
				delete head;
				head = NULL;
				tail = NULL;
				current = NULL;
				return;
			}
			Node* toDel = current;
			
			// Stitch up the gap left by removing current
			current->prev->next = current->next;
			current->next->prev = current->prev;
			
			if(current == head) head = head->next;
			if(current == tail) tail = tail->prev;
			
			// Auto-advance current so it points to a live memory track
			current = current->next; 
			delete toDel;
		}

		void display() {
			if(!head) {
				cout << "Playlist is empty." << endl;
				return;
			}
			Node* temp = head;
			do {
				if(temp == current) cout << "[" << temp->song << "] ";
				else cout << temp->song << " ";
				temp = temp->next;
			} while(temp != head);
			cout << endl;
		}
};

int main() {
	Playlist myPlaylist;
	int tracks[] = {10, 20, 30, 40, 50};
	myPlaylist.create(tracks, 5);
	
	cout << "Initial: "; myPlaylist.display();
	myPlaylist.moveForward(2);
	cout << "Forward 2: "; myPlaylist.display();
	myPlaylist.shiftSong(10);
	cout << "Shift 10 behind current: "; myPlaylist.display();
	myPlaylist.remove();
	cout << "Remove current: "; myPlaylist.display();
	
	return 0;
}
