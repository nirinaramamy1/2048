#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Button.hpp"

Button::Button(){}
Button::Button(
    SDL_Renderer* renderer,
    char const* path,
    SDL_Rect source,
    SDL_Rect destination,
    char const* pathOnHover,
    SDL_Rect srcOnHover,
    SDL_Rect dstOnHover,
    char const* pathBackground,
    SDL_Rect srcBackground,
    SDL_Rect dstBackground
    ) : hover(false), clicked(false) {
    surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    surface = IMG_Load(pathOnHover);
    textureOnHover = SDL_CreateTextureFromSurface(renderer, surface);
    surface = IMG_Load(pathBackground);
    textureOfBackground = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    this->source = source; this->destination = destination;
    SDL_QueryTexture(texture, nullptr, nullptr, &this->source.w, &this->source.h);
    this->srcOnHover = srcOnHover; this->dstOnHover = dstOnHover;
    SDL_QueryTexture(textureOnHover, nullptr, nullptr, &this->srcOnHover.w, &this->srcOnHover.h);
    this->srcBackground = srcBackground; this->dstBackground = dstBackground;
    SDL_QueryTexture(textureOfBackground, nullptr, nullptr, &this->srcBackground.w, &this->srcBackground.h);
    target = {0, 0, 2, 2}; //We click a point
}
Button::~Button() {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureOnHover);
    SDL_DestroyTexture(textureOfBackground);
}
void Button::draw(SDL_Renderer* renderer) {
    if(hover) {
        SDL_RenderCopy(renderer, this->textureOnHover, &this->srcOnHover, &this->dstOnHover);
    } else {
        SDL_RenderCopy(renderer, this->texture, &this->source, &this->destination);
    }
}
void Button::onHover(SDL_Event* event) {
    move.x = event->motion.x;
    move.y = event->motion.y;
    if(SDL_PointInRect(&move, &dstOnHover)) {
        hover = true;
    } else {
        hover = false;
    }
}
void Button::onClick(SDL_Event* event) {
    target.x = event->button.x;
    target.y = event->button.y;
    if(SDL_IntersectRect(&target, &dstOnHover, &result)) {
        //clicked = !clicked;
        //setClickedValue(!clicked);
        clicked = true;
        std::cout << "Click works" << std::endl;
        //std::cout << quitGame << std::endl;
    }
}
bool Button::getClickedValue() {
    return clicked;
}
void Button::setClickedValue(bool value) {
    clicked = value;
}
SDL_Rect* Button::getSrcBackground() {
    return &srcBackground;
}
SDL_Rect* Button::getDstBackground() {
    return &dstBackground;
}
SDL_Texture* Button::getBackgroundTexture() {
    return textureOfBackground;
}
SDL_Texture* Button::getTexture() {
    return texture;
}