#include "FireBall.h"
#include "global.h"
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

void FireBall::projectile() {
    if (global::isPause) return;
    if (state == FINAL /*|| state == FORMATION*/) {
        position.x += v.getX() * speed;
        position.y += v.getY() * speed;
        lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
        lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
        //lumi->x+=3;
        //lumi->w-=3;

        //lumi->y+=3;
        //lumi->h-=3;
    }
}

void FireBall::push() {
    global::lighthouse.push_back(lumi);
}

void FireBall::handleEffect(SDL_Rect target) {
    if (!isCollide) {
        if (isCollision(target)) {
            state = IMPACT;
            isCollide = true;
            frameCount = 0;
            lumi->w = 0;
            lumi->h = 0;
        }
    }
    else {
        //fade();
    }
}

void FireBall::fade() {
    if (lumi->w > 0) {
        lumi->x += 3;
        lumi->w -= 3;
    }

    if (lumi->h > 0) {
        lumi->y += 3;
        lumi->h -= 3;
    }
}