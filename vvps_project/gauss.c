#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>
 
#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))
 
void swap_row(double *a, double *b, int r1, int r2, int n)
{
    assert(a != NULL);
    assert(b != NULL);

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
/*
 Usage:     gauss(a,b,x,n)
		   
		   a   - Matrix a[n][n]
		   b   - Right hand side vector b[n]
		   x   - Desired solution vector
		   n   - Matrix dimensions
 */
#define A(y, x) (*mat_elem(a, y, x, n))

    assert(a != NULL);
    assert(b != NULL);
    assert(x != NULL);
    assert(x > 0);

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

bool is_table_only_zeroes(double *table, int rows, int cols)
{
#define table(row, col) (table[(row) * cols + (col)])
    assert(table != NULL);
    assert(rows > 0);
    assert(cols > 0);
 
    int row, col;
    for(row = 0; row < rows; row++) {
        for(col = 0; col < cols; col++) {
            if(table(row, col) != 0) {
                return false;
            }
        }
    }

    return true;
#undef table
}

void solve(double *table, int rows, int cols, double *result)
{
/*
 Usage:     solve(table, rows, cols, result)                                                      
+                                                                                 
+            table - Matrix table[n][n]                                                 
+            rows - Table rows count                                   
+            cols - Table cols count                                      
+            result - Desired solution vector                   

*/
#define table(row, col) (table[(row) * cols + (col)])
    assert(table != NULL);
    assert(rows > 0);
    assert(cols > 0);
    assert(result != NULL);

    int row, col, i;

    assert(is_table_only_zeroes(table, rows, cols) == false);

    double matrix[cols][cols + 1];
    memset(matrix, 0, sizeof(matrix[0][0]) * cols * (cols + 1));

    double vector[cols];

    for(col = 0; col < cols; col++) {
        for(row = 0; row < rows; row++) {
            for(i = 0; i < cols; i++) {
                if(i == cols - 1) {
                   vector[col] +=   table(row, col); 

                   assert(!isnan(vector[col]));
                }

                matrix[col + 1][i + 1] += table(row, col) * table(row, i);

                assert(!isnan(matrix[col + 1][i + 1]));
            }
        }
    }

    matrix[0][0] = rows;
    for(col = 0; col < cols; col++) {
        matrix[0][col + 1] = vector[col];
        matrix[col + 1][0] = vector[col];
    }

    double left_hand_matrix[cols][cols];
    double right_hand_vector[cols];

    for(col = 0; col < cols; col++) {
        for(i = 0; i <= cols; i++) {

            if(i == cols) {
                right_hand_vector[col] = matrix[col][i];
            } else {
                left_hand_matrix[col][i] = matrix[col][i];
            }
        }
    }

	gauss(&left_hand_matrix[0][0], right_hand_vector, result, cols);

#undef table
}


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
