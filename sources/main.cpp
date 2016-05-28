#include "QMatrix.h"



using namespace std;


int main()
	try {

		ifstream ist("in.txt");
		if (!ist) throw FileNotFound();
		ofstream ost("out.txt");
		if (!ost) throw FileNotFound();

		auto a = QMatrix<Q,2,2>();
		ist >> a;

		auto b = QMatrix<Q, 2, 2>();
		ist >> b;

		QMatrix<Q, 2, 2> c = a + b;
		ost << c;

		ist.close();
		ost.close();

		return 0;
		
	}
	catch (exception& e) {
		cout << "exception caught: " << e.what() << endl;
		return -1;
	}