#include "matrix.h"
#include <string>
#include <fstream>
#include <cmath>

//determinant function - using cofactor expansion and recursion! - base case should be getting a 2x2 matrix to find determinant!
double determinant(Matrix& mat);
double det_recur(Matrix& mat, size_t row, size_t col);


//cramer's rule function
Matrix cramers_rule (Matrix& mat, Matrix& b);

//open file method to get an input stream to matrix data - returns false if failed to open!
bool open_file(std::ifstream& in_filestr, const std::string& filepath);
bool close_file(std::ifstream& in_filestr);

void formatline(int len, char linechar); //prints a simple line depending on the size of chars given! Must specify what char to use!



//Main func for this program!
int main(int argc, char** argv)
{
	//main function is to do cramers rule - Needs two files representing two matrix object's data!!
	//program will exit if not satisfied.
	
	if(argc != 3)
	{
		puts("Error: wrong usage!\nUsage: ./cramers_rule [matrix file data] [vector file data]");
		exit(EXIT_FAILURE);
	}

	std::ifstream inpstream_mat, inpstream_vec;	//two inp file streams
	if(!open_file(inpstream_mat, argv[1]))
	{
		printf("open_file: Failed to open file \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(!open_file(inpstream_vec, argv[2]))
	{
		printf("open_file: Failed to open file \"%s\"\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	//temp vars to read in size of matricies to be costructed from input stream
	int r,c;
	inpstream_mat >> r >> c;
	Matrix A(r, c, inpstream_mat);

	inpstream_vec >> r >> c;
	Matrix b(r, c, inpstream_vec);



	if(!close_file(inpstream_mat))
	{
		printf("close_file: Failed to close file \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(!close_file(inpstream_vec))
	{
		printf("close_file: Failed to close file \"%s\"\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	printf("-=###CRAMER'S RULE###=-");
	formatline(60, '=');


	puts("\nMatrix A");
	formatline(10, '-');
	A.printmat();
	formatline(10, '-');

	puts("\nVector b (result)");
	formatline(10, '-');
	b.printmat();
	formatline(10, '-');


	puts("Finding the solution x from the linear system: Ax = b using Cramer's rule where A is nxn and x & b are nx1 matricies/vectors");
	Matrix x = cramers_rule(A, b);


	puts("\nVector x (solution)");
	formatline(10, '-');
	x.printmat();
	formatline(10, '-');



	puts("\n\nChecking answer by multiplying A & x with matrix multiplication\n\t- Remember: Ax = b");
	Matrix result = A * x;


	puts("\nMatrix(vector) result from multiplying A & x");
	formatline(10, '-');
	result.printmat();
	formatline(10, '-');



	formatline(60, '=');


	formatline(60, '@');
	puts("\n\nTesting out the rest of the matrix operations not shown for the main function of cramer's rule!");

	if(A.is_nxn())
		puts("\nA is an nxn matrix by is_nxn() method!");
	else
		puts("\nA is not an nxn matrix by is_nxn() method");

	double A_det = determinant(A);
	printf("det(A) = %f\n", A_det);


	if(A.is_nonsingular(A_det))
		puts("\nA is nonsingular by is_nonsingular() method! (can also just check its determinant from eariler...)");
	else
		puts("\nA is singular by is_nonsingular() method! (can also just check its determinant from eariler...)");



	puts("\n\nAddition and subtraction of matricies\n\nA + A = C\nContents of Matrix C");
	Matrix C = A + A;

	formatline(10, '-');
	C.printmat();
	formatline(10, '-');


	puts("\nA = new C = C - A\nContents of new Matrix C");
	C = C - A;

	formatline(10, '-');
	C.printmat();
	formatline(10, '-');


	//note to user - I have only implemented scalar multiplication where the matrix must be left-handside only!
	puts("\n\nScalar multiplication of matricies\n\ncA = Ac = C where c is any real number (in this case c = 5)\nContents of Matrix C");
	C = A * 5;

	formatline(10, '-');
	C.printmat();
	formatline(10, '-');


	formatline(60, '@');

	return 0;
}








double determinant(Matrix& mat)
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
		res += mat[0][j] * (pow(-1, 0 + j) * det_recur(mat, 0, j)); //adding this every loop is equivalent to the cofactor expansion equation
	}

	//return the new answer after cofactor expansion! (recursion done)
	return res;
}



double det_recur(Matrix& mat, size_t row, size_t col)
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
		res += M[0][j] * (pow(-1, 0 + j) * det_recur(M, 0, j)); //adding this every loop is equivalent to the cofactor expansion equation
	}

	//return the new answer after cofactor expansion! (recursion done for this matrix)
	return res;
}





Matrix cramers_rule(Matrix& mat, Matrix& b)
{
	//find the solution vec x by find each element of it(ie: x_1, x_2... x_n) where
	// x_i = det(A_i)/det(A) where A_i is the matrix A with the ith column replaced with the values of the result column vector b
	
	//cramer's rule only works if A is nonsingular(ie: A is nxn & has a nonzero determinant)
	
	
	Matrix x;
	double A_det = determinant(mat);
	if(!mat.is_nonsingular(A_det))
	{
		puts("Error! - Cannot find solution of this linear system using Cramer's Rule: not a nonsingular matrix!");
		exit(EXIT_FAILURE);
	}

	for(size_t i = 0; i < mat.get_colSize(); i++)
	{
		Matrix Ai(mat);
		Ai.replace_col(b, i);

		double xi = determinant(Ai) / A_det;
		std::vector<double> xrow_i(1, xi); //1 col, with value xi

		//push back new row into x matrix(col vector) - should be a copy???
		x.push_back_row(xrow_i);
	}

	return x;
}



bool open_file(std::ifstream& in_filestr, const std::string& filepath)
{
	in_filestr.open(filepath);
	if(!in_filestr)
		return false;
	return true;
}


bool close_file(std::ifstream& in_filestr)
{
	in_filestr.close();
	if(!in_filestr)
		return false;
	return true;
}



void formatline(int len, char linechar)
{
	std::cout << '\n';
	for(int i = 0; i < len; i++)
		std::cout << linechar;
	std::cout << '\n';
}


