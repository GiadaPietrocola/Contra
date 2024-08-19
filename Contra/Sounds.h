#pragma once

#include <QSoundEffect>

namespace Contra
{
	class Sounds;
}

class Contra::Sounds
{
private:

	// sounds indexed by filename
	std::map< std::string, QSoundEffect*> _sounds;
	std::map< std::string, QSoundEffect*> _musics;

	Sounds();

public:

	// singleton
	static Sounds* instance();

	// controls
	void playSound(const std::string& id);
	void playMusic(const std::string& id, bool loop = true);
	void stopMusic(const std::string& id);
};