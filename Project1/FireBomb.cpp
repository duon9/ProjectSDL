#include "FireBomb.h"

#define PATH "assets/skill/firebomb.png"

std::vector<std::vector<SDL_Rect>> FireBomb::clips;
std::vector<Frame> FireBomb::limits;
SDL_Texture* FireBomb::vessel = nullptr;

void FireBomb::loadClips() {
    std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 0,0,0,0 });
    final.push_back({ 0, 0, 46,46 });
    final.push_back({ 46, 0, 46,46 });
    final.push_back({ 46*2, 0, 46,46 });
    final.push_back({ 46*3, 0, 46,46 });
    final.push_back({ 46*4, 0, 46,46 });
    final.push_back({ 46*5, 0, 46,46 });
    
    impact.push_back({ 0, 46, 46,46 });
    impact.push_back({ 46, 46, 46,46 });
    impact.push_back({ 46 * 2, 46, 46,46 });
    impact.push_back({ 46 * 3, 46, 46,46 });
    impact.push_back({ 46 * 4, 46, 46,46 });
    impact.push_back({ 46 * 5, 46, 46,46 });
    impact.push_back({ 46 * 6, 46, 46,46 });


    Frame formations = Frame(5, 5, 1);
    Frame finals = Frame(24, 4, 6);
    Frame impacts = Frame(35, 5, 7);

    FireBomb::clips.push_back(formation);
    FireBomb::clips.push_back(final);
    FireBomb::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void FireBomb::loadTexture(SDL_Renderer* renderer) {
    FireBomb::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void FireBomb::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}