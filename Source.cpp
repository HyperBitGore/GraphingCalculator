#include "PixelEdit.h"
#include <vector>
#include <string>
#include <math.h>
#undef main
bool exitf = false;
Gore::Edit edit;
struct point {
	float x;
	float y;
};
struct consts {
	int pos;
	int val;
	char consta;
};

int concat(int x, int y) {
	std::string s1 = std::to_string(x);
	std::string s2 = std::to_string(y);
	s1 = s1 + s2;
	int con = stoi(s1);

	return con;
}
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
int factorial(int in) {
	int fact = 1;
	for (int i = 1; i <= in; i++) {
		fact = fact * i;
	}
	return fact;
}


int main() {
	SDL_Window *wind = SDL_CreateWindow("Graphing Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, 800, 800, 32, SDL_PIXELFORMAT_RGBA8888);
	SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, 0);
	float delta = edit.getDelta();
	SDL_Event e;
	std::vector<consts> equation;
	std::vector<point> bpoints;
	SDL_Rect trect = { 0, 0, 800, 800 };
	std::string inp;
	std::cout << "Input equation: ";
	std::cin >> inp;
	int index = 0;
	for (int i = 0; i < inp.size(); i++) {
		if (validInp(inp[i]) == 0) {
			consts l = { index, 0, inp[i] };
			index++;
			equation.push_back(l);
		}
		else if (std::isdigit(inp[i])) {
			int ld = inp[i]-'0';
			int j;
			for (j = ++i; std::isdigit(inp[j]); j++) {
				int t = inp[j] - '0';
				ld = concat(ld, t);
			}
			i = --j;
			consts l = { index, ld, 0 };
			index++;
			equation.push_back(l);
		}
	}
	bool calcline = false;
	for (int i = 0; i < equation.size(); i++) {
		if (std::isalpha(equation[i].consta)) {
			calcline = true;
		}
		std::cout << "Index: " << equation[i].pos << " Value: " << equation[i].val << " Constant: " << equation[i].consta << std::endl;
	}
	//need to figure out how to fix order of operations to be correct instead of kinda correct
	if (!calcline) {
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
				equation[i].val = 0;
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
					equation[i - 1].val = 0;
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
					equation[i].val = 0;
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
					equation[i].val = 0;
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
					equation[i].val = 0;
					equation[i].consta = 0;
					break;
				}
			}

			point p = { 0, 0 };
			p.x = 0;
			p.y = output;
			std::cout << p.y << std::endl;
			//std::cout << p.y << std::endl;
			bpoints.push_back(p);
	}//make this do actual graphing, input i where x value is in equation and solve
	else {
		std::vector<consts> equa(equation);
		for (int j = 0; j < 1000; j++) {
			for (int i = 0; i < equation.size(); i++) {
				if (std::isalpha(equation[i].consta)) {
					equation[i].val = j;
				}
			}
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
					equation[i].val = 0;
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
					equation[i - 1].val = 0;
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
					equation[i].val = 0;
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
					equation[i].val = 0;
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
					equation[i].val = 0;
					equation[i].consta = 0;
					break;
				}
			}

				point p = { 0, 0 };
				p.x = j;
				p.y = output;
				std::cout << p.y << std::endl;
				//std::cout << p.y << std::endl;
				bpoints.push_back(p);
				equation = equa;
			}
	}
	while (!exitf) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderDrawLine(rend, 400, 400, 0, 400);
		SDL_RenderDrawLine(rend, 400, 400, 800, 400);
		SDL_RenderDrawLine(rend, 400, 400, 400, 0);
		SDL_RenderDrawLine(rend, 400, 400, 400, 800);
		delta = edit.getDelta();
		for (auto& i : bpoints) {
			edit.setPixelRGBASafe(surf, i.x+400, -i.y+400, 255, 0, 150, 255, 800, 800);
		}
		SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
		SDL_RenderCopy(rend, tex, NULL, &trect);

		SDL_DestroyTexture(tex);
		SDL_RenderPresent(rend);
	}
	SDL_FreeSurface(surf);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wind);
	return 0;
}