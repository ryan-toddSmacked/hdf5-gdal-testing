
#include <hdf5.h>

#include <stdio.h>
#include <stdlib.h>

typedef enum type_t {
    TYPE1,
    TYPE2,
    TYPE3
} type_t;

typedef struct {
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
    type_t type;
} s1_t;



int main()
{
    // Allocate 1000 s1_t structures
    // initialize them to all zeros
    // write them to a h5 file, using a compound datatype
    // its dimensions should be 1000x1, hsize_t dims[1] = {1000};
    // dont include the singleton dimension

    // read them back in, and print out the first 10

    s1_t* s1 = calloc(1000, sizeof(s1_t));

    hid_t file_id = H5Fcreate("h5example.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // To insert a compound datatype into a dataset the following steps are required:
    // 1. Create the compound datatype
    // 2. Insert the atomic datatypes into the compound datatype
    // 3. Set the dimensions of the compound datatype
    // 4. Create the dataset
    // 5. Write the dataset

    // 1. Create the compound datatype
    hid_t s1_tid = H5Tcreate(H5T_COMPOUND, sizeof(s1_t));

    // 2. Insert the atomic datatypes into the compound datatype
    // They are all floats, so we can use H5T_NATIVE_FLOAT
    H5Tinsert(s1_tid, "x", HOFFSET(s1_t, x), H5T_NATIVE_FLOAT);
    H5Tinsert(s1_tid, "y", HOFFSET(s1_t, y), H5T_NATIVE_FLOAT);
    H5Tinsert(s1_tid, "z", HOFFSET(s1_t, z), H5T_NATIVE_FLOAT);
    H5Tinsert(s1_tid, "vx", HOFFSET(s1_t, vx), H5T_NATIVE_FLOAT);
    H5Tinsert(s1_tid, "vy", HOFFSET(s1_t, vy), H5T_NATIVE_FLOAT);
    H5Tinsert(s1_tid, "vz", HOFFSET(s1_t, vz), H5T_NATIVE_FLOAT);

    // Create an enum datatype
    hid_t type_tid = H5Tcreate(H5T_ENUM, sizeof(type_t));
    int t1 = TYPE1; int t2 = TYPE2; int t3 = TYPE3;
    H5Tenum_insert(type_tid, "TYPE1", &t1);
    H5Tenum_insert(type_tid, "TYPE2", &t2);
    H5Tenum_insert(type_tid, "TYPE3", &t3);

    // Insert the enum datatype into the compound datatype
    H5Tinsert(s1_tid, "type", HOFFSET(s1_t, type), type_tid);

    // 3. Set the dimensions of the compound datatype
    hsize_t dims[1] = {1000};
    hid_t space_id = H5Screate_simple(1, dims, NULL);

    // 4. Create the dataset
    hid_t dataset_id = H5Dcreate(file_id, "s1", s1_tid, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // 5. Write the dataset
    H5Dwrite(dataset_id, s1_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s1);

    // Close everything
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Tclose(s1_tid);
    H5Fclose(file_id);

    // Deallocate memory
    free(s1);


    // Pointer to results, assume we dont know the required size
    s1_t* s1_read = NULL;

    // Open the file
    file_id = H5Fopen("h5example.h5", H5F_ACC_RDONLY, H5P_DEFAULT);

    // Open the dataset
    dataset_id = H5Dopen(file_id, "s1", H5P_DEFAULT);

    // Get the datatype
    hid_t datatype_id = H5Dget_type(dataset_id);

    // Get the dataspace
    space_id = H5Dget_space(dataset_id);

    // Get the number of elements in the dataset
    hsize_t num_elements = H5Sget_simple_extent_npoints(space_id);

    // Allocate memory
    s1_read = calloc(num_elements, H5Tget_size(datatype_id));

    // Read the dataset
    H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, s1_read);

    // Close everything
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Tclose(datatype_id);
    H5Fclose(file_id);

    // Print out the first 10 elements
    for (int i = 0; i < 10; i++)
    {
        printf("x: %f, y: %f, z: %f, vx: %f, vy: %f, vz: %f\n", s1_read[i].x, s1_read[i].y, s1_read[i].z, s1_read[i].vx, s1_read[i].vy, s1_read[i].vz);
    }

    // Deallocate memory
    free(s1_read);

    return 0;
}


