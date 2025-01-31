#include "PhysicsBypass.h"
#include "Settings.hpp"
#include "Macrobot/Macrobot.h"
#include <Geode/modify/PlayLayer.hpp>
#include "util.hpp"

class $modify(PlayLayer)
{
    bool init(GJGameLevel* p0, bool p1, bool p2)
    {
        PhysicsBypass::timestamp = p0->m_timestamp;
        bool res = PlayLayer::init(p0, p1, p2);

        return res;
    }

    void resetLevel()
    {
        PlayLayer::resetLevel();
        PhysicsBypass::calculateTickrate();
    }
};

void PhysicsBypass::calculateTickrate()
{
    float tps = 240.f;

	if (Settings::get<bool>("general/tps/enabled"))
		tps = Settings::get<float>("general/tps/value", 240.f);
	else
		tps = 240.f;

	if(Macrobot::playerMode == Macrobot::PLAYBACK)
		tps = Macrobot::macro.framerate;

	if(tps < 1.f)
		tps = 1.f;

	util::Write<float>(base::get() + 0x49D548, 1.f / tps);

    float timestampMultiplier = (tps / 240.f);
    
    if(tps == 240.f)
        timestampMultiplier = 1.f;
    
    if(GameManager::get()->getPlayLayer())
    {
        float stepsMultiplier = (timestamp * timestampMultiplier) / GameManager::get()->getPlayLayer()->m_level->m_timestamp;
        GameManager::get()->getPlayLayer()->m_level->m_timestamp = timestamp * timestampMultiplier;
        GameManager::get()->getPlayLayer()->m_gameState.m_unk1f8 *= stepsMultiplier;
    }
}