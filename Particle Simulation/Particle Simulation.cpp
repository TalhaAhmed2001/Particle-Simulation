#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include "particle.h"

using namespace std;

//screen dimensions
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* tex = nullptr;

string path = "images/particle.png";

bool quit = false;
SDL_Event e;

bool init() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xdd, 0xef, 0xff, 0xff);
			}

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				surface = SDL_GetWindowSurface(window);
			}
		}
	}

	return success;
}

bool pic2Texture(string path)
{
	bool success = true;

	SDL_Surface* Surf = IMG_Load(path.c_str());

	if (Surf == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else {
		if (tex != nullptr) {
			SDL_DestroyTexture(tex);
		}
		tex = SDL_CreateTextureFromSurface(renderer, Surf);
		SDL_FreeSurface(Surf);
	}
	return success;
}

void close() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(window);

	SDL_Quit();
}


int main(int argc, char* args[]) {

	if (!init()) {
		printf("fail to initliaze\n");
		system("pause");
	}
	else {
		particle* atom = new particle(SCREEN_HEIGHT / 2 - 32, SCREEN_WIDTH / 2 - 32);
		pic2Texture(path);

		while (!quit) {

			while (SDL_PollEvent(&e) != 0) {

				if (e.type == SDL_QUIT) {
					quit = true;
				}

			}

			cout << "meow" << "\n";
			SDL_RenderClear(renderer);

			SDL_Rect temp = atom->getRect();

			SDL_RenderCopy(renderer, tex, NULL, &temp);
			//SDL_RenderCopyEx(renderer, tex, NULL, atom->getRect(), temp->getAngle(), NULL, SDL_FLIP_NONE);

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderPresent(renderer);
		}
	}

	close();

	return 0;
}
