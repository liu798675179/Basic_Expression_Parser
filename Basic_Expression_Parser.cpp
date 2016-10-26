#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <regex>
#include <cmath>

using namespace std;

//拆分字符
vector<string> Split() {
	vector<string> temp_VecStr;
	regex reg_dig("[[:digit:].]");
	string temp_str, temp_str1, temp_str2, temp_str3;

	cout << "请输入表达式：" << endl;
	cin >> temp_str;

	for (auto i = temp_str.begin(); i != temp_str.end(); ++i) {
		temp_str2 = *i;

		if (regex_search(temp_str2, reg_dig)) {
			temp_str1 += temp_str2;

			auto p = i;

			if (++p == temp_str.end()) {
				temp_VecStr.push_back(temp_str1);
				temp_str1.clear();
			}
			--p;

			if (++p != temp_str.end()) {
				--p;
				temp_str2 = *(++p);

				if (!regex_search(temp_str2, reg_dig)) {
					temp_VecStr.push_back(temp_str1);
					temp_str1.clear();
				}
			}
		}
		else {
			if (temp_str2 == "+" || temp_str2 == "-" || temp_str2 == "*" || temp_str2 == "/" || temp_str2 == "(" || temp_str2 == "%") {
				temp_VecStr.push_back(temp_str2);

				auto p = i;
				if (++p != temp_str.end()) {
					--p;

					temp_str3 = *(++p);
					if (temp_str3 == "-") {
						temp_str1 += temp_str3;

						if (++p != temp_str.end()) {
							auto p1 = p;
							temp_str3 = *p1;
							for (; regex_search(temp_str3, reg_dig) && p1 != temp_str.end(); ++p1, ++i) {
								temp_str3 = *p1;
								if (regex_search(temp_str3, reg_dig)) {
									temp_str1 += temp_str3;
								}
							}
							temp_VecStr.push_back(temp_str1);
							temp_str1.clear();
							if (regex_search(temp_str3, reg_dig)) {
								++i;
							}
						}
					}
				}
			}
			else {
				temp_VecStr.push_back(temp_str2);
			}
		}
	}

	return temp_VecStr;
}

//转换为后缀表达式
stack<string> Postfix_Expression(vector<string> temp_VecStr) {
	stack<string> temp_StackSymbol, temp_StackExp, temp_Stack1, temp_Stack2;
	regex reg_dig("[[:digit:].]+");
	string temp_str;

	for (auto &i : temp_VecStr) {
		temp_str = i;

		if (regex_search(temp_str, reg_dig)) {
			temp_StackExp.push(temp_str);
		}

		if (temp_str == "(") {
			temp_StackSymbol.push(temp_str);
		}

		if (temp_str == ")") {
			while (temp_StackSymbol.top() != "(") {
				temp_StackExp.push(temp_StackSymbol.top());
				temp_StackSymbol.pop();
			}
			temp_StackSymbol.pop();
		}

		if (temp_str == "+" || temp_str == "-") {
			if (!temp_StackSymbol.empty()) {
				if (temp_StackSymbol.top() == "+" || temp_StackSymbol.top() == "-" || temp_StackSymbol.top() == "*" || temp_StackSymbol.top() == "/" || temp_StackSymbol.top() == "%") {
					while (!temp_StackSymbol.empty() && temp_StackSymbol.top() != "(") {
						temp_StackExp.push(temp_StackSymbol.top());
						temp_StackSymbol.pop();
					}
					temp_StackSymbol.push(temp_str);
				}
				else {
					temp_StackSymbol.push(temp_str);
				}
			}
			else {
				temp_StackSymbol.push(temp_str);
			}
		}

		if (temp_str == "%") {
			if (!temp_StackSymbol.empty()) {
				if (temp_StackSymbol.top() == "*" || temp_StackSymbol.top() == "/" || temp_StackSymbol.top() == "%") {
					while (!temp_StackSymbol.empty() && temp_StackSymbol.top() != "(" && temp_StackSymbol.top() != "+" && temp_StackSymbol.top() != "-") {
						temp_StackExp.push(temp_StackSymbol.top());
						temp_StackSymbol.pop();
					}
					temp_StackSymbol.push(temp_str);
				}
				else {
					temp_StackSymbol.push(temp_str);
				}
			}
			else {
				temp_StackSymbol.push(temp_str);
			}
		}

		if (temp_str == "*" || temp_str == "/") {
			if (!temp_StackSymbol.empty()) {
				if (temp_StackSymbol.top() == "*" || temp_StackSymbol.top() == "/") {
					while (!temp_StackSymbol.empty() && temp_StackSymbol.top() != "(" && temp_StackSymbol.top() != "+" && temp_StackSymbol.top() != "-") {
						temp_StackExp.push(temp_StackSymbol.top());
						temp_StackSymbol.pop();
					}
					temp_StackSymbol.push(temp_str);
				}
				else {
					temp_StackSymbol.push(temp_str);
				}
			}
			else {
				temp_StackSymbol.push(temp_str);
			}
		}
	}

	while (!temp_StackSymbol.empty()) {
		temp_StackExp.push(temp_StackSymbol.top());
		temp_StackSymbol.pop();
	}

	while (!temp_StackExp.empty()) {
		temp_Stack1.push(temp_StackExp.top());
		temp_Stack2.push(temp_StackExp.top());
		temp_StackExp.pop();
	}

	cout << endl << "其后缀表达式为:" << endl << endl;
	while (!temp_Stack2.empty()) {
		cout << temp_Stack2.top() << " ";
		temp_Stack2.pop();
	}
	cout << endl << endl;

	return temp_Stack1;
}

