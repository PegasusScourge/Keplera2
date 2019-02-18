#pragma once

/* INCLUDE */

#include <string>

//SDL
#include <SDL.h>

//Get the SDL wrapper
#include "SDLWrap.h"

//Get the maths classes
#include "Maths.h"

/* DECLARATIONS */
using namespace std;

namespace sdl {

	/* Sprite def struct */
	struct SpriteDef {
		int x0;
		int y0;
		int x1;
		int y1;
		int width;
		int height;

		string name = "default";
		string textureName = "res/default.png";
	};

	class Sprite {
		//Private members
		SDL_Rect srcDims;
		maths::Vector2D position;
		maths::Vector2D dimensions;

		string id = "undefined";

		SDLTexture * sdlTexture = NULL;

		//Rotation is in degrees
		float rotation = 0.0;

	public:
		/* Std constructor, takes the dimensions of the source area of the texture (a pointer) and an id */
		Sprite(SDLTexture*, int, int, int, int);

		/* Null constructor */
		Sprite();

		/* Deconstructor for Sprite to free any resources needed, note that the SDLTexture is freed when the SDLTexture goes out of
		scope as per it's deconstructor */
		~Sprite();

		/* Render function */
		void render();

		/* set the size of the Sprite on the screen */
		void setSize(float, float);

		/* Set the rotatation of the Sprite */
		void setRotation(float);

		/* functions for placing the Sprite in space */
		void translate(float, float);
		void moveTo(float, float);

		/* Getters */
		SDL_Rect* getSrcDims();
		maths::Vector2D* getPosition();
		maths::Vector2D* getDimensions();
		float getRotation();
		SDLTexture* getTexture();

		string getId();

	};

}