#ifndef CLIENT_H
#define CLIENT_H

class c_client
{
public:
	c_client( ) = default;
	~c_client( ) = default;

	bool start( );

	int send_data( const char *, int );
private:
	int m_socket { -1 };
};

inline auto g_client = std::make_unique<c_client>( );

#endif 
