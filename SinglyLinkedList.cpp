// Singly Linked List
#include <bits/stdc++.h>
using namespace std;
 
struct Node {
	int data;
	Node *next;
};
 
typedef struct Node* node;
 
// Create new node with value x
node makeNode(int x) {
	node tmp = new Node();
	tmp->data = x;
	tmp->next = NULL;
	return tmp;
}
 
// Check if list is empty
bool empty(node a) {
	return a == NULL;
}
 
// Get size of list
int Size(node a) {
	int cnt = 0;
	while(a != NULL) {
		++cnt;
		a = a->next;
	}
	return cnt;
}
 
// Insert element at beginning
void insertFirst(node &a, int x) {
	node tmp = makeNode(x);
	if(a == NULL) {
		a = tmp;
	} else {
		tmp->next = a;
		a = tmp;
	}
}
 
// Insert element at end
void insertLast(node &a, int x) {
	node tmp = makeNode(x);
	if(a == NULL) {
		a = tmp;
	} else {
		node p = a;
		while(p->next != NULL) {
			p = p->next;
		}
		p->next = tmp;
	}
}
 
// Insert element at position
void insertMiddle(node &a, int x, int pos) {
	int n = Size(a);
	if(pos <= 0 || pos > n + 1) {
		cout << "Invalid position!\\n";
		return;
	}
	if(pos == 1) {
		insertFirst(a, x);
		return;
	}
	else if(pos == n + 1) {
		insertLast(a, x);
		return;
	}
	node p = a;
	for(int i = 1; i < pos - 1; i++) {
		p = p->next;
	}
	node tmp = makeNode(x);
	tmp->next = p->next;
	p->next = tmp;
}
 
// Delete from beginning
void deleteFirst(node &a) {
	if(a == NULL) return;
	a = a->next;
}
 
// Delete from end
void deleteLast(node &a) {
	if(a == NULL) return;
	node prev = NULL, curr = a;
	while(curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	if(prev == NULL) {
		a = NULL;
	} else {
		prev->next = NULL;
	}
}
 
// Delete from position
void deleteMiddle(node &a, int pos) {
	if(pos <= 0 || pos > Size(a)) return;
	node prev = NULL, curr = a;
	for(int i = 1; i < pos; i++) {
		prev = curr;
		curr = curr->next;
	}
	if(prev == NULL) {
		a = a->next;
	} else {
		prev->next = curr->next;
	}
}
 
void print(node a) {
	cout << "--------------------------------\\n";
	while(a != NULL) {
		cout << a->data << " ";
		a = a->next;
	}
	cout << endl;
	cout << "--------------------------------\\n";
}
 
// Sort list using selection sort
void sort(node &a) {
	for(node p = a; p->next != NULL; p = p->next) {
		node minNode = p;
		for(node q = p->next; q != NULL; q = q->next) {
			if(q->data < minNode->data) {
				minNode = q;
			}
		}
		int tmp = minNode->data;
		minNode->data = p->data;
		p->data = tmp;
	}
}
 
//Tim kiem trong dslk
//Tim phan tu lon nhat, nho nhat
 
 
int main() {
	node head = NULL;
	while(1) {
		cout << "-----------MENU-----------\\n";
		cout << "1. Insert at beginning\\n";
		cout << "2. Insert at end\\n";
		cout << "3. Insert at position\\n";
		cout << "4. Delete from beginning\\n";
		cout << "5. Delete from end\\n";
		cout << "6. Delete from position\\n";
		cout << "7. Print list\\n";
		cout << "8. Sort list\\n";
		cout << "0. Exit\\n";
		cout << "-------------------------\\n";
		cout << "Choose: ";
		int choice; cin >> choice;
		if(choice == 1) {
			int x; cout << "Enter value: "; cin >> x;
			insertFirst(head, x);
		}
		else if(choice == 2) {
			int x; cout << "Enter value: "; cin >> x;
			insertLast(head, x);
		}
		else if(choice == 3) {
			int x, pos; 
			cout << "Enter value: "; cin >> x;
			cout << "Enter position: "; cin >> pos;
			insertMiddle(head, x, pos);
		}
		else if(choice == 4) {
			deleteFirst(head);
		}
		else if(choice == 5) {
			deleteLast(head);
		}
		else if(choice == 6) {
			int pos; cout << "Enter position: "; cin >> pos;
			deleteMiddle(head, pos);
		}
		else if(choice == 7) {
			print(head);
		}
		else if(choice == 8) {
			sort(head);
		}
		else if(choice == 0) {
			break;
		}
	}
	return 0;
}
 
 