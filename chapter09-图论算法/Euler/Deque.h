struct DequeRecord;
struct Node;
typedef struct DequeRecord *Deque;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef int ElementType;

int IsEmptyDeque(Deque D);
Deque CreateDeque(void);
void DisposeDeque(Deque D);
void MakeEmptyDeque(Deque D);
void Push(ElementType X, Deque D);
ElementType Pop(Deque D);
void Inject(ElementType X, Deque D);
ElementType Eject(Deque D);
ElementType Front(Deque D);
ElementType Rear(Deque D);
Position DequeFirst(Deque D);
Position DequePrevious(Position P);
Position DequeNext(Position P);
ElementType DequeValue(Position P);
void DequeMerge(int Pos, Deque D1, Deque D2);
void PrintDeque(Deque D);