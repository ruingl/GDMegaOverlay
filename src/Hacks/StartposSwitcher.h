#pragma once

#include <vector>

#include <Geode/modify/StartPosObject.hpp>

namespace StartposSwitcher
{
	inline std::vector<StartPosObject*> startposObjects;
	inline int index = -1;

	StartPosObject* createHook();

	void change(bool right);
}
