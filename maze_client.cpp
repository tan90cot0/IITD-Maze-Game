//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2/SDL_mixer.h>                   //audio
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "coordinates.h"

#include <stdlib.h>       //client
#include<time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


using namespace std;

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 800;
int structures[num_structures][5] = {struct1, struct2, struct3, struct4, struct5, struct6, struct7, struct8, 
struct9, struct10, struct11, struct12, struct13, struct14, struct15, struct16, struct17, struct18,struct65,
struct19, struct20, struct21, struct22, struct23, struct24, struct25, struct26, struct27, struct28, struct29,
struct30, struct31, struct32, struct33, struct34, struct35, struct36, struct37, struct38, struct39, struct40,
struct41, struct42, struct43, struct44, struct45, struct46, struct47, struct48, struct49, struct50, struct51,
struct52, struct53, struct54, struct55, struct56, struct57, struct58, struct59, struct60, struct61, struct62,
struct63, struct64, struct66, struct67, struct68, struct69, struct70, struct71, struct72, struct76, struct77,
struct73, struct74, struct75, struct78, struct79, struct80, struct81, struct82, struct83, struct84, struct85,
struct86, struct87, struct88, struct89, struct90, struct91, struct92, struct93, struct94, struct95, struct96,
struct97, struct98, struct99, struct100, struct101, struct102, struct103, struct104, struct105, struct106,
struct107, struct108, struct109, struct110, struct111, struct112};



void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//A circle stucture
struct Circle
{
	int x, y;
	int r;
};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		int handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;
};

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 8;
		static const int DOT_HEIGHT = 8;

		//Maximum axis velocity of the dot
		int DOT_VEL = 1;

		//Initializes the variables
		Dot( int x, int y );

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e , Dot dot, bool yulu_mode);

		//Moves the dot and checks collision
		void move( SDL_Rect square[], Circle& circle, int n);

		//Shows the dot on the screen
		void render();

		//Gets collision circle
		Circle& getCollider();

		//The X and Y offsets of the dot
		int mPosX, mPosY;

    private:
		
		//The velocity of the dot
		int mVelX, mVelY;
		
		//Dot's collision circle
		Circle mCollider;

		//Moves the collision circle relative to the dot's offset
		void shiftColliders();
};

class BigDot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 15;
		static const int DOT_HEIGHT = 15;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 2;

		//Initializes the variables
		BigDot( int x, int y );

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( SDL_Rect square[], Circle& circle, int n);

		//Shows the dot on the screen
		void render();

		//Gets collision circle
		Circle& getCollider();

    // private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		
		//Dot's collision circle
		Circle mCollider;

		//Moves the collision circle relative to the dot's offset
		void shiftColliders();
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close(int t, int u);

SDL_Texture* loadTexture( std::string path );

//Circle/Circle collision detector
bool checkCollision( Circle& a, Circle& b );

//Circle/Box collision detector
bool checkCollision( Circle& a, SDL_Rect& b );

//Calculates distance squared between two points
double distanceSquared( int x1, int y1, int x2, int y2 );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ];

//Globally used font
TTF_Font *gFont = NULL;

//Menu texture
// LTexture gOptTexture;

//Scene textures
LTexture gTimeTextTexture1;
LTexture gTimeTextTexture2;
LTexture gTimeTextTexture3;
LTexture gTimeTextTexture4;
LTexture gTimeTextTexture5;
LTexture gTimeTextTexture6;
LTexture gTimeTextTexture7;
LTexture gTimeTextTexture8;
LTexture gTimeTextTexture9;
LTexture gTimeTextTexture10;
LTexture gTimeTextTexture11;
LTexture gTimeTextTexture12;
LTexture gTimeTextTexture13;
LTexture gTimeTextTexture14;
LTexture gTimeTextTexture15;
LTexture gTimeTextTexture16;
LTexture gTimeTextTexture17;
LTexture gTimeTextTexture18;
LTexture gTimeTextTexture19;
LTexture gTimeTextTexture20;
LTexture gTimeTextTexture21;
LTexture gTimeTextTexture22;
LTexture gTimeTextTexture23;
LTexture gTimeTextTexture24;
LTexture gTimeTextTexture25;
LTexture gTimeTextTexture26;
LTexture gTimeTextTexture27;
LTexture gTimeTextTexture28;
LTexture gTimeTextTexture29;
LTexture gTimeTextTexture30;
LTexture gTimeTextTexture31;
LTexture gTimeTextTexture32;
LTexture gPromptTextTexture1;
LTexture gPromptTextTexture2;

//Scene textures
LTexture gBigDotTexture;
LTexture gDotTexture;
LTexture gBGTexture1;
LTexture gBGTexture2;
LTexture gBGTexture3;
LTexture gBGTexture4;
LTexture gBGTexture5;
LTexture gBGTexture6;
LTexture gBGTexture7;
LTexture gBGTexture8;
LTexture gBGTexture9;
LTexture gBGTexture10;
LTexture gBGTexture11;
LTexture gBGTexture12;
LTexture gBGTexture13;
LTexture gBGTexture14;
LTexture gBGTexture15;
LTexture gBGTexture16;
LTexture gBGTexture17;
LTexture gBGTexture18;
LTexture gBGTexture19;
LTexture gBGTexture20;
LTexture gBGTexture21;
LTexture gBGTexture22;
LTexture gBGTexture23;
LTexture gBGTexture24;
LTexture gBGTexture25;
LTexture gBGTexture26;
LTexture gBGTexture27;
LTexture gBGTexture28;
LTexture gBGTexture29;
LTexture gBGTexture30;
LTexture gBGTexture31;
LTexture gBGTexture32;
LTexture gBGTexture33;
LTexture gBGTexture35;
LTexture gBGTexture34;
LTexture gBGTexture36;
LTexture gBGTexture37;
LTexture gBGTexture38;
LTexture gBGTexture39;
LTexture gBGTexture40;
LTexture gBGTexture41;
LTexture gBGTexture42;
LTexture gBGTexture43;
LTexture gBGTexture44;
LTexture gBGTexture45;
LTexture gBGTexture46;
LTexture gBGTexture47;
LTexture gBGTexture48;
LTexture gBGTexture49;
LTexture gBGTexture50;
LTexture gBGTexture51;
LTexture gBGTexture52;
LTexture gBGTexture53;
LTexture gBGTexture54;
LTexture gBGTexture55;
LTexture gBGTexture56;
LTexture gBGTexture57;
LTexture gBGTexture58;
LTexture gBGTexture59;
LTexture gBGTexture60;
LTexture gBGTexture61;
LTexture gBGTexture62;
LTexture gBGTexture63;
LTexture gBGTexture64;
LTexture gBGTexture65;
LTexture gBGTexture66;
LTexture gBGTexture67;
LTexture gBGTexture68;
LTexture gBGTexture69;
LTexture gBGTexture70;
LTexture gBGTexture71;
LTexture gBGTexture72;
LTexture gBGTexture73;
LTexture gBGTexture74;
LTexture gBGTexture75;
LTexture gBGTexture76;
LTexture gBGTexture77;
LTexture gBGTexture78;
LTexture gBGTexture79;
LTexture gBGTexture80;
LTexture gBGTexture81;
LTexture gBGTexture82;
LTexture gBGTexture83;
LTexture gBGTexture84;
LTexture gBGTexture85;
LTexture gBGTexture86;
LTexture gBGTexture87;
LTexture gBGTexture88;
LTexture gBGTexture89;
LTexture gBGTexture90;
LTexture gBGTexture91;   //menu
LTexture gBGTexture92;   //menu



SDL_Texture* gTexture = NULL;
SDL_Texture* gOptTexture = NULL;
SDL_Texture* gRuleTexture = NULL;
SDL_Texture* gModeTexture = NULL;
SDL_Texture* gMenuTexture = NULL;
SDL_Texture* gScore1Texture = NULL;
SDL_Texture* gScore2Texture = NULL;
SDL_Texture* gScore3Texture = NULL;

//The music that will be played
Mix_Music *gMusic1 = NULL;           //yulu
Mix_Music *gMusic2 = NULL;           //crow
Mix_Music *gMusic3 = NULL;           //audio
Mix_Music *gMusic4 = NULL;           //audio
Mix_Music *gMusic5 = NULL;           //audio
Mix_Music *gMusic6 = NULL;           //metal
Mix_Music *gMusic7 = NULL;           //jazz
Mix_Music *gMusic8 = NULL;           //rock
Mix_Music *gMusic9 = NULL;           //pop
Mix_Music *gMusic10 = NULL;           //western classical
Mix_Music *gMusic11 = NULL;           //shoegaze
Mix_Music *gMusic12 = NULL;           //punjabi
Mix_Music *gMusic13 = NULL;           //retro bollywood
Mix_Music *gMusic14 = NULL;           //hindi indie
Mix_Music *gMusic15 = NULL;           //bollywood
Mix_Music *gMusic16 = NULL;				//dog
Mix_Music *gMusic17 = NULL;				//edm
Mix_Music *gMusic18 = NULL;				//old pop


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0x00, 0x01 ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		// printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

int LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )      //MOUSEMOTION
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < 50 )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > 1200 )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < 50)
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > 800)
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			return -1;
		}
		//Mouse is inside button
		else
		{
			int temp;
			if (e->type = SDL_MOUSEBUTTONDOWN && x>500 && x<790 && y>510 && y<580)
				temp = 1;
			else if (e->type = SDL_MOUSEBUTTONDOWN && x>430 && x<880 && y>600 && y<680)
				temp = 2;
			else if (e->type = SDL_MOUSEBUTTONDOWN && x>540 && x<760 && y>720 && y<780)
				temp = 3;
			else if (e->type = SDL_MOUSEBUTTONDOWN && x>120 && x<650 && y>140 && y<660)
				temp = 4;
			else if (e->type = SDL_MOUSEBUTTONDOWN && x>690 && x<1170 && y>160 && y<650)
				temp = 5;
			else
				temp = 0;
			return temp;
		}
	}
	return -1;
}
	
