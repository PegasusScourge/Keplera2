#pragma once

/* INCLUDE */

//SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//iostream
#include <iostream>

/* DECLARATIONS */
using namespace std;

//The SDL namespace for the program, contains all functions for managing sdl
namespace sdl {

	//Constant variables
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char windowName[] = "Keplera2";

	const int globalFontSize = 12;

	/* SDLText struct */
	struct SDLText {
		//Must be freed by this struct
		SDL_Texture *texture = NULL;
		int w = 0;
		int h = 0;

		//Free the texture
		void clearTexture() {
			if (texture) {
				//cout << "Imploding texture of SDLText struct" << endl;
				SDL_DestroyTexture(texture);
				texture = NULL;
			}
		}

		~SDLText() {
			clearTexture();
		}
	};

	extern TTF_Font * globalFont;

	/* Texture class */
	class SDLTexture {
		//Private members
		SDL_Texture * texture = NULL;
		bool hTexture = false;

		string name;

	public:

		SDLTexture(string);

		SDLTexture();

		/* Make sure to have a destructor to remove the texture resources after the face */
		~SDLTexture();

		/* Assigns a texture to this class when created with a default constructor */
		void assignTexture(string);

		/* Returns the raw pointer to the sdl texture, not the exactly intended for use outside of the sdl namespace */
		SDL_Texture* rawSDLTexture();

		/* Returns if we have a valid SDL_Texture in our possesion */
		bool hasValidTexture();

		string getName();
	};

	const bool vsync_enabled = false;

	/* Initialise SDL with the basic settings for the program, and create the window and surface */
	bool initSDL();

	/* Terminate SDL and clean up any resources we have used */
	void terminateSDL();

	/* Render texture function, accepts a texture object, and then two SDL_Rects that define the source dimensions
	from the texture, and the destination dimensions to the renderable surface */
	void renderTexture(SDL_Texture*, SDL_Rect*, SDL_Rect*);
	//Overload with rotational and flipping options
	void renderTexture(SDL_Texture*, SDL_Rect*, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip);

	/* Renders a texture from a SDLTexture class */
	void renderTexture(SDLTexture&, SDL_Rect*, SDL_Rect*);

	/* Clear screen function */
	void clearScreen();

	/* Finishes the current frame we are rendering and presents it to the viewer */
	void finishFrame();

	/* A utility function to load textures and return a SDL_Texture pointer */
	SDL_Texture* loadTexture(string);

	/* A utility to load a texture from a text input */
	SDLText* loadTextureFromText(string, SDL_Color);
}