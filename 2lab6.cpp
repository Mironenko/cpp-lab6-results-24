// 2lab6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const int Knum = 11;

template<typename T>
class matr {
	T *e;
	size_t n, m;
public:
	matr(size_t a, size_t b) : n(a), m(b) {
		e = new T[n*m];
	}

	matr(size_t a) : n(a), m(1) {
		e = new T[n*m];
	};

	~matr() {
		delete[] e;
	}

	matr(const matr& ma) {
		n = ma.n;
		m = ma.m;
		e = new T[n*m];
		copy(ma.e, ma.e + n*m, e);
	}

	void set(T a, size_t b) {
		if (b < n*m) e[b] = a;
		else cout << "ERROR: out of size!" << endl;
	}

	const T& operator() (size_t a, size_t b) {
		if (a >= n || b >= m) throw "Error! Can't get element by index";
		return e[a*n + b];
	}


	matr operator* (const matr& m1) const {
		if (m != m1.n) throw "Error! Matrices can't be multiplied because of the size";
		matr ma(n, m1.m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m1.m; j++) {
				for (int k = 0; k < m; k++) {
					ma.e[m1.m*i + j] = ma.e[m1.m*i + j] + e[n * i + k] * m1.e[k + j * m1.m];
				}
			}
		}
		return ma;
	}


	matr operator+ (const matr& m1) const {
		if (n != m1.n || m != m1.m) throw "Error! Matrices can't be folded because of the size";
		matr ma(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) ma.e[m*i + j] = e[n*i + j] + m1.e[n*i + j];
		}
		return ma;
	}


	matr operator &(const matr& m1) const {
		if (n != m1.n) throw "Error! Matrices can't be concatinate because of the size";
		matr ma(n, m + m1.m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) ma.e[(m + m1.m)*i + j] = e[i*n + j];
			for (int j = m; j < m + m1.m; j++) ma.e[(m + m1.m)*i + j] = m1.e[i*n+(j-m)];
		}
		return ma;
	}

	size_t size() {
		return n*m;
	}

	T& get(size_t i) {
		if (i < n*m) return e[i];
		else cout << "ERROR: out of size!" << endl;
	}

	class fwdit : public std::iterator<std::input_iterator_tag, T>{
		matr* ma;
		size_t c;
	public:
		fwdit(matr* a, size_t b) : ma(a), c(b) {};

		fwdit& operator++() {
			c++;
			return *this;
		}

		T& operator*() {
			return ma->e[c];
		}

		T* operator->() {
			return &(ma->e[c]);
		}

		bool operator !=(const fwdit& it) {
			return !(*this == it);
		}

		bool operator ==(const fwdit& it) {
			return (c == it.c);
		}

		size_t getc() {
			return c;
		}
	};

	fwdit begin() {
		return fwdit(this, 0);
	}

	fwdit end() {
		return fwdit(this, n*m);
	}

	//TODO for each

	template<typename T1>
	friend ostream& operator<< (ostream& os, const matr<T1>& m);

	template<typename T1>
	friend istream& operator>> (istream& is, matr<T1> & m);
};

template<typename T>
ostream& operator<< (ostream& os, const matr<T> & m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.m; j++) os << m.e[i*m.m + j] << "\t";
		os << endl;
	}
	os << endl;
	return os;
};

template<typename T>
istream& operator>> (istream& is, matr<T> & m) {
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.m; j++) is >> m.e[i*m.n + j];
	}
	return is;
};


template<template <typename> class cont, typename T, typename U> // good caster for ANY types
cont<U> caster(cont<T> a) {
	cont<U> b(a.size());
	for (size_t i = 0; i != a.size(); ++i) 
		b.get(i) = static_cast<U>(a.get(i));
	return b;
}

class bit11 {
	uint16_t a : 11;
}; // this is not that you mean by 11-bit numbers, isnt it?


template<typename T>
void plusel(T& el, double a) {
		el += a;
}

template<typename T>
void plusnum(T& el, size_t& n) {
	el += n;
	n++;
}

template<typename T>
bool eq1(T el, T k, T b) {
	return (el == -b / k);
}

template<typename T>
bool lesst(T a, T b) {
	return (a < b);
}

template<typename T>
bool eq2(T el, T a, T b, T c) {
	return (a*el*el + b*el + c == 0);
}

int main()
{
	matr<int> g(3, 7);
	for (int i = 0; i < 21; i++) g.set(i, i);

	matr<double> gd = caster<matr, int, double>(g);

	cout << "Matr: " << g << endl << "After make it double:\n" << gd << endl;

	for (matr<int>::fwdit it = g.begin(); it != g.end(); ++it) {
		cout << *it << endl;
	}

	int pel = 3, cel = 14, k = -3, b1 = 12, a = 1, b = -2, c = 1, lel = 12, fel = 77;
	for_each(g.begin(), g.end(), bind(plusel<int>, placeholders::_1, pel));
	cout << g;
	for_each(g.begin(), g.end(), bind(plusnum<int>, placeholders::_1, size_t(1)));
	cout << g;
	cout << "Number of elements equal to " << cel << ": " << count(g.begin(), g.end(), cel) << endl;
	cout << "Nmber of solutions of " << k << "x+" << b1 << "=0: " << count_if(g.begin(), g.end(), bind(eq1<double>, placeholders::_1, k, b1)) << endl;
	cout << "Number of elements less than " << lel <<": " << count_if(g.begin(), g.end(), bind(lesst<double>, placeholders::_1, cel)) << endl;
	cout << "First solution of " << a << "x^2+" << b << "x+" << c << "=0, or memory address if there is no solutions: " << *find_if(g.begin(), g.end(), bind(eq2<double>, placeholders::_1, a, b, c)) << endl;
	cout << "First element equal to " << fel << ", or memory address if there are no such elements: " << *find(g.begin(), g.end(), fel) << endl;

	system("pause");
	return 0;
}
