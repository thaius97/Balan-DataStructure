#include "Balan.h"


// ----------- Token -----------

Token TokenNULL()
{
	Token temp;
	temp.Type = NULL;
	temp.Value = NULL;
	return temp;
}

Token SetToken(int loai, int giatri)
{
	Token temp;
	temp.Type = loai;
	temp.Value = giatri;
	return temp;
}

// ----------- Node -----------

Node* CreateNode(Token Data)
{
	Node *p = new Node;
	if (p == NULL)
	{
		cout << "Khong du vung nho de cap phat!" << endl;
		return NULL;
	}
	p->Info = Data;
	p->pNext = NULL;
	return p;
}

// ----------- Stack -----------

void InitStack(Stack &s) // Tao stack rong
{
	s.Top = NULL;
}

int Stack_IsEmpty(Stack s)
{
	if (s.Top == NULL)
		return 1;
	return 0;
}

void Push(Stack &s, Node *p)
{
	if (Stack_IsEmpty(s))
	{
		s.Top = p;
		return;
	}
	else
	{
		p->pNext = s.Top;
		s.Top = p;
		return;
	}
}

Token Pop(Stack &s)
{
	if (Stack_IsEmpty(s))
	{
		return TokenNULL();
	}
	else
	{
		Node *p = s.Top; // Tro toi con tro Top
		Token temp = p->Info; // Luu gia tri
		s.Top = s.Top->pNext;
		delete p;
		return temp;
	}
}

Token Top(Stack s)
{
	if (Stack_IsEmpty(s))
	{
		//cout << "Stack rong, khong xem duoc Top!" << endl;
		return TokenNULL();
	}
	else
	{
		Token temp = s.Top->Info;
		return temp;
	}
}

// ----------- Queue -----------

void InitQueue(Queue &q)
{
	q.pHead = NULL;
	q.pTail = NULL;
}

int Queue_IsEmpty(Queue q)
{
	if (q.pHead == NULL && q.pTail == NULL)
		return 1;
	return 0;
}

void EnQueue(Queue &q, Node *p)
{
	if (Queue_IsEmpty(q))
	{
		q.pHead = p;
		q.pTail = p;
		return;
	}
	else
	{
		q.pTail->pNext = p;
		q.pTail = p;
		return;
	}
}

Token DeQueue(Queue &q)
{
	if (Queue_IsEmpty(q))
	{
		cout << "Queue rong, DeQueue that bai!" << endl;
		return TokenNULL();
	}
	else
	{
		Node *p = q.pHead;
		Token temp = p->Info;
		q.pHead = q.pHead->pNext;
		delete p;
		return temp;
	}
}

// ----------- #### -----------

bool IsOperator(char c) // kiểm tra ký tự có phải là toán tử hay không
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	return 0;
}

int Rank(char c) // độ ưu tiên của toán tử
{
	if (c == '*' || c == '/')
		return 2;
	if (c == '+' || c == '-')
		return 1;
	return 0;
}

int Tinh(int x, int y, char c)
{
	if (c == '+')
		return x + y;
	if (c == '-')
		return x - y;
	if (c == '*')
		return x * y;
	if (c == '/')
		return x / y;
}

void ConVertInfixToPostfix(Queue &q, string str) // Chuyến đổi biểu thức trung tố sang hậu tố
{
	Stack s;
	InitStack(s);
	InitQueue(q);

	int i = 0;
	int len = str.size();

	while (i < len) // type - 0: mở ngoặc, 1: đóng ngoặc, 2: toán tử, 3: toán hạng
	{
		Node *p = new Node;
		Token tk;

		if (str[i] == '(')	// --- Trường hợp ký tự là dấu ngoặc trái
		{
			tk = SetToken(0, str[i]); // type = 0 : dấu mở ngoặc
			p = CreateNode(tk);
			Push(s, p);
		}
		else if (str[i] == ')')	// --- Trường hợp ký tự là dấu ngoặc phải
		{
			while (1)
			{
				tk = Pop(s);
				if (tk.Type == 0) // type = 0 : là dấu mở ngoặc
				{
					break;
				}
				p = CreateNode(tk);
				EnQueue(q, p);
			}
		}
		else if (IsOperator(str[i])) // --- Trường hợp ký tự là toán tử // op1
		{
			tk = Top(s); // Xem Top có phải là toán tử hay không?
			if (tk.Type == 2) // type = 2: là toán tử // op2
			{
				if (Rank(tk.Value) >= Rank(str[i])) // op2 ưu tiên hơn op1
				{
					tk = Pop(s); // Pop op2 ra
					p = CreateNode(tk);
					EnQueue(q, p); // Đưa vào queue
				}
			}	// ngược lại thì push vào stack, top không phải ope thì cũng push vào stack

			tk = SetToken(2, str[i]); // type = 2: là toán tử
			p = CreateNode(tk);
			Push(s, p);
		}
		else if (str[i] >= '0' && str[i] <= '9')	// --- Trường hợp ký tự là toán hạng (số)
		{
			tk = SetToken(3, str[i] - '0');			// type = 3: là toán hạng(số) // chuyển kí tự thành giá trị số bằng cách trừ cho ký tự 0
			while (str[i + 1] >= '0' && str[i + 1] <= '9')	// ký tự típ theo cũng là số
			{
				int x = str[i + 1] - '0';	// Chuyển ký tự sang giá trị int
				tk.Value *= 10;				// Nhân giá trị lên 10
				tk.Value += x;				// + giá trị x (đơn vị) // chuyển 3, 4 thành 34 // (3*10) + 4
				i++;
			}
			p = CreateNode(tk);
			EnQueue(q, p);
		}
		i++;
	}

	while (Stack_IsEmpty(s) != 1) // Còn phần tử trong stack
	{
		Token tk = Pop(s);
		Node *p = new Node;
		p = CreateNode(tk);
		EnQueue(q, p);			// Lấy ra cho vào queue
	}
}

Token CalculatePostfix(Queue q) // Tính biểu thức ở dạng hậu tố
{
	Stack s;
	InitStack(s);

	while (q.pHead != NULL) // queue còn phần tử
	{
		Node *p = new Node;
		Token tk;

		tk = DeQueue(q);
		if (tk.Type == 3) // 3: toán hạng
		{
			p = CreateNode(tk);
			Push(s, p);
		}
		else if (tk.Type == 2) // 2: toán tử
		{
			Token b = Pop(s);
			Token a = Pop(s);
			int kq = Tinh(a.Value, b.Value, (char)tk.Value);

			tk = SetToken(3, kq); // 3: toán hạng // giá trị bằng kq vừa tính
			p = CreateNode(tk);
			Push(s, p);
		}
	}

	return Pop(s); // kết quả là giá trị phần tử trong cuối cung trong stack
}
