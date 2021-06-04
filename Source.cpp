#include "PixelEdit.h"
#include <vector>
#include <string>
#undef main
bool exitf = false;
Gore::Edit edit;
struct point {
	float x;
	float y;
};
int concat(int x, int y) {
	std::string s1 = std::to_string(x);
	std::string s2 = std::to_string(y);
	s1 = s1 + s2;
	int con = stoi(s1);

	return con;
}



int main() {
	SDL_Window *wind = SDL_CreateWindow("Graphing Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(0, 800, 800, 32,0, SDL_PIXELFORMAT_RGBA8888);
	SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, 0);
	float delta = edit.getDelta();
	SDL_Event e;
	std::vector<int> constants;
	std::vector<char> variables;
	std::vector<point> bpoints;
	SDL_Rect trect = { 0, 0, 800, 800 };
	std::string inp;
	std::cout << "Input equation: ";
	std::cin >> inp;
	for (int i = 0; i < inp.length(); i++) {
		if (std::isdigit(inp[i])) {
			int ld = inp[i];
			int j;
			for (j = ++i; std::isdigit(inp[j]); j++) {
				ld = concat(ld, inp[j]);
			}
			i = j;
			constants.push_back(ld);
		}
		else if (std::isalpha(inp[i])) {
			variables.push_back(inp[i]);
		} 
		else {
			switch (inp[i]) {
			case '+':
				break;
			case '-':
				break;
			case '/':
				break;
			case '*':
				break;
			case '^':
				break;
			case '(':
				break;
			case ')':
				break;
			case '!':
				break;
			}
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
		delta = edit.getDelta();
		for (auto& i : bpoints) {
			edit.setPixelRGBA(surf, i.x, i.y, 255, 0, 150, 255);
		}
		//SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
		//SDL_RenderCopy(rend, tex, NULL, &trect);

		//SDL_DestroyTexture(tex);
		SDL_RenderPresent(rend);
	}


	return 0;
}