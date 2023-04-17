#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 4

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct DoublyLinkedList
{
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;

// Initialize an empty doubly linked list
void initializeList(DoublyLinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Add a new node with the given data to the front of the list
void addFront(DoublyLinkedList *list, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->head;
    if (list->head != NULL)
    {
        list->head->prev = newNode;
    }
    else
    {
        list->tail = newNode;
    }
    list->head = newNode;
    list->size++;
}

// Move the given node to the front of the list
void moveToHead(DoublyLinkedList *list, Node *node)
{
    if (node == list->head)
    {
        return;
    }
    if (node == list->tail)
    {
        list->tail = node->prev;
        list->tail->next = NULL;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

// Remove the node at the end of the list and return its data
int removeEnd(DoublyLinkedList *list)
{
    int data = list->tail->data;
    Node *temp = list->tail;
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    free(temp);
    list->size--;
    return data;
}

// Check if the given value is in the list and move it to the front if found
int findAndMove(DoublyLinkedList *list, int value)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->data == value)
        {
            moveToHead(list, current);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Print the contents of the list
void printList(DoublyLinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// LRU page replacement algorithm using a doubly linked list
int lruPageReplacement(int pageReferences[], int numReferences)
{
    DoublyLinkedList list;
    initializeList(&list);
    int i, pageFaults = 0;
    for (i = 0; i < numReferences; i++)
    {
        if (!findAndMove(&list, pageReferences[i]))
        {
            if (list.size == FRAME_SIZE)
            {
                removeEnd(&list);
            }
            addFront(&list, pageReferences[i]);
            pageFaults++;
        }
        printList(&list);
    }
    return pageFaults;
}

// Second chance page replacement algorithm
int secondChancePageReplacement(int pageReferences[], int numReferences)
{
    int i, pageFaults = 0;
    int pageTable[FRAME_SIZE];
    int referenceBit[FRAME_SIZE];
    int currentIndex = 0;
    for (i = 0; i < FRAME_SIZE; i++)
    {
        pageTable[i] = -1;
        referenceBit[i] = 0;
    }
    for (i = 0; i < numReferences; i++)
    {
        int j, pageFound = 0;
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (pageTable[j] == pageReferences[i])
            {
                referenceBit[j] = 1;
                pageFound = 1;
                break;
            }
        }
        if (!pageFound)
        {
            while (referenceBit[currentIndex] == 1)
            {
                referenceBit[currentIndex] = 0;
                currentIndex = (currentIndex + 1) % FRAME_SIZE;
            }
            if (pageTable[currentIndex] != -1)
            {
                printf("Page %d replaced by %d\n", pageTable[currentIndex], pageReferences[i]);
            }
            else
            {
                printf("Page replaced by %d\n", pageReferences[i]);
            }
            pageTable[currentIndex] = pageReferences[i];
            referenceBit[currentIndex] = 1;
            currentIndex = (currentIndex + 1) % FRAME_SIZE;
            pageFaults++;
        }
        printf("Page table: ");
        for (j = 0; j < FRAME_SIZE; j++)
        {
            printf("%d ", pageTable[j]);
        }
        printf("\n");
    }
    return pageFaults;
}

// LFU page replacement algorithm
int lfuPageReplacement(int pageReferences[], int numReferences)
{
    int i, pageFaults = 0;
    int pageTable[FRAME_SIZE];
    int frequency[FRAME_SIZE];
    int minFrequency = 0;
    for (i = 0; i < FRAME_SIZE; i++)
    {
        pageTable[i] = -1;
        frequency[i] = 0;
    }
    for (i = 0; i < numReferences; i++)
    {
        int j, pageFound = 0, minIndex = 0;
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (pageTable[j] == pageReferences[i])
            {
                frequency[j]++;
                pageFound = 1;
                break;
            }
            if (frequency[j] < frequency[minIndex])
            {
                minIndex = j;
            }
        }
        if (!pageFound)
        {
            if (frequency[minIndex] > 0)
            {
                printf("Page %d replaced by %d\n", pageTable[minIndex], pageReferences[i]);
            }
            else
            {
                printf("Page replaced by %d\n", pageReferences[i]);
            }
            pageTable[minIndex] = pageReferences[i];
            frequency[minIndex] = 1;
            pageFaults++;
        }
        printf("Page table: ");
        for (j = 0; j < FRAME_SIZE; j++)
        {
            printf("%d:%d ", pageTable[j], frequency[j]);
        }
        printf("\n");
    }
    return pageFaults;
}

// MFU page replacement algorithm
int mfuPageReplacement(int pageReferences[], int numReferences)
{
    int i, pageFaults = 0;
    int pageTable[FRAME_SIZE];
    int frequency[FRAME_SIZE];
    for (i = 0; i < FRAME_SIZE; i++)
    {
        pageTable[i] = -1;
        frequency[i] = 0;
    }
    for (i = 0; i < numReferences; i++)
    {
        int j, pageFound = 0, maxIndex = 0;
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (pageTable[j] == pageReferences[i])
            {
                frequency[j]++;
                pageFound = 1;
                break;
            }
            if (frequency[j] > frequency[maxIndex])
            {
                maxIndex = j;
            }
        }
        if (!pageFound)
        {
            if (frequency[maxIndex] > 0)
            {
                printf("Page %d replaced by %d\n", pageTable[maxIndex], pageReferences[i]);
            }
            else
            {
                printf("Page replaced by %d\n", pageReferences[i]);
            }
            pageTable[maxIndex] = pageReferences[i];
            frequency[maxIndex] = 1;
            pageFaults++;
        }
        printf("Page table: ");
        for (j = 0; j < FRAME_SIZE; j++)
        {
            printf("%d:%d ", pageTable[j], frequency[j]);
        }
        printf("\n");
    }
    return pageFaults;
}

int main()
{
    int pageReferences[20];
    int i;
    // srand(time(NULL));
    for (i = 0; i < 20; i++)
    {
        pageReferences[i] = rand() % 10;
    }
    printf("Page references: ");
    for (i = 0; i < 20; i++)
    {
        printf("%d ", pageReferences[i]);
    }
    printf("\n");
    printf("LRU page replacement algorithm\n");
    int lruFaults = lruPageReplacement(pageReferences, 15);
    printf("Number of page faults: %d\n\n", lruFaults);
    printf("Second chance page replacement algorithm\n");
    int secondChanceFaults = secondChancePageReplacement(pageReferences, 15);
    printf("Number of page faults: %d\n\n", secondChanceFaults);
    printf("LFU page replacement algorithm\n");
    int lfuFaults = lfuPageReplacement(pageReferences, 15);
    printf("Number of page faults: %d\n\n", lfuFaults);
    printf("MFU page replacement algorithm\n");
    int mfuFaults = mfuPageReplacement(pageReferences, 15);
    printf("Number of page faults: %d\n\n", mfuFaults);
    return 0;
}
