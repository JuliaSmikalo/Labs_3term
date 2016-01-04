#pragma once
const int MAXN = 100;

class MatrixNxN{
private:
	int n;
	int **matrix;

public:
	MatrixNxN(int);
	MatrixNxN(int n_, int **mas);
	MatrixNxN(MatrixNxN const& other);
	MatrixNxN & operator = (const MatrixNxN & other);
	void output();
	void replace_i_col(int j, int constant_terms[]);
	int solve_det();
	MatrixNxN GetMinor(int row, int col);
	~MatrixNxN();
};

