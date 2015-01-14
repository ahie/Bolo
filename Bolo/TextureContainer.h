#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class TextureContainer
{
public:
	~TextureContainer() {}
	static TextureContainer& instance()
	{
		static TextureContainer* instance = new TextureContainer();
		return *instance;
	}
	sf::Texture* getTexture(string resource)
	{
		unordered_map<string, sf::Texture>::iterator iter =
			container_.find(resource);
		if (iter == container_.end()) {
			sf::Image newImage;
			newImage.loadFromFile(resource);
			newImage.createMaskFromColor(sf::Color(0, 128, 0), 0);
			sf::Texture newTexture;
			newTexture.loadFromImage(newImage);
			container_.insert(std::make_pair(resource, newTexture));
			return getTexture(resource);
		}
		else return &(iter->second);
	}
private:
	TextureContainer() {}
	unordered_map<string, sf::Texture> container_;
};