#include "utils.h"

TextureManagement::TextureManagement() {
}

TextureManagement::~TextureManagement() {
}

SDL_Texture* TextureManagement::LoadTexture(const std::string filename, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_SetTextureBlendMode(tempTexture, SDL_BLENDMODE_NONE);
	SDL_FreeSurface(tempSurface);
	return tempTexture;
}

void TextureManagement::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, texture, &src, &dest);
}

Map::Map() {

}

Map::~Map() {

}

std::vector<std::vector<int>> Map::loadMap(std::string path) {
	std::ifstream file(path);
	std::vector<std::vector<int>> res;

	if (file.is_open()) {
		int m, n;
		file >> m >> n;
		res.resize(100, std::vector<int>(100));

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				file >> res[i][j];
			}
		}
	}
	else {
		std::cout << "Cannot open file" << std::endl;
		return res;
	}
	file.close();
	return res;
}