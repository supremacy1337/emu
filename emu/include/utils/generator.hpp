#ifndef GENERATOR_H
#define GENERATOR_H

#include "stdafx.hpp"

class c_generator
{
public:
	c_generator( ) = default;
	~c_generator( ) = default;

	std::string username( )
	{
		std::string username = random_string( 6 );

		std::cout << "PC Name: " << username << "\n";

		return username;
	}

	std::string mac_address( )
	{
		std::string mac_address = random_preset( "XX-XX-XX-XX-XX-XX" );

		std::cout << "Mac Address: " << mac_address << "\n";

		return mac_address;
	}

	std::string guid( )
	{
		std::string guid = random_preset( "{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}" );

		std::cout << "GUID: " << guid << "\n";

		return guid;
	}
private:
	std::string random_string( std::size_t len, bool lowercase = true )
	{
		static std::string chrs = lowercase ? "0123456789abcdefghijklmnopqrstuvwxyz" : "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		thread_local static std::mt19937 rg { std::random_device{}( ) };
		thread_local static std::uniform_int_distribution<std::string::size_type> pick( 0, sizeof( chrs ) - 2 );

		std::string s;

		s.reserve( len );

		while ( len-- ) s += chrs[ pick( rg ) ];

		return s;
	}

	std::string random_preset( std::string string )
	{
		std::string result {};

		auto replace = [ & ]( unsigned int c )
		{
			switch ( c )
			{
				case 120:
					result += random_string( 1 );
					break;
				case 88:
					result += random_string( 1, false );
					break;
				default:
					result += c;
					break;
			}
		};

		std::for_each( string.begin( ), string.end( ), replace );

		return result;
	}
};

inline auto g_generator = std::make_unique<c_generator>( );

#endif
