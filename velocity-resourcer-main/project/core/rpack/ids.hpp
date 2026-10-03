#pragma once

#include <cstdint>

namespace rpack {

	namespace detail
	{
		inline constexpr std::uint32_t counter_base{ __COUNTER__ };
	}

#define RPACK_ID ( __COUNTER__ - ::rpack::detail::counter_base - 1 )

	namespace fonts::font7
	{
		inline constexpr std::uint32_t regular{ RPACK_ID };
	}

	namespace fonts::inter
	{
		inline constexpr std::uint32_t regular{ RPACK_ID };
		inline constexpr std::uint32_t bold{ RPACK_ID };
	}

	namespace fonts::pixel7
	{
		inline constexpr std::uint32_t smallest{ RPACK_ID };
		inline constexpr std::uint32_t advanced{ RPACK_ID };
	}

	namespace fonts::weapons
	{
		inline constexpr std::uint32_t cs2{ RPACK_ID };
	}

	namespace images::icons
	{
		inline constexpr std::uint32_t logo{ RPACK_ID };
		inline constexpr std::uint32_t user{ RPACK_ID };
		inline constexpr std::uint32_t users{ RPACK_ID };
		inline constexpr std::uint32_t cog{ RPACK_ID };
		inline constexpr std::uint32_t file{ RPACK_ID };
		inline constexpr std::uint32_t skull{ RPACK_ID };
		inline constexpr std::uint32_t weather{ RPACK_ID };
		inline constexpr std::uint32_t brush{ RPACK_ID };
		inline constexpr std::uint32_t crosshair{ RPACK_ID };
		inline constexpr std::uint32_t bars{ RPACK_ID };
	}

	namespace particles::effects
	{
		inline constexpr std::uint32_t killstars{ RPACK_ID };
		inline constexpr std::uint32_t tracer{ RPACK_ID };
		inline constexpr std::uint32_t sparks{ RPACK_ID };
		inline constexpr std::uint32_t fade{ RPACK_ID };
		inline constexpr std::uint32_t halo{ RPACK_ID };
	}

	namespace particles::weather
	{
		inline constexpr std::uint32_t rain{ RPACK_ID };
		inline constexpr std::uint32_t snow{ RPACK_ID };
		inline constexpr std::uint32_t stars{ RPACK_ID };
	}

#undef RPACK_ID

	inline constexpr std::uint32_t k_magic{ 0x5250414B };
	inline constexpr std::uint8_t k_key[ ]{ 0x7A, 0x3F, 0x9E, 0x2D, 0x1C, 0x8B, 0x4A, 0x05, 0xE6, 0xC2, 0xD8, 0x49, 0xF1, 0xB7, 0x3A, 0x90, 0x5D, 0x2E, 0x8F, 0x6A, 0x3C, 0x1B, 0x90, 0x47, 0xA8, 0xF4, 0xE2, 0xC6, 0xD0, 0xB3, 0x91, 0x75 };

} // namespace rpack