#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

void print_mat_ind(double A[][SIZE], int m, int n, const int indices[]);

// 5.1
// Calculate matrix product, AB = A X B
// A[m][p], B[p][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            AB[i][j] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                AB[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Calculate matrix - vector product
void mat_vec_product(double A[][SIZE], const double b[], double Ab[], int m, int n);

void backward_substit(double A[][SIZE], double x[], int n);

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n);

// 5.2
// Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n){
    int ratio, product=1;
    for (int step = 0; step < n - 1; ++step) {
        if (A[step][step] == 0) return NAN;
        for (int i = step + 1; i < n; ++i) {
            ratio = A[i][step] / A[step][step];
            for (int j = 0; j < n; ++j) {
                A[i][j] -= A[step][j] * ratio;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        product *= A[i][i];
    }
    return product;
}

// 5.3
// Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps){
    int max_ind, temp;
    double ratio;

    int indices_arr[n];
    for (int i = 0; i < n; ++i) {
        indices_arr[i] = i;
    }

    for (int step = 0; step < n - 1; ++step) {

        max_ind = step;
        for (int i = step + 1; i < n; ++i) {
            if (fabs(A[indices_arr[i]][step]) > fabs(A[indices_arr[max_ind]][step])) {
                max_ind = i;
            }
        }
        if (max_ind != step) {
            temp = indices_arr[max_ind];
            indices_arr[max_ind] = indices_arr[step];
            indices_arr[step] = temp;
        }

        if (fabs(A[indices_arr[step]][step]) < eps) {
            return 0;
        }

        for (int i = step + 1; i < n; ++i) {
            ratio = A[indices_arr[i]][step] / A[indices_arr[step]][step];
            for (int j = step; j < n; ++j) {
                double hehe = ratio * A[indices_arr[step]][j];
                A[indices_arr[i]][j] -= hehe;
            }
        }

    }

    double determinant = 1;
    for (int i = 0; i < n; ++i) {
        determinant *= A[indices_arr[i]][i];
    }
    // TU UZYJE matrix_inv
}

// 5.4
// Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps){
    int max_index;
    double temp[SIZE];
    for (int step = 0; step < n - 1; ++step) {
        max_index = step;
        for (int i = step + 1; i < n; ++i) {
            if (A[i][step] > A[max_index][step]) {
                max_index = i;
            }
        }
        if (max_index != step) {

        }
    }
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if(det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A,n,n);
			printf("%.4f\n",matrix_inv(A, B, n, eps));
			print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}
