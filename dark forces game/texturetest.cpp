#include "texturetest.h"





texturetest::~texturetest()
{
}

void texturetest::init()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mPitch = 0;
}

bool texturetest::LoadFromFile(std::string path)
{
    free();
    
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(Graphics::window), 0);
        if (formattedSurface == NULL)
        {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            newTexture = SDL_CreateTexture(Graphics::renderer, SDL_GetWindowPixelFormat(Graphics::window), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
            if (newTexture == NULL)
            {
                printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);
                memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);
                SDL_UnlockTexture(newTexture);
                mPixels = NULL;
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;

            }
            SDL_FreeSurface(formattedSurface);
        }
        SDL_FreeSurface(loadedSurface);

    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool texturetest::loadFromRenderedText(std::string texturetext, SDL_Color textcolor)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    /*SDL_Surface* textSurface =
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    else
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }


    //Return success*/
    return mTexture != NULL;
}

void texturetest::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mPixels = NULL;
        mPitch = 0;
    }
}

void texturetest::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture rgb
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void texturetest::setBlendeMoe(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void texturetest::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void texturetest::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x,y,mWidth,mHeight };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(Graphics::renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void texturetest::loadTexture()
{
    //Load foo' texture
    if (!LoadFromFile("stonewall.png"))
    {
        printf("Failed to load corner texture!\n");

    }
    else
    {
        //Lock texture
        if (!lockTexture())
        {
            printf("Unable to lock Foo' texture!\n");
        }
        //Manual color key
        else
        {
            //Allocate format from window
            Uint32 format = SDL_GetWindowPixelFormat(Graphics::window);
            SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);

            //Get pixel data
            Uint32* pixels = (Uint32*)getPixels();
            int pixelCount = (getPitch() / 4) * getHeight();

            //Map colors
           Uint32 colorKey = SDL_MapRGB(mappingFormat, 0, 0xFF, 0xFF);
           Uint32 transparent = SDL_MapRGBA(mappingFormat, 0xFF, 0xFF, 0xFF, 0x00);
           
           //Color key pixels
           for (int i = 0; i < pixelCount; ++i)
           {
               if (pixels[i] == colorKey)
               {
                   pixels[i] = transparent;
               }
           }

            //Unlock texture
            unlockTexture();

            //Free format
            SDL_FreeFormat(mappingFormat);
        }
    }
}

int texturetest::getWidth()
{
    return mWidth;
}

int texturetest::getHeight()
{
    return mHeight;
}

bool texturetest::lockTexture()
{
    bool success = true;

    //Texture is already locked
    if (mPixels != NULL)
    {
        printf("Texture is already locked!\n");
        success = false;
    }
    //Lock texture
    else
    {
        if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0)
        {
            printf("Unable to lock texture! %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool texturetest::unlockTexture()
{
    bool success = true;

    //Texture is not locked
    if (mPixels == NULL)
    {
        printf("Texture is not locked!\n");
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture(mTexture);
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

void* texturetest::getPixels()
{
    return mPixels;
}

int texturetest::getPitch()
{
    return 0;
}
