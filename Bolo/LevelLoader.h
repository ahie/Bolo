#include "ext/jsoncpp/json/json.h"
#include "Level.h"
#include "Hero.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class LevelLoader {
public:
	LevelLoader();
	~LevelLoader();

	vector<Level*> getLevels();
	Hero* getHero();
	int getHeroLevel();
	void parseData(string filename);

private:
	Json::Value attacks_;
	Json::Value items_;
	Json::Value monsters_;
	Json::Value tilesets_;
	
	vector<Level*> levels_;
	Hero* hero_;
	int heroLevel_;
};