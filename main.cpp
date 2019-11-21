#include <iostream>
#include <fstream>
#include "Heap.h"
#include "PerformanceCalculato.h"
using namespace std;

void menu() {
	cout << "1. Stvaranje novog hipa" << endl;
	cout << "2. Dodavanje elementa u hip" << endl;
	cout << "3. Dohvatanje minimalnog/maksimalnog elementa" << endl;
	cout << "4. Brisanje minimalnog/maksimalnog elementa" << endl;
	cout << "5. Pretvaranje hipa" << endl;
	cout << "6. Unistavanje hipa" << endl;
	cout << "7. Brisanje elementa reda" << endl;
	cout << "8. Umetanje u prioritetni red" << endl;
	cout << "9. Prikazi prioritetni red" << endl;
	cout << "10. Performanse" << endl;
}



void perf(const char * name, Heap heap, int &steps) {
	PerformanceCalculator pc;
	ifstream dat;
	dat.open(name, ios::in);
	if (!dat.is_open())  cout << "error opening file" << endl;

	pc.start();
	int key = 1;
	while (!dat.eof()) {
		char c;
		dat.get(c);
		key = c - '0';
		while (c != '\n') {
			dat.get(c);
			if (c == '\n') break;
			key *= 10;
			key += c - '0';
		}
		//cout << key << endl;
		if (key != -38)
			heap.add(key, steps);
	}
	pc.stop();
	double protekloVreme = pc.elapsedMillis();
	cout << "vreme dodavanja: " << protekloVreme << '\t';
	cout << "koraci dodavanja: " << steps << '\t' << '\t';
	pc.start();
	heap.priorityQ(steps);
	pc.stop();
	protekloVreme = pc.elapsedMillis();
	cout << "vreme brisanja: " << protekloVreme << '\t';
	cout << "koraci brisanja: " << steps << endl;
	dat.close();
}



int main() {

	PerformanceCalculator pc;
	ifstream d10, d100, d1000, d10000, d100000;
	
	menu();
	int option;
	cout << "Unesi opciju"<< endl;
	cin >> option;
	int k, val, key;
	Heap heap = Heap();
	int steps = 0;
	while (option <= 10) {
		switch (option) {
		case 1:  break;
		case 2: cout << "Dodaj kljuc: "; cin >> key; heap.add(key, steps); break;
		case 3:
			k = heap.get(); cout << k << endl;
			break;
		case 4: val = heap.del(steps); cout << "Obrisan kljuc: " << val << endl; break;
		case 5: heap.setRoot(heap.convert(steps)); break;
		case 6: heap.destroy(); cout << "Heap je unisten" << endl;
		case 7: val = heap.del(steps); cout << "Obrisan kljuc: " << val << endl; break;
		case 8: cout << "Dodaj kljuc: "; cin >> key; heap.add(key, steps); break;
		case 9: heap.priorityQ(steps); break;
		case 10: 
			cout << "10" << '\t'; perf("test_10.txt", heap, steps);
			cout << "100" << '\t'; perf("test_100.txt", heap, steps);
			cout << "1000" << '\t'; perf("test_1000.txt", heap, steps);
			cout << "10000" << '\t'; perf("test_10000.txt", heap, steps);
			cout << "100000" << '\t'; perf("test_100000.txt", heap, steps);
			break;
		}
		cout << "Unesi opciju" << endl;
		cin >> option;
		cout << endl;
	}
	
	//pc.start();
	//key = 1;
	//while (!d10.eof()) {
	//	char c;
	//	d10.get(c);
	//	key = c - '0';
	//	while (c != '\n') {
	//		d10.get(c);
	//		if (c == '\n') break;
	//		key *= 10;
	//		key += c - '0';
	//	}
	//	//cout << key << endl;
	//	if (key != -38)
	//		heap.add(key, steps);
	//}
	//heap.priorityQ(steps);
	//pc.stop();
	//protekloVreme = pc.elapsedMillis();
	//cout << "vreme: " << protekloVreme << endl;
	//cout << "koraci: " << steps << endl;
	system("PAUSE");
}