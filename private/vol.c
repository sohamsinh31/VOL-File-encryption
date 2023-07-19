// <------------------------------------------VERSION 1.0 ----------------------------------------------------->
// FUNCTIONALITIES OF VERSION 1.0 OF VOL FILE ENCRYPTION:--
// 1.It supports upto 64 files at a time to be encrypted at once.
// 2.End to end decryption and usabilty for user.
// 3.Portability,machine independent and all operating system support.
// 4.Custom file encryption algorithem and user-freindly.

// The MIT License (MIT)

// Copyright (c) 2023 VOLVET LLP

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/* code */
#include "vol.h"

int encrypt_files(int n)
{
    vol_str v1;
    char vol_file[MAX_FILE_SIZE];
    int c;

    // Open input files
    FILE *fp[n];
    for (int i = 0; i < n; i++)
    {
        char temp[MAX_FILE_SIZE];
        printf("Enter filename of file %d: ", i + 1);
        scanf("%s", temp);
        v1.file_names[i] = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(v1.file_names[i], temp);
        fp[i] = fopen(temp, "rb");
        if (fp[i] == NULL)
        {
            printf("\nError while opening file %s! Make sure it exists.\n", temp);
            exit(1);
        }
        fseek(fp[i], 0L, SEEK_END);
        long int res = ftell(fp[i]);
        v1.files_positions[i] = res;
        fseek(fp[i], 0L, SEEK_SET);
    }

    // Open output file
    printf("Enter the filename to output: ");
    scanf("%s", vol_file);
    FILE *fp2 = fopen(vol_file, "wb");
    if (fp2 == NULL)
    {
        printf("Error while opening file %s for writing!\n", vol_file);
        exit(1);
    }
    v1.file_numbers = n;
    fwrite(&v1, sizeof(vol_str), 1, fp2);

    // Write file_names array to output file
    for (int i = 0; i < n; i++)
    {
        int len = strlen(v1.file_names[i]);
        fwrite(&len, sizeof(int), 1, fp2);
        fwrite(v1.file_names[i], sizeof(char), len, fp2);
    }

    // Write input files to output file
    for (int i = 0; i < n; i++)
    {
        while ((c = fgetc(fp[i])) != EOF)
        {
            fputc(c, fp2);
        }
        fclose(fp[i]);
    }
    fclose(fp2);

    printf("\nFiles successfully combined into %s.\n", vol_file);

    return 0;
}

int encrypt_data(char *filenames[], char *output_filename, int n)
{
    vol_str v1;
    int c;

    // Open input files
    FILE *fp[n];
    for (int i = 0; i < n; i++)
    {
        fp[i] = fopen(filenames[i], "rb");
        if (fp[i] == NULL)
        {
            printf("\nError while opening file %s! Make sure it exists.\n", filenames[i]);
            exit(1);
        }
        fseek(fp[i], 0L, SEEK_END);
        long int res = ftell(fp[i]);
        v1.files_positions[i] = res;
        fseek(fp[i], 0L, SEEK_SET);

        // Copy file name to v1.file_names array
        int name_len = strlen(filenames[i]);
        v1.file_names[i] = (char *)malloc(name_len + 1);
        strcpy(v1.file_names[i], filenames[i]);
    }

    // Open output file
    FILE *fp2 = fopen(output_filename, "wb");
    if (fp2 == NULL)
    {
        printf("Error while opening file %s for writing!\n", output_filename);
        exit(1);
    }
    v1.file_numbers = n;
    fwrite(&v1, sizeof(vol_str), 1, fp2);

    // Write file_names array to output file
    for (int i = 0; i < n; i++)
    {
        int len = strlen(v1.file_names[i]);
        fwrite(&len, sizeof(int), 1, fp2);
        fwrite(v1.file_names[i], sizeof(char), len, fp2);
    }

    // Write input files to output file
    for (int i = 0; i < n; i++)
    {
        while ((c = fgetc(fp[i])) != EOF)
        {
            fputc(c, fp2);
        }
        fclose(fp[i]);
    }
    fclose(fp2);

    printf("\nFiles successfully combined into %s.\n", output_filename);

    return 0;
}

