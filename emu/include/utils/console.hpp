#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdafx.hpp"

class c_console
{
public:
	c_console( )
	{
		SetConsoleTitleA( "" );

		std::atexit( [ ]( )
		{
			std::this_thread::sleep_for( 10s );
		} );
	}

	~c_console( ) = default;

	template< typename ... arg >
	void print( const std::string &format, arg ... a )
	{
		auto const size = 1ull + std::snprintf( nullptr, 0, format.c_str( ), a ... );

		const std::unique_ptr<char[ ]> buf( new char[ size ] );
		std::snprintf( buf.get( ), size, format.c_str( ), a ... );

		std::cout << std::string( buf.get( ), buf.get( ) + size - 1 );
	}
};

inline auto g_console = std::make_unique<c_console>( );

#define log(...) g_console->print( __VA_ARGS__ );

#endif 