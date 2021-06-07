#pragma once
#include "PixelEdit.h"
#include <vector>
#include <string>
#include <math.h>

struct point {
	float x;
	float y;
};
struct consts {
	int pos;
	int val;
	char consta;
};
int validInp(char val) {
	if (std::isalpha(val)) {
		return 0;
	}
	char vals[] = { '+', '-', '/', '*', '^', '!' };
	for (int i = 0; i < 6; i++) {
		if (val == vals[i]) {
			return 0;
		}
	}
	return -1;
}
int concat(int x, int y) {
	std::string s1 = std::to_string(x);
	std::string s2 = std::to_string(y);
	s1 = s1 + s2;
	int con = stoi(s1);

	return con;
}
int factorial(int in) {
	int fact = 1;
	for (int i = 1; i <= in; i++) {
		fact = fact * i;
	}
	return fact;
}

int solveEquation(std::vector<consts> equation) {
	int y = 0;
	int output = 0;
	for (int i = 0; i < equation.size(); i++) {
		int nextnum = i + 1;
		switch (equation[i].consta) {
		case '^':
			for (int k = i + 1; k < equation.size(); k++) {
				if (equation[k].val != 0 && validInp(equation[k].consta) == -1) {
					nextnum = k;
					break;
				}
			}
			output = std::pow(equation[i - 1].val, equation[nextnum].val);
			equation[i + 1].val = output;
			equation[i - 1].val = 0;
			equation[i].consta = 0;
			break;
		case '!':
			output = factorial(equation[i - 1].val);
			equation[i].val = output;
			equation[i].consta = 0;
			break;
		}
	}
	for (int i = 0; i < equation.size(); i++) {
		int nextnum = i + 1;
		switch (equation[i].consta) {
		case '*':
			for (int k = i + 1; k < equation.size(); k++) {
				if (equation[k].val != 0 && validInp(equation[k].consta) == -1) {
					nextnum = k;
					break;
				}
			}
			output = equation[i - 1].val * equation[nextnum].val;
			equation[i + 1].val = output;
			equation[i].consta = 0;
			break;
		case '/':
			for (int k = i + 1; k < equation.size(); k++) {
				if (equation[k].val != 0 && validInp(equation[k].consta) == -1) {
					nextnum = k;
					break;
				}
			}
			output = equation[i - 1].val / equation[nextnum].val;
			equation[i + 1].val = output;
			equation[i - 1].val = 0;
			equation[i].consta = 0;
			break;
		}
	}
	for (int i = 0; i < equation.size(); i++) {
		int nextnum = i + 1;
		switch (equation[i].consta) {
		case '+':
			for (int k = i + 1; k < equation.size(); k++) {
				if (equation[k].val != 0 && validInp(equation[k].consta) == -1) {
					nextnum = k;
					break;
				}
			}
			output = equation[i - 1].val + equation[nextnum].val;
			equation[i + 1].val = output;
			equation[i - 1].val = 0;
			equation[i].consta = 0;
			break;
		case '-':
			for (int k = i + 1; k < equation.size(); k++) {
				if (equation[k].val != 0 && validInp(equation[k].consta) == -1) {
					nextnum = k;
					break;
				}
			}
			output = equation[i - 1].val - equation[nextnum].val;
			equation[i + 1].val = output;
			equation[i - 1].val = 0;
			equation[i].consta = 0;
			break;
		}
	}
	y = output;
	return y;
}