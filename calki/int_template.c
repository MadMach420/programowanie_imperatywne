#include <stdio.h>
#include <math.h>

typedef double (*f_1d)(double);
typedef double (*f_2d)(double, double);
typedef double (*f_3d)(double, double, double);
typedef int (*boundary_2d)(double, double);
typedef double (*int_1d)(double, double, int, f_1d);

// 6.1
double int_left_rectangle(double x1, double x2, int n, f_1d f) {
    double delta = (x2 - x1) / n, ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += f(x1) * delta;
        x1 += delta;
    }
    return ans;
}

double int_right_rectangle(double x1, double x2, int n, f_1d f) {
    double delta = (x2 - x1) / n, ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += f(x1 + delta) * delta;
        x1 += delta;
    }
    return ans;
}

double int_mid_rectangle(double x1, double x2, int n, f_1d f) {
    double delta = (x2 - x1) / n, ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += f(x1 + (delta / 2)) * delta;
        x1 += delta;
    }
    return ans;
}

double int_trapezoid(double x1, double x2, int n, f_1d f) {
    double delta = (x2 - x1) / n, ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += ((f(x1) + f(x1 + delta)) / 2) * delta;
        x1 += delta;
    }
    return ans;
}

// 6.2
double integral_2d(double x1, double x2, int nx, double y1, double y2, int ny,
		f_2d f, boundary_2d boundary) {
    double delta_x = (x2 - x1) / nx, delta_y = (y2 - y1) / ny, ans = 0;
    for (int i = 0; i < nx; ++i)  {
        double temp_y = y1;
        for (int j = 0; j < ny; ++j)  {
            if (boundary(x1, temp_y)) {
                ans += f(x1, temp_y) * delta_x * delta_y;
            }
            temp_y += delta_y;
        }
        x1 += delta_x;
    }
    return ans;
}

//6.3
double integral_3d(double x1, double x2, int nx, double y1, double y2, int ny,
		double z1, double z2, int nz, f_3d f) {
    double delta_x = (x2 - x1) / nx;
    double delta_y = (y2 - y1) / ny;
    double delta_z = (z2 - z1) / nz;
    double ans = 0;

    for (int i = 0; i < nx; ++i)  {
        double temp_y = y1;
        for (int j = 0; j < ny; ++j) {
            double temp_z = z1;
            for (int k = 0; k < nz; ++k) {
                ans += f(x1, temp_y, temp_z) * delta_x * delta_y * delta_z;
                temp_z += delta_z;
            }
            temp_y += delta_y;
        }
        x1 += delta_x;
    }
    return ans;
}

double f_1d_1(double x) {
	return x;
}

double f_1d_2(double x) {
    return x*x/2;
}

double f_1d_3(double x) {
    return 1/(x+1);
}

double f_1d_4(double x){
    return log10(x + 1);
}

double f_2d_1(double x, double y) {
    return x * y * y;
}

double f_2d_2(double x, double y) {
    return (x * x) + (y * y);
}

double f_2d_3(double x, double y) {
    return 1 / ((1 - (x * x) - (y * y)) * (1 - (x * x) - (y * y)));
}

int f_2d_1_boundary(double x, double y) {
	return x*x + y*y <= 4 && x >= 0;
}

int f_2d_2_boundary(double x, double y) {
    return x*x + x*y - 2*y <= 0 || x*x + x*y - 2*y >= 1;
}

int f_2d_3_boundary(double x, double y) {
    return x*x + y*y <= x && x*x + y*y <= y;
}

double f_3d_1(double x, double y, double z) {
    return x + 3*y + 5*z;
}

double f_3d_2(double x, double y, double z) {
    return 8*sin(x) + (5*cos(y)) * (5*cos(y)) + 2*z;
}

int main(void) {
	int to_do;
	double x1, x2, y1, y2, z1, z2;
	int n, nx, ny, nz;
	scanf("%d", &to_do);
	switch (to_do) {
		case 1: // 6.1
			scanf("%lf %lf %d", &x1, &x2, &n);
			int_1d int_f[] = {int_left_rectangle, int_right_rectangle,
				int_mid_rectangle, int_trapezoid };
			f_1d p_function_1d[] = {f_1d_1, f_1d_2, f_1d_3, f_1d_4 };
			for(int i = 0; i < sizeof(p_function_1d) / sizeof(f_1d); i++) {
				for(int j = 0; j < sizeof(int_f) / sizeof(int_1d) ; j++) {
					printf("%.2f ", int_f[j](x1, x2, n, p_function_1d[i]));
				}
				printf("\n");
			}
			break;
		case 2: // 6.2
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			f_2d p_function_2d[] = {f_2d_1, f_2d_2, f_2d_3 };
			boundary_2d p_boundaries[] = {f_2d_1_boundary, f_2d_2_boundary,
				f_2d_3_boundary };
			for(int i = 0; i < sizeof(p_function_2d) / sizeof(f_2d); ++i) {
				printf("%.2f ",
						integral_2d(x1, x2, nx, y1, y2, ny,
							p_function_2d[i], p_boundaries[i]));
			}
			printf("\n");
			break;
		case 3: // 6.3
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			scanf("%lf %lf %d", &z1, &z2, &nz);
			f_3d function_3d[] = {f_3d_1, f_3d_2};
			for(int i = 0; i < sizeof(function_3d) / sizeof(f_3d); ++i) {
				printf("%.2f ",
						integral_3d(x1, x2, nx, y1, y2, ny, z1, z2, nz, function_3d[i]));
			}
			printf("\n");
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

