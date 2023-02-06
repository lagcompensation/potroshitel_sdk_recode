#include "interfaces.h"

void interfaces::parse( ) {
	m_client_dll = get_interface< i_client_dll >( "client.dll", "VClient018", true );
	m_engine_client = get_interface< i_engine_client >( "engine.dll", "VEngineClient014", true );
	m_entity_list = get_interface< i_client_entity_list >( "client.dll", "VClientEntityList003", true );

	m_global_vars = **( i_global_vars*** )( ( *( DWORD** )m_client_dll )[ 11 ] + 10 );
}