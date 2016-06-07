#pragma once
#include <stdexcept>


using namespace std;


class ZeroDenominatorException : public runtime_error
{
public:
	ZeroDenominatorException() : runtime_error("Zero denominator in rational number.") {}
};


class ZeroSizeOfMatrix : public runtime_error
{
public:
	ZeroSizeOfMatrix() : runtime_error("Zero size of matrix.") {}
};


class BadSizeOfMatrix : public runtime_error
{
public:
	BadSizeOfMatrix() : runtime_error("Bad size of matrix.") {}
};


class FileNotFound : public runtime_error
{
public:
	FileNotFound() : runtime_error("File not found.") {}
};
