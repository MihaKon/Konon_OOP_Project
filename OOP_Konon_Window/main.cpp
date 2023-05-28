#include <SDL.h>
#include <iostream>

const int WINDOW_HEIGHT = 1000;
const int WINDOW_WIDTH = 1000;
const int G = 1;

class Rectangle {
private:
	int posX, posY;
	int dimX, dimY;
	int velX, velY;
public:
	Rectangle(int pX, int pY, int dX, int dY) {
		
		posY = pY;
		posX = pX;
		dimY = dY;
		dimX = dX;
		velX = 0;
		velY = 0;
	}
	void updatePosition(SDL_Renderer * renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect(posY, posX += velX, dimX, dimY);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
		updateVelocity();
	}

	void updateVelocity() {
		if ((velX + G) < 20)
			velX += G;
		else
			velX = 21;
	}
};

class Renderer {
private:
	Rectangle* rect;
	SDL_Renderer* sdl_renderer;
	int last_frame_time;
public:
	Renderer(SDL_Window* window) {
		sdl_renderer = SDL_CreateRenderer(window, -1, 0);
		if (sdl_renderer == nullptr) {
			std::cout << "Renderer could not be created! SDL_Error: %s\n", SDL_GetError();
		}
		last_frame_time = 0;

		rect = new Rectangle(0,500,100,100);
	}
	~Renderer() {
		SDL_DestroyRenderer(sdl_renderer);
		sdl_renderer = nullptr;
	}

	void render() {
		SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl_renderer);
		
		

	}

	void update() {
		
		//Should be: SDL_Delay() - easier for CPU
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + 10));
		last_frame_time = SDL_GetTicks();
		
		rect->updatePosition(sdl_renderer);
	}
};

class Window {
private:
	Renderer* renderer;
	SDL_Window* window;
	bool quit;

public:
	Window(){
		
		quit = false;

		if (SDL_Init(SDL_INIT_VIDEO) < 0){
			std::cout << "SDL_VIDEO not initalized! SDL_Error: %s\n", SDL_GetError();
			quit = true;
		}

		window = SDL_CreateWindow(
			"Konon_OOP_Project",
			SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
			WINDOW_HEIGHT, WINDOW_WIDTH,
			SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
			quit = true;
		}

		renderer = new Renderer(window);
	}

	~Window() {
		delete renderer;

		SDL_DestroyWindow(window);
		window = nullptr;

		SDL_Quit;
	}

	void simulation(){
		while (!quit) {
			//checkInput();
			renderer->update();
			renderer->render();
		}
	}
};


int main(int argc, char* args[])
{
	Window visualize;
	visualize.simulation();
	return 0;
}