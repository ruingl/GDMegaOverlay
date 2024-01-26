#pragma once
#include <cocos2d.h>
#include <array>
#include <vector>
#include <utility>

#include <Geode/loader/Hook.hpp>


inline constexpr std::size_t PATCHES_SIZE = 15;

namespace SafeMode
{
	using opcode = std::pair<unsigned long, std::vector<uint8_t>>;

	void updateState();

	// move to JsonHacks
	inline const std::array<opcode, PATCHES_SIZE> opcodes{
		// PlayLayer::levelComplete
		opcode{ 0x2DDC7E, { 0x0F, 0x84, 0xCA, 0x00, 0x00, 0x00 } },
		{ 0x2DDD6A, { 0x0F, 0x84, 0xEA, 0x01, 0x00, 0x00 } },
		{ 0x2DDD70, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },
		{ 0x2DDD77, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },
		{ 0x2DDEE5, { 0x90 } },
		{ 0x2DDF6E, { 0x0F, 0x84, 0xC2, 0x02, 0x00, 0x00 } },

		// PlayLayer::destroyPlayer
		{ 0x2E6BDE, { 0x90, 0xE9, 0xAD, 0x00, 0x00, 0x00 } },
		{ 0x2E6B32, { 0xEB, 0x0D } },
		{ 0x2E69F4, { 0x0F, 0x4C, 0xC1 } },
		{ 0x2E6993, { 0x90, 0xE9, 0x85, 0x01, 0x00, 0x00 } },

		// PlayLayer::incrementJumps
		{ 0x2EACD0, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },
		{ 0x2EACD6, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } }, // i have no clue what this inc instruction increments
		{ 0x2EACF7, { 0x90 } },

		// PlayLayer::resetLevel
		{ 0x2EA81F, { 0x6A, 0x00 } },
		{ 0x2EA83D, { 0x90 } }
	};
	inline std::array<geode::Patch*, PATCHES_SIZE> patches;
}
