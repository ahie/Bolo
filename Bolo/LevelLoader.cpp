#include "LevelLoader.h"
#include "Terrain.h"
#include "Monster.h"
#include "MonsterAI.h"
#include "Item.h"

#include <fstream>
#include <iostream>

using std::ifstream;

LevelLoader::LevelLoader() 
{

	Json::Reader jreader;

	ifstream tilesets("Resources/tilesets.json", std::ios_base::binary);
	ifstream attacks("Resources/attacks.json", std::ios_base::binary);
	ifstream monsters("Resources/monsters.json", std::ios_base::binary);
	ifstream items("Resources/items.json", std::ios_base::binary);
	jreader.parse(tilesets, tilesets_);
	jreader.parse(attacks, attacks_);
	jreader.parse(items, items_);
	jreader.parse(monsters, monsters_);

}

LevelLoader::~LevelLoader() {}

vector<Level*> LevelLoader::getLevels() 
{
	return levels_;
}

Hero* LevelLoader::getHero()
{
	return hero_;
}

int LevelLoader::getHeroLevel() 
{
	return heroLevel_;
}


void LevelLoader::parseData(string filename)  
{

	Json::Reader jreader;
	Json::Value rootNode;
	ifstream file(filename.c_str(), std::ios_base::binary);
	if (!jreader.parse(file, rootNode)) {
		std::cout << jreader.getFormattedErrorMessages() << std::endl;
	}

	Hero* hero = new Hero();
	hero->setPosition(sf::Vector2f(rootNode["hero"]["x"].asFloat(), rootNode["hero"]["y"].asFloat()));
	hero->setHP(rootNode["hero"]["currHP"].asFloat());
	heroLevel_ = rootNode["hero"]["level"].asInt();
	hero_ = hero;

	Json::Value levels = rootNode["levels"];
	if (!levels.isArray()) {
		// TODO: error on bad file?
	}
	for (auto& jlevel : levels) {

		// 0. Create empty level
		Level* level = new Level();

		// 1. Create Terrain
		Json::Value jterrain = jlevel["terrain"];
		int width = jterrain["width"].asInt();
		int height = jterrain["height"].asInt();
		string tilesetString = jterrain["tileset"].asString();
		
		Json::Value tileDescriptions = tilesets_.get(tilesetString, Json::nullValue);
		Json::Value tileOrder = jterrain["tiles"];
		Tile* tiles = new Tile[width*height];
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				Json::Value nextTile = tileDescriptions[tileOrder[i + j*height].asInt()];
				bool walkable[4];
				bool collidable[4];
				for (int k = 0; k < 4; k++) {
					walkable[k] = nextTile["walkable"][k].asBool();
					collidable[k] = nextTile["collidable"][k].asBool();
				}
				(tiles + i*height + j)->
					setTileInfo(nextTile["x"].asInt(), nextTile["y"].asInt(), walkable, collidable);
			}
		}
		Terrain* terrain = new Terrain(width, height, tiles, tilesetString);
		level->setTerrain(terrain);

		// 2. Create monsters
		if (jlevel["monsters"].isArray()) {
			for (auto& jmonster : jlevel["monsters"]) {
				Monster* monster = new Monster(jmonster["id"].asString());
				monster->setLevel(level);
				level->addEntity(monster);
				MonsterAI* ai = new MonsterAI();
				monster->setAI(ai);
				monster->setPosition(sf::Vector2f(jmonster["x"].asInt(), jmonster["y"].asInt()));
				monster->setHP(jmonster["currHP"].asFloat());
			}
		}

		// 3. Droppable items
		for (auto jitem : items_["items"]) {

			std::string name = jitem["name"].asString();
			std::string image = jitem["image"].asString();
			std::string sprite = jitem["sprite"].asString();
			ItemSlot slot = (ItemSlot)jitem["slot"].asInt();
			int width = jitem["width"].asInt();
			int height = jitem["height"].asInt();
			StatModifiers mods;

			for (auto mod : jitem["mods"]) {
				mods.insert(std::make_pair<ModType,float>((ModType)mod[0].asInt(),mod[1].asFloat()));
			}

			ItemDescriptor item(name, slot, width, height, mods, image, sprite);
			level->addSpawnableItem(item);
		}

		// 4. Push to vector of loaded levels
		levels_.push_back(level);
	}
}