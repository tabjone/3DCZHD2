#include "hdf5.h"
#include <stdlib.h>
#include "functions.h"
#include <mpi.h>
#include <omp.h>



int main(int nargs, char **args) {
    int dx, dy, dz;
    double dt;

    double ***rho, ***rho_prev;
    double ***P, ***P_prev;
    double ***ux, ***uy, ***uz;
    double ***ux_prev, ***uy_prev, ***uz_prev;
    double ***S, ***S_prev;
    double ***tmp_ptr;

    double* z;
    double* g; // gravity at all z-locations

    hid_t file_id;
    herr_t status;
    hsize_t dims[3];

    bool load_snapshot = false;
    if (load_snapshot) {
        // get dims
        file_id = H5Fopen("./snapshots/snap0.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
        get_dims(file_id, "/rho", dims);
    } else {
        // set dims, this should be as args from command line
        // or if no args is passed then use default values
        dims[0] = 500;
        dims[1] = 100;
        dims[2] = 100;
    }

    dx = 1.0/(dims[2]-1);
    dy = 1.0/(dims[1]-1);
    dz = 1.0/(dims[0]-1);
    dt = 2.0*dx;  // maximum value allowed for the time step size

    // Allocate memory
    allocate_all_3D(&rho, &rho_prev, &P, &P_prev, &ux, &ux_prev, &uy, &uy_prev, &uz, &uz_prev, &S, &S_prev, dims[0], dims[1], dims[2]);
    allocate_1D_array(&z, dims[0]);
    allocate_1D_array(&g, dims[0]);

    if (load_snapshot)
    {
        // Read the datasets
        read_dataset(file_id, "/rho", dims, rho);
        read_dataset(file_id, "/P", dims, P);
        read_dataset(file_id, "/ux", dims, ux);
        read_dataset(file_id, "/uy", dims, uy);
        read_dataset(file_id, "/uz", dims, uz);
        read_dataset(file_id, "/S", dims, S);
        // Close the HDF5 file
        status = H5Fclose(file_id);
    }
    else
    {
        initialize_ideal_gas(rho, P, ux, uy, uz, S, g, z, dims[0], dims[1], dims[2]);
        initialize_ideal_gas(rho_prev, P_prev, ux_prev, uy_prev, uz_prev, S_prev, g, z, dims[0], dims[1], dims[2]);
    }

    /*
    // compute the remaining time steps using a faster implementation
    t = dt;
    while (t<T) {
        t += dt;
        // compute u_new using u and u_prev
        one_fast_time_step (nx, ny, dx, dy, dt, u_new, u, u_prev);
        // pointer swaps
        tmp_ptr = u_prev;
        u_prev = u;
        u = u_new;
        u_new = tmp_ptr;
    }*/
    
    
    bool save_snapshot = true;
    if (save_snapshot)
    {
        // Create a new file using default properties.
        file_id = H5Fcreate("./snapshots/snap0.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

        // Create and write datasets
        create_and_write_dataset(file_id, "/rho", dims, rho);
        create_and_write_dataset(file_id, "/P", dims, P);
        create_and_write_dataset(file_id, "/ux", dims, ux);
        create_and_write_dataset(file_id, "/uy", dims, uy);
        create_and_write_dataset(file_id, "/uz", dims, uz);
        create_and_write_dataset(file_id, "/S", dims, S);
        create_and_write_dataset_1D(file_id, "/z", &dims[0], z);
        // Close the file
        status = H5Fclose(file_id);
    }

    // Free the allocated memory
    deallocate_all(rho, rho_prev, P, P_prev, ux, ux_prev, uy, uy_prev, uz, uz_prev, S, S_prev, z, g);
};