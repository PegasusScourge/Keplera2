//Get our header
#include "Sprite.h"

/* CODE */
namespace sdl {

	int sprite_wizard_id_next = 0;

	/* SPRITE CLASS*/
	Sprite::Sprite(SDLTexture * texture, int mX, int mY, int MX, int MY) {
		sdlTexture = texture;

		//Give this sprite an identity
		id = "sprite_" + to_string(sprite_wizard_id_next++);
		//Init the texture information
		srcDims.x = mX;
		srcDims.y = mY;
		srcDims.w = (MX - mX);
		srcDims.h = (MY - mY);

		//Init the position data
		position.x = 0;
		position.y = 0;

		dimensions.x = 0;
		dimensions.y = 0;

		cout << "New sprite with id \"" << id << "\"" << endl;
	}

	Sprite::Sprite() {
		//Null sprite constructed
	}

	Sprite::~Sprite() {
		//Unlink from the texture
		sdlTexture = NULL;
	}

	void Sprite::render() {
		SDL_Rect destDims;
		destDims.x = (int)getPosition()->x;
		destDims.y = (int)getPosition()->y;

		//Renders based off of the desired dimensions
		destDims.w = (int)getDimensions()->x;
		destDims.h = (int)getDimensions()->y;

		//Call the render
		sdl::renderTexture(getTexture()->rawSDLTexture(), &srcDims, &destDims, getRotation(), NULL, SDL_FLIP_NONE);
	}

	void Sprite::moveTo(float a, float b) {
		position.x = a;
		position.y = b;
	}

	void Sprite::translate(float dx, float dy) {
		position.x += dx;
		position.y += dy;
	}

	void Sprite::setRotation(float a) {
		rotation = a;
	}

	SDLTexture* Sprite::getTexture() {
		return sdlTexture;
	}

	maths::Vector2D* Sprite::getPosition() {
		return &position;
	}

	float Sprite::getRotation() {
		return rotation;
	}

	SDL_Rect* Sprite::getSrcDims() {
		return &srcDims;
	}

	string Sprite::getId() {
		return id;
	}

	void Sprite::setSize(float a, float b) {
		dimensions.x = a;
		dimensions.y = b;
	}

	maths::Vector2D* Sprite::getDimensions() {
		return &dimensions;
	}

}