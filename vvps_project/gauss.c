#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
 
#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))
 
void swap_row(double *a, double *b, int r1, int r2, int n)
{
	double tmp, *p1, *p2;
	int i;
 
	if (r1 == r2) return;
	for (i = 0; i < n; i++) {
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	}
	tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}
 
void gauss(double *a, double *b, double *x, int n)
{
#define A(y, x) (*mat_elem(a, y, x, n))
	int i, j, col, row, max_row,dia;
	double max, tmp;
 
	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);
 
		for (row = dia + 1; row < n; row++)
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;
 
		swap_row(a, b, dia, max_row, n);
 
		for (row = dia + 1; row < n; row++) {
			tmp = A(row, dia) / A(dia, dia);
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	for (row = n - 1; row >= 0; row--) {
		tmp = b[row];
		for (j = n - 1; j > row; j--)
			tmp -= x[j] * A(row, j);
		x[row] = tmp / A(row, row);
	}
#undef A
}

void solve(double *table, int rows, int cols, double *result)
{
#define A(row, col) (table[(row) * cols + (col)])

    int row, col, i;

    double sums[rows];
    double sums_mult[cols][cols];
    memset(sums_mult, 0, sizeof(sums_mult[0][0]) * rows * cols);

    for(col = 0; col < cols; col++) {
        for(row = 0; row < rows; row++) {
            sums[col] += A(row, col);

            for(i = 0; i < cols; i++) {
                sums_mult[col][i] += A(row, col) * A(row, i);
            }
        }
    }

   double a[] = {
        rows, sums[0], sums[1], sums[2],
        sums[0], sums_mult[0][0], sums_mult[0][1], sums_mult[0][2],
        sums[1], sums_mult[0][1], sums_mult[1][1], sums_mult[1][2],
        sums[2], sums_mult[0][2], sums_mult[2][1], sums_mult[2][2]
    };


    double b[] = {
       sums[3],
       sums_mult[0][3],
       sums_mult[1][3],
       sums_mult[3][2],
    };

	gauss(a, b, result, cols);

#undef A
}
