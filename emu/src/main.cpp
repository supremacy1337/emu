#include "stdafx.hpp"
#include "client/client.hpp"
#include "client/packet.hpp"
#include "utils/console.hpp"
#include "utils/generator.hpp"

int main( )
{
	log( "Steam: " );

	std::string id {};
	std::cin >> id;

	if ( id.empty( ) || !id.starts_with( "765" ) )
	{
		log( "Invalid SteamID64.\n" );
		return 1;
	}

	if ( !g_client->start( ) )
	{
		log( "Failed to connect to server.\n" );
		return 1;
	}

	log( "Connected!\n\n" );

	g_client->send_data( reinterpret_cast< const char * >( keep_alive ), 24 );

	const std::vector<identifier_t> items
	{
		{ 24,	g_generator->username( )	},
		{ 279,	g_generator->mac_address( ) },
		{ 311,	g_generator->guid( )		},
		{ 383,	id							},
	};

	for ( const auto &item : items )
	{
		for ( int i = 0; i < item.string.length( ); ++i )
		{
			authentication[ item.start_pos + i ] = static_cast< unsigned int > ( item.string[ i ] );
		}
	}

	g_client->send_data( reinterpret_cast< const char * >( authentication ), 416 );

	log( "\nRunning! GLHF!\n" );

	while ( true )
	{
		std::this_thread::sleep_for( 10s );

		g_client->send_data( reinterpret_cast< const char * >( keep_alive ), 24 );
	}
}

