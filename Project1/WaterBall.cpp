#include "WaterBall.h"

#define PATH "assets/skill/water.png"

std::vector<std::vector<SDL_Rect>> WaterBall::clips;
std::vector<Frame> WaterBall::limits;
SDL_Texture* WaterBall::vessel = nullptr;

void WaterBall::loadClips() {
	std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 0,0,64,64 });
    formation.push_back({ 64,0,64,64 });
    formation.push_back({ 128,0,64,64 });
    formation.push_back({ 192, 0, 64,64 });
    final.push_back({ 256, 0, 64,64 });
    final.push_back({ 0, 64, 64,64 });
    final.push_back({ 64, 64, 64,64 });
    final.push_back({ 128, 64, 64,64 });
    final.push_back({ 192, 64, 64,64 });
    final.push_back({ 256, 64, 64,64 });
    final.push_back({ 0, 128, 64,64 });
    final.push_back({ 64, 128, 64,64 });
    final.push_back({ 128, 128, 64,64 });
    final.push_back({ 192, 128, 64,64 });
    final.push_back({ 256, 128, 64,64 });
    final.push_back({ 0, 192, 64,64 });
    final.push_back({ 64, 192, 64,64 });
    final.push_back({ 128, 192, 64,64 });
    final.push_back({ 192, 192, 64,64 });
    final.push_back({ 256, 192, 64,64 });
    final.push_back({ 0, 0, 256,64 });
    impact.push_back({ 0,320,64,64 });
    impact.push_back({ 64,320,64,64 });
    impact.push_back({ 128,320,64,64 });
    impact.push_back({ 192, 320, 64,64 });
    impact.push_back({ 0,384,64,64 });
    impact.push_back({ 64,384,64,64 });
    impact.push_back({ 128,384,64,64 });
    impact.push_back({ 192, 384, 64,64 });
    impact.push_back({ 0,448,64,64 });
    impact.push_back({ 64,448,64,64 });
    impact.push_back({ 128,448,64,64 });
    impact.push_back({ 192, 448, 64,64 });
    impact.push_back({ 0,512,64,64 });
    impact.push_back({ 64,512,64,64 });
    impact.push_back({ 128,512,64,64 });
    impact.push_back({ 192, 512, 64,64 });

    Frame formations = Frame(20, 5, 4);
    Frame finals = Frame(64, 4, 16);
    Frame impacts = Frame(80, 5, 16);

    WaterBall::clips.push_back(formation);
    /*std::cout << formation.size() << std::endl;
    std::cout << final.size() << std::endl;
    std::cout << impact.size() << std::endl;*/

    WaterBall::clips.push_back(final);
    WaterBall::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void WaterBall::loadTexture(SDL_Renderer* renderer) {
    WaterBall::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void WaterBall::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}