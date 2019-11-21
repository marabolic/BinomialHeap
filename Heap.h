#pragma once
class Heap
{
	struct Node {
		int key, cnt;
		Node *child, *sibling, *parent; 
		Node(int k, int d = 1, Node* c = nullptr, Node *s=nullptr, Node *p = nullptr): key(k), cnt(d), child(c), sibling(s), parent(p) {}
	};
	int min, heapSize = 0;
	Node *root;
public:
	Heap() { init(); }
	~Heap();
	void init();
	int getMin()const { return min; }
	void add(int key, int &steps);
	int get() const ;
	int del(int &steps);
	void setRoot(Node * newRoot) { root = newRoot; }
	void addSub(Node * up, Node * down);
	void delSub(Node * up, Node * down);
	Node * mergeAdd(Node * temp, Node * prev, int &steps);
	Node * mergeDel(Node * temp, Node * prev, int &steps);
	Node * unionHeap(Node * h1, Node * h2, int &steps);
	Node * convert(int &steps);
	void destroy();
	void priorityQ(int &steps);
	void levelOrder() const;
private:

};

