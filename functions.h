#ifndef functions_H__
#define functions_H__


void allocate_3D_array(double ****array_ptr, int nx, int ny, int nz);
void allocate_all_3D(
    double ****rho, double ****rho_prev, double ****P, double ****P_prev, double ****ux, double ****ux_prev,
    double ****uy, double ****uy_prev, double ****uz, double ****uz_prev, double ****S, double ****S_prev, int nz, int ny, int nx);
void allocate_1D_array(double **array_ptr, int nz);
void deallocate_3D_array(double ***array);
void deallocate_all(
    double ***rho, double ***rho_prev, double ***P, double ***P_prev, double ***ux, double ***ux_prev,
    double ***uy, double ***uy_prev, double ***uz, double ***uz_prev, double ***S, double ***S_prev,
    double *g, double *z);


void create_and_write_dataset(hid_t file_id, const char* datasetname, hsize_t* dims, double*** data);
void create_and_write_dataset_1D(hid_t file_id, const char* datasetname, hsize_t* dims, double* data);

void read_dataset(hid_t file_id, const char* datasetname, hsize_t* dims, double*** data);
void read_dataset_1D(hid_t file_id, const char* datasetname, hsize_t* dims, double** data);

void get_dims(hid_t file_id, const char* datasetname, hsize_t* dims);

void initialize_hydrostatic_equilibrium(
    double ***rho, double ***P, double ***ux, double ***uy, double ***uz, double ***S, double *g, double *z,
    int nz, int ny, int nx);

void one_timestep(
    double ***rho, double ***rho_prev, double ***P, double ***P_prev, double ***ux, double ***ux_prev,
    double ***uy, double ***uy_prev, double ***uz, double ***uz_prev, double ***S, double ***S_prev,
    double dz, double dx, double dy,
    int nz, int ny, int nx);

#endif