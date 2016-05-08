#pragma once
#include "Q.h"
#include "al-6.h"


class Q;

template <class T, unsigned R, unsigned C>
class QMatrix
{
private:
	unsigned int rows, columns;

public:
	QMatrix(unsigned int m = 1, unsigned int n = 1);
	~QMatrix();
	QMatrix(QMatrix<T, R, C>&& oth);


	unsigned int rows_count (void) const { return rows; }
	unsigned int columns_count(void) const { return columns; }

	T** element;

	T& const operator()(unsigned int i, unsigned int j) const;
	T& operator()(unsigned int i, unsigned int j);

	QMatrix<T, R, C> transposition() const;

	QMatrix<T, R, C>& operator=(QMatrix<T, R, C>&& oth) {
		rows = oth.rows_count();
		columns = oth.columns_count();
		element = oth.element;

		oth.element = nullptr;

		return *this;
	}


	template <class T, unsigned R, unsigned C>
	friend istream& operator>>(istream& in, QMatrix<T, R, C>& mat);


	template <class T, unsigned R, unsigned C>
	friend ostream& operator<<(ostream& out, const QMatrix<T, R, C>& mat);

	template <class T, unsigned R, unsigned C>
	friend QMatrix<T, R, C> operator* (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs);

	template <class T, unsigned R, unsigned C>
	friend QMatrix<T, R, C> operator+ (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs);
};



template <class T, unsigned R, unsigned C>
QMatrix<T, R, C>::QMatrix(unsigned int m, unsigned int n)
{
	if ((m == 0) || (n == 0)) throw ZeroSizeOfMatrix();
	rows = m;
	columns = n;
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
QMatrix<T, R, C>::~QMatrix()
{
	if (element == nullptr) return;
	for (unsigned int i = 0; i < rows_count(); i++)
		delete element[i];
	delete element;
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C> QMatrix<T, R, C>::transposition() const {
	QMatrix<T, R, C> result = QMatrix(columns_count(), rows_count()); // m, n

	for (unsigned int i = 0; i < rows_count(); i++)
		for (unsigned int j = 0; j < columns_count(); j++)
			result(j, i) = element[i][j];

	return result;
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C> operator* (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs) {
	if (lhs.columns_count() != rhs.rows_count()) throw BadSizeOfMatrix();
	QMatrix<T, R, C> result = QMatrix(lhs.rows_count(), rhs.columns_count());

	for (unsigned int i = 0; i < lhs.rows_count(); i++)
		for (unsigned int j = 0; j < rhs.columns_count(); j++)
			for (unsigned int k = 0; k < lhs.columns_count(); k++)
				result(i, j) = result(i, j) + lhs(i, k) * rhs(k, j);

	return result;
}


template <class T, unsigned R, unsigned C>
QMatrix<T, R, C> operator+ (const QMatrix<T, R, C>& lhs, const QMatrix<T, R, C>& rhs) {
	if ((lhs.columns_count() != rhs.columns_count())
		|| (lhs.rows_count() != rhs.rows_count()))
		throw BadSizeOfMatrix();
	QMatrix<T, R, C> result = QMatrix<T, R, C>(lhs.rows_count(), rhs.columns_count());

	for (unsigned int i = 0; i < result.rows_count(); i++)
		for (unsigned int j = 0; j < result.columns_count(); j++)
			result(i, j) = lhs(i, j) + rhs(i, j);

	return result;
}


template <class T, unsigned R, unsigned C>
T& const QMatrix<T, R, C>::operator()(unsigned int i, unsigned int j) const { return element[i][j]; }

template <class T, unsigned R, unsigned C>
T& QMatrix<T, R, C>::operator()(unsigned int i, unsigned int j) { return element[i][j]; }


template <class T, unsigned R, unsigned C>
istream& operator>>(istream& ins, QMatrix<T, R, C>& mat) {
	for (unsigned int i = 0; i < mat.rows_count(); i++)
		for (unsigned int j = 0; j < mat.columns_count(); j++) {
			ins >> mat(i, j);
		}

	return ins;
}


template <class T, unsigned R, unsigned C>
ostream& operator<<(ostream& out, const QMatrix<T, R, C>& mat) {
	out << mat.rows_count() << " " << mat.columns_count() << endl;
	for (unsigned int i = 0; i < mat.rows_count(); i++) {
		for (unsigned int j = 0; j < mat.columns_count(); j++)
			out << mat(i, j) << "\t";
		out << endl;
	}

	return out;
}