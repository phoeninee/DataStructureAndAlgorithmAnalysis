struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode CircleList;
typedef PtrToNode Position;
typedef int ElementType;

CircleList MakeEmpty(CircleList CL);
Position NewNode(ElementType elt, Position next, Position previous);
int IsEmpty(Position P, CircleList CL);
int IsLast(Position P, CircleList CL);
Position Find(ElementType X, CircleList CL);
void Delete(ElementType X, CircleList CL);
void DeletePos(Position P, CircleList CL);
void Insert(ElementType X, CircleList CL, Position P);
void Transfer(Position P1, Position P2, CircleList CL1, CircleList CL2);
void DeleteCircleList(CircleList CL);
void PrintCircleList(CircleList CL);
Position First(CircleList CL);
Position Last(CircleList CL);
int Length(CircleList CL);
Position Next(Position P);
ElementType Retrieve(Position P);