#include "statsBar.h"

void Bar::setProperties(int maxProperty) {
	Bar::maxProperty = maxProperty;
    Bar::currentProperty = maxProperty;

    std::cout << Bar::maxProperty << " " << Bar::currentProperty << std::endl;
}

void Bar::updateProperties(int newProperty) {
    if (newProperty != currentProperty && newProperty >= 0) {
        std::cout << "new property: " << newProperty << std::endl;
        currentProperty = newProperty;
    }
}

void Bar::updateBar() {
    statsRect.w = static_cast<int>(((1.0 * currentProperty) / (1.0 * maxProperty)) * maxWidth);
}

void Bar::render() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &statsRect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &outlineRect);
}
