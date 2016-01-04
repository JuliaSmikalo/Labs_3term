#include "MatrixNxN.h"
#include <iostream>

MatrixNxN::MatrixNxN(int n_){
	this->matrix = new int*[n_];
	for (int i = 0; i < n_; i++)
		this->matrix[i] = new int[n_];
}


MatrixNxN::MatrixNxN(int n_, int **mas){
	this->n = n_;
	this->matrix = new int*[n_];

	for (int i = 0; i < n; i++){
		this->matrix[i] = new int[n_];

		for (int j = 0; j < n; j++)
			this->matrix[i][j] = mas[i][j];
	}

}

MatrixNxN::MatrixNxN(MatrixNxN const& other){
	this->n = other.n;
	this->matrix = new int*[this->n];

	for (int i = 0; i < n; i++){
		this->matrix[i] = new int[this->n];

		for (int j = 0; j < n; j++)
			this->matrix[i][j] = other.matrix[i][j];
	}
}


MatrixNxN::~MatrixNxN(){
	if (NULL != this->matrix)
		delete[] this->matrix;
}


MatrixNxN & MatrixNxN::operator=(const MatrixNxN & other){
	if (this != &other){
		if (NULL != this->matrix)
			delete[] this->matrix;

		this->n = other.n;
		this->matrix = new int*[this->n];

		for (int i = 0; i < n; i++){
			this->matrix[i] = new int[this->n];

			for (int j = 0; j < n; j++)
				this->matrix[i][j] = other.matrix[i][j];
		}


	}

	return *this;

}

void MatrixNxN::output(){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			std::cout << matrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void MatrixNxN::replace_i_col(int j, int constant_terms[]){
	for (int i = 0; i < n; i++)
		matrix[i][j] = constant_terms[i];
}

int MatrixNxN::solve_det(){
	int det = 0, koef = 1; // koeficient = (-1)^i

	MatrixNxN Minor(n - 1);

	if (n < 1)
		std::cout << "Determinant can`t be solved!";

	if (n == 1) {
		det = matrix[0][0];
		return det;
	}

	if (n == 2) {
		det = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		return det;
	}

	if (n > 2){
		for (int i = 0; i < n; i++) {
			Minor = GetMinor(i, 0);			//?
			det = det + koef * matrix[i][0] * Minor.solve_det();
			koef = -koef;
		}
	}
	return det;
}

MatrixNxN MatrixNxN::GetMinor(int row, int col){		//cut of the matrix this row and this colon
	int step_i = 0;
	int step_j = 0;
	int m = n - 1;
	int **mas;
	mas = new int*[m];
	for (int i = 0; i < m; i++) {
		mas[i] = new int[m];

		if (i == row)
			step_i = 1;
		
		step_j = 0;
		
		for (int j = 0; j < m; j++) {
			if (j == col)
				step_j = 1;
			mas[i][j] = matrix[i + step_i][j + step_j];
		}
	}

	return MatrixNxN(n - 1, mas);
}
