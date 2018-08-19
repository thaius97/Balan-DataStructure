#include <iostream>
#include <string>
using namespace std;



// ----------- Token -----------

struct Token
{
	int Type; // Loai token // 0: mở ngoặc, 1: đóng ngoặc, 2: toán tử, 3: toán hạng
	int Value; // Gia tri token
};

Token TokenNULL();
Token SetToken(int loai, int giatri);

// ----------- Node -----------

struct Node
{
	Token Info;
	Node *pNext;
};

Node* CreateNode(Token Data);

// ----------- Stack -----------

struct Stack
{
	Node *Top; // con trỏ top quản lý node ở đầu stack
};

void InitStack(Stack &s);
int Stack_IsEmpty(Stack s);
void Push(Stack &s, Node *p);
Token Pop(Stack &s);
Token Top(Stack s);

// ----------- Queue -----------

struct Queue
{
	Node *pHead;
	Node *pTail;
};

void InitQueue(Queue &q);
int Queue_IsEmpty(Queue q);
void EnQueue(Queue &q, Node *p);
Token DeQueue(Queue &q);

// ----------- #### -----------

bool IsOperator(char c);
int Rank(char c);
int Tinh(int x, int y, char c);
void ConVertInfixToPostfix(Queue &q, string str);
Token CalculatePostfix(Queue q);
