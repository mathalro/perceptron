/*
	TAD matrix para operacoes com as matrizes
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

template <typename T> class Matrix {
	private:
		vector< vector<T> > mat;
		unsigned rows, cols;
	
	public:
		Matrix(unsigned rows, unsigned cols, const T& init);
		void init(vector<T> v);
		virtual ~Matrix();
		
		// Overloading Operations
		Matrix<T>& operator=(const Matrix<T>& rhs);
		Matrix<T> operator+(const Matrix<T>& rhs);
		Matrix<T> operator-(const Matrix<T>& rhs);
		Matrix<T> operator*(const Matrix<T>& rhs);
		Matrix<T> operator*(const T& rhs);
		Matrix<T> transpose();
		Matrix<T> getColumn(int col);
		
		T& operator()(const unsigned& row, const unsigned& col);
		const T& operator()(const unsigned& row, const unsigned& col)	const;
		
		unsigned get_rows() const;
		unsigned get_cols() const;
		void print();
		double sum();
};

#include "matrix.cpp"

#endif