int decrypt_files()
{
    vol_str v1;
    char vol_file[MAX_FILE_SIZE];
    int c;

    // Open input file
    printf("Enter the filename to decrypt: ");
    scanf("%s", vol_file);
    FILE *fp = fopen(vol_file, "rb");
    if (fp == NULL)
    {
        printf("\nError while opening file %s! Make sure it exists.\n", vol_file);
        exit(1);
    }
    fread(&v1, sizeof(vol_str), 1, fp);

    // Read file_names array from input file
    for (int i = 0; i < v1.file_numbers; i++)
    {
        int len;
        fread(&len, sizeof(int), 1, fp);
        v1.file_names[i] = (char *)malloc(sizeof(char) * (len + 1));
        fread(v1.file_names[i], sizeof(char), len, fp);
        v1.file_names[i][len] = '\0';
    }

    // Open output files and write decrypted data
    for (int i = 0; i < v1.file_numbers; i++)
    {
        FILE *out_fp = fopen(v1.file_names[i], "wb");
        if (out_fp == NULL)
        {
            printf("\nError while opening file %s for writing!\n", v1.file_names[i]);
            exit(1);
        }
        int size = v1.files_positions[i];
        for (int j = 0; j < size; j++)
        {
            c = fgetc(fp);
            fputc(c, out_fp);
        }
        fclose(out_fp);
    }
    fclose(fp);

    printf("\nFile successfully decrypted.\n");

    return 0;
}

int decrypt_data(char *input_filename)
{
    vol_str v1;
    int c;

    // Open input file
    FILE *fp = fopen(input_filename, "rb");
    if (fp == NULL)
    {
        printf("\nError while opening file %s! Make sure it exists.\n", input_filename);
        exit(1);
    }
    fread(&v1, sizeof(vol_str), 1, fp);

    // Read file_names array from input file
    for (int i = 0; i < v1.file_numbers; i++)
    {
        int len;
        fread(&len, sizeof(int), 1, fp);
        v1.file_names[i] = (char *)malloc(sizeof(char) * (len + 1));
        fread(v1.file_names[i], sizeof(char), len, fp);
        v1.file_names[i][len] = '\0';
    }

    // Open output files and write decrypted data
    for (int i = 0; i < v1.file_numbers; i++)
    {
        FILE *out_fp = fopen(v1.file_names[i], "wb");
        if (out_fp == NULL)
        {
            printf("\nError while opening file %s for writing!\n", v1.file_names[i]);
            exit(1);
        }
        int size = v1.files_positions[i];
        for (int j = 0; j < size; j++)
        {
            c = fgetc(fp);
            fputc(c, out_fp);
        }
        fclose(out_fp);
    }
    fclose(fp);

    printf("\nFile successfully decrypted.\n");

    return 0;
}

void print_exec_info(char *exec_name)
{
    printf("\n%s Usege:-\n-o:\tspecify output file name to store.\n-s\tspecify souces not more than %d to be encrypted.\n-d:\tspecify encrypted file to decompress.\n", exec_name, MAX_FILE_SIZE);
}

// FUNCTION TO IMPLEMENT MAIN BLOCK OF CODE:THIS FUNCTION IS TO TAKE INPUT AND RUN PROGRAM FROM TERMINAL
void exec_main(int argc, char *argv[])
{
    // DECLARATIONS
    char *files[64], *output, *decrypt;
    int to_encrypt = 0, to_decrypt = 0;
    int k = 0, n = 0;

    // PROGRAMMING LOGIC IS STARTED FROM HERE

    if (argc == 1)
    {
        print_exec_info(argv[0]);
    }

    if(argc >= MAX_FILE_SIZE)
    {
        printf("You reached maximum file limit");
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            to_encrypt = 1;
            for (int j = i + 1; j < argc; j++)
            {
                if (strcmp(argv[j], "-o") == 0 || strcmp(argv[j], "-p") == 0)
                {
                    break;
                }
                else
                {
                    files[k] = (char *)malloc(sizeof(char) * strlen(argv[j]) + 1);
                    strcat(files[k], argv[j]);
                    k++;
                    n++;
                }
            }
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            output = (char *)malloc(sizeof(char) * strlen(argv[i + 1]) + 1);
            strcat(output, argv[i + 1]);
        }
        if (strcmp(argv[i], "-d") == 0)
        {
            to_decrypt = 1;
            decrypt = (char *)malloc(sizeof(char) * strlen(argv[i + 1]) + 1);
            strcat(decrypt, argv[i + 1]);
        }
    }
    if (to_encrypt)
    {
        encrypt_data(files, output, n);
        compress_file(output);
    }
    if (to_decrypt)
    {
        decrypt_data(decrypt);
    }
}

/* Function to encrypt files with help of python */

int compress_file(char *file_name)
{
    Py_Initialize();

    // Create the Python code string with the input and output file names
    char pythonCode[256];
    snprintf(pythonCode, sizeof(pythonCode),
             "import gzip\n"
             "import shutil\n"
             "input_file = '%s'\n"
             "inp2 = input_file.split('.')[0]\n"
             "output_file = inp2 + '.vol'\n"
             "with open(input_file, 'rb') as f_in:\n"
             "    with gzip.open(output_file, 'wb') as f_out:\n"
             "        shutil.copyfileobj(f_in, f_out)\n",
             file_name);

    // Execute Python code to compress the file
    PyRun_SimpleString(pythonCode);

    Py_Finalize();

    // Delete the input file
    unlink(file_name);

    return 0;
}
