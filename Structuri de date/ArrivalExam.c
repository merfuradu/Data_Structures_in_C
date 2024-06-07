#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 255

// Implement a C application for managing all the arrivais in a train station. For this, you can use
// a Binary Search Tree structure (BST). The tree node useful information is composed of a pointer to
// structure Amrival, which contains the following attributes: train code (char"), coming from (char*),
// arrival time (char" - HH.MM). delay (unsigned short - expressed in minutes1, no. of passengers (unsgned short).
// The application must implement the following functionalities:
// 1. Create a Binary Search Tree having as key the attribute arrival time. The tree must have at
// least 7 entries that are read from a Bie. (1 p)
// 2. Print all trains in the reversed order of their arrival time. (0.5p)
// 3. Write the function that retums the arrival that is the last one to come in the train station.
// The value is returned in the main() section and al the details of that arrival are displayed at the console. (1 p)
// 4. Write the function that counts how many arrivals have a delay. The value is returned in the
// main section and displayed at the conscie. (1 p)
// 5. Write the function that calculates the total number of passengers for the arrivals coming from a given
// value passed as a parameter. The value is retumed in the main section and displayed at the console. (1 p)
// 6. Write the function that searches for an arrival based on the arrival time. The function returns the
// pointer to the node that contains the arrival. If the arrival is not found, the function returns NULL. (1 p)
// 7. Write the function that saves all the arrivals starting from the root of the tree all the way to a given
// node (given as a parameter by is arrival time) in an array of pointers to be displayed
// (the array doesn't share memory space with the BST implementation).
// (1.5 р)
// This is mandatory:
// Functions that are not tested in the main() function are not considered for evaluation, All implementations must be caled in the main() function!

typedef struct BSTNode
{
    struct BSTNode *left;
    struct Arrival *info;
    struct BSTNode *right;
} BSTNode;

typedef struct Arrival
{
    char *train_code;
    char *coming_from;
    char *arrival_time;
    unsigned short delay;
    unsigned short no_of_passangers;
} Arrival;

BSTNode *createNode(Arrival *ar)
{
    BSTNode *root = (BSTNode *)malloc(sizeof(BSTNode));
    root->left = NULL;
    root->info = ar;
    root->right = NULL;
    return root;
}

Arrival *createArrival(char *code, char *from, char *arr_time,
                       unsigned short delay, unsigned short pass)
{
    Arrival *node = (Arrival *)malloc(sizeof(Arrival));
    if (node == NULL)
    {
        perror("Memory allocation failed\n");
        exit(1);
    }
    node->train_code = (char *)malloc(strlen(code) + 1);
    strcpy(node->train_code, code);
    node->coming_from = (char *)malloc(strlen(from) + 1);
    strcpy(node->coming_from, from);
    node->arrival_time = (char *)malloc(strlen(arr_time) + 1);
    strcpy(node->arrival_time, arr_time);
    node->delay = delay;
    node->no_of_passangers = pass;
    return node;
}

void insert(BSTNode **root, Arrival *ar)
{
    if (*root == NULL)
        *root = createNode(ar);
    else
    {
        if (strcmp((*root)->info->arrival_time, ar->arrival_time) > 0)
            insert(&(*root)->left, ar);
        else if (strcmp((*root)->info->arrival_time, ar->arrival_time) < 0)
            insert(&(*root)->right, ar);
    }
}

void printArrivals(BSTNode *root)
{
    if (root != NULL)
    {
        printArrivals(root->right);
        printf("The train %s arrived at the time %s\n", root->info->train_code, root->info->arrival_time);
        printArrivals(root->left);
    }
}

Arrival *printLastArrival(BSTNode *root)
{
    if (root != NULL)
    {
        while (root->right)
            root = root->right;

        return root->info;
    }
    else
    {
        return NULL;
    }
}

unsigned char delayed_trains(BSTNode *root)
{
    if (root != NULL)
    {
        if (root->info->delay > 0)
        {
            return 1 + delayed_trains(root->left) + delayed_trains(root->right);
        }
        else
            return delayed_trains(root->left) + delayed_trains(root->right);
    }
    else
        return 0;
}

