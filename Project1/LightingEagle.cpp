#include "LightingEagle.h"

#define PATH "assets/skill/lighting.png"

std::vector<std::vector<SDL_Rect>> LightingEagle::clips;
std::vector<Frame> LightingEagle::limits;
SDL_Texture* LightingEagle::vessel = nullptr;

void LightingEagle::loadClips() {
    std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 0 * 48, 0, 48, 48 }); // 7
    formation.push_back({ 1 * 48, 0, 48, 48 });
    formation.push_back({ 2 * 48, 0, 48, 48 });
    formation.push_back({ 3 * 48, 0, 48, 48 });
    formation.push_back({ 4 * 48, 0, 48, 48 });
    formation.push_back({ 5 * 48, 0, 48, 48 });
    formation.push_back({ 6 * 48, 0, 48, 48 }); // 9
    formation.push_back({ 7 * 48, 0, 48, 48 });
    final.push_back({ 8 * 48, 0, 48, 48 });
    final.push_back({ 9 * 48, 0, 48, 48 });
    final.push_back({ 10 * 48, 0, 48, 48 });
    final.push_back({ 11 * 48, 0, 48, 48 });
    final.push_back({ 12 * 48, 0, 48, 48 });
    final.push_back({ 13 * 48, 0, 48, 48 });
    final.push_back({ 14 * 48, 0, 48, 48 });
    final.push_back({ 15 * 48, 0, 48, 48 });
    impact.push_back({ 0 * 48, 48, 48,48 }); // 5
    impact.push_back({ 1 * 48, 48, 48,48 });
    impact.push_back({ 2 * 48, 48, 48,48 });
    impact.push_back({ 3 * 48, 48, 48,48 });
    impact.push_back({ 4 * 48, 48, 48,48 });


    Frame formations = Frame(80, 10, 8);
    Frame finals = Frame(80, 10, 8);
    Frame impacts = Frame(25, 5, 5);

    LightingEagle::clips.push_back(formation);
    LightingEagle::clips.push_back(final);
    LightingEagle::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void LightingEagle::loadTexture(SDL_Renderer* renderer) {
    LightingEagle::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void LightingEagle::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}

