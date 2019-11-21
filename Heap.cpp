#include "Heap.h"
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

Heap::~Heap()
{
	destroy();
}

void Heap::init()
{
	root = nullptr;
	cout << "min = 1 " << endl << " max = 0" << endl;
	cin >> min;
	try {
		if (min != 0 && min != 1) {
			throw min;
		}
	}
	catch (int) {
		cout << "*** Pogresan unos ***" << endl;
	}
	
}

void Heap::add(int k, int & steps)
{
	Node *temp = root;
	stack <Node*> s;
	
	if (temp != nullptr) {
		s.push(temp);
		
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
			s.push(temp);
		}
		Node *n = new Node(k);
		temp->sibling = n;
		bool mrg = false;
		while (!s.empty()) {
			temp = s.top();
			s.pop();
			if (temp->cnt == n->cnt) {
				n = mergeAdd(n, temp,steps);
				mrg = true;
			}
			else {
				if (mrg == true) {
					temp->sibling = n;
					mrg = false;
				}
			}
		}
		
		//cout << "*** " << n->key << " " << n->cnt << " ***" << endl;
	}
	else {
		root = new Node(k);
	}
	steps++;
	heapSize++;
}

int Heap::get() const
{
	Node * del = nullptr, *prevDel = nullptr;
	Node *it = root;
	if (min == 1) {
		int minVal = INT_MAX;
		while (it != nullptr) {
			if (it->key < minVal) {
				minVal = it->key;
				prevDel = del;
				del = it;
				while (prevDel != nullptr && prevDel->sibling != del) {
					prevDel = prevDel->sibling;
				}
			}
			it = it->sibling;
		}
		cout << "Min kljuc je: ";
	}
	else {
		int maxVal = INT_MIN;
		while (it != nullptr) {
			if (it->key > maxVal) {
				maxVal = it->key;
				prevDel = del;
				del = it;
				while (prevDel != nullptr && prevDel->sibling != del) {
					prevDel = prevDel->sibling;
				}
			}
			it = it->sibling;
		}
		cout << "Max kljuc je: ";
	}
	return del->key;
}

void Heap::addSub(Node * up, Node * down) {
	Node * temp = up;
	if (down == root) {
		root = up;
	}
	if (temp->child != nullptr) {
		temp = temp->child;
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
		}
	}
	else {
		temp->child = down;
	}
	temp->sibling = down;
	down->sibling = nullptr;
	up->sibling = nullptr;
	down->parent = up;
	up->cnt++;
}

void Heap::delSub(Node * up, Node * down) {
	Node * temp = up;
	if (down == root) {
		root = up;
	}
	if (temp->child != nullptr) {
		temp = temp->child;
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
		}
		temp->sibling = down;
	}
	else {
		temp->child = down;
	}
	down->sibling = nullptr;
	//up->sibling = nullptr;
	down->parent = up;
	up->cnt++;
}

Heap::Node * Heap::mergeAdd(Node * temp, Node * prev, int &steps)
{
	if (min == 1) {
		steps++;
		if (temp->key > prev->key) {
			prev->sibling = temp->sibling;
			addSub(prev, temp);
			return prev;
		}
		else {
			steps++;
			if (temp->key < prev->key) {
				addSub(temp, prev);
			}
			return temp;
		}
	}
	else {
		steps++;
		if (temp->key < prev->key) {
			prev->sibling = temp->sibling;
			addSub(prev, temp);
			return prev;
		}
		else {
			steps++;
			if(temp->key > prev->key)
				addSub(temp, prev);
		}
		return temp;
	}
}

