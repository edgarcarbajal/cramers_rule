#include "matrix.h"



//default constructor
Matrix::Matrix(unsigned int r, unsigned int c)
{
	//matrix will be constructed as the zero-matrix by default if not given arguments
	this->matrix.resize(r);	//allocate # of rows
	for(auto elem : matrix)
	{
		elem.resize(c); //allocate # of cols
	}
}



//constructor #1 -	No default arguments here! please insert row & col size!
Matrix::Matrix(unsigned int r, unsigned int c, std::istream& inpstream)
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
void Matrix::size() const { printf("Size of this matrix is: %ux%u", this->get_rowSize(), this->get_colSize()); }

unsigned int Matrix::get_rowSize() const { return this->matrix.size(); }
unsigned int Matrix::get_colSize() const { return this->matrix[0].size(); }


std::vector<std::vector<double>>::const_iterator Matrix::begin() const { return this->matrix.begin(); }
std::vector<std::vector<double>>::const_iterator Matrix::end() const { return this->matrix.end(); }



void Matrix::printmat() const
{
	printf("%u x %u\n\n", this->get_rowSize(), this->get_colSize());

	for(auto elem : this->matrix)
	{
		for(auto innerelem : elem)
		{
			std::cout << innerelem << ' ';
		}
		std::cout << '\n';
	}
}



void Matrix::replace_col(Matrix& b, size_t col)
{
	if(b.get_rowSize() != this->get_rowSize() || b.get_colSize() != 1)
	{
		puts("replace_col: Not valid b-vector to replace col!");
		exit(EXIT_FAILURE);
	}

	//replace all elements in a certain column with the elements in b vector
	for(size_t i = 0; i < this->get_rowSize(); i++)
	{
		this->matrix[i][col] = b[i][0];		//should only have 1 element in inner vectors since they represent rows
	}
}




void Matrix::push_back_row(std::vector<double>& row) { this->matrix.push_back(row); }





//operator methods----
Matrix Matrix::operator+(Matrix& rhs)
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
Matrix Matrix::operator-(Matrix& rhs) 
{
	Matrix B = rhs * -1.0;
	return *this + B;
}



Matrix Matrix::operator*(Matrix& rhs)
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


//should return inner vector, then operator[] from std::vector should get the returned vector and return the number: ie--> mat[1][2] - returns row 2, then elem 3
std::vector<double>& Matrix::operator[](const int& rhs) { return this->matrix[rhs]; }




//checking(bool) methods-----
bool Matrix::valid_mat_add(const Matrix& rhs) const { if(this->get_rowSize() == rhs.get_rowSize() && this->get_colSize() == rhs.get_colSize()) return true; return false; }

bool Matrix::valid_mat_mult(const Matrix& rhs) const { if(this->get_colSize() == rhs.get_rowSize()) return true; return false; }


bool Matrix::is_nxn() const { if(this->get_rowSize() == this->get_colSize()) return true; return false; }

bool Matrix::is_nonsingular(const double& det) const { if(det == 0 && this->is_nxn()) return true; return false; }


