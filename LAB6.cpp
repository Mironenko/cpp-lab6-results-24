#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class compx
{
private:
	int di, mn; // di - целая , mn - мнимая
public:
	int get_di() {
		return di;
	}
	int get_mn() {
		return mn;
	}
	compx() {};
	compx(int d) {
		di = d;
		mn = 0;
	}
	compx(int d, int m) {
		di = d;
		mn = m;
	}
	compx(compx &i) { // конструктор copy
		di = i.di;
		mn = i.mn;
	}
	~compx() {}

	compx & operator=  (compx &i) { // перегрузка присваивания
		di = i.di;
		mn = i.mn;
		return (*this);
	}
	compx & operator=  (const compx &i) { // перегрузка присваивания
		di = i.di;
		mn = i.mn;
		return (*this);
	}
	compx operator * (compx &i)// перегрузка произведения 
	{
		compx tm;
		tm.di = di*i.di;
		tm.mn = di*i.mn;
		return tm;
	}
	compx operator + (compx &i) // перегрузка сложения
	{
		compx tm;
		tm.di = di + i.di;
		tm.mn = di + i.mn;
		return tm;
	}
	compx operator + (const compx &i) // перегрузка сложения
	{
		compx tm;
		tm.di = di + i.di;
		tm.mn = di + i.mn;
		return tm;
	}
};
template <typename T>
class matrix {
	T** A;
	int M;
	int N;
public:
	matrix<T>(int m, int n) : A(NULL), M(m), N(n)
	{
		A = new T*[M]; //строки в массиве
		for (int i = 0; i < M; i++)
		{
			A[i] = new T[N]; //  столбцы
			for (int j = 0; j < N; j++)
				A[i][j] = T(0, 0);
		}
	}
	T& operator () (int i, int j) // перегрузка оператора обращение к элементу ()
	{
		return A[i][j];
	}
	
	int m() {return M;};
	int n() {return N;};
	

	void print()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				cout << A[i][j].get_di() << ", " << A[i][j].get_mn() << " | ";
			cout << endl;
		}
		cout << endl;
	}


	~matrix<T>()
	{

	}

};


template <typename T> matrix<T> operator+(matrix<T>& M1,  matrix<T>& M2)//перегрузка сложения матриц
{
	matrix<T> L(M1.m(), M1.n());
	for (int i = 0; i < M1.m(); i++)
	{
		for (int j = 0; j < M1.n(); j++)
		{
			L(i, j) = M2(i, j) + M1(i, j);
		}
	}
	return L;
}
template <typename T>  matrix<T> operator*(matrix<T>& M1, matrix<T>& M2)//перегрузка перемножения матриц
{
	if (M1.n() != M2.m())
		throw "dont true size";
	matrix<T> Q(M1.m(), M1.n());
	for (int i = 0; i < M1.m(); i++)
	{
		for (int j = 0; j < M1.n(); j++)
		{
			for (int t = 0; t < M1.n(); t++)
			{
				Q(i, j) = Q(i, j) + (M1(i, t) * M2(t, j));
			}
		}
	}
	return Q;
}

template <typename T> matrix<T> operator~(matrix<T>& M1)//перегрузка транспонирования матрицы
{
	matrix<T> L(M1.n(), M1.m());
	for (int i = 0; i < M1.m(); i++)
	{
		for (int j = 0; j < M1.n(); j++)
		{
			L(j, i) = M1(i, j);
		}
	}
	return L;
}
	

int main()
{
	compx value1(1, 7);
	compx value2(6, -2);

	matrix <compx> A(3, 2);        // До запятой целай часть числа , а потом мнимая
	A(0, 0) = compx(2, 3);
	A(0, 1) = compx(1, 1);
	A(1, 0) = compx(0, 1);
	A(1, 1) = compx(3, 4);
	A(2, 0) = compx(0, 0);
	A(2, 1) = compx(1, 3);

	matrix <compx> B(2, 2);
	B(0, 0) = compx(1, 5);
	B(0, 1) = compx(3, 3);
	B(1, 0) = compx(6, 1);
	B(1, 1) = compx(1, 0);

	matrix <compx> X(3, 2);
	X(0, 0) = compx(2, 2);
	X(0, 1) = compx(1, 3);
	X(1, 0) = compx(7, 3);
	X(1, 1) = compx(2, 1);
	X(2, 0) = compx(0, 0);
	X(2, 1) = compx(1, 1);

	cout << "Matrica A: " << endl;
	A.print();
	cout << "Matrica B: " << endl;
	B.print();
	cout << "Matrica X: " << endl;
	X.print();
	matrix <compx> C(2, 2);
	C = A + X;//сложение матриц
	cout << "Matrica A+F: " << endl;
	C.print();
	matrix <compx> O(2, 2);
	O = A * B;//перемножение матриц
	cout << "Matrica A*B: " << endl;
	O.print();
	matrix <compx> E(2, 2);
	E = ~A;//транспонирование матрицы
	cout << "Transponir matr A: " << endl;
	E.print();
	try // исключение
	{
		O = A * X;
		O.print();
	}
	catch (const char * z)
	{
		cout << "iskl for * " << z << endl;
	}
	cout << endl;

	cout << " di " << value1.get_di() << " mn ";
	cout << value1.get_mn() << endl;
	cout << " di " << value2.get_di() << " mn ";
	cout << value2.get_mn() << endl;

	system("pause");
	return 0;
}
