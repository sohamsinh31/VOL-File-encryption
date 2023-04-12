#include "vol.h"

int main(int argc, char const *argv[])
{
    char *files[64], *output,*decrypt;
    int k = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
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
            decrypt = (char *)malloc(sizeof(char) * strlen(argv[i + 1]) + 1);
            strcat(decrypt, argv[i + 1]);
        }
    }
    for (int i = 0; i < k; i++)
    {
        printf("\n%s", files[i]);
    }
    printf("\n%s", output);
    return 0;
}
