#ifndef VOL_H_INCLUDED
#define VOL_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

#endif // VOL_H_INCLUDED
