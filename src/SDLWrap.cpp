//Get our header
#include "SDLWrap.h"

/* CODE */
namespace sdl {

	//Variables
	SDL_Window * appWindow = NULL;
	SDL_Surface * windowSurface = NULL;
	SDL_Renderer * windowRenderer = NULL;

	//Globally used font
	TTF_Font * globalFont = NULL;

	//Functions
	//See header for descriptions

	bool initSDL() {
		//Try to initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO < 0)) {
			//We failed to do this
			cout << "SDL failed to initialise: " << SDL_GetError() << endl;
			return false;
		}
		
		//Attempt to create a window
		appWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (appWindow == NULL) {
			//Window failed to create, so error
			cout << "SDL window failed to open: " << SDL_GetError() << endl;
			return false;
		}
		//We got a window, so get the surface from it
		windowSurface = SDL_GetWindowSurface(appWindow);

		//Attempt to create a renderer for the window
		//Use accelerated rendering
		auto hints = (vsync_enabled) ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_ACCELERATED;
		windowRenderer = SDL_CreateRenderer(appWindow, -1, hints);
		if (windowRenderer == NULL) {
			//Failed to create our renderer, so fail
			cout << "SDL renderer for the window failed to be created: " << SDL_GetError() << endl;
			return false;
		}

		//Init our Image interface
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			cout << "Failed to init IMG lib" << endl;
			return false;
		}

		//Init our TTF interface
		if (TTF_Init() == -1) {
			cout << "Failed to init TTF" << endl;
			return false;
		}
		//Load a font:
		globalFont = TTF_OpenFont("res/Arkitech Medium.ttf", globalFontSize);
		if (globalFont == NULL) {
			cout << "Failed to load default font!" << endl;
			return false;
		}

		//We got through without dying or losing anything
		//We can proceed with the game
		return true;
	}

	void terminateSDL() {
		//Destroy the renderer
		SDL_DestroyRenderer(windowRenderer);

		//Destroy window
		//This also frees the window surface. No need to free manually
		SDL_DestroyWindow(appWindow);

		//Quit SDL subsystems
		SDL_Quit();
	}

	/* ----- Rendering functions ----- */
	void finishFrame() {
		SDL_RenderPresent(windowRenderer);
	}

	void renderTexture(SDL_Texture* texture, SDL_Rect* srcDims, SDL_Rect* destDims) {
		//Check to see we won't write a null texture
		if (texture == NULL) {
			cout << "Texture that was requested to render was null" << endl;
			return;
		}
		SDL_RenderCopy(windowRenderer, texture, srcDims, destDims);
	}

	void renderTexture(SDL_Texture* texture, SDL_Rect* srcDims, SDL_Rect* destDims, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		//Check to see we won't write a null texture
		if (texture == NULL) {
			cout << "Texture that was requested to render was null" << endl;
			return;
		}
		SDL_RenderCopyEx(windowRenderer, texture, srcDims, destDims, angle, center, flip);
	}

	void renderTexture(SDLTexture& t, SDL_Rect* srcDims, SDL_Rect* destDims) {
		//Check to see that we won't write a null texture
		if (!t.hasValidTexture()) {
			cout << "Texture that was requested to render was null" << endl;
			return;
		}
		SDL_RenderCopy(windowRenderer, t.rawSDLTexture(), srcDims, destDims);
	}

	void clearScreen() {
		SDL_RenderClear(windowRenderer);
	}

	/* ----- SDL utility functions ------ */

	SDL_Texture* loadTexture(string path){
		//The final texture
		SDL_Texture * newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL){
			cout << "Unable to load image \"" << path.c_str() << "\", because: " << IMG_GetError() << endl;
		}
		else{
			//Create texture from surface we have loaded
			newTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
			if (newTexture == NULL){
				cout << "Unable to create texture from \"" << path.c_str() << "\", because: " << IMG_GetError() << endl;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	SDLText* loadTextureFromText(string text, SDL_Color textColor) {
		SDL_Texture * newTexture = NULL;
		SDLText * newText = new SDLText;

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(globalFont, text.c_str(), textColor);
		if (textSurface == NULL){
			cout << "Unable to load text surface \"" << TTF_GetError() << endl;
		}
		else {
			//Create the texture from the surface we have loaded
			newTexture = SDL_CreateTextureFromSurface(windowRenderer, textSurface);
			if (newTexture == NULL) {
				cout << "Unable to create texture from text \"" << text.c_str() << "\", because: " << IMG_GetError() << endl;
			}

			newText->w = textSurface->w;
			newText->h = textSurface->h;

			//Get rid of old loaded surface
			SDL_FreeSurface(textSurface);
		}
		
		newText->texture = newTexture;

		return newText;
	}

	/* TEXURE CLASS */
	SDLTexture::SDLTexture(string s) {
		texture = sdl::loadTexture(s);
		//Check that the texture exists
		hTexture = (texture != NULL);
		cout << "Created texture object from \"" << s.c_str() << "\"" << endl;
		name = s;
	}

	SDLTexture::SDLTexture() {
		name = "undefined";
		hTexture = false;
	}

	SDLTexture::~SDLTexture() {
		//Blow up our texture
		SDL_DestroyTexture(texture);
		texture = NULL;
		hTexture = false;
		cout << "Texture imploded: " << getName().c_str() << endl;
	}

	void SDLTexture::assignTexture(string s) {
		if (!hTexture) {
			texture = sdl::loadTexture(s);
			//Check that the texture exists
			hTexture = (texture != NULL);
			cout << "Created texture object from \"" << s.c_str() << "\"" << endl;
			name = s;
		}
		else {
			cout << "Texture class could not be reassigned: already has texture" << endl;
		}
	}

	SDL_Texture* SDLTexture::rawSDLTexture() {
		return texture;
	}

	bool SDLTexture::hasValidTexture() {
		return hTexture;
	}

	string SDLTexture::getName() {
		return name;
	}

}