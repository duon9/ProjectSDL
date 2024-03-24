#include "FireBall.h"

#define PATH "assets/skill/fire.png"

std::vector<std::vector<SDL_Rect>> FireBall::clips;
std::vector<Frame> FireBall::limits;
SDL_Texture* FireBall::vessel = nullptr;

void FireBall::loadClips() {
    std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 4 * 48, 0, 48, 48 });
    final.push_back({ 0,0,48,48 });
    final.push_back({ 1 * 48, 0, 48,48 });
    final.push_back({ 2 * 48, 0, 48,48 });
    final.push_back({ 3 * 48, 0, 48,48 });
    impact.push_back({ 5 * 48, 0, 48,48 });
    impact.push_back({ 6 * 48, 0, 48,48 });
    impact.push_back({ 7 * 48, 0, 48,48 });
    impact.push_back({ 8 * 48, 0, 48,48 });
    impact.push_back({ 9 * 48, 0, 48,48 });
    impact.push_back({ 10 * 48, 0, 48,48 });


    Frame formations = Frame(10, 10, 1);
    Frame finals = Frame(16, 4, 4);
    Frame impacts = Frame(30, 5, 6);

    FireBall::clips.push_back(formation);
    FireBall::clips.push_back(final);
    FireBall::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void FireBall::loadTexture(SDL_Renderer* renderer) {
    FireBall::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void FireBall::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}