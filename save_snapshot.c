#include "hdf5.h"
#include <stdlib.h>

// Function to create and write HDF5 dataset
void create_and_write_dataset(hid_t file_id, const char* datasetname, hsize_t* dims, double*** data) {
    hid_t dataspace_id, dataset_id;  
    herr_t status;

    dataspace_id = H5Screate_simple(3, dims, NULL);
    dataset_id = H5Dcreate2(file_id, datasetname, H5T_NATIVE_DOUBLE, dataspace_id,
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data[0][0][0]);
    status = H5Dclose(dataset_id);
    status = H5Sclose(dataspace_id);
}

// Function to create and write 1D dataset
void create_and_write_dataset_1D(hid_t file_id, const char* datasetname, hsize_t* dims, double* data) {
    hid_t dataspace_id, dataset_id;  
    herr_t status;

    dataspace_id = H5Screate_simple(1, dims, NULL);
    dataset_id = H5Dcreate2(file_id, datasetname, H5T_NATIVE_DOUBLE, dataspace_id,
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    status = H5Dclose(dataset_id);
    status = H5Sclose(dataspace_id);
}