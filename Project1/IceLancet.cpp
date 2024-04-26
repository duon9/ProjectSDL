#include "IceLancet.h"
#include "global.h"

#define PATH "assets/skill/ice.png"

std::vector<std::vector<SDL_Rect>> IceLancet::clips;
std::vector<Frame> IceLancet::limits;
SDL_Texture* IceLancet::vessel = nullptr;

void IceLancet::loadClips() {
    std::vector<SDL_Rect> formation;
    std::vector<SDL_Rect> final;
    std::vector<SDL_Rect> impact;

    formation.push_back({ 0,0,48,32});
    formation.push_back({ 48,0,48,32 });
    formation.push_back({ 48 * 2,0,48,32 }); // 3 frames
    final.push_back({ 0, 32, 48,32 });
    final.push_back({ 48, 32, 48,32 });
    final.push_back({ 48 * 2, 32, 48,32 });
    final.push_back({ 48 * 3, 32, 48,32 });
    final.push_back({ 48 * 4, 32, 48,32 });
    final.push_back({ 48 * 5, 32, 48,32 });
    final.push_back({ 48 * 6, 32, 48,32 });
    final.push_back({ 48 * 7, 32, 48,32 });
    final.push_back({ 48 * 8, 32, 48,32 });
    final.push_back({ 48 * 9, 32, 48,32 }); // 10 frames
    impact.push_back({ 0,64,48,32 });
    impact.push_back({ 48,64,48,32 });
    impact.push_back({ 48*2,64,48,32 });
    impact.push_back({ 48*3, 64, 48,32 });
    impact.push_back({ 48*4,64,48,32 });
    impact.push_back({ 48*5,64,48,32 });
    impact.push_back({ 48*5,64,48,32 });
    impact.push_back({ 48*6, 64, 48,32 });
    impact.push_back({ 48*7,64,48,32 }); // 8 frames

    Frame formations = Frame(15, 5, 3);
    Frame finals = Frame(40, 4, 10);
    Frame impacts = Frame(40, 5, 8);

    IceLancet::clips.push_back(formation);
    /*std::cout << formation.size() << std::endl;
    std::cout << final.size() << std::endl;
    std::cout << impact.size() << std::endl;*/

    IceLancet::clips.push_back(final);
    IceLancet::clips.push_back(impact);

    limits.push_back(formations);
    limits.push_back(finals);
    limits.push_back(impacts);
}

void IceLancet::loadTexture(SDL_Renderer* renderer) {
    IceLancet::vessel = TextureManagement::LoadTexture(PATH, renderer);
}

void IceLancet::draw() {
    SDL_RenderCopyEx(renderer, vessel, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}

void IceLancet::handleEffect(SDL_Rect target) {
    if (!isCollide) {
        if (isCollision(target)) {
            state = IMPACT;
            isCollide = true;
            frameCount = 0;
            Ice* ice = new Ice(renderer);
            ice->setLocation({ position.x, position.y });
            ice->create();
            global::dtiles.push_back(ice);
            global::layers.push_back(ice);
        }
    }
}