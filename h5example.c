


#include <hdf5.h>

#include <stdlib.h>


struct customer
{
    char* name;
    int age;
    float height;
    float id[200];
};



void writeString(const char* filename, const char* fieldname, const char* string)
{
    // Create file, overwriting if exists, using default file creation properties, and default file access properties
    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create dataspace for the string
    hsize_t dims[1] = {1};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create the string datatype
    hid_t stringtype = H5Tcopy(H5T_C_S1);
    H5Tset_size(stringtype, H5T_VARIABLE);

    // Create the dataset
    hid_t dataset_id = H5Dcreate(file_id, fieldname, stringtype, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the string
    H5Dwrite(dataset_id, stringtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, &string);

    // Release resources
    H5Sclose(dataspace_id);
    H5Tclose(stringtype);
    H5Dclose(dataset_id);
    H5Fclose(file_id);
}

char* readString(const char* filename, const char* fieldname)
{
    // Open the file for reading
    hid_t file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);

    // Open the dataset
    hid_t dataset_id = H5Dopen(file_id, fieldname, H5P_DEFAULT);

    // Get the datatype
    hid_t datatype = H5Dget_type(dataset_id);

    // Get the dataspace
    hid_t dataspace = H5Dget_space(dataset_id);

    // Get the number of dimensions
    int ndims = H5Sget_simple_extent_ndims(dataspace);

    // Get the dimensions
    hsize_t dims[ndims];
    H5Sget_simple_extent_dims(dataspace, dims, NULL);

    // Get the size of the datatype
    size_t type_size = H5Tget_size(datatype);

    // Allocate space for the string
    char* string = malloc(dims[0] * type_size);

    // Read the string
    H5Dread(dataset_id, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, &string);

    // Release resources
    H5Dclose(dataset_id);
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Fclose(file_id);

    return string;
}

void writeCompound(const char* filename, const char* fieldname, const struct customer* customer)
{
    // Create file
    hid_t file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create dataspace
    hsize_t dims[1] = {1};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create the compound datatype
    hid_t compoundtype = H5Tcreate(H5T_COMPOUND, sizeof(struct customer));

    herr_t err;
    // Add the fields
    
    // Name field, null-terminated string
    hid_t stringtype = H5Tcopy(H5T_C_S1);
    H5Tset_size(stringtype, H5T_VARIABLE);
    H5Tinsert(compoundtype, "name", HOFFSET(struct customer, name), stringtype);

    // age field, integer
    hid_t inttype = H5Tcopy(H5T_NATIVE_INT);
    H5Tinsert(compoundtype, "age", HOFFSET(struct customer, age), inttype);

    // height field, float
    hid_t floattype = H5Tcopy(H5T_NATIVE_FLOAT);
    err = H5Tinsert(compoundtype, "height", HOFFSET(struct customer, height), floattype);

    if (err < 0)
        printf("Error inserting float into compound type\n");

    // id field, variable-length array of floats
    hsize_t array_dims[1] = {200};
    hid_t array_type = H5Tarray_create2(floattype, 1, array_dims);
    H5Tinsert(compoundtype, "id", HOFFSET(struct customer, id), array_type);

    // Create the dataset
    hid_t dataset_id = H5Dcreate(file_id, fieldname, compoundtype, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the data
    H5Dwrite(dataset_id, compoundtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, customer);

    // Release resources
    H5Sclose(dataspace_id);
    H5Tclose(stringtype);
    H5Tclose(inttype);
    H5Tclose(floattype);
    H5Tclose(array_type);
    H5Tclose(compoundtype);
    H5Dclose(dataset_id);
    H5Fclose(file_id);
}

struct customer* readCompound(const char* filename, const char* fieldname)
{
    // Open file for reading
    hid_t file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);

    // Open the dataset
    hid_t dataset_id = H5Dopen(file_id, fieldname, H5P_DEFAULT);

    // Get the datatype
    hid_t datatype = H5Dget_type(dataset_id);

    // Get the dataspace
    hid_t dataspace = H5Dget_space(dataset_id);

    // Get the number of dimensions
    int ndims = H5Sget_simple_extent_ndims(dataspace);

    // Get the dimensions
    hsize_t dims[ndims];
    H5Sget_simple_extent_dims(dataspace, dims, NULL);

    // Get the size of the datatype
    size_t type_size = H5Tget_size(datatype);

    // Allocate space for the compound type
    struct customer* customer = malloc(dims[0] * type_size);

    // Read the data
    H5Dread(dataset_id, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, customer);

    // Release resources
    H5Dclose(dataset_id);
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Fclose(file_id);

    return customer;
}





int main()
{
    writeString("h5example_string.h5", "string", "Hello, World!");

    char* string = readString("h5example_string.h5", "string");

    printf("%s\n", string);

    free(string);

    struct customer customer;
    customer.name = "John Smith";
    customer.age = 42;
    customer.height = 1.8;
    for (int i = 0; i < 200; i++)
        customer.id[i] = rand() / (float)RAND_MAX;

    writeCompound("h5example_compound.h5", "customer", &customer);

    struct customer* customer2 = readCompound("h5example_compound.h5", "customer");

    printf("Name: %s\n", customer2->name);
    printf("Age: %d\n", customer2->age);
    printf("Height: %f\n", customer2->height);
    printf("ID:");
    for (int i = 0; i < 200; i++)
        printf(" %f", customer2->id[i]);
    printf("\n");

    free(customer2);

    return 0;
}

