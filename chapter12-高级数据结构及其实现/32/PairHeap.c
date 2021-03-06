#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define OK       1
#define MaxSiblings 100
#define Infinity    1000000

struct PairNode;
typedef struct PairNode *PairHeap;
typedef struct PairNode *Position;

typedef int ElementType;
typedef unsigned short USHORT;

PairHeap Initialize(void);
PairHeap Insert(ElementType Item, PairHeap H, Position *Loc);
PairHeap DecreaseKey(Position P, ElementType Delta, PairHeap H);
PairHeap DeleteMin(ElementType *MinItem, PairHeap H);
void PrintPairHeap(PairHeap H);

void test_pairheap(void);
void print_help(void);
void process_args(char *first);
void process_input(void);
void process_error(void);

struct PairNode {
    ElementType Element;
    PairHeap    Prev;
    PairHeap    LeftChild;
    PairHeap    NextSibling;
};

static Position NullNode = NULL;
static void Error(char *Message);

PairHeap Initialize(void)
{
    if (NullNode == NULL) {
        NullNode = malloc(sizeof(struct PairNode));
        NullNode->Prev = NullNode;
        NullNode->LeftChild = NullNode->NextSibling = NullNode;
        NullNode->Element = Infinity;
    }
    return NullNode;
}

Position CompareAndLink(Position First, Position Second)
{
    if (First->Element <= Second->Element) {
        // attach second as the leftmost child of first
        Second->Prev = First;
        First->NextSibling = Second->NextSibling;
        First->NextSibling->Prev = First;
        Second->NextSibling = First->LeftChild;
        Second->NextSibling->Prev = Second;
        First->LeftChild = Second;
        return First;
    } else {
        // attach first as the leftmost child of second
        Second->Prev = First->Prev;
        First->Prev = Second;
        First->NextSibling = Second->LeftChild;
        First->NextSibling->Prev = First;
        Second->LeftChild = First;
        return Second;
    }
}

PairHeap Insert(ElementType Item, PairHeap H, Position *Loc)
{
    Position NewNode;

    NewNode = malloc(sizeof(struct PairNode));
    if (NewNode == NULL)
        Error("Out of space");
    NewNode->Element = Item;
    NewNode->LeftChild = NewNode->NextSibling = NewNode->Prev = NullNode;

    *Loc = NewNode;
    return CompareAndLink(H, NewNode);
}

PairHeap DecreaseKey(Position P, ElementType Delta, PairHeap H)
{
    if (Delta < 0)
        fprintf(stderr, "%s\n", "DecreaseKey called with negative Delta");

    P->Element -= Delta;
    if (P == H)
        return H;

    P->NextSibling->Prev = P->Prev;
    if (P->Prev->LeftChild == P)
        P->Prev->LeftChild = P->NextSibling;
    else
        P->Prev->NextSibling = P->NextSibling;

    P->NextSibling = NullNode;
    return CompareAndLink(H, P);
}

PairHeap CombineSiblings(Position FirstSibling)
{
    static Position TreeArray[MaxSiblings];
    int i, j, NumSiblings;
    
    if (FirstSibling->NextSibling == NullNode)
        return FirstSibling;

    for (NumSiblings = 0; FirstSibling != NullNode; NumSiblings++) {
        TreeArray[NumSiblings] = FirstSibling;
        FirstSibling->Prev->NextSibling = NullNode;
        FirstSibling = FirstSibling->NextSibling;
    }
    TreeArray[NumSiblings] = NullNode;

    // combine the subtrees two at a time going left to right
    for (i = 0; i + 1 < NumSiblings; i+=2)
        TreeArray[i] = CompareAndLink(TreeArray[i], TreeArray[i+1]);
    // j has the result of the last CompareAndLink
    // if an odd number of trees, get the last one
    j = i - 2;
    if (j == NumSiblings - 3)
        TreeArray[j] = CompareAndLink(TreeArray[j], TreeArray[j+2]);

    // now go right to left, merging last tree with next to last.
    // the result becomes the new last
    for ( ; j >= 2; j -= 2)
        TreeArray[j-2] = CompareAndLink(TreeArray[j-2], TreeArray[j]);

    return TreeArray[0];
}

PairHeap DeleteMin(ElementType *MinItem, PairHeap H)
{
    Position NewRoot = NullNode;

    if (H == NullNode)
        Error("Pairing heap is empty");
    else {
        *MinItem = H->Element;
        NewRoot = CombineSiblings(H->LeftChild);
        free(H);
    }
    return NewRoot;
}

void PrintPairHeap1(PairHeap H)
{
    if (H != NullNode) {
        printf("( %d ", H->Element);
        PrintPairHeap1(H->LeftChild);
        PrintPairHeap1(H->NextSibling);
        printf(")");
    } else
        printf("* ");
}

void PrintPairHeap(PairHeap H)
{
    if (H == NullNode)
        printf("(null)");
    else
        PrintPairHeap1(H);
    putchar('\n');
}

void Error(char *Message)
{
    fprintf(stderr, "%s\n", Message);
    exit(1);
}

void test_pairheap(void)
{
    int i, Min;
    PairHeap H, Loc;

    srand(time(NULL));
    H = Initialize();

    for (i = 0; i < 20; i++) {
        H = Insert(rand() % 200, H, &Loc);
    }

    PrintPairHeap(H);
    for (i = 0; i < 20; i++) {
        H = DeleteMin(&Min, H);
        printf("Delete %d...\n", Min);
    }
    PrintPairHeap(H);
}

/* for user interface */
void print_help(void)
{  
    puts("\nPairing heap implementation.\n");
    puts(" Pairing heap [/h]");
    puts(" Pairing heap [/i]");
    puts(" Pairing heap [/t]\n");
    puts("  /h\tdisplay help info");
    puts("  /i\tto input points");
    puts("  /t\ttest Pairing heap implementation");
}

void process_args(char *first)
{
    if (strcmp(first, "/h") == 0 || strcmp(first, "/?") == 0)
        print_help();
    else if (strcmp(first, "/t") == 0)
        test_pairheap();
    else if (strcmp(first, "/i") == 0)
        process_input();
    else
        process_error();
}

void process_input(void)
{

}

void process_error(void)
{
    fprintf(stderr, "%s\n", "Arguments Error\n");
    print_help();
}

int main(int argc, char *argv[])
{
    switch (argc) {
        case   1: print_help(); break;
        case   2: process_args(argv[1]); break;
        default : process_error();
    }
    return OK;
}