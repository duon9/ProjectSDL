#include "player.h"

#define check (!orient.up && !orient.down && !orient.left && !orient.right)

int cost[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
Stat& Player::getStat() {
	return stat;
}

SDL_Point& Player::getAddressLocation() {
	return position;
}

void Player::handleUserEvents(SDL_Event *e) {
	stat.health += global::stats[type]->health / 10000;
	stat.mana += global::stats[type]->mana / 10000;
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_e) protocol->send(getPosition(), true);
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_q) protocol->send(getPosition(), false);
	if (!check_death && !global::isPause) {
		move();
		if (e->type == SDL_KEYDOWN) {
			switch (e->key.keysym.sym) {
			case SDLK_z:
				if (magic < MAX_TYPE) magic++;
				else magic = 1;
				break;
			case SDLK_x:
				std::cout << position.x << " " << position.y << std::endl;
				break;
			case SDLK_r:
				//llma.setCurr();
				break;
			/*case SDLK_e:
				protocol->send(getPosition(), true);
				break;
			case SDLK_q:
				protocol->send(getPosition(), false);
				break;*/
			case SDLK_LSHIFT:
				stat.speed = 4;
				//stat.mana -= 1;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				if (orient.right == 1 || status == ATTACKING) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.left = 1;
				status = RUNNING;
				//flip = SDL_FLIP_HORIZONTAL;
				velo_x = -1;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if (orient.up == 1 || status == ATTACKING) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.down = 1;
				status = RUNNING;
				velo_y = 1;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if (orient.left == 1 || status == ATTACKING) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.right = 1;
				status = RUNNING;
				//flip = SDL_FLIP_NONE;
				velo_x = 1;
				break;
			case SDLK_w:
			case SDLK_UP:
				if (orient.down == 1 || status == ATTACKING) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.up = 1;
				status = RUNNING;
				velo_y = -1;
				break;
			default:
				break;
			}
		}
		if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym) {
			case SDLK_LSHIFT:
				stat.speed /= 2;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				//status = IDLE;
				//runSound->stop();
				velo_x = 0;
				orient.left = 0;
				//velo_x = 0;
				//flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				//status = IDLE;
				//runSound->stop();
				orient.down = 0;
				velo_y = 0;
		
				//velo_y = 0;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				//status = IDLE;
				//velo_x = 0;
				//runSound->stop();
				orient.right = 0;
				velo_x = 0;
				break;
			case SDLK_w:
			case SDLK_UP:
				//status = IDLE;
				//runSound->stop();
				orient.up = 0;
				velo_y = 0;
				//velo_y = 0;
				break;
			default:break;
			}
		}

		if (e->type == SDL_MOUSEMOTION) {
			if (e->motion.x > desRect.x + desRect.w / 2) flip = SDL_FLIP_NONE;
			else flip = SDL_FLIP_HORIZONTAL;
		}

		if (e->type == SDL_MOUSEBUTTONDOWN) {
			if (e->button.button == SDL_BUTTON_LEFT) {
				if (status == RUNNING) return;
				if (frameTick > 0) return;
				status = ATTACKING;
				attackSound->play();
				attack();
			}
			if (e->button.button == SDL_BUTTON_RIGHT && global::isHaveArcane) {
				stat.mana -= cost[magic];
				switch (magic) {
				case 1:
				{
					FireBall* balls = new FireBall(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(balls);
					break;
				}
				case 2:
				{
					WaterBall* ball = new WaterBall(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(ball);
					break;
				}
				case 3:
				{
					IceLancet* ball = new IceLancet(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(ball);
					break;
				}
				case 4:
				{
					HolySpear* ball = new HolySpear(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(ball);
					break;
				}
				case 5:
				{
					FireBomb* ball = new FireBomb(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(ball);
					break;
				}
				case 6:
				{
					LightingEagle* ball = new LightingEagle(renderer, { desRect.x, desRect.y }, { e->motion.x, e->motion.y }, { interface->camera.x, interface->camera.y }, code);
					global::missles.push_back(ball);
					break;
				}
				case 7:
				{
					/*if (stat.mana > 1000) {
						stat.mana -= 1000;
						effect = HEAL;
						TimerManager::createTimer(id, 10000);
					}*/
					SDL_Point point = { interface->camera.x + e->motion.x, interface->camera.y + e->motion.y };
					for (int i = 0; i < global::layers.size(); i++) {
						SDL_Rect rect = global::layers[i]->getRect();
						if (SDL_PointInRect(&point, &rect)) {
							global::layers[i]->setLocation({ position.x, position.y });
							setLocation({ interface->camera.x + e->motion.x, interface->camera.y + e->motion.y });
							break;
						}
					}
					//setLocation({interface->camera.x + e->motion.x, interface->camera.y + e->motion.y});
					break;
				}
				/*case 8:
				{
					SDL_Point point = getCursorPosition(e);
					for (int i = 0; i < global::layers.size(); i++) {
						SDL_Rect rect = global::layers[i]->getRect();
						if (SDL_PointInRect(&point, &rect)) {
							
						}
					}
					break;
				}*/
				default:
					break;
				}
			}
		}

		if (check && frameTick == 0) {
			status = IDLE;
			runSound->stop();
		}
	}
}

void Player::move() {
	if (/*collisionHandle(collider) && */!check_death && !check_pause) {
		// TODO: found some problem here
		if (frameTick > 0) {
			frameTick--;
			if (frameTick == 0) {
				status = IDLE;
				attackSound->stop();
			};
			return;
		} 
		else if ((velo_x != 0 || velo_y != 0) && frameTick == 0) {
			Math::Vector v = Math::Vector(velo_x, velo_y);
			v.normalize();
			velo_x = v.getX() * stat.speed;
			velo_y = v.getY() * stat.speed;
			if (!collision->isColliding(velo_x, velo_y)) {
				if (velo_x != 0) {
					position.x += velo_x;
					if (interface->isCameraCollideCornerHorizontal(velo_x) || !interface->isCenterHorizontal(desRect)) {
						desRect.x += velo_x;
						global::lightRect.x = desRect.x + desRect.w / 2 - 180;
					}
					else {
						interface->camera.x += velo_x;
					}
				}

				if (velo_y != 0) {
					position.y += velo_y;
					if (interface->isCameraCollideCornerVertical(velo_y) || !interface->isCenterVertical(desRect)) {
						desRect.y += velo_y;
						global::lightRect.y = desRect.y + desRect.h / 2 - 180;
					}
					else {
						interface->camera.y += velo_y;
					}
				}
			}
		}
	}
}

void Player::setLocation() {
	map_x = 1;
	map_y = 1;
	//setSize(64, 64);
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
	position.x = interface->camera.x + desRect.x;
	position.y = interface->camera.y + desRect.y;
	/*global::lightRect.x = desRect.x + desRect.w / 2 - 180;
	global::lightRect.y = desRect.y + desRect.h / 2 - 180;*/
}

void Player::setLocation(SDL_Point p) {
	map_x = p.x / TILE_WIDTH;
	map_y = p.y / TILE_HEIGHT;
	//setSize(64, 64);
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
	position.x = interface->camera.x + desRect.x;
	position.y = interface->camera.y + desRect.y;
	global::lightRect.x = desRect.x + desRect.w / 2 - 180;
	global::lightRect.y = desRect.y + desRect.h / 2 - 180;
	global::lightRect.w = 360;
	global::lightRect.h = 360;
}

void Player::setCollision() {
	//collider = File::readCollision(path);
	collision = new Collision(&desRect, &interface->camera, &position);
}

void Player::setProtocolCode() {
	code = ALLY_CODE;
}

void Player::handleBarDisplay() {
	interface->mana_display->updateProperties(stat.mana);
	interface->mana_display->updateBar();

	interface->health_display->updateProperties(stat.health);
	interface->health_display->updateBar();
}

void Player::setSFX() {
	attackSound->add("assets/audio/player-attack.wav");
	runSound->add("assets/audio/run.mp3");
}

void Player::init() {
	setRandomId();
	setAbility();
	setSize(54, 54);
	setSFX();
	setProtocolCode();
	setProtocol();
	setLocation();
	setProperties();
	setBarProperties();
	setFrameLimit();
	setClip();
	setCollision();
	setTexture();
	setLumination();
}

void Player::setBarProperties() {
	interface->mana_display->setProperties(stat.mana);
	interface->health_display->setProperties(stat.health);
}

void Player::reload() {
	//collision->reload(Object::collider);
}

//void Player::draw() {
//	SDL_RenderCopyEx(renderer, Player::vessel, &srcRect, &desRect, NULL, NULL, flip);
//	/*llma.show();
//	llma.present();*/
//}

void Player::setAbility() {
	WaterBall::loadClips();
	WaterBall::loadTexture(renderer);

	FireBall::loadClips();
	FireBall::loadTexture(renderer);

	IceLancet::loadClips();
	IceLancet::loadTexture(renderer);

	HolySpear::loadClips();
	HolySpear::loadTexture(renderer);

	FireBomb::loadClips();
	FireBomb::loadTexture(renderer);

	LightingEagle::loadClips();
	LightingEagle::loadTexture(renderer);
}

SDL_Point Player::getCursorPosition(SDL_Event* e) {
	return { e->motion.x + interface->camera.x, e->motion.y + interface->camera.y };
}

void Player::setLumination() {
	//lumi = new SDL_Rect();
	global::lightRect.x = desRect.x + desRect.w / 2 - 180;
	global::lightRect.y = desRect.y + desRect.h / 2 - 180;
	global::lightRect.w = 360;
	global::lightRect.h = 360;
	//global::lighthouse.push_back(lumi);
}

SDL_Point Player::getExactPosition() {
	return { interface->camera.x + desRect.x, interface->camera.y + desRect.y };
}