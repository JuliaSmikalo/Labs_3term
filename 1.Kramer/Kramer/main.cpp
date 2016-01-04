#include <iostream>
#include <fstream>
#include "MatrixNxN.h"
using namespace std;

void output(int **mas, int n, int *(&constant_terms)){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n - 1; j++){
			if (mas[i][j] < 0)
				std::cout << "(" << mas[i][j] << ")a" << j + 1 << " + ";
			else
				std::cout << mas[i][j] << 'a' << j + 1 << " + ";
		}

		if (mas[i][n - 1] < 0)
			std::cout <<'('<< mas[i][n - 1] << ")a";
		else
			std::cout << mas[i][n - 1] << 'a';
		
		std::cout << n - 1 << " = " << constant_terms[i] << std::endl;
	}
}

MatrixNxN input_System_of_linear_equations(int &n, int *(&constant_terms)){
	ifstream fin;
	fin.open("tests\\3.txt");
	fin >> n; // amount of vaiables and at the same time th amount of equations

	int **mas;
	mas = new int*[n]; // create matrix of rates near variables in each equation
	constant_terms = new int[n]; // numbers on the right side of equation

	for (int i = 0; i < n; i++){
		mas[i] = new int[n];

		for (int j = 0; j < n; j++){
			fin >> mas[i][j];
		}
		fin >> constant_terms[i];
	}
	output(mas, n, constant_terms);
	fin.close();
	return MatrixNxN(n, mas);
};



int main(int argc, char* argv[]) {
	int* constant_terms;
	int n;

	MatrixNxN general_matrix = input_System_of_linear_equations(n, constant_terms);
	int general_det = general_matrix.solve_det(); // solve determinant of general matrix

	if (general_det == 0)
		cout << "System of linear equations don`t have a solution.\n";
	else {
		for (int i = 0; i < n; i++){						
			MatrixNxN i_matrix = general_matrix;			
			i_matrix.replace_i_col(i, constant_terms);		// put constant terms in general matrix instead of each colon
			int x = i_matrix.solve_det();					// and solve determinant in each of such created matrix
			cout << i + 1 << ": " << x / general_det << '\n'; // have results by the Kramer's method 
		}
	}

	system("pause");
}