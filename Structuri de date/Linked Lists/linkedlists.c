#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

struct doublenode
{
    int data;
    struct doublenode *prev;
    struct doublenode *next;
};

struct doublenode *addToEmpty(int data)
{
    struct doublenode *temp = malloc(sizeof(struct doublenode));
    temp->next = NULL;
    temp->data = data;
    temp->prev = NULL;
    return temp;
}

struct doublenode *add_at_end_double(struct doublenode *head, int data)
{
    struct doublenode *new_node = malloc(sizeof(struct doublenode));
    new_node->data = data;
    new_node->next = NULL;

    if (head == NULL)
    {
        printf("The list was empty");
        new_node->prev = NULL;
        head = new_node;
        printf("\n%d added to the list", new_node->data);
        return head;
    }
    struct doublenode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current;
    printf("\n%d added at end of double list", new_node->data);
    return head;
}

struct doublenode *add_after_pos_double(struct doublenode *head, int data, int pos)
{
    struct doublenode *newP = addToEmpty(data);
    struct doublenode *temp = head;

    while (pos > 1)
    {
        temp = temp->next;
        pos--;
    }
    if (temp->next == NULL)
    {
        head = add_at_end_double(head, data);
        return head;
    }
    struct doublenode *temp2 = temp->next;
    temp->next = newP;
    temp2->prev = newP;
    newP->next = temp2;
    newP->prev = temp;
    return head;
}

void create_new_node(struct node *head, int data)
{
    struct node *ptr = NULL;
    if (head == NULL)
        printf("Linked list is empty");
    ptr = head;
    while (ptr->link != NULL)
    {
        ptr = ptr->link;
    }
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
    ptr->link = new_node;
    new_node->data = data;
    new_node->link = NULL;

    printf("\n%d ", new_node->data);
    printf("-new node created succesfully");
};

struct node *add_at_end(struct node *ptr, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = NULL;
    ptr->link = new_node;
    return new_node;
}

void add_at_pos(struct node *head, int data, int pos)
{
    struct node *ptr = head;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = NULL;
    pos--;

    while (pos < 1)
    {
        ptr = ptr->link;
        pos--;
    }
    new_node->link = ptr->link;
    ptr->link = new_node;
}

struct node *add_at_beg(struct node *head, int data)
{
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = head;
    head = new_node;
    printf("\n%d ", head->data);
    printf(" - new node added to the beggining");
    return head;
}

struct node *del_first(struct node *head)
{
    if (head == NULL)
    {
        printf("The list is already empty, we ll delete the head too");
        return NULL;
    }
    struct node *temp = head;
    head = head->link;
    free(temp);
    temp = NULL;
    printf("\nFirst node deleted succesfully");
    return head;
}

void del_last(struct node *head)
{
    if (head == NULL)
    {
        printf("The list is already empty");
    }
    struct node *ptr = head;
    struct node *ptr2 = head;

    while (ptr->link != NULL)
    {
        ptr2 = ptr;
        ptr = ptr->link;
    }
    ptr2->link = NULL;
    free(ptr);
    ptr = NULL;
}

void del_at_pos(struct node **head, int pos)
{
    int poscopy = pos;
    struct node *previous = *head;
    struct node *current = *head;
    if (*head == NULL)
    {
        printf("The list is already empty");
    }
    else if (pos == 1)
    {
        *head = current->link;
        free(current);
        current = NULL;
    }
    else
    {
        while (pos > 1)
        {
            previous = current;
            current = current->link;
            pos--;
        }
        previous->link = current->link;
        free(current);
        current = NULL;
        printf("\nThe element at pos %d was deleted succesfully", poscopy);
    }
}

struct node *del_list(struct node *head)
{
    while (head != NULL)
    {
        head = del_first(head);
    }
    printf("\nThe list have been succesfully deleted");
    return head;
}

struct node *reverse_list(struct node *head)
{
    struct node *prev = NULL, *next = NULL;
    while (head != NULL)
    {
        next = head->link;
        head->link = prev;
        prev = head;
        head = next;
    }
    head = prev;
    return head;
}

void print_list(struct node *head)
{
    struct node *ptr = NULL;
    if (head == NULL)
    {
        printf("\nThe linked list is empty");
    }
    else
    {
        printf("\nHere is the list:");
        ptr = head;
        while (ptr != NULL)
        {
            printf("\n%d ", ptr->data);
            ptr = ptr->link;
        }
    }
}

void print_double_list(struct doublenode *head)
{
    struct doublenode *node = NULL;
    if (head == NULL)
    {
        printf("The list is fkin empty, what to print ni**a?");
    }
    else
    {
        printf("\nHere is the double list:");
        node = head;
        while (node != NULL)
        {
            printf("\n%d", node->data);
            node = node->next;
        }
    }
}

int main()
{
    // struct node *head;
    // head = (struct node *)malloc(sizeof(struct node));
    // head->data = 23;
    // head->link = NULL;
    // printf("%d", head->data);

    int data = 46;
    struct doublenode *headd = addToEmpty(data);
    headd = add_at_end_double(headd, 47);
    headd = add_after_pos_double(headd, 22, 2);
    print_double_list(headd);

    // create_new_node(head, 24);
    // create_new_node(head, 25);
    // head = add_at_beg(head, 21);
    // add_at_pos(head, 22, 2);
    // print_list(head);
    // head = reverse_list(head);
    // print_list(head);
}