void LButton::render()
{
	//Show current button sprite
	// gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}

Dot::Dot( int x, int y )
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;

	//Set collision circle size
	mCollider.r = DOT_WIDTH / 2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	//Move collider relative to the circle
	shiftColliders();
}

BigDot::BigDot( int x, int y )
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;

	//Set collision circle size
	mCollider.r = DOT_WIDTH / 2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	//Move collider relative to the circle
	shiftColliders();
}

bool music = false;
bool yulu = false;

void Dot::handleEvent( SDL_Event& e , Dot dot, bool yulu_mode)
{

	if (((mPosX >=1055 && mPosX <= 1080 && mPosY >=75 && mPosY <= 105) || (mPosX >=408 && mPosX <= 458 && mPosY >=375 && mPosY <= 380) || (mPosX >=941 && mPosX <= 975 && mPosY >=290 && mPosY <= 330) || (mPosX >=205 && mPosX <= 240 && mPosY >=480 && mPosY <= 525)) && yulu == false && yulu_mode == false){       //audio
					Mix_PlayMusic( gMusic1, 0 );
					yulu = true;
	}
	if (((((mPosX <=1055 || mPosX >= 1080) || (mPosY <=75 || mPosY >= 105)) && ((mPosX >=1035 && mPosX <= 1100) && (mPosY >=55 && mPosY <= 125))) || (((mPosX <=408 || mPosX >= 458) || (mPosY <=375 || mPosY >= 380)) && ((mPosX >=388 && mPosX <= 478) && (mPosY >=355 && mPosY <= 400))) || (((mPosX <=941 || mPosX >= 975) || (mPosY <=290 || mPosY >= 330)) && ((mPosX >=921 && mPosX <= 995) && (mPosY >=270 && mPosY <= 350))) || (((mPosX <=205 || mPosX >= 240) || (mPosY <=480 || mPosY >= 525)) && ((mPosX >=185 && mPosX <= 260) && (mPosY >=460 && mPosY <= 545)))) && yulu == true){ 
					Mix_HaltMusic();
					yulu = false;
	}
	if (mPosX >=755 && mPosX <= 800 && mPosY >=360 && mPosY <= 400 && !Mix_PlayingMusic())          //audio
					Mix_PlayMusic( gMusic2, 0 );
	if (mPosX >=360 && mPosX <= 505 && mPosY >=105 && mPosY <= 200 && !Mix_PlayingMusic())          //audio
					Mix_PlayMusic( gMusic16, 0 );
	if (mPosX >=70 && mPosX <= 130 && mPosY >=380 && mPosY <= 440 && !Mix_PlayingMusic())          //audio
					Mix_PlayMusic( gMusic3, 0 );
	if (mPosX >=70 && mPosX <= 130 && mPosY >=120 && mPosY <= 150 && !Mix_PlayingMusic())          //audio
					Mix_PlayMusic( gMusic5, 0 );
	// if ((mPosX <=1055 || mPosX >= 1080) && (mPosY <=75 || mPosY >= 105) && mPosX >=1035 && mPosX <= 1100 && mPosY >=55 && mPosY <= 125)  
					// Mix_HaltMusic();
	if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE && music == false)
					music = true;
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_1 && music == true){  //metal
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic6, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_2 && music == true){  //jazz
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic7, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_3 && music == true){  //rock
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic8, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_4 && music == true){  //pop
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic9, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_5 && music == true){  //western classical
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic10, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_6 && music == true){  //shoegaze
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic11, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_7 && music == true){  //punjabi
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic12, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_8 && music == true){  //retro bollywood
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic13, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_9 && music == true){  //hindi indie
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic14, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_0 && music == true){  //bollywood
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic15, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_MINUS && music == true){  //edm
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic17, 0);
	}
	else if (mPosX >= 270 && mPosX <= 330 && mPosY >= 480 && mPosY <= 520 && e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_EQUALS && music == true){  //old pop
					Mix_HaltMusic();
					Mix_PlayMusic (gMusic18, 0);
	}
	if (((mPosX <=270 || mPosX >= 330) || (mPosY <=480 || mPosY >= 520)) && mPosX >=250 && mPosX <= 350 && mPosY >=460 && mPosY <= 540) { 
					Mix_HaltMusic();
					music = false;
	}
	
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
			case SDLK_s:  mVelY -= DOT_VEL;	mVelX += DOT_VEL; break;
			case SDLK_a:  mVelY -= DOT_VEL;	mVelX -= DOT_VEL; break;
			case SDLK_z:  mVelY += DOT_VEL;	mVelX -= DOT_VEL; break;
			case SDLK_x:  mVelY += DOT_VEL;	mVelX += DOT_VEL; break;

        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
			case SDLK_s:  mVelY += DOT_VEL;	mVelX -= DOT_VEL; break;
			case SDLK_a:  mVelY += DOT_VEL;	mVelX += DOT_VEL; break;
			case SDLK_z:  mVelY -= DOT_VEL;	mVelX += DOT_VEL; break;
			case SDLK_x:  mVelY -= DOT_VEL;	mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move( SDL_Rect square[], Circle& circle, int n)
{

	

    //Move the dot left or right
    mPosX += mVelX;
	shiftColliders();

    //If the dot collided or went too far to the left or right
	bool x = false;
	for(int i = 0;i<n;i++)
		x = x || checkCollision( mCollider, square[i]);

	if( ( mPosX - mCollider.r < 0 ) || ( mPosX + mCollider.r > SCREEN_WIDTH ) || x )//|| checkCollision( mCollider, circle ) )
    {
        //Move back
        mPosX -= mVelX;
		shiftColliders();
    }

    //Move the dot up or down
    mPosY += mVelY;
	shiftColliders();

	for(int i = 0;i<n;i++)
		x = x || checkCollision( mCollider, square[i]);

    //If the dot collided or went too far up or down
    if( ( mPosY - mCollider.r < 0 ) || ( mPosY + mCollider.r > SCREEN_HEIGHT ) || x)// || checkCollision( mCollider, circle ) )
    {
        //Move back
        mPosY -= mVelY;
		shiftColliders();
    }
}

void Dot::render()
{
    //Show the dot
	//gDotTexture.render( mPosX - mCollider.r, mPosY - mCollider.r );
}

void BigDot::render()
{
    //Show the dot
	gBigDotTexture.render( mPosX - mCollider.r, mPosY - mCollider.r );
}

Circle& Dot::getCollider()
{
	return mCollider;
}

Circle& BigDot::getCollider()
{
	return mCollider;
}

