#include "matrix.h"
#include <iostream>



//default constructor
Matrix::Matrix(unsigned int r = 0, unsigned int c = 0)
{
	//matrix will be constructed as the zero-matrix
	this->matrix.resize(r);	//allocate # of rows
	for(auto elem : matrix)
	{
		elem.resize(c); //allocate # of cols
	}
}



//constructor #1
Matrix::Matrix(unsigned int r = 0, unsigned int c = 0, std::istream& inpstream)
{
	this->matrix.resize(r);	//allocate # of rows
	for(auto elem : matrix)
	{
		elem.resize(c); //allocate # of cols
	}

	construct_matrix(inpstream);	//construct matrix!
}



//copy constructor
Matrix::Matrix(const Matrix& mat) { this->matrix.assign(mat.begin(), mat.end()); }



//helper constructor(from a file)
void Matrix::construct_matrix(std::istream& inpstream)
{
	for(size_t i = 0; i < this->get_rowSize(); i++)
	{
		for(size_t j = 0; j < this->get_colSize(); j++)
		{
			inpstream >> this->matrix[i][j];
		}
	}
}



//general info methods
void size() { printf("Size of this matrix is: %ux%u", this->get_rowSize(), this->get_colSize()); }

unsigned int get_rowSize() { return this->matrix.size(); }
unsigned int get_colSize() { return this->matrix[0].size(); }



//operator methods----
Matrix Matrix::operator+(const Matrix& rhs)
{
	if(!valid_mat_add(rhs))
	{
		puts("Error! - Cannot add these matricies together: Not the same size!");
		exit(EXIT_FAILURE);
	}


	Matrix C(this->get_rowSize(), this->get_colSize());

	//Add each element of matrix A & B together and store it in the same element location in C
	for(size_t i = 0; i < C.get_rowSize(); i++)
	{
		for(size_t j = 0; j < C.get_colSize(); j++)
		{
			C[i][j] = this->matrix[i][j] + rhs[i][j];
		}
	}

	return C;
}



//The syntax it should call operator+ and operator* (the scalar version)
Matrix Matrix::operator-(const Matrix& rhs) { return (*this + (rhs * -1.0)); }



Matrix Matrix::operator*(const Matrix& rhs)
{
	if(!valid_mat_mult(rhs))
	{
		puts("Error! - Cannot multiply these matricies toghether: lefthand-side matrix does not have same # of cols as # of rows for righthand-side matrix!");
		exit(EXIT_FAILURE);
	}

	//New matrix inherits rows of lhs and cols of rhs
	Matrix C(this->get_rowSize(), rhs.get_colSize());

	//Need triple loop to multiply matricies! last loop is shared between both matricies elements!
	for(size_t i = 0; i < C.get_rowSize(); i++)
	{
		for(size_t j = 0; j < C.get_colSize(); j++)
		{
			//k is the cols of lhs/rows of rhs!
			for(size_t k = 0; k < this->get_colSize(); k++)
			{
				C[i][j] += (*this)[i][k] * rhs[k][j];
			}
		}
	}

	return C;
}



Matrix Matrix::operator*(const double& rhs)
{
	//make copy of this matrix to return after doing ops!
	Matrix C(*this);

	for(size_t i = 0; i < this->get_rowSize(); i++)
	{
		for(size_t j = 0; j < this->get_colSize(); j++)
		{
			(*this)[i][j] *= rhs;// scalar mult!
		}
	}

	return C;
}



