#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "particle.h"
#include <chrono>
#include <SDL_thread.h>

using namespace std;
using namespace std::chrono;

//screen dimensions
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

const int N = 1600;
const int num_threads = N / 10;
const int workload = N / num_threads;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Texture* tex = nullptr;

string path = "images/particle9.png";
string path2 = "images/particle2.png";
string path3 = "images/particle3.png";

vector<particle*> list;
Uint32 start_time = 0;
Uint32 end_time = 0;

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

bool pic2Texture()
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

int threadFunction(void* data){
	//Print incoming data
	//printf("Running thread with value = %d\n", (int)data);

	int x = (int)data * workload;

	/*for (int i = x; i < (x + N / 10); i++) {
		printf("%d\n", i);
	}*/

	for (int i = x; i < (x + workload)-1; i++) {

		list.at(i)->move();
		for (int j = (i + 1);j < (x + workload);j++) {

			list.at(i)->move();
			bool collided = list.at(i)->detCollision(list.at(i)->getX(), list.at(i)->getY(), list.at(j)->getX(), list.at(j)->getY());

			if (collided) {
				int x_vec = list.at(i)->getXVec();
				int y_vec = list.at(i)->getYVec();
				list.at(i)->bounce(list.at(j)->getXVec(), list.at(j)->getYVec());
				list.at(j)->bounce(x_vec, y_vec);
			}
		}
		SDL_Rect rect = list.at(i)->getRect();
		//pic2Texture(temp->getPath());
		SDL_RenderCopy(renderer, tex, NULL, &rect);
		//SDL_DestroyTexture(tex);
	}

	return 0;
}

void synch_func() {

	for (int i = 0; i < list.size()-1; i++) {
		for (int j = (i + 1);j < list.size();j++) {

			list.at(i)->move();
			bool collided = list.at(i)->detCollision(list.at(i)->getX(), list.at(i)->getY(), list.at(j)->getX(), list.at(j)->getY());

			if (collided) {
				int x_vec = list.at(i)->getXVec();
				int y_vec = list.at(i)->getYVec();
				list.at(i)->bounce(list.at(j)->getXVec(), list.at(j)->getYVec());
				list.at(j)->bounce(x_vec, y_vec);
			}
		}

		SDL_Rect rect = list.at(i)->getRect();
		SDL_RenderCopy(renderer, tex, NULL, &rect);
	}

}

void close() {
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(tex);

	list.clear();

	SDL_Quit();
}


int main(int argc, char* args[]) {

	if (!init()) {
		printf("fail to initliaze\n");
		system("pause");
	}
	else {

		pic2Texture();

		for (int i = 0; i < sqrt(N); i++) {
			for (int j = 0; j < sqrt(N); j++) {
				particle* atom = new particle(SCREEN_WIDTH / sqrt(N) * i, SCREEN_HEIGHT / sqrt(N) * j);
				list.insert(list.begin(), atom);
			}
		}

		//int data = 101;
		//SDL_Thread* threadID = SDL_CreateThread(threadFunction, "LazyThread", (void*)data);

		SDL_Thread* threads[num_threads];
		//vector<SDL_Thread*> threads;

		while (!quit) {

			auto start = high_resolution_clock::now();

			start_time = SDL_GetTicks();

			while (SDL_PollEvent(&e) != 0) {

				if (e.type == SDL_QUIT) {
					quit = true;
				}

			}

			//cout << "meow" << "\n";
			SDL_RenderClear(renderer);

			//synch_func(); //synchronous func to do work

			for (int i = 0; i < num_threads; i++) { //create threads
				threads[i] = SDL_CreateThread(threadFunction, "LazyThread", (void*)i);
			}

			for (int i = 0; i < num_threads;i ++ ) { //join threads
				SDL_WaitThread(threads[i], NULL);
			}

			//SDL_RenderCopyEx(renderer, tex, NULL, atom->getRect(), temp->getAngle(), NULL, SDL_FLIP_NONE);

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderPresent(renderer);

			end_time = SDL_GetTicks();

			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);

			double fps = duration.count();
			fps = 1 / fps;
			fps *= 1000000;

			/*cout << "Time taken by function: "
				<< duration.count() << " microseconds" << endl;*/
			cout << int(fps) << " fps" << "\n";
			//cout << "end time = " << end_time << "start time = " << start_time << "" << "\n";
		}
		//delete(atom);

		//system("pause");
	}

	close();

	return 0;
}
