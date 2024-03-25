#include "HolySpear.h"

#define PATH "assets/skill/holy.png"

std::vector<std::vector<SDL_Rect>> HolySpear::clips;
std::vector<Frame> HolySpear::limits;
SDL_Texture* HolySpear::vessel = nullptr;

void HolySpear::loadClips() {
    std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 0,32*2,32,32 });
    formation.push_back({ 32,32*2,32,32 }); // 2 frames

    final.push_back({ 0,32,32,32 });
    final.push_back({ 32,32,32,32 });
    final.push_back({ 32*2,32,32,32 });
    final.push_back({ 32*3,32,32,32 });
    final.push_back({ 32*4,32,32,32 });
    final.push_back({ 32*5,32,32,32 });
    final.push_back({ 32*6,32,32,32 });
    final.push_back({ 32*7,32,32,32 }); // 8 frames

    impact.push_back({ 0,0,32,32 });
    impact.push_back({ 32,0,32,32 });
    impact.push_back({ 32*2,0,32,32 });
    impact.push_back({ 32*3,0,32,32 });
    impact.push_back({ 32*4,0,32,32 });
    impact.push_back({ 32*5,0,32,32 });
    impact.push_back({ 32*6,0,32,32 }); // 7 frames



    Frame formations = Frame(10, 5, 2);
    Frame finals = Frame(32, 4, 8);
    Frame impacts = Frame(35, 5, 7);

    HolySpear::clips.push_back(formation);
    /*std::cout << formation.size() << std::endl;
    std::cout << final.size() << std::endl;
    std::cout << impact.size() << std::endl;*/

    HolySpear::clips.push_back(final);
    HolySpear::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void HolySpear::loadTexture(SDL_Renderer* renderer) {
    HolySpear::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void HolySpear::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}