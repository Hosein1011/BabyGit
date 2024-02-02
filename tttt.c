#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NumberOfKnights = 0;

struct Knight
{
    struct Knight *prev;
    int data;
    struct Knight *next;
};

struct Knight *CreateList(int n)
{
    struct Knight *currentKnight = NULL;
    struct Knight *head = NULL;

    for (int i = 0; i < n; i++)
    {
        struct Knight *newKnight = (struct Knight *)malloc(sizeof(struct Knight));
        newKnight->prev = NULL;
        newKnight->data = NumberOfKnights++;
        newKnight->next = NULL;

        if (head == NULL)
        {
            head = newKnight;
            currentKnight = newKnight;
        }
        else
        {
            currentKnight->next = newKnight;
            newKnight->prev = currentKnight;
            currentKnight = newKnight;
        }
    }

    return head;
}

struct Knight *AddNewKnight(struct Knight *currentKnight)
{
    struct Knight *newKnight = (struct Knight *)malloc(sizeof(struct Knight));
    newKnight->prev = currentKnight;
    newKnight->data = NumberOfKnights++;
    newKnight->next = currentKnight->next;

    if (currentKnight->next != NULL)
    {
        currentKnight->next->prev = newKnight;
    }

    currentKnight->next = newKnight;

    return newKnight;
}

struct Knight *RemoveCurrentKnight(struct Knight *currentKnight)
{
    struct Knight *prevKnight = currentKnight->prev;
    struct Knight *nextKnight = currentKnight->next;

    if (prevKnight != NULL)
    {
        prevKnight->next = nextKnight;
    }

    if (nextKnight != NULL)
    {
        nextKnight->prev = prevKnight;
    }

    if (currentKnight == prevKnight)
    {
        return nextKnight;
    }

    free(currentKnight);
    NumberOfKnights--;

    return prevKnight;
}

int KnightDirection(char order[100])
{
    char Direction;
    int move, result;
    sscanf(order, "%d%c", &move, &Direction);
    result = (Direction == 'F') ? move : -move;
    return result;
}

struct Knight *Move(int move, struct Knight *currentKnight)
{
    if (move > 0)
    {
        for (int i = 0; i < move; i++)
        {
            currentKnight = currentKnight->next;
        }
    }
    else
    {
        for (int i = 0; i < -move; i++)
        {
            currentKnight = currentKnight->prev;
        }
    }

    return currentKnight;
}

void printList(struct Knight *head)
{
    struct Knight *temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main()
{
    int n;
    struct Knight *currentKnight;
    char orders[100];
    scanf("%d", &n);
    scanf("%s", orders);
    struct Knight *head = CreateList(n);
    currentKnight = head;
    while (strcmp(orders, "END") != 0)
    {
        if (strcmp(orders, "REMOVE") == 0)
        {
            currentKnight = RemoveCurrentKnight(currentKnight);
            if (currentKnight != NULL)
            {
                printf("%d\n", currentKnight->data);
            }
        }
        else if (strcmp(orders, "ADD") == 0)
        {
            currentKnight = AddNewKnight(currentKnight);
            printf("%d\n", currentKnight->data);
        }
        else
        {
            int move = KnightDirection(orders);
            currentKnight = Move(move, currentKnight);
            if (currentKnight != NULL)
            {
                printf("%d\n", currentKnight->data);
            }
        }

        scanf("%s", orders); // Read the next order
    }

    // Uncomment the following line to print the list
    // printList(head);

    return 0;
}