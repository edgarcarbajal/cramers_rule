#include "matrix.h"

//determinant function - using cofactor expansion and recursion! - base case should be getting a 2x2 matrix to find determinant!
double determinant(const Matrix& mat);
double det_recur(const Matrix& mat, size_t row, size_t col);


//cramer's rule function
std::vector<double> cramers_rule(const Matrix& mat, const std::vector<double>& x);






//Main func for this program!
int main()
{
	return 0;
}








double determinant(const Matrix& mat)
{
	//always choose the expansion of det(A) along the first(i)th row - so always i = 1 or in coding i = 0
	//ie: det(A) = a_i1(A_i1) + a_i2(A_i2) + ... + a_in(A_in)
	// a_ij is the element in the matrix
	// A_ij is the cofactor where A_ij = [(-1)^(i+j)] * det(M_ij)
	// M_ij is the submatrix of A obtained by deleting(omitting) ith row and jth col of A
	

	if(!mat.is_nxn())
	{
		puts("Error! - Cannot find determinant of this matrix: not an nxn matrix!");
		exit(EXIT_FAILURE);
	}

	if(mat.get_rowSize() == 2)
	{
		//for 2x2 determinants:
		//a_11(a_22) - a_12(a_21)
		return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
	}

	//since not a 2x2, must do cofactor expansion to find determinant!
	double res = 0;
	for(size_t j = 0; j < mat.get_colSize(); j++)
	{
		//doing cofactor expansion with fixed row i = 0
		//The i & j being -1 of what they should be should not affect the result of the positive/negative 1....
		res += mat[0][j] * (pow(-1, 0 + j) * det_recur(mat, 0, j)) //adding this every loop is equivalent to the cofactor expansion equation
	}

	//return the new answer after cofactor expansion! (recursion done)
	return res;
}



double det_recur(const Matrix& mat, size_t row, size_t col)
{
	//already checked for nxn in starter function so no need

	//create new matrix M_ij - should still be nxn just smaller
	//Also created here and not in the starter func so that it deallocates when out of scope!(hopefully)
	Matrix M(mat, row, col);

	if(M.get_rowSize() == 2)	//Base case!
	{
		//for 2x2 determinants:
		//a_11(a_22) - a_12(a_21)
		return (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
	}


	//since not a 2x2, must do cofactor expansion!
	double res = 0;
	for(size_t j = 0; j < M.get_colSize(); j++)
	{
		//doing cofactor expansion with fixed row i = 0
		//The i & j being -1 of what they should be should not affect the result of the positive/negative 1....
		res += M[0][j] * (pow(-1, 0 + j) * det_recur(M, 0, j)) //adding this every loop is equivalent to the cofactor expansion equation
	}

	//return the new answer after cofactor expansion! (recursion done for this matrix)
	return res;
}





std::vector<double> cramers_rule(const Matrix& mat, const std::vector<double>& x)
{
}

