#pragma once
#include "Q.h"
#include "al-6.h"



template <class T, unsigned R, unsigned C>
class QMatrix
{
private:
    T** element;

public:
	QMatrix();
	~QMatrix();
	QMatrix(QMatrix<T, R, C>&& oth);

	
	const T& operator()(unsigned int i, unsigned int j) const;
	T& operator()(unsigned int i, unsigned int j);

	
    QMatrix<T, R, C> transposition() const;

	
    QMatrix<T, R, C>& operator=(QMatrix<T, R, C>&& oth) {
		element = oth.element;
		oth.element = nullptr;

		return *this;
	}


	template <class M, unsigned I, unsigned J>
	friend istream& operator>>(istream& in, QMatrix<T, R, C>& mat);


	template <class M, unsigned I, unsigned J>
	friend ostream& operator<<(ostream& out, const QMatrix<T, R, C>& mat);

    
	template <class M, unsigned I, unsigned J>
	friend QMatrix<T, R, C> operator* (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs);

    
	template <class M, unsigned I, unsigned J>
	friend QMatrix<T, R, C> operator+ (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs);


	class Iterator
	{
	public:
		Iterator(T** _data, unsigned r, unsigned c) : data(_data), i(r), j(c) {}

		Iterator& operator++() {
			j++;
			if (j >= C) {
				i++;
				j = 0;
			}

			return *this;
		}

		T** operator*() { return &data[i][j]; }
		T& operator->() { return data[i][j]; }

        Iterator begin() { return Iterator(data, 0, 0); }
        Iterator end() { return Iterator(data, R-1, C-1); }

	private:
        T** data;
		unsigned i, j;
	};
};



template <class T, unsigned R, unsigned C>
QMatrix<T, R, C>::QMatrix() {
	if ((R == 0) || (C == 0)) throw ZeroSizeOfMatrix();
	element = new T*[R];
	for (unsigned int i = 0; i < R; i++) {
		element[i] = new T[C]();
		for (unsigned int j = 0; j < C; j++)
			element[i][j] = T();
	}
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C>::QMatrix(QMatrix<T, R, C>&& oth) {
	*this = move(oth);
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C>::~QMatrix() {
	if (element == nullptr) return;
	for (unsigned int i = 0; i < R; i++)
		delete element[i];
	delete element;
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C> QMatrix<T, R, C>::transposition() const {
	QMatrix<T, R, C> result = QMatrix(C, R);

	for (unsigned int i = 0; i < R; i++)
		for (unsigned int j = 0; j < C; j++)
			result(j, i) = element[i][j];

	return result;
}


template <class T, unsigned R1, unsigned R2, unsigned C1, unsigned C2>
QMatrix<T, R1, C2> operator* (const QMatrix<T, R1, C1>& lhs, const QMatrix<T, R2, C2>& rhs) {
	if (lhs.columns_count() != rhs.rows_count()) throw BadSizeOfMatrix();
	QMatrix<T, R1, C2> result = QMatrix<T, R1, C2>(lhs.rows_count(), rhs.columns_count());

	for (auto i = 0; i < R1; i++)
		for (auto j = 0; j < C2; j++)
			for (auto k = 0; k < C1; k++)
				result(i, j) = result(i, j) + lhs(i, k) * rhs(k, j);

	return result;
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C> operator+ (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs) {
	QMatrix<T, R, C> result = QMatrix<T, R, C>();

	for (auto i = 0; i < R; i++)
		for (auto j = 0; j < C; j++)
			result(i, j) = lhs(i, j) + rhs(i, j);

	return result;
}


template <class T, unsigned R, unsigned C>
const T& QMatrix<T, R, C>::operator()(unsigned int i, unsigned int j) const { return element[i][j]; }


template <class T, unsigned R, unsigned C>
T& QMatrix<T, R, C>::operator()(unsigned int i, unsigned int j) { return element[i][j]; }


template <class T, unsigned R, unsigned C>
istream& operator>>(istream& ist, QMatrix<T, R, C>& mat) {
	for (auto i = 0; i < R; i++)
		for (unsigned int j = 0; j < C; j++) {
			ist >> mat(i, j);
		}

	return ist;
}


template <class T, unsigned R, unsigned C>
ostream& operator<<(ostream& ost, const QMatrix<T, R, C>& mat) {
	for (unsigned int i = 0; i < R; i++) {
		for (unsigned int j = 0; j < C; j++)
			ost << mat(i, j) << "\t";
		ost << endl;
	}

	return ost;
}
