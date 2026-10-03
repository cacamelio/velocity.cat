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

				std::uint8_t j{ 0 };
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

	void writer::add( std::uint32_t resource_id, const void* data, std::size_t size )
	{
		this->m_entries.push_back( { resource_id, std::vector<std::uint8_t>( reinterpret_cast< const std::uint8_t* >( data ), reinterpret_cast< const std::uint8_t* >( data ) + size ) } );
	}

	bool writer::save( const std::string& path ) const
	{
		std::ofstream out( path, std::ios::binary );
		if ( !out )
		{
			return false;
		}

		out.write( reinterpret_cast< const char* >( &k_magic ), sizeof( k_magic ) );

		const auto count = static_cast< std::uint32_t >( this->m_entries.size( ) );
		out.write( reinterpret_cast< const char* >( &count ), sizeof( count ) );
		auto data_offset = static_cast< std::uint32_t >( 8 + count * 12 );

		for ( const auto& entry : this->m_entries )
		{
			const auto id_val = static_cast< std::uint32_t >( entry.resource_id );
			const auto size = static_cast< std::uint32_t >( entry.data.size( ) );

			out.write( reinterpret_cast< const char* >( &id_val ), sizeof( id_val ) );
			out.write( reinterpret_cast< const char* >( &data_offset ), sizeof( data_offset ) );
			out.write( reinterpret_cast< const char* >( &size ), sizeof( size ) );

			data_offset += size;
		}

		for ( const auto& entry : this->m_entries )
		{
			std::vector<std::uint8_t> encrypted( entry.data );

			detail::rc4 cipher( k_key, sizeof( k_key ) );
			cipher.crypt( encrypted.data( ), encrypted.size( ) );

			out.write( reinterpret_cast< const char* >( encrypted.data( ) ), encrypted.size( ) );
		}

		return out.good( );
	}

	void writer::clear( )
	{
		this->m_entries.clear( );
	}

} // namespace rpack