#include "al-6.h"
#include <iostream>



using namespace std;


int main()
	try {

		ifstream ist("in.txt");
		if (!ist) throw FileNotFound();
		ofstream ost("out.txt");
		if (!ost) throw FileNotFound();
		int m, n;

		ist >> m >> n;
		auto a = QMatrix<Q,2,2>();
		ist >> a;

		ist >> m >> n;
		QMatrix<Q, 2, 2> c(m,n);
		ist >> c;

		QMatrix<Q, 2, 2> b = a + c;
		cout << b;

		ist.close();
		ost.close();

		return 0;
		
	}
	catch (exception& e) {
		cout << "exception caught: " << e.what() << endl;
		return -1;
	}