#include "Q.h"



Q::Q(int _m, unsigned int _n) {
	if (_n == 0) throw ZeroDenominatorException();
	m = _m;
	n = _n;
}


Q operator*(const Q& lhs, const Q& rhs) {

	return Q(lhs.m * rhs.m, lhs.n * rhs.n);
}


Q operator+(const Q& lhs, const Q& rhs) {

	return Q(lhs.m * rhs.n + lhs.n * rhs.m, lhs.n * rhs.n);
}


istream& operator>>(istream& ins, Q& q) {
	unsigned int m, n;
	char frac;
	ins >> m;
	ins >> frac;
	ins >> n;

	q = Q(m, n);

	return ins;
}


ostream& operator<<(ostream& out, const Q& q) {
	out << q.m << "/" << q.n << " ";

	return out;
}