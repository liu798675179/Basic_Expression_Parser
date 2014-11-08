#include <iostream>
#include <stack>
using namespace std;

//中缀转后缀

/*规则：从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，
*即成为后缀表达式的一部分；若是符号，则判断其与栈顶符号的优先级，
*是右括号或优先级低于找顶符号（乘除优先加减）则栈顶元素依次出找并输出，
*并将当前符号进栈，一直到最终输出后缀表达式为止。
*/

/*                 IADA
*                刘乘艺
*/

int main()
{
	stack<char> Stacks;
	stack<char> Sc;
	char b;
	cout << "请输入中缀表达式" << endl;
	while (cin >> b){
		switch (b){
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			Sc.push(b);
			break;
		case'*':case'/':
			if (!Stacks.empty()){
				if (Stacks.top() == '*' || Stacks.top() == '/'){
					while (!Stacks.empty() && Stacks.top() != '('){
						Sc.push(Stacks.top());
						Stacks.pop();
					}
					Stacks.push(b);
					break;
				}
				else{
					Stacks.push(b);
					break;
				}
			}
		case'(':
			Stacks.push(b);
			break;
		case '+':case '-':
			if (!Stacks.empty()){
				if (Stacks.top() == '+' || Stacks.top() == '-' || Stacks.top() == '*' || Stacks.top() == '/'){
					while (!Stacks.empty() && Stacks.top() != '('){
						Sc.push(Stacks.top());
						Stacks.pop();
					}
					Stacks.push(b);
					break;
				}
				else{
					Stacks.push(b);
					break;
				}
			}
			else{
				Stacks.push(b);
				break;
			}
		case ')':
			while (Stacks.top() != '('){
				Sc.push(Stacks.top());
				Stacks.pop();
			}
			Stacks.pop();
			break;
		}
	}
	while (!Stacks.empty()){
		Sc.push(Stacks.top());
		Stacks.pop();
	}
	stack<char> Ys_Source_temp;
	stack<char> temp;
	while (!Sc.empty()){
		Ys_Source_temp.push(Sc.top());
		temp.push(Sc.top());
		Sc.pop();
	}
	cout << "其后缀表达式为" << endl;
	while (!temp.empty()){
		cout << temp.top() << " ";
		temp.pop();
	}
	cout << endl;

	/*             后缀表达式求值运算               */

	//问题：stack<char> --> stack<int> 转换，编码存在差异数字总多48,所以不得不减去48......

	stack<long> Ys_temp;
	int n1, n2;
	while (!Ys_Source_temp.empty()){
		switch (Ys_Source_temp.top()){
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			Ys_temp.push(Ys_Source_temp.top() - 48);
			Ys_Source_temp.pop();
			break;
		case '+':
			if (!Ys_temp.empty()){
				n1 = Ys_temp.top();
				Ys_temp.pop();
				n2 = Ys_temp.top();
				Ys_temp.pop();
				Ys_temp.push(n1 + n2);
				Ys_Source_temp.pop();
				break;
			}
			else{
				cout << "表达式输入错误，请重新输入" << endl;
				break;
			}
		case'*':
			if (!Ys_temp.empty()){
				n1 = Ys_temp.top();
				Ys_temp.pop();
				n2 = Ys_temp.top();
				Ys_temp.pop();
				Ys_temp.push(n1 * n2);
				Ys_Source_temp.pop();
				break;
			}
			else{
				cout << "表达式输入错误，请重新输入" << endl;
				break;
			}
		case '-':
			if (!Ys_temp.empty()){
				n1 = Ys_temp.top();
				Ys_temp.pop();
				n2 = Ys_temp.top();
				Ys_temp.pop();
				Ys_temp.push(n2 - n1);
				Ys_Source_temp.pop();
				break;
			}
			else{
				cout << "表达式输入错误，请重新输入" << endl;
				break;
			}
		case '/':
			if (!Ys_temp.empty()){
				n1 = Ys_temp.top();
				Ys_temp.pop();
				n2 = Ys_temp.top();
				Ys_temp.pop();
				Ys_temp.push(n2 / n1);
				Ys_Source_temp.pop();
				break;
			}
			else{
				cout << "表达式输入错误，请重新输入" << endl;
				break;
			}
		}
	}
	cout << "表达式的值为：";
	cout << Ys_temp.top() << endl;
	return 0;
}
