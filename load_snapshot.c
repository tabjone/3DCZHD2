#include "hdf5.h"
#include <stdlib.h>

// Function to read HDF5 dataset
void read_dataset(hid_t file_id, const char* datasetname, hsize_t* dims, double*** data) {
    hid_t dataset_id = H5Dopen2(file_id, datasetname, H5P_DEFAULT);
    herr_t status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(data)[0][0][0]);
    status = H5Dclose(dataset_id);
}


// Function to read 1D HDF5 dataset
void read_dataset_1D(hid_t file_id, const char* datasetname, hsize_t* dims, double** data) {
    hid_t dataspace_id, dataset_id;  
    herr_t status;

    dataset_id = H5Dopen2(file_id, datasetname, H5P_DEFAULT);
    dataspace_id = H5Dget_space(dataset_id);
    int ndims = H5Sget_simple_extent_dims(dataspace_id, dims, NULL);

    // Allocating space for data
    *data = (double*)malloc(dims[0] * sizeof(double));

    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, *data);
    status = H5Dclose(dataset_id);
    status = H5Sclose(dataspace_id);
}

void get_dims(hid_t file_id, const char* datasetname, hsize_t* dims) {
    hid_t dataset_id, dataspace_id;
    dataset_id = H5Dopen2(file_id, datasetname, H5P_DEFAULT);
    dataspace_id = H5Dget_space(dataset_id);

    H5Sget_simple_extent_dims(dataspace_id, dims, NULL);

    H5Sclose(dataspace_id);
    H5Dclose(dataset_id);
}
