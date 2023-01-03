# cramers_rule
A simple project for a **Cramer's Rule** calculator. Finds the solutions of a linear system Ax=b where A is an nxn matrix and x,b are nx1 vectors.

This will have all the operations needed such as basic matrix operations, determinant calculations, etc.  

The implementation of the **Matrix** class while extensive, is not fully complete as I decided to not spend time developing the extra features as I wanted to work on other things.  
Things such as commutativity with some operations such as scalar multiplication. So please pay close attention to the method/function definitions if using the code past its demonstration in main function!  

#### How to use
Usage after running `make` on your machine to compile the code:
`./cramers_rule [input_matrix filepath] [input_vec filepath]`  
  
file path can be local or absolute (whatever works according to **std::fstream**)  
  
### Some issues that might arise  
I tested the code with successful output with the four sets of input files that I have included here (inputs 2, 3, 4 are from a math textbook), but I did not extensively test my code for any breakpoints, so if you tested it with more nonsense input, it might break, although I did put some sort of safeguards for this but not too extensive.  
  
Also I do not know how efficient **std::vector**'s are with memory but if you end up making too many matricies, or too big matricies, you might run into memory issues since finding determinants using cofactor expansion is recursive, there will be alot of matrix copies which will take up memory.  
Should not be much of an issue on modern machines but just be warned.  

I consider this project to be pretty much finished (satisfied on how it works), and will not continue developing this. (1/3/2023)
