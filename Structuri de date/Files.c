#include "Structs.h"

int main()
{
    FILE *f = fopen("Accounts.txt", "r");
    char buffer[256];
    unsigned char ba_array_size = 0;
    BankAccount *ba_array = NULL;

    while (fgets(buffer, sizeof(buffer), f))
    {
        ba_array = realloc(ba_array, (ba_array_size + 1) * sizeof(BankAccount));

        strncpy(ba_array[ba_array_size].iban, buffer, strlen(buffer) - 1);
        ba_array[ba_array_size].iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        ba_array[ba_array_size].owner_name = (char *)malloc(strlen(buffer) + 1);
        strncpy(ba_array[ba_array_size].owner_name, buffer, strlen(buffer) - 1);
        ba_array[ba_array_size].owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        ba_array[ba_array_size].balance = atof(buffer);

        fgets(buffer, sizeof(buffer), f);
        ba_array[ba_array_size].currency = (char *)malloc(strlen(buffer) + 1);
        strncpy(ba_array[ba_array_size].currency, buffer, strlen(buffer) - 1);
        ba_array[ba_array_size].currency[strlen(buffer) - 1] = 0;

        ba_array_size++;
    }

    for (unsigned char i = 0; i < ba_array_size; i++)
    {
        printf("\n%s \n%s", ba_array[i].iban, ba_array[i].owner_name);
    }

    for (unsigned char i = 0; i < ba_array_size; i++)
    {
        free(ba_array[i].owner_name);
        free(ba_array[i].currency);
    }
    free(ba_array);
    ba_array = NULL;

    fclose(f);
    return 0;
}