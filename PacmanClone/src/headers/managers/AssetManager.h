#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	sf::Texture* getTexture(std::string filename);
	//sf::Sound* getSound(std::string filename);
	//sf::Music* getMusic(std::string filename);

	void unloadTexture(std::string filename);
	//void unloadSound(std::string filename);
	//void unloadMusic(std::string filename);

private:
	/*maps of filepaths/filenames to the specific asset.
	there are a couple ways to do this:
	 - we could load an asset that doesn't exist when it is first
	   called, and keep it until it is unloaded 
	 - same as above, except we add a condition that an asset will
	   unload after a certain amount of time has passed with no
	   reference to it (though this would probably require a
	   different structure to accomodate lifespan, likely changing
	   to a map<string, pair<Texture, float>>)
	 - just cache the crap out of everything.

	 I think the most ideal system would combine the lifetime and
	 cacheing ideas, but this ideal system wouldnt even be necessary
	 unless the game got fairly large.  If that happens, we could
	 refactor this class for optimization and efficiency without
	 needing to touch the code anywhere else.

	 For now though, we'll just use the simplest idea, the first one.
	*/
	std::map<std::string, sf::Texture*> _textures;	//not sure if i should use image or texture...
	//std::map<std::string, sf::Sound*> _sounds;
	//std::map<std::string, sf::Music*> _music;
};

#endif