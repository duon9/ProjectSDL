#include "statsBar.h"

void Bar::setProperties(int maxProperty) {
	Bar::maxProperty = maxProperty;
}

void Bar::updateProperties(int newProperty) {
	currentProperty = newProperty;
}

void Bar::updateBar() {
    //healthRect.w = static_cast<int>((currentHealth / maxHealth) * maxWidth);
}

void Bar::render() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); 
    SDL_RenderFillRect(renderer, &healthRect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &outlineRect);
}