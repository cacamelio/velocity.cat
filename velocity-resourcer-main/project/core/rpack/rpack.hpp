#pragma once

#include "ids.hpp"

namespace rpack {

	class writer
	{
	public:
		void add( std::uint32_t resource_id, const void* data, std::size_t size );

		template<typename T, std::size_t N>
		void add( std::uint32_t resource_id, const T( &arr )[ N ] )
		{
			add( resource_id, arr, sizeof( arr ) );
		}

		bool save( const std::string& path ) const;
		void clear( );

	private:
		struct entry
		{
			std::uint32_t resource_id{ 0 };
			std::vector<std::uint8_t> data{};
		};

		std::vector<entry> m_entries{};
	};

	class reader
	{
	public:
		bool load( const std::string& path );
		bool load( const void* data, std::size_t size );

		std::span<const std::uint8_t> get( std::uint32_t resource_id ) const;
		const std::uint8_t* data( std::uint32_t resource_id ) const;
		std::size_t size( std::uint32_t resource_id ) const;
		bool has( std::uint32_t resource_id ) const;

	private:
		bool parse( );

		struct entry
		{
			std::uint32_t offset{ 0 };
			std::uint32_t size{ 0 };
		};

		std::vector<std::uint8_t> m_data{};
		std::unordered_map<std::uint32_t, entry> m_entries{};
	};

} // namespace rpack