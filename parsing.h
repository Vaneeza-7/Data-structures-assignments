#pragma once
#include<iostream>
#include<string>
#include<stack>
using namespace std;


bool prcd(char op1, char op2)
{
	if (op1 == '(')
		return false;
	else if (op2 == '(' && op1 != ')')
		return false;
	else if (op2 == ')' && op1 == '(')
		return true;
	else if (op1 == ')')
		return -1;
	else if (op1 == '^' || op1=='$')
		return true;
    else if (op1 == '*')
		return true;
	else if (op1 == '/')
		return true;
	else if (op1 == '+' && op2 == '*')
		return false;
	else if (op1 == '+' && op2 == '+')
		return true;
	else if (op1 == '+' && op2 == '-')
		return true;
	else if (op1 == '+' && op2 == '/')
		return false;
	
	if (op1 == '-')
		if (op2 == '-' || op2 == '+')
			return true;

	if (op1 == '-')
		if (op2 == '*' || op2 == '/')
			return false;

}


string convertToPostfix(string exp)
{
	stack<char> opstk;
	char symb, topsymb;
	string postfix;
	int length = exp.length();
	for (int i = 0; i<length; i++)
	{
		while((exp[i] == 32))
		{
			i++;
		}
		symb = exp[i];
		if (symb >= 'A' && symb <= 'Z')
		{
			string s(1, symb);
			postfix.append(s);
		}
		else if (symb >= 'a' && symb <= 'z')
		{
			string s(1, symb);
			postfix.append(s);
		}
		else
		{
			while (!empty(opstk) && prcd(opstk.top(), symb))
			{
				topsymb = opstk.top();
				string s(1, topsymb);
				postfix.append(s);
				opstk.pop();
			}
			if (opstk.empty() || symb != ')')
				opstk.push(symb);
			else
				opstk.pop();
		}
	}

	while (!opstk.empty())
	{
		topsymb = opstk.top();
		string s(1, topsymb);
		postfix.append(s);
		
		opstk.pop();
	}
	//cout << postfix << endl;
	return postfix;
	
}

void evalPost(string postfix)
{
	stack<string> opstk;
	string symb, result, op1, op2;

	string exp;
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		while ((postfix[i] == 32))
		{
			i++;
		}
		symb = postfix[i];
		if (symb >= "A" && symb <= "Z")
		{
			opstk.push(symb);
		}
		else if (symb >= "a" && symb <= "z")
		{
			opstk.push(symb);
		}
		else
		{
				op2 = opstk.top();
				opstk.pop();
				op1 = opstk.top();
				opstk.pop();
				result.append(op1);
				result.append(symb);
				result.append(op2);
				opstk.push(result);
				result = "\0";
		}
	}
	result = opstk.top();
	opstk.pop();
	cout << result << endl;
}

void convertToPrefix(string exp)
{
	int length=exp.length();
	string rev, prefix, postfix;
	rev = exp;
	int j = 0;
	for (int i = length-1; i >= 0; i--)
	{
		if (exp[i] == '(')
		{
			rev[j] = ')';
		
		}
		if (exp[i] == ')')
		{
			rev[j] = '(';
		
		}
		if (exp[i]!='(' && exp[i]!=')')
		{
			rev[j] = exp[i];
			
		}
		j++;
	}
	postfix = convertToPostfix(rev);
	length = postfix.length();
	prefix = postfix;
	j = 0;
	for (int i = length-1; i >= 0; i--)
	{
			prefix[j] = postfix[i];
			j++;
	}
	cout << prefix << endl;
}

void tagparse(string filename)
{
	stack<string> tags;
	static int time = 0;
	fstream input, output;
	string temp;
	//string filename = "Test-2.txt";
	string result = "Output.txt";
	input.open(filename);
	output.open(result, ios::app);
	string tag;
	while (input >> tag)
	{
		//input >> tag;

		//if (tag == "|start|" || tag == "|priorty|" || tag == "|head|" || tag == "|paragraph|" || tag == "|post_exp|" || tag == "|pre_exp|" || tag == "|sol_exp|" || tag == "|src|" || tag == "|chk|" || tag == "|pick|" || tag == "|tick|" || tag == "|hick|")
		//{
		//	tags.push(tag);
		//	/*cout << tags.top() << "has been pushed at time " << time << endl;
		//	time++;
		//	*/

		//}/*
		if (tag == "|start|")
		{
			tags.push(tag);
		}
		else if (tag == "|tab|")
		{
			tags.push(tag);
			output << char(9);
		}
		else if (tag == "|priorty|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;
			output << " ";

		}
		else if (tag == "|head|")
		{
			tags.push(tag);
			output << char(9) << char(9) << char(9) << char(9) << char(9) << char(9);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|paragraph|")
		{
			tags.push(tag);
			output << char(11) << endl;
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|post_exp|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|pre_exp|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|sol_exp|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|src|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|chk|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|pick|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|hick|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}
		else if (tag == "|tick|")
		{
			tags.push(tag);
			//cout << tags.top() << "has been pushed." << endl;

		}

		else if (tag == R"(|\start|)" || tag == R"(|\priorty|)" || tag == R"(|\tab|)" || tag == R"(|\head|)" || tag == R"(|\paragraph|)" || tag == R"(|\post_exp|)" || tag == R"(|\pre_exp|)" || tag == R"(|\sol_exp|)" || tag == R"(|\src|)" || tag == R"(|\chk|)" || tag == R"(|\pick|)" || tag == R"(|\tick|)" || tag == R"(|\hick|)")
		{

			if (!tags.empty()) {
				if (tags.top() == "|paragraph|" && tag == R"(|\paragraph|)")
				{
					/*cout << tags.top() << "has been popped at time " << time << endl;
					time++;*/
					tags.pop();

				}
				else if (tags.top() == "|start|" && tag == R"(|\start|)")
				{
					/*cout << tags.top() << "has been popped at " << time << endl;
					time++;*/
					tags.pop();
				}
				else if (tags.top() == "|priorty|" && tag == R"(|\priorty|)")
				{
					/*cout << tags.top() << "has been popped " << time << endl;
					time++;*/
					tags.pop();
				}

				else if (tags.top() == "|head|" && tag == R"(|\head|)")
				{

					/*cout << tags.top() << "has been popped" << time << endl;
					time++;*/
					tags.pop();
				}
				else if (tags.top() == "|post_exp|" && tag == R"(|\post_exp|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|pre_exp|" && tag == R"(|\pre_exp|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|sol_exp|" && tag == R"(|\sol_exp|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|src|" && tag == R"(|\src|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|chk|" && tag == R"(|\chk|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|pick|" && tag == R"(|\pick|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|hick|" && tag == R"(|\hick|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|tick|" && tag == R"(|\tick|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
				else if (tags.top() == "|tab|" && tag == R"(|\tab|)")
				{
					//cout << tags.top() << "has been popped" << time << endl;
					tags.pop();
					//time++;
				}
			}
		}
		else if (tag == "." || tag == "," || tag == "File." || tag == "picture.")
		{
			output << tag << endl;
		}
		else
			output << tag << " ";

	} //while (input.eof() == false);
//-------------------------------------------ERROR DETECTION--------------------//
	input.close();
	output.close();
	if (tags.empty() == true)
	{
		cout << "All fine in " << filename << endl;
	}
	else
	{
		cout << "Syntax error in " << filename << endl;
	}

}
