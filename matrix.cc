#include "matrix.h"
#include <iostream>
#include <cmath>



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


//copy constructor by omission
Matrix::Matrix(const Matrix& mat, size_t row, size_t col)
{
	//copy original mat, then delete row and col from it!
	this->matrix.assign(mat.begin(), mat.end());

	//for cols we need to iterate to each vector pos! - do this first before erasing a row!
	for(auto r_itr = this->matrix.begin(); r_itr != this->matrix.end(); ++r_itr)
	{
		r_itr->erase(r_itr->begin() + col); // erase each element in the col
	}

	//for rows, since inner vectors are rows, it is easy!
	this->matrix.erase(this->matrix.begin() + row);

	//done! - size should now be (n-1)x(m-1) from original!
}



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




//checking(bool) methods-----
bool Matrix::valid_mat_add(const Matrix& rhs) { if(this->get_rowSize() == rhs.get_rowSize() && this->get_colSize() == rhs.get_colSize()) return true; return false; }

bool Matrix::valid_mat_mult(const Matrix& rhs) { if(this->get_colSize() == rhs.get_rowSize()) return true; return false; }


bool Matrix::is_nxn() { if(this->getrowSize() == this->get_colSize()) return true; return false; }

bool Matrix::is_nonsingular(const double& det) { if(det == 0 && this->is_nxn()) return true; return false; }


