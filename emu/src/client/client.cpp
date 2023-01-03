#include "stdafx.hpp"
#include "client/client.hpp"

bool c_client::start( )
{
	WSADATA data {};
	if ( WSAStartup( MAKEWORD( 2, 2 ), &data ) != NO_ERROR )
		return false;

	if ( !( m_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) )
		return false;

	sockaddr_in addr {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr( "80.94.90.209" );
	addr.sin_port = htons( 5522 );

	if ( connect( m_socket, reinterpret_cast< sockaddr * >( &addr ), sizeof( addr ) ) < 0 )
		return false;

	return true;
}

int c_client::send_data( const char *buffer, int length )
{
	return send( m_socket, buffer, length, 0 );
}