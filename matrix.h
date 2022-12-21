#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
	private:
		std::vector<std::vector<double>> matrix;	//inner vectors in outer vector are rows!
	public:
		Matrix(unsigned int r = 0, unsigned int c = 0);
		Matrix(unsigned int r = 0, unsigned int c = 0, std::istream& inpstream);

		Matrix operator+(const Matrix& rhs);	//matrix addition
		Matrix operator-(const Matrix& rhs);	//matrix subtraction
		Matrix operator*(const Matrix& rhs);	//matrix multiplication
		Matrix operator*(const double& rhs);	//scalar matrix multiplication

		void construct_matrix(std::istream& inpstream);	//create matrix from stdinput (cin) - If not constructed during object creation
		void size();				//returns size(nxm) of matrix printed in stdout
		unsigned int get_rowSize();		//returns row size of matrix
		unsigned int get_colSize();		//returns col size of matrix

};


#endif //MATRIX_H end
