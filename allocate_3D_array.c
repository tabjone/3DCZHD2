#include <stdlib.h>

void allocate_3D_array(double ****array_ptr, int nz, int ny, int nx) {
    *array_ptr = malloc(nz * sizeof(***array_ptr));
    if (*array_ptr == NULL) {
        // handle malloc failure
        return;
    }

    (*array_ptr)[0] = malloc(nz*ny * sizeof(**array_ptr[0]));
    if ((*array_ptr)[0] == NULL) {
        // handle malloc failure
        free(*array_ptr);
        return;
    }

    (*array_ptr)[0][0] = malloc(nz*ny*nx * sizeof(*array_ptr[0][0])); // Contiguous
    if ((*array_ptr)[0][0] == NULL) {
        // handle malloc failure
        free((*array_ptr)[0]);
        free(*array_ptr);
        return;
    }

    for (int i = 1; i < nz; i++) {
        (*array_ptr)[i] = &(*array_ptr)[0][i*ny];
    }

    for (int j = 1; j < nz*ny; j++) {
        (*array_ptr)[0][j] = &(*array_ptr)[0][0][j*nx];
    }
}

void allocate_1D_array(double **array_ptr, int nz) {
    *array_ptr = (double*)malloc(nz * sizeof(**array_ptr));
}

void allocate_all_3D(
    double ****rho, double ****rho_prev, double ****P, double ****P_prev, double ****ux, double ****ux_prev,
    double ****uy, double ****uy_prev, double ****uz, double ****uz_prev, double ****S, double ****S_prev, int nz, int ny, int nx)
{
  allocate_3D_array(rho, nz, ny, nx);
  allocate_3D_array(rho_prev, nz, ny, nx);
  allocate_3D_array(P, nz, ny, nx);
  allocate_3D_array(P_prev, nz, ny, nx);
  allocate_3D_array(ux, nz, ny, nx);
  allocate_3D_array(ux_prev, nz, ny, nx);
  allocate_3D_array(uy, nz, ny, nx);
  allocate_3D_array(uy_prev, nz, ny, nx);
  allocate_3D_array(uz, nz, ny, nx);
  allocate_3D_array(uz_prev, nz, ny, nx);
  allocate_3D_array(S, nz, ny, nx);
  allocate_3D_array(S_prev, nz, ny, nx);
}
