#include "Structs.h"

#define HASH_TABLE_SIZE 100

Node *insert_begining(Node *list, BankAccount ba)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = ba;
    newNode->next = list;

    return newNode;
}

unsigned char hash_function(char *key, unsigned char ht_size)
{
    unsigned char sum;
    for (unsigned char i = (char)(strlen(key) - 1); i > (char)(strlen(key) - 5) && i > 0; i--)
    {
        sum += key[i];
    }
    return sum % ht_size;
}

void insert_ba_hash_table(Node **HT, unsigned char ht_size, BankAccount ba_data)
{
    unsigned char offset = hash_function(ba_data.owner_name, ht_size);
    printf("The key %s is inserted into list #%d\n ", ba_data.owner_name, (int)offset);
    HT[offset] = insert_begining(HT[offset], ba_data);
}

Node *search_first_ba(Node **HT, unsigned char ht_size, char *name)
{
    unsigned char offset = hash_function(name, ht_size);

    Node *temp = HT[offset];
    while (temp)
    {
        if (strcmp(name, temp->data.owner_name) == 0)
            return temp;
        temp = temp->next;
    }
    return temp;
}

BankAccount **search_all_ba(Node **HT, unsigned char ht_size, char *searching_name, unsigned char *array_size)
{
    unsigned char offset = hash_function(searching_name, ht_size);
    *array_size = 0;
    Node *temp = HT[offset];

    while (temp)
    {
        if (strcmp(searching_name, temp->data.owner_name) == 0)
        {
            (*array_size)++;
        }
        temp = temp->next;
    }

    BankAccount **out_array = NULL;

    if (*array_size != 0)
    {
        out_array = (BankAccount **)malloc(sizeof(BankAccount *) * *array_size);

        unsigned char i = 0;
        Node *temp = HT[offset];
        while (temp)
        {
            if (strcmp(searching_name, temp->data.owner_name) == 0)
            {
                out_array[i] = &temp->data;
                i++;
            }
            temp = temp->next;
        }
    }
    return out_array;
}

int main()
{
    FILE *f = fopen("Accounts.txt", "r");
    char buffer[256];
    Node **HTable = (Node **)malloc(HASH_TABLE_SIZE * sizeof(Node *));
    for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
        HTable[i] = NULL;

    while (fgets(buffer, sizeof(buffer), f) != NULL)
    {
        BankAccount ba;
        strncpy(ba.iban, buffer, strlen(buffer) - 1);
        ba.iban[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        ba.owner_name = (char *)malloc(strlen(buffer) + 1);
        strncpy(ba.owner_name, buffer, strlen(buffer) - 1);
        ba.owner_name[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), f);
        ba.balance = atof(buffer);

        fgets(buffer, sizeof(buffer), f);
        ba.currency = (char *)malloc(strlen(buffer) + 1);
        strncpy(ba.currency, buffer, strlen(buffer) - 1);
        ba.currency[strlen(buffer) - 1] = 0;

        insert_ba_hash_table(HTable, HASH_TABLE_SIZE, ba);
    }

    // search a name in the table
    Node *temp = search_first_ba(HTable, HASH_TABLE_SIZE, "Vasilescu Miruna");
    if (temp)
    {
        printf("The account of the owner %s was found", temp->data.owner_name);
    }

    // Searching for more accounts in the table
    unsigned char size_all_ba;
    BankAccount **array_all_ba = search_all_ba(HTable, HASH_TABLE_SIZE, "Vasilescu Miruna", &size_all_ba);
    printf("\nSeaching for bank accounts\n");
    if (array_all_ba != NULL)
    {
        for (unsigned char i = 0; i < size_all_ba; i++)
        {
            printf("Bank account %s %s\n", array_all_ba[i]->iban, array_all_ba[i]->owner_name);
        }
    }
    else
    {
        printf("There were no bank accounts with this name sir\n");
    }

    fclose(f);

    return 0;
}