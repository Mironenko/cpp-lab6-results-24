#include <vector>
#include <list>
#include <algorithm>
#include "QMatrix.h"



using namespace std;


template <class T>
void inc(T& num) { num = num + T(1); }

template <class T>
bool linear(const T& num) {
    T k(1), b(-1);
    
    return (k*num + b) == 0;
}


int main()
	try {

//		ifstream ist("in.txt");
//		if (!ist) throw FileNotFound();
//		ofstream ost("out.txt");
//		if (!ost) throw FileNotFound();
//
//		auto a = QMatrix<Q,2,2>();
//		ist >> a;
//
//		auto b = QMatrix<Q, 2, 2>();
//		ist >> b;
//
//		QMatrix<Q, 2, 2> c = a + b;
//		ost << c;
//
//		ist.close();
//		ost.close();
        
        auto a = QMatrix<int,2,2>();

        for_each(a.begin(), a.end(), inc<int>);
        cout << a;
        
        cout << count(a.begin(), a.end(), 1) << endl;
        cout << count_if(a.begin(), a.end(), linear<int>) << endl;
        
        auto it = find(a.begin(), a.end(), 1);
        cout << *it << endl;
        
		return 0;
		
	}
	catch (exception& e) {
		cout << "exception caught: " << e.what() << endl;
		return -1;
	}