//求值
void Evaluation(stack<string> temp_StackExp) {
	auto temp_num1 = 0.0, temp_num2 = 0.0;
	regex reg_dig("[[:digit:].]+");
	stack<double> temp_StackNum;
	string temp_str;

	try {
		while (!temp_StackExp.empty()) {
			temp_str = temp_StackExp.top();

			if (regex_search(temp_str, reg_dig)) {
				temp_StackNum.push(stod(temp_str));
				temp_StackExp.pop();
			}

			if (temp_str == "+") {
				if (!temp_StackNum.empty()) {
					temp_num1 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_num2 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_StackNum.push(temp_num1 + temp_num2);
					temp_StackExp.pop();
				}
				else {
					throw runtime_error("表达式输入错误，请重新输入!");
				}
			}

			if (temp_str == "-") {
				if (!temp_StackNum.empty()) {
					temp_num1 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_num2 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_StackNum.push(temp_num2 - temp_num1);
					temp_StackExp.pop();
				}
				else {
					throw runtime_error("表达式输入错误，请重新输入!");
				}
			}

			if (temp_str == "%") {
				if (!temp_StackNum.empty()) {
					temp_num1 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_num2 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_StackNum.push(fmod(temp_num2, temp_num1));
					temp_StackExp.pop();
				}
				else {
					throw runtime_error("表达式输入错误，请重新输入!");
				}
			}

			if (temp_str == "*") {
				if (!temp_StackNum.empty()) {
					temp_num1 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_num2 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_StackNum.push(temp_num1 * temp_num2);
					temp_StackExp.pop();
				}
				else {
					throw runtime_error("表达式输入错误，请重新输入!");
				}
			}

			if (temp_str == "/") {
				if (!temp_StackNum.empty()) {
					temp_num1 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_num2 = temp_StackNum.top();
					temp_StackNum.pop();
					temp_StackNum.push(temp_num2 / temp_num1);
					temp_StackExp.pop();
				}
				else {
					throw runtime_error("表达式输入错误，请重新输入!");
				}
			}
		}
	}

	catch (runtime_error &err) {
		cout << err.what() << endl;
		return Evaluation(Postfix_Expression(Split()));
	}

	cout << "表达式的值为： " << temp_StackNum.top() << endl << endl;
}

int main() {
	while (1) {
		Evaluation(Postfix_Expression(Split()));
	}

	return 0;
}
