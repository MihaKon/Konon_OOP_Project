#include <SDL.h>
#include <iostream>
#include <chrono>

class Window {
private:
	//Renderer renderer;
	SDL_Window* window;
	bool quit;

public:
	Window(){
		
		quit = true;

		if (SDL_Init(SDL_INIT_VIDEO) < 0){
			std::cout << "SDL_VIDEO not initalized! SDL_Error: %s\n", SDL_GetError();
			quit = false;
		}

		window = SDL_CreateWindow(
			"Konon_OOP_Project",
			SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
			600,600,
			SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
			quit = false;
		}

		//TODO: init renderer(window)
	}

	~Window() {
		//delete &renderer;
		SDL_DestroyWindow(window);
		window = nullptr;

		SDL_Quit;
	}

	void simulation(){
		while (!quit) {
			//checkInput();
			//update();
			renderer.render();
		}
	}
};

class Renderer {
private:
	SDL_Renderer* renderer;
public:
	Renderer(SDL_Window* window) {
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == nullptr) {
			std::cout << "Renderer could not be created! SDL_Error: %s\n", SDL_GetError();
		}
	}
	~Renderer() {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	void render() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}
};

int main(int argc, char* args[])
{
	Window visualize;
	visualize.simulation();
	return 0;
}