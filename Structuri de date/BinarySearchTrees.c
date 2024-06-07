#include "Structs.h"

NodeBST *insert_ba_bst(NodeBST *root, BankAccount ba, char *insert_flag)
{
    if (root != NULL)
    {
        if (strcmp(root->data.iban, ba.iban) == 0)
        {
            *insert_flag = 0;
        }
        else
        {
            if (strcmp(root->data.iban, ba.iban) < 0)
            {
                root->left = insert_ba_bst(root->left, ba, insert_flag);
            }
            else
            {
                if (strcmp(root->data.iban, ba.iban) > 0)
                {
                    root->right = insert_ba_bst(root->right, ba, insert_flag);
                }
            }
        }
    }
    else
    {
        NodeBST *newNode = malloc(sizeof(NodeBST));
        newNode->data = ba;
        newNode->left = NULL;
        newNode->right = NULL;
        root = newNode;
        *insert_flag = 1;
    }
    return root;
}

void parse_ascending_keys(NodeBST *r)
{
    if (r != NULL)
    {
        parse_ascending_keys(r->left);
        printf("%s %s\n", r->data.iban, r->data.owner_name);
        parse_ascending_keys(r->right);
    }
}

NodeBST *deallocate_BST(NodeBST *r)
{
    if (r != NULL)
    {
        r->left = deallocate_BST(r->left);
        r->right = deallocate_BST(r->right);

        // we may dealocate the current node r because r->left and r->right were deallocate by above calls
        free(r->data.owner_name);
        free(r->data.currency);
        free(r);

        r = NULL;
    }

    return r;
}

BankAccount *search_BST_key(NodeBST *r, char *iban_key)
{
    if (r != NULL)
    {
        if (strcmp(r->data.iban, iban_key) == 0)
        {
            return &(r->data);
        }
        else
        {
            if (strcmp(r->data.iban, iban_key) < 0)
                return search_BST_key(r->left, iban_key);
            else
            {
                if (strcmp(r->data.iban, iban_key) > 0)
                    return search_BST_key(r->right, iban_key);
            }
        }
    }
    return NULL;
}
