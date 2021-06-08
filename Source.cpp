#include "solve.h"
#undef main
bool exitf = false;
Gore::Edit edit;
int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *wind = SDL_CreateWindow("Graphing Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, 800, 800, 32, SDL_PIXELFORMAT_RGBA8888);
	SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, 0);
	float delta = edit.getDelta();
	SDL_Event e;
	std::vector<consts> equation;
	std::vector<point> bpoints;
	std::vector<point> lines;
	SDL_Rect trect = { 0, 0, 800, 800 };
	SDL_Rect camera = { 0, 0, 800, 800 };
	std::string inp;
	std::cout << "Input equation: ";
	std::cin >> inp;
	for (int i = 400; i < 2000; i++) {
		point l = { i, 400 };
		lines.push_back(l);
	}
	for (int i = 400; i > -2000; i--) {
		point l = { i, 400 };
		lines.push_back(l);
	}
	for (int i = 400; i < 2000; i++) {
		point l = { 400, i };
		lines.push_back(l);
	}
	for (int i = 400; i > -2000; i--) {
		point l = { 400, i };
		lines.push_back(l);
	}
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
			point p = { 0, 0 };
			p.x = 0;
			p.y = solveEquation(equation);
			std::cout << p.y << std::endl;
			bpoints.push_back(p);
	}//make this do actual graphing, input i where x value is in equation and solve
	else {
		for (int j = -1000; j < 1000; j++) {
			for (int i = 0; i < equation.size(); i++) {
				if (std::isalpha(equation[i].consta)) {
					equation[i].val = j;
				}
			}
			point p = { 0, 0 };
			p.x = j;
			p.y = solveEquation(equation);
			std::cout << p.y << std::endl;
			bpoints.push_back(p);
			}
	}
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);
	while (!exitf) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		SDL_PumpEvents();
		if (keys[SDL_SCANCODE_RIGHT]) {
			camera.x++;
		}
		else if (keys[SDL_SCANCODE_LEFT]) {
			camera.x--;
		}
		else if (keys[SDL_SCANCODE_DOWN]) {
			camera.y++;
		}
		else if (keys[SDL_SCANCODE_UP]) {
			camera.y--;
		}
		int x, y;
		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			camera.x = (int)x - 400;
			camera.y = (int)y - 400;
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		edit.clearSurface(surf, 800, 800);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		delta = edit.getDelta();
		for (auto& i : lines) {
			edit.setPixelRGBASafe(surf, i.x + 400 - camera.x, -i.y + 400 - camera.y, 255, 255, 255, 255, 800, 800);
		}
		for (auto& i : bpoints) {
			edit.setPixelRGBASafe(surf, i.x+400-camera.x, -i.y+400-camera.y, 255, 0, 150, 255, 800, 800);
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