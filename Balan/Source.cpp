#include "Balan.h"


int main(int argc, char* argv[])
{
	cout << argv[0] << endl;
	if (argc != 1)
	{
		Queue q;
		Token kq;
		string str;

		for (int i = 1; i < argc; i++)
		{
			str += argv[i];
			str += " "; // + khoảng trắng cho giống str biểu thức
		}

		ConVertInfixToPostfix(q, str);
		kq = CalculatePostfix(q);
		cout << "Ket qua cua bieu thuc: " << str << " = " << kq.Value << endl; // int
	}
}
