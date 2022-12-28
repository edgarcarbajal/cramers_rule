#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{
	private:
		std::vector<std::vector<double>> matrix;	//inner vectors in outer vector are rows!

	public:
		Matrix(unsigned int r = 0, unsigned int c = 0);				//default constructor
		Matrix(unsigned int r, unsigned int c, std::istream& inpstream);//direct-from-file constructor
		Matrix(const Matrix& mat);		//matrix copy constructor
		Matrix(const Matrix& mat, size_t row, size_t col);	//matrix copy constructor by omission! Excludes the row & col specified!

		Matrix operator+(Matrix& rhs);		//matrix addition
		Matrix operator-(Matrix& rhs);		//matrix subtraction
		Matrix operator*(Matrix& rhs);		//matrix multiplication
		Matrix operator*(const double& rhs);		//scalar matrix multiplication
		std::vector<double>& operator[](const int& rhs);	//index-at operation - returns inner vec then uses std::vector operator[] to get number

		void construct_matrix(std::istream& inpstream);	//create matrix from stdinput (cin) - If not constructed during object creation
		void size() const;				//returns size(nxm) of matrix printed in stdout
		unsigned int get_rowSize() const;		//returns row size of matrix
		unsigned int get_colSize() const;		//returns col size of matrix
		std::vector<std::vector<double>>::const_iterator begin() const;				//returns the begining iterator of the private var matrix
		std::vector<std::vector<double>>::const_iterator end() const;				//returns the end iterator of the private var matrix

		void printmat() const;				//prints matrix in its corresponing size - not taking into account window size
		void replace_col(Matrix& b, size_t col);	//replaces a column in a matrix with a vector(nx1 matrix) - necessary for cramer's rule
		void push_back_row(std::vector<double>& row);	//push back a row into the outer-vector matrix

		bool valid_mat_add(const Matrix& rhs) const;	//checks if matrix addition can be succesfully performed or not
		bool valid_mat_mult(const Matrix& rhs) const;	//checks if matrix mult can be successfuly performed or not
		bool is_nxn() const;				//checks if matrix is nxn
		bool is_nonsingular(const double& det) const;	//checks if matrix is nonsingular using determinant

};


#endif //MATRIX_H end
