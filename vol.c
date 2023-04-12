// The MIT License (MIT)

// Copyright (c) 2023 VOLVET India

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

int encrypt_data(char *filenames[],char *output_filename,int n)
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

int decrypt_files(char *input_filename)
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
