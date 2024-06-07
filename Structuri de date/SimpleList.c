#include "structs.h"

Node *insert_beggining(Node *head, BankAccount ba)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = ba;
    newNode->next = head;
    return newNode;
}

int main()
{
    FILE *f = fopen("Accounts.txt", "r");
    char buffer[256];
    Node *head = NULL;

    while (fgets(buffer, sizeof(buffer), f))
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
        ba.currency = malloc(strlen(buffer) + 1);
        strncpy(ba.currency, buffer, strlen(buffer) - 1);
        ba.currency[strlen(buffer) - 1] = 0;

        head = insert_beggining(head, ba);
    }

    printf("\nList after creation");
    Node *temp = head;
    while (temp->next != NULL)
    {
        printf("\n%s %s", temp->data.iban, temp->data.owner_name);
        temp = temp->next;
    }

    while (head)
    {
        temp = head;       // temp is the actual 1st node in the list
        head = head->next; // head moved to the 2nd node in the list

        free(temp->data.owner_name);
        free(temp->data.currency);
        free(temp);
    }
}