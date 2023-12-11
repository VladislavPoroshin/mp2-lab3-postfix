#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Stack.h"
using namespace std;
typedef long long unsigned int llui;
typedef long long int lli;

class Postfix {
	string infix;
	string postfix;
public:
	Postfix() {
		infix = "";
		postfix = "";
	}
	Postfix(string A) {
		infix = A;
		postfix = this->ToPostfix();
	}
	bool Parse(string A) {
		Stack<char> ST;
		bool flag = true;
		map<char, int> items;
		items = { 
		{ '0', 2}, { '1', 2}, { '2', 2}, { '3', 2}, { '4', 2}, { '5', 2}, { '6', 2}, { '7', 2}, { '8', 2}, { '9', 2},
		{ '+', 1}, { '-', 1}, { '/', 1}, { '*', 1},
		{ '(', 0}, { ')', 0} 
		};
		for (int i = 0; i < A.size(); i++) {
			auto iter = items.find(A[i]);
			if (iter != items.end()) {
				int id = (items.find(A[i]))->second;
				switch (id) {
				default:
				{
					throw out_of_range("incorrect expression");
					break;
				}
				case 0:
				{
					if (A[i] == '(')
						ST.Push('(');
					if (A[i] == ')') {
						if (!ST.IsEmpty())
							ST.Pop();
						else
							return(!flag);
					}
					if (i != A.size() - 1) {
						auto iter_next = items.find(A[i + 1]);
						if (iter_next != items.end()) {
							int id_next = (items.find(A[i + 1]))->second;
							if ((id_next == 1) && (A[i+1] != '-') && (A[i] == '('))
								return(!flag);
							if ((id_next == 2) && (A[i] == ')'))
								return(!flag);
							if ((A[i] == '(') && (A[i] == ')'))
								return(!flag);
						}
						else
							return(!flag);
					}
					break;
				}
				case 1:
				{
					if ((i == 0) && (A[i] != '-'))
						return(!flag);
					if (i == A.size() - 1)
						return(!flag);
					else {
						auto iter_next = items.find(A[i + 1]);
						if (iter_next != items.end()) {
							int id_next = (items.find(A[i + 1]))->second;
							if (id == id_next)
								return(!flag);
							if (A[i+1] == ')')
								return(!flag);
						}
						else
							return(!flag);
					}

					break;
				}
				case 2:
				{
					if (i != A.size() - 1) {
						auto iter_next = items.find(A[i + 1]);
						if (iter_next != items.end()) {
							int id_next = (items.find(A[i + 1]))->second;
							if (id == id_next)
								return(!flag);
							if (A[i + 1] == '(')
								return(!flag);
						}
						else
							return(!flag);
					}
					break;
				}
				}
			}
			else {
				return(!flag);
			}
		}
		if (!ST.IsEmpty())
			return(!flag);
		return(flag);
	}
	string GetInfix() {
		return(infix);
	}
	string GetPostfix() {
		return(postfix);
	}
	string ToPostfix() {
		Stack<char> ST;
		string tmp = "";
		if (!Parse(infix)) {
			throw out_of_range("incorrect expression");
			return(tmp);
		}
		for (int i = 0; i < infix.size(); i++) {
			switch (infix[i])
			{
			default:
			{
				postfix = "";
				throw out_of_range("failed to translate to postfix");
				break;
			}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				tmp.push_back(infix[i]);
				break;
			}
			case '(':
			{
				ST.Push(infix[i]);
				break;
			}
			case ')':
			{
				char item = ST.Pop();
				while (item != '(') {
					tmp.push_back(item);
					item = ST.Pop();
				}
				break;
			}
			case '+':
			case '/':
			case '-':
			case '*':
			{
				map<char, int> priority;
				priority = { { '+', 1}, { '-', 1}, { '/', 2}, { '*', 2} };
				if ((i == 0) && (infix[i] == '-'))
					tmp.push_back('0');
				if ((i > 0) && (infix[i] == '-') && (infix[i-1] == '('))
					tmp.push_back('0');
				while (!ST.IsEmpty()) {
					char item = ST.Pop();
					if (item == '(') {
						ST.Push(item);
						break;
					}
					else {
						int id1 = (priority.find(infix[i]))->second;
						int id2 = (priority.find(item))->second;
						if (id1 <= id2)
							tmp.push_back(item);
						else {
							ST.Push(item);
							break;
						}
					}
				}
				ST.Push(infix[i]);
				break;
			}
			}
		}
		while (!ST.IsEmpty()) {
			char item = ST.Pop();
			tmp.push_back(item);
		}
		postfix = tmp;
		return(postfix);
	}
	double Calculate() {
		double res = 0;
		Stack<double> ST;
		if (postfix == "")
			return(res);
		for (int i = 0; i < postfix.size(); i++) {
			switch (postfix[i])
			{
			default:
			{
				res = 0;
				throw out_of_range("failed to calculate");
				break;
			}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				ST.Push((double)((int)postfix[i]-(int)'0'));
				break;
			}
			case '+':
			{
				double R = ST.Pop();
				double L = ST.Pop();
				ST.Push(L + R);
				break;
			}
			case '*':
			{
				double R = ST.Pop();
				double L = ST.Pop();
				ST.Push(L * R);
				break;
			}
			case '/':
			{
				double R = ST.Pop();
				double L = ST.Pop();
				if (R) {
					ST.Push(L / R);
					break;
				}
				else {
					throw out_of_range("can not divide by zero");
					break;
				}
			}
			case '-':
			{
				double R = ST.Pop();
				double L = ST.Pop();
				ST.Push(L - R);
				break;
			}
			}
		}
		res = ST.Pop();
		return(res);
	}
};
