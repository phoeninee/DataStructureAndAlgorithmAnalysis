#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

struct TreeNode {
    ElementType Element;
    SearchTree  Left;
    SearchTree  Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

static Position NewNode(ElementType X, SearchTree left, SearchTree right)
{
    Position TmpCell;

    if ((TmpCell = malloc(sizeof(struct TreeNode))) == NULL)
        Error("NewNode: out of space");

    TmpCell->Element = X;
    TmpCell->Left = left;
    TmpCell->Right = right;
    return TmpCell;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Left);
    else if (X > T->Element)
        return Find(X, T->Right);
    else 
        return T;
}

Position FindMin(SearchTree T)
{
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;

    return T;
}

Position FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;

    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL)
        /* Create and return a one-node tree */
        T = NewNode(X, NULL, NULL);
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* else X is in the tree already; we'll do nothing */

    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;

    if (T == NULL)
        Error("Element not found");
    else if (X < T->Element)
        T->Left = Delete(X, T->Left);
    else if (X > T->Element)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right) {
        /*Replace with smallest in right subtree */
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    } else {
        TmpCell = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    
    return T;
}

void Error(char *Message)
{
    fprintf(stderr, "%s\n", Message);
    // exit(1);
}