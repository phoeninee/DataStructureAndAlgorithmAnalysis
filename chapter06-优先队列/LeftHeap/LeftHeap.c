#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LeftHeap.h"

#define MinData     -1
#define MinPQSize   7
#define Error(Message) fprintf(stderr, "%s\n", Message)

struct TreeNode {
    ElementType   Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int           Npl;
};

PriorityQueue Initialize(void)
{
    return NULL;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
    PriorityQueue TmpH;

    if (H1->Left == NULL)   // Single node
        H1->Left = H2;      // H1->Right is already NULL, H1->Npl is already 0
    else {
        H1->Right = Merge(H1->Right, H2);
        if (H1->Left->Npl < H1->Right->Npl) {
            TmpH = H1->Left;
            H1->Left = H1->Right;
            H1->Right = TmpH;
        }

        H1->Npl = H1->Right->Npl + 1;
    }
    return H1;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
    if (H1 == NULL)
        return H2;
    if (H2 == NULL)
        return H1;
    if (H1->Element < H2->Element)
        return Merge1(H1, H2);
    else
        return Merge1(H2, H1);
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
    PriorityQueue SingleNode;

    SingleNode = malloc(sizeof(struct TreeNode));
    if (SingleNode == NULL)
        Error("Out of space");
    else {
        SingleNode->Element = X; SingleNode->Npl = 0;
        SingleNode->Left = SingleNode->Right = NULL;
        H = Merge(SingleNode, H);
    }
    return H;
}

PriorityQueue DeleteMin1(PriorityQueue H)
{
    PriorityQueue LeftHeap, RightHeap;

    if (IsEmpty(H)) {
        Error("Priority queue is empty");
        return H;
    }

    LeftHeap = H->Left;
    RightHeap = H->Right;
    free(H);
    return Merge(LeftHeap, RightHeap);
}

ElementType FindMin(PriorityQueue H)
{
    if (IsEmpty(H))
        Error("Priority queue is empty");
    else
        return H->Element;
}

int IsEmpty(PriorityQueue H)
{
    return H == NULL;
}

static void PrintLeftHeap1(PriorityQueue H)
{
    if (!IsEmpty(H)) {
        putchar('(');
        printf("%d ", H->Element);
        PrintLeftHeap1(H->Left);
        putchar(' ');
        PrintLeftHeap1(H->Right);
        putchar(')');
    } else
        printf(".");
}

void PrintLeftHeap(PriorityQueue H)
{
    if (IsEmpty(H))
        printf("()\n");
    else {
        PrintLeftHeap1(H);
        putchar('\n');
    }
}
