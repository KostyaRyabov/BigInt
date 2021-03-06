#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T> class vector {
private:
	int size;
	T *arr;
public:
	vector() {
		size = 1;
		arr = new T[1];
		*arr = 0;
	}
	vector(int n) {
		size = n;
		arr = new T[n];
		for (int i = 0; i < size; i++) {
			*(arr + i) = 0;
		}
	}
	T& operator[] (int id) {
		if (id >= 0 && id < size) {
			return *(arr + id);
		}
		else {
			return *(arr + size - 1);
		}
	}
	T& operator= (vector <T> Obj, vector <T> input) {
		cout << Obj << "  " << input << endl;
	}
	
	~vector() {
		delete(arr);
	}
};

int main() {
	setlocale(0, "");

	vector <int> A1(2);

	A1[0] = 2;
	A1[1] = 5;

	cout << A1[0] << " " << A1[4] << endl;

	system("pause");
}