Heap::Node * Heap::mergeDel(Node * temp, Node * next, int &steps)
{
	if (min == 1) {
		steps++;
		if (temp->key >= next->key) {
			next->sibling = temp->sibling;
			delSub(next, temp);
			return next;
		}
		else {
			steps++;
			if (temp->key < next->key) {
				Node *a = temp->child;
				temp->child = next->child;
				next->child = a;
				int k = temp->key;
				temp->key = next->key;
				next->key = k;
				next->sibling = temp->sibling;
				delSub(next, temp);
			}
			return next;
		}
	}
	else {
		/*if (temp->key >= next->key) {
			Node *a = temp->child;
			temp->child = next->child;
			next->child = a;
			int k = temp->key;
			temp->key = next->key;
			next->key = k;
			next->sibling = temp->sibling;
			delSub(next, temp);
			return temp;
		}
		else {
			next->sibling = temp->sibling;
			delSub(next, temp);
			return next;
		}*/
		steps++;
		if (temp->key <= next->key) {
			next->sibling = temp->sibling;
			delSub(next, temp);
			return next;
		}
		else {
			steps++;
			if (temp->key > next->key) {
				Node *a = temp->child;
				temp->child = next->child;
				next->child = a;
				int k = temp->key;
				temp->key = next->key;
				next->key = k;
				next->sibling = temp->sibling;
				delSub(next, temp);
			}
			return next;
		}
	}
}

Heap::Node * Heap::unionHeap(Node * h1, Node * h2, int &steps)
{
	Node *q = h1, *p = h2, *pnext, *prev = nullptr, *temp = nullptr, *next = nullptr, *prevq = nullptr, *prevqnext = nullptr;
	stack<Node*> s;
	//s.push(nullptr);
	s.push(q);
	while (q->sibling != nullptr) {
		q = q->sibling;
		s.push(q);
	}
	q = s.top();
	s.pop();
	bool mrg = false;
	while (p != nullptr) {
		if (p->cnt == q->cnt) {
			pnext = p->sibling;
			prevqnext = q; // q->sibling
			p->sibling = q->sibling;
			p->parent = nullptr;
			q->sibling = p;
			temp = p;
			prev = p->sibling; // prev = prevq
			next = q;
			if (prev != nullptr && prev->cnt == temp->cnt) {
				if (next != nullptr && temp->cnt == next->cnt) {
					q = mergeDel(temp, next, steps);
				}
				else q = mergeDel(prev, temp, steps);
				
				prevq = q;
				mrg = true;
			}
			else {
				if (temp->cnt == next->cnt) {
					//opasna zona
					if (!s.empty() && s.top()->cnt == next->cnt) {
						next->sibling = temp->sibling;
						temp->sibling = next;
						prev = next;
						next = s.top();
						s.pop();
						next->sibling = temp;
					}
					//kraj
					q = mergeDel(temp, next, steps);
					prevq = q;
					mrg = true;
				}
			}
			h1 = q;
			p = pnext;
		}
		else {
			if (p->cnt < q->cnt) {
				pnext = p->sibling;
				p->sibling = q->sibling;
				q->sibling = p;
				p->parent = nullptr;
				p = pnext;
			}
			else //p->cnt > q->cnt
			{
				if (!s.empty()) {
					q = s.top();
					s.pop();
					if (mrg == true) {
						q->sibling = prevq;
						mrg = false;
					}
				}
				else {
					pnext = p->sibling;
					p->sibling = prev;
					h1 = p;
					p = pnext;
				}
			}
		}
	}
	return h1;
}

