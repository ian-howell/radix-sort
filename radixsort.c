#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int data;
    struct node *next;
} queue;

int select_digit(int num, int pos);

void counting_sort(int a[], int size, int base, int d);

void radix_sort(int a[], int size, int base, int word_length);

struct node *create_node(int x);
void enqueue(struct node **q, int x);
int dequeue(struct node **q);
int is_empty(struct node *q);
void print_queue(struct node *q);

const int WORD_LEN = 5;
const int SIZE = 20;

int main()
{
    srand(5);

    int a[SIZE];
    int i = 0;
    for(i = 0; i < SIZE; i++)
    {
        a[i] = (rand() % (int)pow(10, WORD_LEN));
    }

    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    radix_sort(a, SIZE, 10, WORD_LEN);

    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

int select_digit(int num, int pos)
{
    return (num / (int)pow(10, pos)) % 10;
}

/* Counting Sort
 *
 * Sort an array of integers
 *
 * Param a: the array to sort
 * Type: int[]
 * Param SIZE: the number of elements in a
 * Type: const int
 * Param k: the number of unique numbers in a
 * Type: int
 * Param d: the place value of the digit to sort on. Used in radix sort
 * Type: int
 */
void counting_sort(int a[], const int SIZE, int k, int d)
{
    queue *bucket[SIZE];

    int i;
    for(i = 0; i < k; i++)
    {
        bucket[i] = NULL;
    }

    for (i = 0; i < SIZE; i++)
    {
        enqueue(&bucket[select_digit(a[i], d)], a[i]);
    }

    int j = 0;
    for (i = 0; i < k; i++)
    {
        while (!is_empty(bucket[i]))
        {
            a[j] = dequeue(&bucket[i]);
            j++;
        }
    }

    return;
}

void radix_sort(int a[], int size, int base, int word_length)
{
    int i;
    for (i = 0; i < word_length; i++)
    {
        counting_sort(a, size, base, i);
    }
}

struct node *create_node(int x)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = x;
    new_node->next = new_node;
    return new_node;
}

void enqueue(struct node **q, int x)
{
    struct node *new_node = create_node(x);
    if (*q != NULL && (*q)->next == (*q)->next->next)
    {
        new_node->next = *q;
        (*q)->next = new_node;
        *q = new_node;
    }
    else if (*q != NULL)
    {
        struct node *tmp = (*q)->next;
        (*q)->next = new_node;
        new_node->next = tmp;
        *q = new_node;
    }
    *q = new_node;
    return;
}

int dequeue(struct node **q)
{
    if (*q == NULL)
    {
        return -1;
    }
    else if ((*q)->next == (*q)->next->next)
    {
        int ret_val = (*q)->data;
        free(*q);
        *q = NULL;
        return ret_val;
    }
    else
    {
        int ret_val = (*q)->next->data;
        struct node *tmp = (*q)->next;
        (*q)->next = (*q)->next->next;
        free(tmp);
        return ret_val;
    }
}

int is_empty(struct node *q)
{
    return q == NULL;
}

void print_queue(struct node *q)
{
    struct node *r = q;
    if (r != NULL)
    {
        do
        {
            r = r->next;
            printf("%d -> ", r->data);
        } while (r != q);
        printf("\n");
    }
    else
    {
        printf("The queue is empty\n");
    }
}

