#ifndef VOL_H_INCLUDED
#define VOL_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "python3.10/Python.h"
#include <unistd.h> // For unlink()

// Maximum files to encrypt at a time
#define MAX_FILE_SIZE 64

// MetaData structures
typedef struct
{
    int file_numbers;                   // File numbers that is encrypted by User
    int files_positions[MAX_FILE_SIZE]; // Positions of each files
    char *file_names[MAX_FILE_SIZE];    // File names that encrypted
} vol_str;

int encrypt_files(int n);
int decrypt_files();
int encrypt_data(char *filenames[],char *output_filename, int n);
int decrypt_data(char *input_filename);
void exec_main(int argc, char *argv[]);
void print_exec_info(char *exec_name);
int compress_file(char *file_name);
void init_gui();


#endif // VOL_H_INCLUDED
