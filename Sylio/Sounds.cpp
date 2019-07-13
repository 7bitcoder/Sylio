#include "Sounds.h"

Sounds::Sounds(std::string click_, std::string switch_)
{
	if (!switchBuffer.loadFromFile("../Sounds/"+switch_))
		exit(-1);
	switchSound.setBuffer(switchBuffer);
	switchSound.setVolume(30);

	if (!clickBuffer.loadFromFile("../Sounds/" + click_))
		exit(-1);
	clickSound.setBuffer(clickBuffer);
	clickSound.setVolume(100);
}

void Sounds::setVolume(float vol)
{
	switchSound.setVolume(30 * vol);
	clickSound.setVolume(100 * vol);
}

Sounds::~Sounds()
{

}
