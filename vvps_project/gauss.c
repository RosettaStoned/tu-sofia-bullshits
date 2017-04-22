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

    double a[cols][cols + 1];
    memset(a, 0, sizeof(a[0][0]) * cols * (cols + 1));

    double b[cols];

    for(col = 0; col < cols; col++) {
        for(row = 0; row < rows; row++) {
            for(i = 0; i < cols; i++) {
                if(i == cols - 1) {
                   b[col] +=   A(row, col); 
                }

                a[col + 1][i + 1] += A(row, col) * A(row, i);
            }
        }
    }

    a[0][0] = rows;
    for(col = 0; col < cols; col++) {
        a[0][col + 1] = b[col];
        a[col + 1][0] = b[col];

    }

    double left_term[cols][cols];
    double right_term[cols];

    for(col = 0; col < cols; col++) {
        for(i = 0; i <= cols; i++) {

            if(i == cols) {
                right_term[col] = a[col][i];
            } else {
                left_term[col][i] = a[col][i];
            }
        }
    }

    double *mitko = &left_term[0][0];

	gauss(mitko, right_term, result, cols);

#undef A
}

/*
int main()
{

    double table[6][4] = {
        { 1142, 1060, 325, 201 },
        { 863, 995, 98, 98 },
        { 1065, 3205, 23, 162 },
        { 554, 120, 0, 54 },
        { 983, 2896, 120, 138 },
        { 256, 485, 88, 61 }
    };

    double result[4];
    solve(*(table), 6, 4, result);

    int i;
    for(i = 0; i < 4; i++) {
        printf("%g\n", result[i]);
    }

    return 0;
}
*/