void Dot::shiftColliders()
{
	//Align collider to center of dot
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void BigDot::shiftColliders()
{
	//Align collider to center of dot
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "IIT Delhi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 255 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )        //audio
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	/*if( !gBigDotTexture.loadFromFile( "images/dot_medium.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}*/
	gTexture = loadTexture( "images/bg.png" );
	gOptTexture = loadTexture( "images/home.png" );
	gRuleTexture = loadTexture( "images/rules.png" );
	gModeTexture = loadTexture( "images/mode.png" );
	gMenuTexture = loadTexture( "images/menu.png" );
	gScore1Texture = loadTexture( "images/server.png" );
	gScore2Texture = loadTexture( "images/client.png" );
	gScore3Texture = loadTexture( "images/solo.png" );

    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	if( gOptTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	if( gRuleTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	if( gModeTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	if( gMenuTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	//Load background texture
	if( !gBGTexture1.loadFromFile( "images/hospital.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture2.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture3.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture4.loadFromFile( "images/library.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture5.loadFromFile( "images/lhc.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture6.loadFromFile( "images/sprites/first.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture7.loadFromFile( "images/sprites/second.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture8.loadFromFile( "images/sprites/third.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture9.loadFromFile( "images/sprites/fourth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture10.loadFromFile( "images/sprites/fifth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture11.loadFromFile( "images/sprites/sixth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture12.loadFromFile( "images/sprites/seventh.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture13.loadFromFile( "images/sprites/eighth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture14.loadFromFile( "images/sprites/zeroth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture15.loadFromFile( "images/sprites/flipped/first.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture16.loadFromFile( "images/sprites/flipped/second.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture17.loadFromFile( "images/sprites/flipped/third.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBGTexture18.loadFromFile( "images/sprites/flipped/fourth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture19.loadFromFile( "images/sprites/flipped/fifth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture20.loadFromFile( "images/sprites/flipped/sixth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture21.loadFromFile( "images/sprites/flipped/seventh.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture22.loadFromFile( "images/sprites/flipped/eighth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture23.loadFromFile( "images/delhi16.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture24.loadFromFile( "images/rajdhani.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture25.loadFromFile( "images/amul.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture26.loadFromFile( "images/sac.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture27.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture28.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture29.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture30.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture31.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture32.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture33.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture34.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture35.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture36.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture37.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture38.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture39.loadFromFile( "images/yulu45.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture40.loadFromFile( "images/yulu-45.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture41.loadFromFile( "images/yulu-45.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture42.loadFromFile( "images/yulu_ride.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture43.loadFromFile( "images/yulu_rideL.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture44.loadFromFile( "images/hostel.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture45.loadFromFile( "images/bharti.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture46.loadFromFile( "images/ground.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture47.loadFromFile( "images/circle.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture48.loadFromFile( "images/pharmacy.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture49.loadFromFile( "images/circle.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture50.loadFromFile( "images/circle.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture51.loadFromFile( "images/prof/first.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture52.loadFromFile( "images/prof/second.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture53.loadFromFile( "images/prof/third.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture54.loadFromFile( "images/prof/fourth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture55.loadFromFile( "images/prof/fifth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture56.loadFromFile( "images/prof/sixth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture57.loadFromFile( "images/prof/seventh.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture58.loadFromFile( "images/prof/eighth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture59.loadFromFile( "images/prof/flipped/first.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture60.loadFromFile( "images/prof/flipped/second.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture61.loadFromFile( "images/prof/flipped/third.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture62.loadFromFile( "images/prof/flipped/fourth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture63.loadFromFile( "images/prof/flipped/fifth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture64.loadFromFile( "images/prof/flipped/sixth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture65.loadFromFile( "images/prof/flipped/seventh.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture66.loadFromFile( "images/prof/flipped/eighth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture67.loadFromFile( "images/phone/phone_0.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture68.loadFromFile( "images/phone/phone_1.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture69.loadFromFile( "images/phone/phone_2.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture70.loadFromFile( "images/phone/phone_3.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture71.loadFromFile( "images/phone/phone_4.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture72.loadFromFile( "images/phone/phone_5.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture73.loadFromFile( "images/biotech.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture74.loadFromFile( "images/main.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture75.loadFromFile( "images/oat.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture76.loadFromFile( "images/tennis.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture77.loadFromFile( "images/tennis.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture78.loadFromFile( "images/volley.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture79.loadFromFile( "images/volley.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture80.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture81.loadFromFile( "images/yulu90.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture82.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture83.loadFromFile( "images/yulu-45.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture84.loadFromFile( "images/yulu90.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture85.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture86.loadFromFile( "images/sprite2/zeroth.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture87.loadFromFile( "images/atm.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture88.loadFromFile( "images/prof_msg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture89.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture90.loadFromFile( "images/yulu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture91.loadFromFile( "images/menu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gBGTexture92.loadFromFile( "images/menuR.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	

	//Load dot texture
	if( !gDotTexture.loadFromFile( "images/dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	gMusic1 = Mix_LoadMUS( "audio/YuluZone2.wav" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic2 = Mix_LoadMUS( "audio/Crow.wav" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic3 = Mix_LoadMUS( "audio/CuteBird.wav" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic4 = Mix_LoadMUS( "audio/Vehicle1.wav" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic5 = Mix_LoadMUS( "audio/Vehicle2.wav" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic6 = Mix_LoadMUS( "audio/Master_of_Puppets.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic7 = Mix_LoadMUS( "audio/Dave_Brubeck_Take_Five.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic8 = Mix_LoadMUS( "audio/When_the_Levee_Breaks.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic9 = Mix_LoadMUS( "audio/Aqua_Barbie_Girl.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic10 = Mix_LoadMUS( "audio/Chopin_Nocturne_op.9_No.2.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic11 = Mix_LoadMUS( "audio/Fade_Into_You.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic12 = Mix_LoadMUS( "audio/Harrdy_Sandhu_Dance_Like_Lauren_Gottlieb_Jaani_B_Praak.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic13 = Mix_LoadMUS( "audio/Mere_Sapno_Ki_Rani.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic14 = Mix_LoadMUS( "audio/The_Local_Train_Choo_Lo.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic15 = Mix_LoadMUS( "audio/Maahi_Ve_Udit_Narayan.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic16 = Mix_LoadMUS( "audio/Bark.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic17 = Mix_LoadMUS( "audio/Avicii_Waiting_For_Love.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusic18 = Mix_LoadMUS( "audio/Michael_Jackson_Billie_Jean.mp3" );
	if( gMusic1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gFont = TTF_OpenFont( "images/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
		
		//Load prompt texture
		if( !gPromptTextTexture1.loadFromRenderedText( " ", textColor ) )
		{
			printf( "Unable to render prompt texture!\n" );
			success = false;
		}
		if( !gPromptTextTexture2.loadFromRenderedText( " ", textColor ) )
		{
			printf( "Unable to render prompt texture!\n" );
			success = false;
		}
	}
	//Set buttons in corners
	gButtons[ 0 ].setPosition( 0, 0 );
	gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
	gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
	gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );

	return success;
}

void close(int t, int u)
{
	//Free loaded images
	// gOptTexture.free();
	gDotTexture.free();
	gBigDotTexture.free();
	gBGTexture1.free();
	gBGTexture2.free();
	gBGTexture3.free();
	gBGTexture4.free();
	gBGTexture5.free();
	gBGTexture6.free();
	gBGTexture7.free();
	gBGTexture8.free();
	gBGTexture9.free();
	gBGTexture10.free();
	gBGTexture11.free();
	gBGTexture12.free();
	gBGTexture13.free();
	gBGTexture14.free();
	gBGTexture15.free();
	gBGTexture16.free();
	gBGTexture17.free();
	gBGTexture18.free();
	gBGTexture19.free();
	gBGTexture20.free();
	gBGTexture21.free();
	gBGTexture22.free();
	gBGTexture23.free();
	gBGTexture24.free();
	gBGTexture25.free();
	gBGTexture26.free();
	gBGTexture27.free();
	gBGTexture28.free();
	gBGTexture29.free();
	gBGTexture30.free();
	gBGTexture31.free();
	gBGTexture32.free();
	gBGTexture33.free();
	gBGTexture34.free();
	gBGTexture35.free();
	gBGTexture36.free();
	gBGTexture37.free();
	gBGTexture38.free();
	gBGTexture39.free();
	gBGTexture40.free();
	gBGTexture41.free();
	gBGTexture42.free();
	gBGTexture43.free();
	gBGTexture44.free();
	gBGTexture45.free();
	gBGTexture46.free();
	gBGTexture47.free();
	gBGTexture48.free();
	gBGTexture49.free();
	gBGTexture50.free();
	gBGTexture51.free();
	gBGTexture52.free();
	gBGTexture53.free();
	gBGTexture54.free();
	gBGTexture55.free();
	gBGTexture56.free();
	gBGTexture57.free();
	gBGTexture58.free();
	gBGTexture59.free();
	gBGTexture60.free();
	gBGTexture61.free();
	gBGTexture62.free();
	gBGTexture63.free();
	gBGTexture64.free();
	gBGTexture65.free();
	gBGTexture66.free();
	gBGTexture67.free();
	gBGTexture68.free();
	gBGTexture69.free();
	gBGTexture70.free();
	gBGTexture71.free();
	gBGTexture72.free();
	gBGTexture73.free();
	gBGTexture74.free();
	gBGTexture75.free();
	gBGTexture76.free();
	gBGTexture77.free();
	gBGTexture78.free();
	gBGTexture79.free();
	gBGTexture80.free();
	gBGTexture81.free();
	gBGTexture82.free();
	gBGTexture83.free();
	gBGTexture84.free();
	gBGTexture85.free();
	gBGTexture86.free();
	gBGTexture87.free();
	gBGTexture88.free();
	gBGTexture89.free();
	gBGTexture90.free();
	


	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	Mix_FreeMusic( gMusic1 );          //audio
	gMusic1 = NULL;
	Mix_FreeMusic( gMusic2 );          //audio
	gMusic2 = NULL;
	Mix_FreeMusic( gMusic3 );          //audio
	gMusic3 = NULL;
	Mix_FreeMusic( gMusic4 );          //audio
	gMusic4 = NULL;
	Mix_FreeMusic( gMusic5 );          //audio
	gMusic5 = NULL;
	Mix_FreeMusic( gMusic6 );          //audio
	gMusic6 = NULL;
	Mix_FreeMusic( gMusic7 );          //audio
	gMusic7 = NULL;
	Mix_FreeMusic( gMusic8 );          //audio
	gMusic8 = NULL;
	Mix_FreeMusic( gMusic9 );          //audio
	gMusic9 = NULL;
	Mix_FreeMusic( gMusic10 );          //audio
	gMusic10 = NULL;
	Mix_FreeMusic( gMusic11 );          //audio
	gMusic11 = NULL;
	Mix_FreeMusic( gMusic12 );          //audio
	gMusic12 = NULL;
	Mix_FreeMusic( gMusic13 );          //audio
	gMusic13 = NULL;
	Mix_FreeMusic( gMusic14 );          //audio
	gMusic14 = NULL;
	Mix_FreeMusic( gMusic15 );          //audio
	gMusic15 = NULL;
	Mix_FreeMusic( gMusic16 );          //audio
	gMusic16 = NULL;
	Mix_FreeMusic( gMusic17 );          //audio
	gMusic17 = NULL;
	Mix_FreeMusic( gMusic18 );          //audio
	gMusic18 = NULL;


		gTimeTextTexture1.free();
	gTimeTextTexture2.free();
	gTimeTextTexture3.free();
	gTimeTextTexture4.free();
	gTimeTextTexture5.free();
	gTimeTextTexture6.free();
	gTimeTextTexture7.free();
	gTimeTextTexture8.free();
	gTimeTextTexture9.free();
	gTimeTextTexture10.free();
	gTimeTextTexture11.free();
	gTimeTextTexture12.free();
	gTimeTextTexture13.free();
	gTimeTextTexture14.free();
	gTimeTextTexture15.free();
	gTimeTextTexture16.free();
	gTimeTextTexture17.free();
	gTimeTextTexture18.free();
	gTimeTextTexture19.free();
	gTimeTextTexture20.free();
	gTimeTextTexture21.free();
	gTimeTextTexture22.free();
	gTimeTextTexture23.free();
	gTimeTextTexture24.free();
	gTimeTextTexture25.free();
	gTimeTextTexture26.free();
	gTimeTextTexture27.free();
	gTimeTextTexture28.free();
	gTimeTextTexture29.free();
	gTimeTextTexture30.free();
	gTimeTextTexture31.free();
	gTimeTextTexture32.free();
	gPromptTextTexture1.free();
	gPromptTextTexture2.free();


	if (t == 3){
		SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gScore3Texture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
	}
	else if (t==1){
		SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gScore1Texture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
	}

	else {
		SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gScore2Texture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
	}
	gTimeTextTexture12.render(  500, 200 );	//score 
	if(t!=3)
		gTimeTextTexture13.render(  700, 200 ); // score2
	

	SDL_Event e;
	bool quit = false;
	while (!quit){
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

			}
	SDL_DestroyTexture(gScore1Texture);
			gScore1Texture = NULL;
	SDL_DestroyTexture(gScore2Texture);
			gScore2Texture = NULL;
	SDL_DestroyTexture(gScore3Texture);
			gScore3Texture = NULL;

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();            //audio
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


bool checkCollision( Circle& a, Circle& b )
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) )
        //The circles have collided
        return true;
    //If not
    return false;
}

bool checkCollision( Circle& a, SDL_Rect& b )
{
    //Closest point on collision box
    int cX, cY;

    //Find closest x offset
    if( a.x < b.x )
        cX = b.x;
    else if( a.x > b.x + b.w )
        cX = b.x + b.w;
    else
        cX = a.x;

    //Find closest y offset
    if( a.y < b.y )
        cY = b.y;
    else if( a.y > b.y + b.h )
        cY = b.y + b.h;
    else
        cY = a.y;

    //If the closest point is inside the circle
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
        //This box and the circle have collided
        return true;

    //If the shapes have not collided
    return false;
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;
    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int
SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void make_structures(int structures[num_structures][5], SDL_Rect wall[])
{
	int cumsum[num_structures+1];
	cumsum[0] = 0;
	for(int i = 0;i<num_structures;i++)
	{
		int sum = 0;
		for(int j = 0;j<=i;j++)
			sum+=structures[j][2];
		cumsum[i+1] = sum;
	}

	for(int j = 0;j<num_structures;j++)
	{
		for(int i = 0;i<structures[j][2];i++)
		{
			wall[i + cumsum[j]].x = structures[j][0] - i*structures[j][3];
			wall[i + cumsum[j]].y = structures[j][1] + i*structures[j][4];
			wall[i + cumsum[j]].w = structures[j][3];
			wall[i + cumsum[j]].h = structures[j][4];
		}
	}
}

int last_yulu_state = 0;
void character_sprite(SDL_Event& e, int time, SDL_Rect& camera6, SDL_Rect& camera7
, SDL_Rect& camera8, SDL_Rect& camera9, SDL_Rect& camera10, SDL_Rect& camera11
, SDL_Rect& camera12, SDL_Rect& camera13, SDL_Rect& camera14,SDL_Rect& camera15
, SDL_Rect& camera16, SDL_Rect& camera17, SDL_Rect& camera18, SDL_Rect& camera19
, SDL_Rect& camera20, SDL_Rect& camera21, SDL_Rect& camera22, Dot dot, bool yulu_mode, 
SDL_Rect& camera42, SDL_Rect& camera43)
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
			case SDLK_a:
			case SDLK_z:
			case SDLK_DOWN:
            case SDLK_LEFT: if(yulu_mode == true)
							{
								gBGTexture43.render( dot.mPosX - 30, dot.mPosY - 55, &camera43 );		//yulu ride
								last_yulu_state = -1;
							}
								
							else
							{
							if((time%72)/9==0)
								gBGTexture6.render( dot.mPosX - 30, dot.mPosY - 80, &camera6 );
							else if((time%72)/9==1)
								gBGTexture7.render( dot.mPosX - 30, dot.mPosY - 80, &camera7 );
							else if((time%72)/9==2)
								gBGTexture8.render( dot.mPosX - 30, dot.mPosY - 80, &camera8 );
							else if((time%72)/9==3)
								gBGTexture9.render( dot.mPosX - 30, dot.mPosY - 80, &camera9 );
							else if((time%72)/9==4)
								gBGTexture10.render( dot.mPosX - 30, dot.mPosY - 80, &camera10 );
							else if((time%72)/9==5)
								gBGTexture11.render( dot.mPosX - 30, dot.mPosY - 80, &camera11 );
							else if((time%72)/9==6)
								gBGTexture12.render( dot.mPosX - 30, dot.mPosY - 80, &camera12 );
							else
								gBGTexture13.render( dot.mPosX - 30, dot.mPosY - 80, &camera13 ); 
							
							}break;
			case SDLK_UP:
			case SDLK_s:
			case SDLK_x:
			
			case SDLK_RIGHT: if(yulu_mode == true)
								gBGTexture42.render( dot.mPosX - 30, dot.mPosY - 55, &camera42 );		//yulu ride
							else
							{
							if((time%72)/9==0)
								gBGTexture15.render( dot.mPosX - 30, dot.mPosY - 80, &camera15 );
							else if((time%72)/9==1)
								gBGTexture16.render( dot.mPosX - 30, dot.mPosY - 80, &camera16 );
							else if((time%72)/9==2)
								gBGTexture17.render( dot.mPosX - 30, dot.mPosY - 80, &camera17 );
							else if((time%72)/9==3)
								gBGTexture18.render( dot.mPosX - 30, dot.mPosY - 80, &camera18 );
							else if((time%72)/9==4)
								gBGTexture19.render( dot.mPosX - 30, dot.mPosY - 80, &camera19 );
							else if((time%72)/9==5)
								gBGTexture20.render( dot.mPosX - 30, dot.mPosY - 80, &camera20 );
							else if((time%72)/9==6)
								gBGTexture21.render( dot.mPosX - 30, dot.mPosY - 80, &camera21 );
							else
								gBGTexture22.render( dot.mPosX - 30, dot.mPosY - 80, &camera22 ); 
							break;
							}
        }
    }
	else
		if(yulu_mode == true)
		{
			if(last_yulu_state == -1)
				gBGTexture43.render( dot.mPosX - 30, dot.mPosY - 55, &camera43 );		//yulu ride
			else
				gBGTexture42.render( dot.mPosX - 30, dot.mPosY - 55, &camera42 );		//yulu ride
		}
			
		else
			gBGTexture14.render( dot.mPosX - 30, dot.mPosY - 80, &camera14 );
}


void prof_sprite(int time, SDL_Rect& camera51, SDL_Rect& camera52
, SDL_Rect& camera53, SDL_Rect& camera54, SDL_Rect& camera55, SDL_Rect& camera56
, SDL_Rect& camera57, SDL_Rect& camera58, SDL_Rect& camera59,SDL_Rect& camera60
, SDL_Rect& camera61, SDL_Rect& camera62, SDL_Rect& camera63, SDL_Rect& camera64
, SDL_Rect& camera65, SDL_Rect& camera66, Dot dot, bool forward)
{
	if(forward == false)
	{
		if((time%72)/9==0)
			gBGTexture51.render( dot.mPosX - 30, dot.mPosY - 80, &camera51 );
		else if((time%72)/9==1)
			gBGTexture52.render( dot.mPosX - 30, dot.mPosY - 80, &camera52 );
		else if((time%72)/9==2)
				gBGTexture53.render( dot.mPosX - 30, dot.mPosY - 80, &camera53 );
		else if((time%72)/9==3)
				gBGTexture54.render( dot.mPosX - 30, dot.mPosY - 80, &camera54 );
		else if((time%72)/9==4)
				gBGTexture55.render( dot.mPosX - 30, dot.mPosY - 80, &camera55 );
		else if((time%72)/9==5)
				gBGTexture56.render( dot.mPosX - 30, dot.mPosY - 80, &camera56 );
		else if((time%72)/9==6)
				gBGTexture57.render( dot.mPosX - 30, dot.mPosY - 80, &camera57 );
		else
				gBGTexture58.render( dot.mPosX - 30, dot.mPosY - 80, &camera58 ); 
	}
	else
	{
		if((time%72)/9==0)
			gBGTexture59.render( dot.mPosX - 30, dot.mPosY - 80, &camera59 );
		else if((time%72)/9==1)
			gBGTexture60.render( dot.mPosX - 30, dot.mPosY - 80, &camera60 );
		else if((time%72)/9==2)
			gBGTexture61.render( dot.mPosX - 30, dot.mPosY - 80, &camera61 );
		else if((time%72)/9==3)
			gBGTexture62.render( dot.mPosX - 30, dot.mPosY - 80, &camera62 );
		else if((time%72)/9==4)
			gBGTexture63.render( dot.mPosX - 30, dot.mPosY - 80, &camera63 );
		else if((time%72)/9==5)
			gBGTexture64.render( dot.mPosX - 30, dot.mPosY - 80, &camera64 );
		else if((time%72)/9==6)
			gBGTexture65.render( dot.mPosX - 30, dot.mPosY - 80, &camera65 );
		else
			gBGTexture66.render( dot.mPosX - 30, dot.mPosY - 80, &camera66 ); 
	}
}

pair<int,bool> prof_path(int constrained_var, int path_var, int constraint, int path_lower_bound, int path_upper_bound, bool forward)
{
	if(constrained_var==constraint)
		{
			if(path_var+1>=path_upper_bound)
			{
				path_var = path_var - 1;
				forward = false;
			}
			else if(path_var-1<=path_lower_bound)
			{
				path_var = path_var + 1;
				forward = true;
			}
			else if(forward == true)
				path_var = path_var+1;
			else
				path_var = path_var-1;
		}
	return {path_var,forward};
}

int game_over(int foodie, int fitness, int nerd, int health, int money)
{
	int a = rand()%5;
	int b = rand()%5;
	int c = rand()%5;
	int d = rand()%5;
	int e = rand()%5;
	double score = (a*foodie + b*fitness + c*nerd + d*health * e*money)/(a+b+c+d+e);
	return score;
}

int main( int argc, char* argv[] )
{
	//Start up SDL and create window

	srand(time(0));

	int temp;
	int score = 0;
	int score2 = 0;


	//Current time start time
			int time;
			Uint32 startTime = -504000;
			Uint32 startTime_nerd = 0;
			Uint32 startTime_fitness = 0;
			Uint32 startTime_foodie = 0;
			bool entered_nerd = false;
			bool entered_fitness = false;
			bool entered_foodie = false;
			int nerd_time = 0;
			int social_time = 0;
			int fitness_time = 0;
			int foodie_time = 0;
			int leftover_nerd = 0;
			int leftover_fitness = 0;
			int leftover_foodie = 0;
			int health = 100;
			bool health_dec = false;
			bool yulu = false;
			int yulu_start_time = 0;
			int money = 500;
			int yulu_end_time = 0;
			bool yulu_mode = false;
			bool transaction = false;
			bool menu = false;
			bool gameover = false;
			int start_timer = 0;
			int prof_collide = 0;
			bool main_done = false;
			bool lhc_done = false;
			int depression = 0;
			int price_deducted = 0;
			bool atm_visited = false;

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			SDL_Color textColor = { 0, 0, 0, 255 };

			//In memory text stream
			std::stringstream timeText1;
			std::stringstream timeText2;
			std::stringstream timeText3;
			std::stringstream timeText4;
			std::stringstream timeText5;
			std::stringstream timeText6;
			std::stringstream timeText7;
			std::stringstream timeText8;
			std::stringstream timeText9;
			std::stringstream timeText10;
			std::stringstream timeText11;
			std::stringstream timeText12;
			std::stringstream timeText13;
			std::stringstream timeText14;
			std::stringstream timeText15;
			std::stringstream timeText16;
			std::stringstream timeText17;
			std::stringstream timeText18;
			std::stringstream timeText19;
			std::stringstream timeText20;
			std::stringstream timeText21;
			std::stringstream timeText22;
			std::stringstream timeText23;
			std::stringstream timeText24;
			std::stringstream timeText25;
			std::stringstream timeText26;
			std::stringstream timeText27;
			std::stringstream timeText28;
			std::stringstream timeText29;
			std::stringstream timeText30;
			std::stringstream timeText31;
			std::stringstream timeText32;
			//The dot that will be moving around on the screen
			Dot dot(init_x + x_offset, init_y + y_offset);
			Dot dot2(init_x + x_offset, init_y + y_offset);
			Dot dot3(600, 69);
			// BigDot otherDot( himadri_circle_x + x_offset, himadri_circle_y + y_offset);
			BigDot otherDot( 200, himadri_circle_y + y_offset);

			for(int i = 0;i<num_structures;i++)
				structures[i][1]+=y_offset;
			for(int i = 0;i<num_structures;i++)
				structures[i][0]+=x_offset;
			

			while(!quit){
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
						// close(sockfd);
						goto label1;
					}

					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
						temp = gButtons[ i ].handleEvent( &e );
						if (temp == 1)
							goto label1;
						else if (temp == 2)
							goto label1;
					}

					//Handle input for the dot
					// dot.handleEvent( e , dot);
				}
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gOptTexture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
			}
			label1:	SDL_DestroyTexture(gOptTexture);
			gOptTexture = NULL;
			if (e.type == SDL_QUIT)
				goto label5;
			if (temp == 1)
				goto label3;
			
			quit = false;

			while(!quit){
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gRuleTexture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
						// close(sockfd);
						goto label2;
					}

					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
						int temp = gButtons[ i ].handleEvent( &e );
						if (temp == 3)
							goto label2;
					}

					//Handle input for the dot
					// dot.handleEvent( e , dot);
				}
				// SDL_RenderClear( gRenderer );
				// SDL_RenderCopy( gRenderer, gRuleTexture, NULL, NULL ); 
				// SDL_RenderPresent( gRenderer );
			}
			label2:	SDL_DestroyTexture(gRuleTexture);
			gRuleTexture = NULL;
			if (e.type == SDL_QUIT)
				goto label5;
			
			label3: quit = false;

			while (!quit){
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
						// close(sockfd);
						goto label4;
					}

					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
						temp = gButtons[ i ].handleEvent( &e );
						if (temp == 4)               //single
							goto label4;
						else if (temp == 5)          //multi
							goto label4;
					}

					//Handle input for the dot
					// dot.handleEvent( e , dot);
				}
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy( gRenderer, gModeTexture, NULL, NULL ); 
				SDL_RenderPresent( gRenderer );
			}
			label4:	SDL_DestroyTexture(gModeTexture);
			gModeTexture = NULL;
			if (e.type == SDL_QUIT)
				goto label5;

			quit = false;

			int sockfd, portno, n;
    		struct sockaddr_in serv_addr;
    		struct hostent *server;

			int buffer[256];
			
			if (temp == 5){
				if (argc < 3) {
					fprintf(stderr,"usage %s hostname port\n", argv[0]);
					exit(0);
				}
				portno = atoi(argv[2]);
				sockfd = socket(AF_INET, SOCK_STREAM, 0);
				if (sockfd < 0) 
					error("ERROR opening socket");
				server = gethostbyname(argv[1]);
				if (server == NULL) {
					fprintf(stderr,"ERROR, no such host\n");
					exit(0);
				}
				bzero((char *) &serv_addr, sizeof(serv_addr));
				serv_addr.sin_family = AF_INET;
				bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
				serv_addr.sin_port = htons(portno);
				if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
					error("ERROR connecting");
			}
			int x = rand()%750 + 50;
			int y = 365;
			
			bool forward = true;
			bool move_x = true;
			//While application is running
			while( !quit )
			{
				bool yulu_gate = dot.mPosX >=1055 && dot.mPosX <= 1080 && dot.mPosY >=75 && dot.mPosY <= 105;
				bool yulu_sac = dot.mPosX >=180 && dot.mPosX <= 240 && dot.mPosY >=480 && dot.mPosY <= 600;
				bool yulu_ground = dot.mPosX >=578 && dot.mPosX <= 628 && dot.mPosY >=375 && dot.mPosY <= 380;
				bool yulu_rajdhani = dot.mPosX >=408 && dot.mPosX <= 458 && dot.mPosY >=375 && dot.mPosY <= 380;
				bool yulu_lib = dot.mPosX >=750 && dot.mPosX <= 777 && dot.mPosY >=220 && dot.mPosY <= 240;
				bool yulu_nilgiri = dot.mPosX >=60 && dot.mPosX <= 90 && dot.mPosY >=550 && dot.mPosY <= 580;
				bool yulu_jwala = dot.mPosX >=75 && dot.mPosX <= 90 && dot.mPosY >=20 && dot.mPosY <=60;
				bool yulu_satpura = dot.mPosX >=395 && dot.mPosX <= 435 && dot.mPosY >=180 && dot.mPosY <= 200;
				bool yulu_himadri = dot.mPosX >=1250 && dot.mPosX <= 1275 && dot.mPosY >=20 && dot.mPosY <= 58;
				bool yulu_lhc = dot.mPosX >=941 && dot.mPosX <= 1000 && dot.mPosY >=290 && dot.mPosY <= 345;

				bool yulu_zone = yulu_gate || yulu_sac || yulu_ground || yulu_lhc || yulu_rajdhani
				||yulu_lib || yulu_nilgiri || yulu_jwala || yulu_satpura || yulu_himadri;

				bool at_kailash = dot.mPosX>1160 && dot.mPosX<1185 && dot.mPosY > 120 && dot.mPosY <130;
				bool at_himadri = dot.mPosX>1260 && dot.mPosX<1270 && dot.mPosY > 50 && dot.mPosY <75;
				bool at_lhc = dot.mPosX>970 && dot.mPosX<1060 && dot.mPosY > 315 && dot.mPosY <370;
				bool at_lib = dot.mPosX>805 && dot.mPosX<838 && dot.mPosY > 265 && dot.mPosY <293;
				bool at_hospital = dot.mPosX>595 && dot.mPosX<618 && dot.mPosY > 340 && dot.mPosY <360;
				bool at_rajdhani = dot.mPosX>490 && dot.mPosX<505 && dot.mPosY > 274 && dot.mPosY <291;
				bool at_amul = dot.mPosX>772 && dot.mPosX<801 && dot.mPosY > 245 && dot.mPosY <258;
				bool at_biotech = dot.mPosX>990 && dot.mPosX<1002 && dot.mPosY > 147 && dot.mPosY <161;
				bool at_pharmacy = dot.mPosX>520 && dot.mPosX<530 && dot.mPosY > 345 && dot.mPosY <360;
				bool at_sac = dot.mPosX>300 && dot.mPosX<325 && dot.mPosY > 480 && dot.mPosY <515;
				bool at_delhi16 = dot.mPosX>140 && dot.mPosX<170 && dot.mPosY > 227 && dot.mPosY <249;
				bool at_ground = dot.mPosX>530 && dot.mPosX<548 && dot.mPosY > 383 && dot.mPosY <394;
				bool at_tennis_court = dot.mPosX>167 && dot.mPosX<182 && dot.mPosY > 350 && dot.mPosY <359;
				bool at_volley_court1 = dot.mPosX> 238 && dot.mPosX< 250 && dot.mPosY > 167 && dot.mPosY <188;
				bool at_volley_court2 = dot.mPosX> 101 && dot.mPosX< 113 && dot.mPosY > 167 && dot.mPosY < 189;
				bool at_volley_court = at_volley_court1 || at_volley_court2;
				bool at_bharti = dot.mPosX>690 && dot.mPosX<720 && dot.mPosY > 270 && dot.mPosY <300;
				bool at_main = dot.mPosX> 810 && dot.mPosX<835 && dot.mPosY > 160 && dot.mPosY <190;
				bool at_rkpgate= dot.mPosX>99 && dot.mPosX<115 && dot.mPosY > 23 && dot.mPosY <35;
				bool at_jnu = dot.mPosX>80 && dot.mPosX<119 && dot.mPosY > 699 && dot.mPosY <717;
				bool at_maingate = dot.mPosX>1107 && dot.mPosX< 1156 && dot.mPosY > 32 && dot.mPosY <43;
				bool at_atm = dot.mPosX>969 && dot.mPosX< 993 && dot.mPosY > 289 && dot.mPosY <304;


				if (temp == 5){
					bzero(buffer,256);
					buffer[0] =  dot.mPosX;
					buffer[1] =  dot.mPosY;
					buffer[2] = score;
					n = write(sockfd,buffer,12);
					if (n < 0) 
						error("ERROR writing to socket");
					else
						printf("Write as client: %d %d\n",buffer[0],buffer[1]);

					
					bzero(buffer,256);
					n = read(sockfd,buffer,12);
					if (n < 0) 
						error("ERROR reading from socket");
					else
						printf("Message from server: %d %d\n",buffer[0], buffer[1]);

					dot2.mPosX = buffer[0];
					dot2.mPosY = buffer[1];
					score2 = buffer[2];
				}
				
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
						close(sockfd);
					}
					else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
					{
						printf("keydown");
						startTime = SDL_GetTicks();
					}

					//Handle input for the dot
					dot.handleEvent( e , dot, yulu_mode);
				}

				//Set the wall
				int n= 0;
				for(int i = 0;i<num_structures;i++)
					n+=structures[i][2];
				SDL_Rect wall[n];
				
				make_structures(structures, wall);

				//Move the dot and check collision
				dot.move( wall, otherDot.getCollider(), n);

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );	
				for(int i = 0;i<n;i++)	
					SDL_RenderDrawRect( gRenderer, &wall[i] );

				//Render texture to screen
				//if( e.type == SDL_KEYDOWN )
				//	if(e.key.keysym.sym ==SDLK_DOWN)
                		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL ); 

				//SDL_RenderFillCircle( gRenderer, himadri_circle_x + x_offset, himadri_circle_y + y_offset,8);
				
				//create paths inside buildings to restrict movement
				//Update screen

				//Set text to be rendered
				timeText1.str( " " );
				time = (SDL_GetTicks() - startTime)/20;
				int hours = (time/3600)%24;
				int minutes = (time/60)%60;
				int seconds = time%60;
				timeText1 << "Time: " << hours<<":"<<minutes<<":"<<seconds;
				timeText4.str( " " );
				timeText4 << "Money: " <<money;

				
				//spawn profs
				bool sac_circle = false;
				bool kara_circle = false;
				bool jwala_circle = false;
				bool vindy_circle = false;
				if(x==258 && y==365)
					sac_circle = true;
				if(x==98 && y==365)
					kara_circle = true;
				if(x==98 && y==69)
					kara_circle = true;
				if(x==258 && y==69)
					kara_circle = true;
					pair<int, bool> val;//258 and 97
					bool take_turn = rand()%2;
					if(take_turn &&(sac_circle || kara_circle || jwala_circle || vindy_circle))
					{	
						if(move_x == true)
						{
							forward = rand()%2;
							val = prof_path(x, y, x, 60, 500 , forward);
							y = val.first;
						}
						else
						{
							forward = rand()%2;
							val = prof_path(y, x, y, 50, 800, forward);
							x = val.first;
						}
						move_x = !move_x;						
					}
					else if(move_x == true)
					{
						if(y==69)
						{
							val = prof_path(y, x, y, 50, 270, forward);
							x = val.first;
							forward = val.second;
						}
						else
						{
								val = prof_path(y, x, y, 50, 800, forward);
							x = val.first;
							forward = val.second;
						}
					}
					else
					{
						if(x==258)
						{
							val = prof_path(x, y, x, 60, 500 , forward);
							y = val.first;
							forward = val.second;
						}
						else if(x==98)
						{
							val = prof_path(x, y, x, 60, 650 , forward);
							y = val.first;
							forward = val.second;
						}
					}
			
				dot3.mPosX = x;
				dot3.mPosY = y;


				//quotients
				//nerd
				if(at_lhc || at_lib)
				{
					if(entered_nerd==false)
					{
						startTime_nerd = SDL_GetTicks();
						entered_nerd = true;
					}
					else
						nerd_time = leftover_nerd + (SDL_GetTicks() - startTime_nerd)/20;
				} 
				else
				{
					if(entered_nerd==true)
					{
						leftover_nerd = nerd_time;
						entered_nerd = false;
					}
				}
				//fitness
				if(at_sac || at_ground|| at_tennis_court|| at_volley_court)
				{
					if(entered_fitness==false)
					{
						startTime_fitness = SDL_GetTicks();
						entered_fitness = true;
					}
					else
						fitness_time = leftover_fitness + (SDL_GetTicks() - startTime_fitness)/20;
				} 
				else
				{
					if(entered_fitness==true)
					{
						leftover_fitness = fitness_time;
						entered_fitness = false;
					}
				}
				//foodie
				if(at_delhi16 || at_rajdhani || at_amul)
				{
					if(entered_foodie==false)
					{
						startTime_foodie = SDL_GetTicks();
						entered_foodie = true;
					}
					else
						foodie_time = leftover_foodie + (SDL_GetTicks() - startTime_foodie)/20;
				} 
				else
				{
					if(entered_foodie==true)
					{
						leftover_foodie = foodie_time;
						entered_foodie = false;
					}
				}
				

				if(at_jnu||at_rkpgate||at_maingate)
				{
					money-=250;
					health-=1;
				}
					

				//make user use atm only once per game
				if(at_atm)
				{
					if(atm_visited==false)
						money+=500;
					atm_visited = true;
				}
					


				if(money<0)
					gameover = true;

				timeText2.str( " " );
				timeText2 << "Fitness: " <<fitness_time/100;

				timeText8.str( " " );
				timeText8 << "Nerdness: " <<nerd_time/100;

				timeText9.str( " " );
				timeText9 << "Foodie: " <<foodie_time/100;

				timeText3.str( " " );
				timeText3<<"Health: "<<health;


				if(time%1800==0 && health_dec == false)
				{
					health-=1;
					health_dec = true;
				}
				else if(time%100==0 && health_dec == true)
					health_dec = false;
					
				//7 minutes 12 seconds day


				//EDIT THIS LATER WHEN THERE ARE NO FURTHER CHANGES TO THE MAP.
				SDL_Rect camera1 = { 30,0, 80,67};
				SDL_Rect camera2 = { 0,0, 90,52};
				SDL_Rect camera3 = { 0,0, 90,52};
				SDL_Rect camera4 = { 0,0, 80,80};
				SDL_Rect camera5 = { 0,0, 100,70};
				SDL_Rect camera6 = { 0,0, 55,85};
				SDL_Rect camera7 = { 0,0, 55,85};
				SDL_Rect camera8 = { 0,0, 55,85};
				SDL_Rect camera9 = { 0,0, 55,85};
				SDL_Rect camera10 = { 0,0, 55,85};
				SDL_Rect camera11 = { 0,0, 55,85};
				SDL_Rect camera12 = { 0,0, 55,85};
				SDL_Rect camera13 = { 0,0, 55,85};
				SDL_Rect camera14 = { 0,0, 55,85};
				SDL_Rect camera15 = { 0,0, 55,85};
				SDL_Rect camera16 = { 0,0, 55,85};
				SDL_Rect camera17 = { 0,0, 55,85};
				SDL_Rect camera18 = { 0,0, 55,85};
				SDL_Rect camera19 = { 0,0, 55,85};
				SDL_Rect camera20 = { 0,0, 55,85};
				SDL_Rect camera21 = { 0,0, 55,85};
				SDL_Rect camera22 = { 0,0, 55,85};
				SDL_Rect camera23 = { 0,0, 75,75};
				SDL_Rect camera24 = { 0,0, 75,75};
				SDL_Rect camera25 = { 0,0, 30,30};
				SDL_Rect camera27 = { 0,0, 90,52};
				SDL_Rect camera26 = { 0,0, 90,90};
				SDL_Rect camera28 = { 0,0, 90,52};
				SDL_Rect camera29 = { 0,0, 90,52};
				SDL_Rect camera30 = { 0,0, 90,52};
				SDL_Rect camera31 = { 0,0, 90,52};
				SDL_Rect camera32 = { 0,0, 90,52};
				SDL_Rect camera33 = { 0,0, 90,52};
				SDL_Rect camera34 = { 0,0, 90,52};
				SDL_Rect camera35 = { 0,0, 90,52};
				SDL_Rect camera36 = { 0,0, 90,52};
				SDL_Rect camera37 = { 0,0, 90,52};
				SDL_Rect camera38 = { 0,0, 55,50};
				SDL_Rect camera39 = { 0,0, 60,60};
				SDL_Rect camera40 = { 0,0, 60,60};
				SDL_Rect camera41 = { 0,0, 60,60};
				SDL_Rect camera42 = { 0,0, 60,60};
				SDL_Rect camera43 = { 0,0, 60,60};
				SDL_Rect camera44 = { 0,0, 90,52};
				SDL_Rect camera45 = { 0,0, 50,49};
				SDL_Rect camera46 = { 0,0, 399,131};
				SDL_Rect camera47 = { 0,0, 25,25};
				SDL_Rect camera48 = { 0,0, 50,41};
				SDL_Rect camera49 = { 0,0, 25,25};
				SDL_Rect camera50 = { 0,0, 25,25};
				SDL_Rect camera51 = { 0,0, 55,85};
				SDL_Rect camera52 = { 0,0, 55,85};
				SDL_Rect camera53 = { 0,0, 55,85};
				SDL_Rect camera54 = { 0,0, 55,85};
				SDL_Rect camera55 = { 0,0, 55,85};
				SDL_Rect camera56 = { 0,0, 55,85};
				SDL_Rect camera57 = { 0,0, 55,85};
				SDL_Rect camera58 = { 0,0, 55,85};
				SDL_Rect camera59 = { 0,0, 55,85};
				SDL_Rect camera60 = { 0,0, 55,85};
				SDL_Rect camera61 = { 0,0, 55,85};
				SDL_Rect camera62 = { 0,0, 55,85};
				SDL_Rect camera63 = { 0,0, 55,85};
				SDL_Rect camera64 = { 0,0, 55,85};
				SDL_Rect camera65 = { 0,0, 55,85};
				SDL_Rect camera66 = { 0,0, 55,85};
				SDL_Rect camera67 = { 0,0, 100,200};
				SDL_Rect camera68 = { 0,0, 120,240};
				SDL_Rect camera69 = { 0,0, 120,240};
				SDL_Rect camera70 = { 0,0, 120,240};
				SDL_Rect camera71 = { 0,0, 120,240};
				SDL_Rect camera72 = { 0,0, 120,240};
				SDL_Rect camera73 = { 0,0, 130,130};
				SDL_Rect camera74 = { 0,0, 195,185};
				SDL_Rect camera75 = { 0,0, 80,78};
				SDL_Rect camera76 = { 0,0, 39,80};
				SDL_Rect camera77 = { 0,0, 39,80};
				SDL_Rect camera78 = { 0,0, 50,79};
				SDL_Rect camera79 = { 0,0, 50,79};
				SDL_Rect camera80 = { 0,0, 55,50};
				SDL_Rect camera81 = { 0,0, 50,55};
				SDL_Rect camera82 = { 0,0, 55,50};
				SDL_Rect camera83 = { 0,0, 60,60};
				SDL_Rect camera84 = { 0,0, 50,55};
				SDL_Rect camera85 = { 0,0, 50,55};
				SDL_Rect camera86 = { 0,0, 55,85};
				SDL_Rect camera87 = { 0,0, 40,40};
				SDL_Rect camera88 = { 0,0, 250,154};
				SDL_Rect camera91 = { 0,0, 974, 730};
				SDL_Rect camera92 = { 0,0, 972, 730};

				if (((dot.mPosX <= 180 && dot.mPosX >= 130 && dot.mPosY <=242 && dot.mPosY >= 229) || (dot.mPosX <= 520 && dot.mPosX >= 470 && dot.mPosY <=320 && dot.mPosY >= 270)) && e.key.keysym.sym == SDLK_SPACE)
					menu = true;
				if (((dot.mPosX >= 180 || dot.mPosX <= 130 || dot.mPosY >=242 || dot.mPosY <= 229) && (dot.mPosX >= 520 || dot.mPosX <= 470 || dot.mPosY >=320 || dot.mPosY <= 270)) || (menu == true && e.key.keysym.sym == SDLK_ESCAPE))
					menu = false;
				
				int a = 0;
				if (menu == true && e.type == SDL_MOUSEBUTTONDOWN){
					int x, y;
					SDL_GetMouseState( &x, &y );

					if (x>203 && x<681 && y>119 && y<150 && transaction == false)
						money -= 20;
					if (x>203 && x<681 && y>150 && y<175 && transaction == false)
						money -= 24;
					if (x>203 && x<681 && y>175 && y<201 && transaction == false)
						money -= 48;
					if (x>203 && x<681 && y>201 && y<225 && transaction == false)
						money -= 20;
					if (x>203 && x<681 && y>228 && y<253 && transaction == false)
						money -= 12;
					if (x>203 && x<681 && y>255 && y<278 && transaction == false)
						money -= 20;
					if (x>203 && x<681 && y>331 && y<355 && transaction == false)
						money -= 48;
					if (x>203 && x<681 && y>357 && y<382 && transaction == false)
						money -= 48;
					if (x>203 && x<681 && y>382 && y<404 && transaction == false)
						money -= 48;
					if (x>203 && x<681 && y>407 && y<432 && transaction == false)
						money -= 29;
					if (x>203 && x<681 && y>432 && y<455 && transaction == false)
						money -= 29;
					if (x>203 && x<681 && y>460 && y<483 && transaction == false)
						money -= 53;
					if (x>203 && x<681 && y>534 && y<559 && transaction == false)
						money -= 29;
					if (x>203 && x<681 && y>561 && y<586 && transaction == false)
						money -= 77;
					if (x>203 && x<681 && y>587 && y<614 && transaction == false)
						money -= 77;
					if (x>203 && x<681 && y>663 && y<688 && transaction == false)
						money -= 6;
					if (x>203 && x<681 && y>688 && y<716 && transaction == false)
						money -= 5;
					if (x>203 && x<681 && y>716 && y<739 && transaction == false)
						money -= 12;
						
						
					if (x>694 && x<1175 && y>119 && y<150 && transaction == false)
						money -= 20;
					if (x>694 && x<1175 && y>150 && y<175 && transaction == false)
						money -= 39;
					if (x>694 && x<1175 && y>175 && y<201 && transaction == false)
						money -= 33;
					if (x>694 && x<1175 && y>255 && y<278 && transaction == false)
						money -= 59;
					if (x>694 && x<1175 && y>278 && y<305 && transaction == false)
						money -= 58;
					if (x>694 && x<1175 && y>305 && y<330 && transaction == false)
						money -= 39;
					if (x>694 && x<1175 && y>331 && y<355 && transaction == false)
						money -= 48;
					if (x>694 && x<1175 && y>357 && y<382 && transaction == false)
						money -= 77;
					if (x>694 && x<1175 && y>382 && y<404 && transaction == false)
						money -= 48;
					if (x>694 && x<1175 && y>460 && y<483 && transaction == false)
						money -= 58;
					if (x>694 && x<1175 && y>483 && y<511 && transaction == false)
						money -= 68;
					if (x>694 && x<1175 && y>561 && y<586 && transaction == false)
						money -= 12;
					if (x>694 && x<1175 && y>587 && y<614 && transaction == false)
						money -= 15;
					if (x>694 && x<1175 && y>663 && y<688 && transaction == false)
						money -= 8;
					if (x>694 && x<1175 && y>688 && y<716 && transaction == false)
						money -= 15;
					if (x>694 && x<1175 && y>716 && y<739 && transaction == false)
						money -= 29;
					transaction = true;
					health+=10;
					a = time;
					
				}

				if (time == a + 50)
					transaction = false;





				//Render dots
				dot.render();
				dot2.render();
				dot3.render();
				gBGTexture1.render( 565, 270, &camera1 );		//hospital
				gBGTexture2.render( 1130, 70, &camera2 );		//kailash
				gBGTexture3.render( 1185, 60, &camera3 );		//himadri
				gBGTexture4.render( 770, 260, &camera4 );		//library
				gBGTexture5.render( 970, 300, &camera5 );		//lhc
				
				gBGTexture24.render( 430, 220, &camera24 );		//rajdhani
				gBGTexture25.render( 770, 245, &camera25 );		//amul
				gBGTexture26.render( 300, 470, &camera26 );		//sac
				gBGTexture27.render( 270, 200, &camera27 );		//shivalik
				gBGTexture28.render( 357, 114, &camera28 );		//satpura
				gBGTexture29.render( 165, 0, &camera29 );		//kumaon
				gBGTexture30.render( -20, 48, &camera30 );		//jwala
				gBGTexture31.render( -20, 210, &camera31 );		//ara
				gBGTexture32.render( -20, 340, &camera32 );		//kara
				gBGTexture33.render( -20, 525, &camera33 );		//nilgiri
				gBGTexture34.render( 100, 570, &camera34 );		//nalanda
				gBGTexture35.render( 430, 150, &camera35 );		//girnar
				gBGTexture36.render( 475, 140, &camera36 );		//udaigiri
				gBGTexture37.render( 300, 255, &camera37 );		//zanskar
				gBGTexture38.render( 400, 355, &camera38 );		//yulu rajdhani
				gBGTexture39.render( 910, 280, &camera39 );		//yulu lhc
				gBGTexture40.render( 175, 445, &camera40 );		//yulu sac
				gBGTexture41.render( 1010,40, &camera41 );		//yulu main gate
				gBGTexture44.render( 290,40, &camera44 );		//vindy
				gBGTexture45.render( 650,230, &camera45 );		//bharti
				gBGTexture46.render( 440,390, &camera46 );		//ground
				gBGTexture47.render( 1017,125, &camera47 );		//himadri circle
				gBGTexture48.render( 500,300, &camera48 );		//pharmacy
				gBGTexture49.render( 244,350, &camera49 );		//sac circle
				gBGTexture50.render( 84,60, &camera50 );		//jwala circle
				gBGTexture73.render( 878,75, &camera73 );		//biotech lawns
				gBGTexture74.render( 740,104, &camera74 );		//main building
				gBGTexture76.render( 130,254, &camera76 );		//tennis court left
				gBGTexture77.render( 180,254, &camera77 );		//tennis court right
				
				gBGTexture23.render( 140, 190, &camera23 );		//delhi16
				gBGTexture75.render( 250,574, &camera75 );		//oat
				gBGTexture78.render( 120,110, &camera78 );		//volley court left
				gBGTexture79.render( 180,110, &camera79 );		//volley court right
				gBGTexture80.render( 387,160, &camera80 );		//yulu satpura
				gBGTexture81.render( 32,8, &camera81 );		//yulu jwala
				gBGTexture82.render( 40,540, &camera82 );		//yulu nilgiri
				gBGTexture83.render( 710,175, &camera83 );		//yulu library
				gBGTexture84.render( 1215,12, &camera84 );		//yulu himadri
				gBGTexture85.render( 600, 345, &camera85 );		//yulu ground
				if (menu == true && dot.mPosX < 190)
					gBGTexture91.render( 200,25, &camera91 );		//menu
				if (menu == true && dot.mPosX > 190)
					gBGTexture92.render( 200,25, &camera92 );		//menu
				//select only if multi
				if(temp==5)
					gBGTexture86.render( dot2.mPosX - 30, dot2.mPosY - 55, &camera86 );		//sprite2
				if (menu == false)
					gBGTexture87.render( 965, 260, &camera87 );		//atm
				if(abs(dot3.mPosX - dot.mPosX) <=30 && abs(dot3.mPosY - dot.mPosY) <=30 && prof_collide ==0)
				{
					gBGTexture88.render( dot3.mPosX, dot3.mPosY - 200, &camera88 );		//prof_msg
					if(prof_collide==0)
					{
						prof_collide = 2;
						depression+=50;
					}
						
				}

				
					
					
				if(depression == 100)
					gameover = true;

				int x, y;
				SDL_GetMouseState( &x, &y );
				
				if (menu == false){
				character_sprite(e, time, camera6, camera7,camera8,camera9,
				camera10,camera11,camera12,camera13,camera14,camera15,camera16,
				camera17,camera18,camera19,camera20,camera21,camera22, dot, yulu_mode,
				camera42, camera43);
				}

				if (menu == false){
				prof_sprite(time, camera51, camera52,camera53,camera54,
				camera55,camera56,camera57,camera58,camera59,camera60,camera61,
				camera62,camera63,camera64,camera65,camera66, dot3, forward);
				}


				if(hours == 8)
				{
					gPromptTextTexture1.loadFromRenderedText( "It's time for Breakfast", textColor );
					health-=1;
				}	
				else if(hours == 13)
				{
					gPromptTextTexture1.loadFromRenderedText( "It's time for Lunch", textColor );
					health-=1;
				}
				else if(hours == 20)
				{
					gPromptTextTexture1.loadFromRenderedText( "It's time for Dinner", textColor );
					health-=1;
				}
					
				else
					gPromptTextTexture1.loadFromRenderedText( " ", textColor );

				if(at_kailash)
					gPromptTextTexture2.loadFromRenderedText( "You are now in Kailash", textColor );
				else if(at_himadri)
					gPromptTextTexture2.loadFromRenderedText( "You are now in Himadri", textColor );
				else if(at_lhc)
					gPromptTextTexture2.loadFromRenderedText( "You are now in LHC", textColor );
				else if(at_lib)
					gPromptTextTexture2.loadFromRenderedText( "You are now in the Central Library", textColor );
				else if(at_hospital)
				{
					if(e.key.keysym.sym == SDLK_1)
						gPromptTextTexture2.loadFromRenderedText( "You are now in IIT Hospital, press 1 to consult", textColor );
					else
						gPromptTextTexture2.loadFromRenderedText( "Please visit the pharmacy next door for your medicines", textColor );
				}
					
				else if(at_rajdhani)
					gPromptTextTexture2.loadFromRenderedText( "You are now at Rajdhani", textColor );
				else if(at_amul)
					gPromptTextTexture2.loadFromRenderedText( "You are now in Amul", textColor );
				else if(at_biotech)
					gPromptTextTexture2.loadFromRenderedText( "You are now in Biotech Lawns", textColor );
				else if(at_pharmacy)
				{
					if(e.key.keysym.sym == SDLK_1)
						gPromptTextTexture2.loadFromRenderedText( "Medicines worth 100rs bought", textColor );
					else
						gPromptTextTexture2.loadFromRenderedText( "You are now in Pharmacy, press 1 to buy meds", textColor );
				}
					
				else if(at_delhi16)
					gPromptTextTexture2.loadFromRenderedText( "You are now in Delhi 16", textColor );
				else if(at_main)
					gPromptTextTexture2.loadFromRenderedText( "You are now in the main building", textColor );
				else 
					gPromptTextTexture2.loadFromRenderedText( " ", textColor );

				if(at_main && start_timer !=0)
				{
					gPromptTextTexture2.loadFromRenderedText( "You are now in the main building, now go to LHC", textColor );	
					main_done = true;	
				}
				if(at_lhc && start_timer !=0 && main_done)
				{	
					gPromptTextTexture2.loadFromRenderedText( "You are now in the LHC, now go to bharti building", textColor );	
					lhc_done = true;	
				}
				if(at_bharti && start_timer !=0 && lhc_done)
				{	
						
					if(e.key.keysym.sym == SDLK_1)
					{
						gPromptTextTexture2.loadFromRenderedText( "Submitted, but you will be penalised", textColor );
						prof_collide = 0;
					}
					else
						gPromptTextTexture2.loadFromRenderedText( "You are now in the bharti building, press 1 to submit apology", textColor );
							
				}
				timeText11.str(" ");
				timeText11<<" ";
				if(yulu_zone && yulu_mode == false && (time-yulu_end_time)>50)
				{
					gBGTexture68.render( 580,560, &camera68 );			//yulu phone
					timeText5.str(" ");
					
    					if(e.key.keysym.sym == SDLK_1)
						{
							timeText5<<" ";
							gBGTexture69.render( 580,560, &camera69 );
							
							yulu_mode = true;	
							yulu_start_time = time;
							yulu = true;
							dot.DOT_VEL = 5;	
						}	
						else
						{
							timeText5<<"Press 1";
						}
				}
				else if(yulu_zone && yulu_mode == true && (time-yulu_start_time)>50 )
				{
					gBGTexture72.render( 580,560, &camera72 );
					timeText5.str(" ");
    					if(e.key.keysym.sym == SDLK_2)
						{
							timeText5<<" ";
							yulu_mode = false;
							dot.DOT_VEL = 1;
							yulu_end_time = time;
							price_deducted = (time-yulu_start_time)/100;
							timeText11<<"Price deducted = "<<price_deducted;
							money-=price_deducted;
						}
						else
						{
							timeText5<<"Press 2";
						}
							
				}
				else
				{
					timeText5.str(" ");
					timeText5<<" ";
				}

				if(prof_collide==2)
					start_timer = time;
				int timer = (((9000 + start_timer-time)/60)%60);
				if(timer == 0 && prof_collide==1)
					gameover= true;
				if(prof_collide==1)
				{
					timeText7.str(" ");
					timeText7<<"TIMER: "<<timer;
				}

				timeText10.str(" ");
				timeText10<<" ";
				if(at_sac)
				{
					if(e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_1 || e.key.keysym.sym == SDLK_2 || e.key.keysym.sym == SDLK_3 || e.key.keysym.sym == SDLK_4 || e.key.keysym.sym == SDLK_5 || e.key.keysym.sym == SDLK_6 || e.key.keysym.sym == SDLK_7 || e.key.keysym.sym == SDLK_8 || e.key.keysym.sym == SDLK_9 ||e.key.keysym.sym ==  SDLK_0)
						gBGTexture71.render( 580,560, &camera71 );
					else
					{
						timeText10<<"Press Space and then a number from 1 to +(12 keys) to play music";
						gBGTexture70.render( 580,560, &camera70 );
					}
						
				}
					//check later
				
				//Render text
				if( !gTimeTextTexture1.loadFromRenderedText( timeText1.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture2.loadFromRenderedText( timeText2.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture3.loadFromRenderedText( timeText3.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture4.loadFromRenderedText( timeText4.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture5.loadFromRenderedText( timeText5.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture6.loadFromRenderedText( timeText6.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture7.loadFromRenderedText( timeText7.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture8.loadFromRenderedText( timeText8.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture9.loadFromRenderedText( timeText9.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture10.loadFromRenderedText( timeText10.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture11.loadFromRenderedText( timeText11.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture12.loadFromRenderedText( timeText12.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				if( !gTimeTextTexture13.loadFromRenderedText( timeText13.str().c_str(), textColor ) )
				{
					// printf( "Unable to render time texture!\n" );
				}
				gPromptTextTexture1.render( ( SCREEN_WIDTH - gPromptTextTexture1.getWidth() ) / 2, 0 );
				gPromptTextTexture2.render( ( SCREEN_WIDTH - gPromptTextTexture2.getWidth() ) / 2, 700 );
				if (menu == false){
				gTimeTextTexture1.render(  1050, 610 ); //time
				gTimeTextTexture2.render(  1050, 670 ); //fitness
				gTimeTextTexture3.render(  1050, 700 );	//health
				gTimeTextTexture4.render(  1050, 640 ); //money
				gTimeTextTexture7.render(  1050, 580 ); //timer
				gTimeTextTexture5.render(  598, 725 );
				gTimeTextTexture8.render(  1050, 730 );
				gTimeTextTexture9.render(  1050, 760 );
				gTimeTextTexture10.render(  200, 725 );
				gTimeTextTexture11.render(  520, 725 ); //yulu price

				/*gTimeTextTexture12.render(  500, 200 );	//score 
				if(gameover)
				{
					gTimeTextTexture12.render(  500, 200 );	//score 
					if(temp==5)
						gTimeTextTexture13.render(  700, 200 ); // score2
				}*/
				
				gTimeTextTexture14.render(  598, 725 );
				gTimeTextTexture15.render(  598, 725 );
				gTimeTextTexture16.render(  598, 725 );
				gTimeTextTexture17.render(  598, 725 );
				gTimeTextTexture18.render(  598, 725 );
				gTimeTextTexture19.render(  598, 725 );
				gTimeTextTexture20.render(  598, 725 );
				gTimeTextTexture21.render(  598, 725 );
				gTimeTextTexture22.render(  598, 725 );
				gTimeTextTexture23.render(  598, 725 );
				gTimeTextTexture24.render(  598, 725 );
				gTimeTextTexture25.render(  598, 725 );
				gTimeTextTexture26.render(  598, 725 );
				gTimeTextTexture27.render(  598, 725 );
				gTimeTextTexture28.render(  598, 725 );
				gTimeTextTexture29.render(  598, 725 );
				gTimeTextTexture30.render(  598, 725 );
				gTimeTextTexture31.render(  598, 725 );
				gTimeTextTexture32.render(  598, 725 );
				}
				if(yulu_mode == true)
					gTimeTextTexture6.render(  1050, 580 );

					//change

				SDL_RenderPresent( gRenderer );
				if(yulu)
				{
					SDL_Delay( 2000 );
					yulu = false;
				}
				if(prof_collide == 2)
				{
					SDL_Delay( 3000 );
					prof_collide = 1;
				}
				if(gameover==true)
					{
						score = game_over(foodie_time, fitness_time, nerd_time, health, money );
						cout<<"Score 1: "<<score;
						cout<<"Score 2: "<<score2;
						break;
					}
				if(price_deducted!=0)
				{
					SDL_Delay( 1000 );
					price_deducted = 0;
				}
					
			}

			
		}
	}

	//Free resources and close SDL
	label5: if (temp != 5) close(3,0);
			else if (score2 > score) close(1,0);
			else close(2,0);

	return 0;
}