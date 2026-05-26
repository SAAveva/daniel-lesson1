#include <SDL2/SDL.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Pixel;

typedef struct {
	int running;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Pixel *pixels;
	int width;
	int height;
} State;

void example1(State *state) {
	for (int y = 0;y < state->height;++y) {
		for (int x = 0;x < state->width;++x) {
			int index = y * state->width + x;
			state->pixels[index] = (Pixel) {.g = 0xff, .b = 0xff, .a = 0xff};
		}
	}

}

void init(State *state) {
	state->pixels = malloc(sizeof(Pixel) * state->width * state->height);
	state->texture = SDL_CreateTexture(
		state->renderer, 
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		state->width,
		state->height
	);
}

void _update(State *state) {
	SDL_UpdateTexture(state->texture, NULL, state->pixels, state->width);
}

void update(State *state) {
	example1(state);
	_update(state);
}

void handle_input(State *state) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
			state->running = 0;
		}
	}
}

void render_frame(State *state) {
	SDL_RenderClear(state->renderer);
	SDL_RenderCopy(state->renderer, state->texture, NULL, NULL);
	SDL_RenderPresent(state->renderer);
}

void cleanup(State *state) {
	if (state->pixels != NULL) {
		free(state->pixels);
	}
}
int main(void) {
	char *title 	= "Simple 2D effects";
	int win_width	= 800;
	int win_height	= 800;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window		= SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer	= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	State state = {
		.renderer = renderer,
		.running = 1,
		.width = win_width,
		.height = win_height,
	};
	init(&state);
	
	while (state.running) {
		handle_input(&state);
		update(&state);
		render_frame(&state);
	}

	cleanup(&state);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}
