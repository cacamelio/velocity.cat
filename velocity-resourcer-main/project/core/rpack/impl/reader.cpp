#include <pch/stdafx.hpp>

namespace rpack {

	namespace detail {

		class rc4
		{
		public:
			rc4( const std::uint8_t* key, std::size_t key_size )
			{
				for ( std::size_t i = 0; i < 256; ++i )
				{
					this->m_s[ i ] = static_cast< std::uint8_t >( i );
				}

				std::uint8_t j = 0;
				for ( std::size_t i = 0; i < 256; ++i )
				{
					j = j + this->m_s[ i ] + key[ i % key_size ];
					std::swap( this->m_s[ i ], this->m_s[ j ] );
				}

				this->m_i = 0;
				this->m_j = 0;
			}

			void crypt( std::uint8_t* data, std::size_t size )
			{
				for ( std::size_t n = 0; n < size; ++n )
				{
					this->m_i = this->m_i + 1;
					this->m_j = this->m_j + this->m_s[ this->m_i ];
					std::swap( this->m_s[ this->m_i ], this->m_s[ this->m_j ] );

					const auto k = this->m_s[ static_cast< std::uint8_t >( this->m_s[ this->m_i ] + this->m_s[ this->m_j ] ) ];
					data[ n ] ^= k;
				}
			}

		private:
			std::uint8_t m_s[ 256 ]{};
			std::uint8_t m_i{ 0 };
			std::uint8_t m_j{ 0 };
		};

	} // namespace detail

	bool reader::load( const std::string& path )
	{
		std::ifstream file( path, std::ios::binary | std::ios::ate );
		if ( !file )
		{
			return false;
		}

		const auto file_size = static_cast< std::size_t >( file.tellg( ) );
		file.seekg( 0 );

		this->m_data.resize( file_size );
		if ( !file.read( reinterpret_cast< char* >( this->m_data.data( ) ), file_size ) )
		{
			return false;
		}

		return this->parse( );
	}

	bool reader::load( const void* data, std::size_t size )
	{
		this->m_data.assign( reinterpret_cast< const std::uint8_t* >( data ), reinterpret_cast< const std::uint8_t* >( data ) + size );
		return this->parse( );
	}

	bool reader::parse( )
	{
		if ( this->m_data.size( ) < 8 )
		{
			return false;
		}

		if ( *reinterpret_cast< std::uint32_t* >( this->m_data.data( ) ) != k_magic )
		{
			return false;
		}

		const auto count = *reinterpret_cast< std::uint32_t* >( this->m_data.data( ) + 4 );

		this->m_entries.clear( );
		this->m_entries.reserve( count );

		for ( std::uint32_t i = 0; i < count; ++i )
		{
			const auto toc_offset = 8 + i * 12;
			const auto id_val = *reinterpret_cast< std::uint32_t* >( this->m_data.data( ) + toc_offset );
			const auto offset = *reinterpret_cast< std::uint32_t* >( this->m_data.data( ) + toc_offset + 4 );
			const auto size = *reinterpret_cast< std::uint32_t* >( this->m_data.data( ) + toc_offset + 8 );

			this->m_entries[ id_val ] = { offset, size };

			detail::rc4 cipher( k_key, sizeof( k_key ) );
			cipher.crypt( this->m_data.data( ) + offset, size );
		}

		return true;
	}

	std::span<const std::uint8_t> reader::get( std::uint32_t resource_id ) const
	{
		const auto it = this->m_entries.find( resource_id );
		if ( it == this->m_entries.end( ) )
		{
			return { };
		}

		return { this->m_data.data( ) + it->second.offset, it->second.size };
	}

	const std::uint8_t* reader::data( std::uint32_t resource_id ) const
	{
		const auto span = this->get( resource_id );
		return span.empty( ) ? nullptr : span.data( );
	}

	std::size_t reader::size( std::uint32_t resource_id ) const
	{
		return this->get( resource_id ).size( );
	}

	bool reader::has( std::uint32_t resource_id ) const
	{
		return this->m_entries.contains( resource_id );
	}

} // namespace rpack