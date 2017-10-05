#ifndef _MATRIX_CPP
#define _MATRIX_CPP

#include <iostream>
#include <cstdio>
#include "matrix.h"

using namespace std;

// construtor
template<typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols, const T& init) {
	mat.resize(rows);
	for (unsigned i = 0; i < rows; i++) {
		mat[i].resize(cols, init);
	}
	this->rows = rows;
	this->cols = cols;
}

// inicializar com um vetor
template<typename T>
void Matrix<T>::init(vector<T> v) {
	if (v.size() != get_rows()*get_cols()) {
		printf("Unsuported size %d!\n", v.size());
		exit(0);
	}

	int k = 0;
	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++, k++) {
			mat[i][j] = v[k];
		}
	}
}


template<typename T>
void Matrix<T>::print() {
	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			cout << this->mat[i][j] << ' ';
		} cout << endl;
	} cout << endl;
}

// destrutor
template<typename T>
Matrix<T>::~Matrix() {}


// atribuicao
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
	if (&rhs == this) return *this;
	
	unsigned new_rows = rhs.get_rows();
	unsigned new_cols = rhs.get_cols();

	mat.resize(new_rows);
	for (unsigned i = 0; i < new_rows; i++) {
		mat[i].resize(new_cols);	
	}

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			mat[i][j] = rhs(i, j);
		}
	}

	this->rows = new_rows;
	this->cols = new_cols;

	return *this;
}


// adicao
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
	if (rhs.get_rows() != this->rows || rhs.get_cols() != this->cols) {	
		printf("Illegal dimensions [%u][%u] + [%u][%u]\n", rows, cols, rhs.get_rows(), rhs.get_cols());
		exit(1);
	}

	Matrix result = Matrix(this->rows, this->cols, 0.0);

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			result(i, j) = this->mat[i][j] + rhs.mat[i][j];
		}
	}

	return result;
}


// subtracao
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
	if (rhs.get_rows() != rows || rhs.get_cols() != cols) {	
		printf("Illegal dimensions [%u][%u] - [%u][%u]\n", rows, cols, rhs.get_rows(), rhs.get_cols());
		exit(1);
	}
	Matrix result = Matrix(this->rows, this->cols, 0.0);

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			result(i, j) = this->mat[i][j] - rhs.mat[i][j];
		}
	}

	return result;
}


// produto
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
	if (this->cols != rhs.get_rows()) {	
		printf("Illegal dimensions [%u][%u] * [%u][%u]\n", rows, cols, rhs.get_rows(), rhs.get_cols());
		exit(1);
	}
	unsigned new_rows = this->rows;
	unsigned new_cols = rhs.get_cols();
	Matrix result = Matrix(new_rows, new_cols, 0.0);

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			for (unsigned k = 0; k < this->cols; k++) {
				result(i, j) += this->mat[i][k] * rhs(k, j);
			}
		}
	}

	return result;
}


// produto escalar
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs) {
	Matrix result = Matrix(this->rows, this->cols, 0.0);
	
	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			result(i, j) = this->mat[i][j] * rhs;
		}
	}

	return result;
}

// transposta
template<typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix result = Matrix(this->cols, this->rows, 0.0);

	for (unsigned i = 0; i < this->rows; i++) {
		for (unsigned j = 0; j < this->cols; j++) {
			result(j, i) = this->mat[i][j];
		}
	} 

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::getColumn(int col) {
	Matrix result = Matrix(this->rows, 1, 0.0);

	for (unsigned i = 0; i < this->rows; i++) {
		result.mat[i][0] = this->mat[i][col];		
	}

	return result;
}

// acesar uma posicao
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
	return this->mat[row][col];
}

// acessar uma posicao
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
	return this->mat[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
	return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const {
	return this->cols;
}

template<typename T>
double Matrix<T>::sum() {
	double result = 0;
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result += mat[i][j]*mat[i][j];
		}
	}
	return result;
}
#endif





