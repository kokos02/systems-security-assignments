#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#define   SIZE   10

int calculatePolynomial(int degree, int point, int password, int ai[])
{
    int coef;
    int calculation;

    point = password;

    for (coef = 0; coef < 4; coef++)
    {
        calculation = ai[coef] * pow(degree + 1, coef + 1);
        point += calculation;
        //printf("----->%d\n", point);
    }
    printf("\n");
    return point;
}

int main()
{

    //ULONG_MAX
    int points[10] = {};
    int a0 = 23;
    int ai[8] = {2, 2, 3, 4, 2, 2, 3, 3};
    int point;
    int coef;

    for (coef = 0; coef < 5; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%d\n", points[coef]);
    }

     float matrix[SIZE][SIZE], x[SIZE], ratio;
	 int row,column,k,unknown;
	
	 
	
	 /* Inputs */
	 /* 1. Reading number of unknowns */
	 printf("Enter number of unknowns: ");
	 scanf("%d", &unknown);
	 /* 2. Reading Augmented Matrix */
	 for(row=1;row<=unknown;row++)
	 {
		  for(column=1;column<=unknown+1;column++)
		  {
			   printf("matrix[%d][%d] = ",row,column);
			   scanf("%f", &matrix[row][column]);
		  }
	 }
	/* Applying Gauss Elimination */
	 for(row=1;row<=unknown-1;row++)
	 {
		  if(matrix[row][row] == 0.0)
		  {
			   printf("Mathematical Error!");
			   exit(0);
		  }
		  for(column=row+1;column<=unknown;column++)
		  {
			   ratio = matrix[column][row]/matrix[row][row];
			   
			   for(k=1;k<=unknown+1;k++)
			   {
			  		matrix[column][k] = matrix[column][k] - ratio*matrix[row][k];
			   }
		  }
	 }
	 /* Obtaining Solution by Back Subsitution */
	 x[unknown] = matrix[unknown][unknown+1]/matrix[unknown][unknown];
	
	 for(row=unknown-1;row>=1;row--)
	 {
		  x[row] = matrix[row][unknown+1];
		  for(column=row+1;column<=unknown;column++)
		  {
		  		x[row] = x[row] - matrix[row][column]*x[column];
		  }
		  x[row] = x[row]/matrix[row][row];
	 }
	 /* Displaying Solution */ 
	 printf("\nSolution:\n");
	 for(row=1;row<=unknown;row++)
	 {
	  	printf("x[%d] = %0.3f\n",row, x[row]);
	 }

}