int total_pass_from_city(BSTNode *root, char *from)
{
    if (root != NULL)
    {
        if (from)
        {
            if (strcmp(root->info->coming_from, from) == 0)
                return (int)root->info->no_of_passangers + (int)total_pass_from_city(root->left, from) + (int)total_pass_from_city(root->right, from);
            else
                return (int)total_pass_from_city(root->left, from) + (int)total_pass_from_city(root->right, from);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

BSTNode *search_by_arrival_time(BSTNode *root, char *arr_time)
{
    if (root != NULL)
    {
        if (strcmp(root->info->arrival_time, arr_time) == 0)
        {
            return root;
        }
        else
        {
            if (strcmp(root->info->arrival_time, arr_time) < 0)
                return search_by_arrival_time(root->right, arr_time);
            else
                return search_by_arrival_time(root->left, arr_time);
        }
    }
}

void array_of_arrivals(BSTNode *root, char *target_arrival_time, BSTNode **pathArray, int *index)
{
    if (root == NULL)
        return;

    pathArray[(*index)++] = root; // Add current node to array and increment index

    if (strcmp(root->info->arrival_time, target_arrival_time) == 0)
        return; // Stop if target is found

    if (strcmp(root->info->arrival_time, target_arrival_time) < 0)
    {
        array_of_arrivals(root->right, target_arrival_time, pathArray, index);
    }
    else
    {
        array_of_arrivals(root->left, target_arrival_time, pathArray, index);
    }
}

void delete_tree(BSTNode *root)
{
    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root->info->train_code);
        free(root->info->coming_from);
        free(root->info->arrival_time);
        free(root->info);
        free(root);
    }
}

int main()
{
    BSTNode *tree = NULL;
    FILE *pFile = fopen("BST.txt", "r");
    if (pFile)
    {
        char delimiter[] = ",";
        char *token = NULL;
        unsigned short delay, no_of_passengers;
        char buffer[LINE_SIZE], code[LINE_SIZE], from[LINE_SIZE], time[LINE_SIZE];
        while (fgets(buffer, sizeof(buffer), pFile))
        {
            token = strtok(buffer, delimiter);
            strcpy(code, token);
            token = strtok(NULL, delimiter);
            strcpy(from, token);
            token = strtok(NULL, delimiter);
            strcpy(time, token);
            token = strtok(NULL, delimiter);
            delay = atoi(token);
            token = strtok(NULL, delimiter);
            no_of_passengers = atoi(token);
            Arrival *ar = createArrival(code, from, time, delay, no_of_passengers);
            insert(&tree, ar);
        }
        printArrivals(tree);
        Arrival *lastTrain = printLastArrival(tree);
        printf("The last train arrived at %s\n ", lastTrain->arrival_time);
        unsigned char delayed = delayed_trains(tree);
        printf("The number of delayed trains is %u\n ", delayed);
        int total_passengers = total_pass_from_city(tree, "Constanta");
        printf("The number of passengers from constanta is %d\n", total_passengers);
        int noPass = 0;
        BSTNode *search = search_by_arrival_time(tree, "13:06");
        if (search != NULL && search->info != NULL)
            printf("We found the train %s, it arrived at %s and came from %s\n", search->info->train_code, search->info->arrival_time, search->info->coming_from);
        else
            printf("The train was not found\n");

        int index = 0;
        int estimatedMaxPath = 10;
        BSTNode **pathArray = malloc(sizeof(BSTNode *) * estimatedMaxPath);
        if (!pathArray)
        {
            perror("Failed to allocate memory for pathArray");
            return EXIT_FAILURE;
        }
        array_of_arrivals(tree, "22:06", pathArray, &index);
        for (int i = 0; i < index; i++)
        {
            printf("Node %d Arrival Time: %s\n", i, pathArray[i]->info->arrival_time);
        }
        free(pathArray);

        delete_tree(tree);
        fclose(pFile);

        return 0;
    }
}