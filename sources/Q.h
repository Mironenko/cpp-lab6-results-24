#pragma once
#include "al-6.h"



using namespace std;


class Q
{
private:
	int m;
	unsigned int n;

public:
	Q(int m = 0, unsigned int n = 1);

	friend Q operator*(const Q& lhs, const Q& rhs);
	friend Q operator+(const Q& lhs, const Q& rhs);
	friend std::istream& operator>>(std::istream& in, Q& q);
	friend std::ostream& operator<<(std::ostream& out, const Q& q);
};