int Heap::del(int & steps)
{
	Node * del = nullptr, * prevDel = nullptr, *prev = nullptr, *h1=nullptr, *h2=nullptr;
	Node * it = root;
	if (min == 1) {
		int minVal = INT_MAX;
		while (it != nullptr) {
			steps++;
			if (it->key < minVal) {
				minVal = it->key;
				prevDel = del;
				del = it;
				while (prevDel != nullptr && prevDel->sibling != del) {
					prevDel = prevDel->sibling;
				}
			}
			it = it->sibling;
		}
	}
	else {
		int maxVal = INT_MIN;
		while (it != nullptr) {
			steps++;
			if (it->key > maxVal) {
				maxVal = it->key;
				prevDel = del;
				del = it;
				while (prevDel != nullptr && prevDel->sibling != del) {
					prevDel = prevDel->sibling;
				}
			}
			it = it->sibling;
		}
	}

	if (del != nullptr) {
		if (del->sibling != nullptr)
			h1 = del->sibling;

		if (del->child != nullptr) {
			h2 = del->child;
		}
		int val = del->key;
		if (h1 != nullptr && h2 != nullptr) {
			h1 = unionHeap(h1, h2, steps);
			if (prevDel!=nullptr)
				prevDel->sibling = h1;  
			else root = h1;
		}
		else {
			if (h1 == nullptr && h2 != nullptr) {
				//transform
				Node * temp = h2;
				stack<Node*> s;
				s.push(temp);
				prev = nullptr; //reciklaza
				while (temp->sibling != nullptr) {
					temp = temp->sibling;
					s.push(temp);
					h2 = temp;
				}
				while (!s.empty()) {
					temp = s.top();
					s.pop();
					if (prev != nullptr)
						prev->sibling = temp;
					temp->sibling = nullptr;
					prev = temp;
				}
				if (prevDel != nullptr)
					prevDel->sibling = h2;
				else root = h2;
			}
			else {
				if (h2 == nullptr && h1 != nullptr) {
				}
				else {
					if (root != del) {
						Node * temp = root;
						stack<Node*> s;
						s.push(temp);
						prev = nullptr; //reciklaza
						while (temp->sibling != nullptr) {
							temp = temp->sibling;
							s.push(temp);
							//h2 = temp;
						}
						while (!s.empty()) {
							temp = s.top();
							s.pop();
							if (prev != nullptr)
								prev->sibling = temp;
							temp->sibling = nullptr;
							prev = temp;
							break;
						}
						if (prevDel != nullptr)
							prevDel->sibling = h2;
						//else root = h2;
					}
					else {
						root = nullptr;
					}
				}
			}
		}
		//cout << endl;
		//levelOrder();
		//cout << endl;
		delete del;
		return val;
	}
	else {
		return 0;
	}
}

Heap::Node * Heap::convert(int &steps)
{
	Node *temp = root;
	Heap newHeap = Heap();
	if (temp == nullptr) {
		cout << "prazan heap" << endl;
	}
	else {
		queue<Node*> q;
		q.push(temp);
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
			q.push(temp);
		}
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			int steps = 0;
			newHeap.add(temp->key, steps);
			if (temp != nullptr) {
				if (temp->child != nullptr) {
					temp = temp->child;
					q.push(temp);
					while (temp->sibling != nullptr) {
						temp = temp->sibling;
						q.push(temp);
					}
				}
			}
		}
	}
	destroy();
	return newHeap.root;
}

void Heap::destroy()
{
	Node *temp = root;
	if (temp == nullptr) {
		//cout << "prazan heap" << endl;
	}
	else {
		queue<Node*> q;
		q.push(temp);
		
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
			q.push(temp);
		}
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			Node *old = temp;
			if (temp != nullptr) {

				if (temp->child != nullptr) {
					temp = temp->child;
					q.push(nullptr);
					q.push(temp);
					while (temp->sibling != nullptr) {
						temp = temp->sibling;
						q.push(temp);
					}
				}
			}
			old = nullptr;
		}
	}
}

void Heap::priorityQ(int &steps) {
	Node *temp = root;
	if (temp == nullptr) {
		cout << "prazan red" << endl;
	}
	else {
		int x = heapSize;
		for (int i = 0; i < x; i++)
		{
			int val = del(steps);
			//cout << " * " << val << " * " << endl;
		}
	}
}

void Heap::levelOrder() const {
	Node *temp = root;
	if (temp == nullptr) {
		cout << "prazan heap" << endl;
	}
	else {
		queue<Node*> q;
		q.push(temp);
		while (temp->sibling != nullptr) {
			temp = temp->sibling;
			q.push(temp);
		}
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			if (temp != nullptr) {
				cout << temp->key << "  ";
				if (temp->child != nullptr) {
					temp = temp->child;
					q.push(nullptr);
					q.push(temp);
					while (temp->sibling != nullptr) {
						temp = temp->sibling;
						q.push(temp);
					}
				}
			}
			else cout << endl;
		}
	}
}

