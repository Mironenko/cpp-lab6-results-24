#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <istream>
using namespace std;

class sthbad {};

template <class T>
class matrix {
public:
	T **elem;
	int n, m;

	matrix(const matrix& m) {}
	matrix(int a, int b, const T *p, int size) {
		n = a;
		m = b;
		int c = 0;
		elem = new T*[n];
		for (int i = 0; i < n; i++) {
			elem[i] = new T[m];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (c != size) {
					elem[i][j] = p[c];
					c++;
				}
				else elem[i][j] = T();
			}
		}
	}
	matrix operator*(int number) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				elem[i][j] *= number;
		}
		return *this;
	}
	matrix operator*(const matrix& matr)
	{
		T *res = new T[n*matr.m];
		if (m == matr.n)
		{
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < matr.m; j++) {
					for (int k = 0; k < m; k++) {
						res[matr.m*i + j] += elem[i][k] * matr.elem[k][j];
					}
				}
			}
		}
		else throw sthbad();
		matrix matr0(n, matr.m, res, n*matr.m);
		delete[] res;
		return matr;
	}
	matrix operator&(const matrix& matr)
	{
		T* res = new T[n*(m + matr.m)];
		if (n == matr.n)
		{
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++)
					res[(m+matr.m)*i+j] = elem[i][j];
				for (int j = m; j < (m + matr.m); j++)
					res[(m + matr.m)*i + j] = matr.elem[i][j - m];
			}
		}
		else throw sthbad();
		matrix matr1(n, (m+matr.m), res, n*(m+matr.m));
		delete[] res;
		return matr;
	}

	struct iterator
	{
		int z;
		matrix* c;
		iterator(matrix* d, int a): c(d), z(a) {}
		iterator& operator++() {
			z += 1;
			return *this;
		}
		T& operator*() {
			return c->elem[z / c->m][z%c->m];
		}
		T* operator->() {
			return &(c->elem[z / c->m][z%c->m]);
		}
		bool operator ==(const iterator& i) {
			return (z == i.z);
		}
		bool operator!=(const iterator& i) {
			return !(*this == i);
		}
	};
	iterator begin() {
		return iterator(this, 0);
	}
	iterator end() {
		return iterator(this, n*m);
	}
	~matrix()
	{
		delete[] elem;
	}
	template <typename Q>
	friend ostream& operator<<(ostream& ost, matrix<Q> const& matr);
	template <typename Q>
	friend istream& operator>>(istream& ist, matrix<Q>& matr);
};
template <typename T>
ostream& operator<<(ostream& ost, matrix<T> const& matr) {
	for (int i = 0; i < matr.n; i++) {
		for (int j = 0; j < matr.m; j++) ost << matr.elem[i][j] << "  ";
		ost << endl;
	}
	ost << endl;
	return ost;
}
template <typename T>
istream& operator>>(istream& ist, matrix<T>& matr) {
	for (int i = 0; i < matr.n; i++) {
		for (int j = 0; j < matr.m; j++) ist >> matr.elem[i][j];
	}
	return ist;
}

void setCounterValue(int& i)
{
	static int counter = 0;
	i = counter++;
}

template<typename T>
int mymain()
{
	int a, n, m, q, w, num;
	T *mas;
	cout << "Number of elements: ";
	cin >> a;
	mas = new T[a];
	for (int i = 0; i < a; i++)
	{
		cout << "Element number " << i + 1 << ": ";
		cin >> mas[i];
	}
	for (int i = 0; i < a; i++)
		cout << i + 1 << ": " << mas[i] << endl;

	cout << "Size of the first matrix (n m): ";
	cin >> n >> m;
	matrix<T> matr1(n, m, mas, a);
	cout << "Size of the second matrix (n m): ";
	cin >> q >> w;
	matrix<T> matr2(q, w, mas, a);
	cout << "The first matrix: " << endl << matr1 << endl;
	cout << "The second matrix: " << endl << matr2 << endl;
	matrix<T>* pp = &matr1;
	matrix<T>::iterator g(pp, 0);
	for (matrix<T>::iterator it = pp->begin(); it != pp->end(); ++it)
	{
		cout << *it << endl;
	}
	system("pause");
	return 0;
}

int main() {
	return mymain<int>();
}