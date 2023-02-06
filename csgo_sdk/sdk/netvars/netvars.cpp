#include "netvars.h"

std::vector< std::string > split( std::string to_split, std::string delimeter ) {
	std::vector< std::string > split;
	int start = 0;
	int end = 0;

	while ( ( end = to_split.find( delimeter, start ) ) < to_split.size( ) ) {
		std::string val = to_split.substr( start, end - start );
		split.push_back( val );
		start = end + delimeter.size( );
	}

	if ( start < to_split.size( ) ) {
		std::string val = to_split.substr( start );
		split.push_back( val );
	}

	return split;
}

bool netvars::parse( ) {
	if ( !interfaces::m_client_dll )
		return false;

	auto all_classes = interfaces::m_client_dll->get_all_classes( );

	if ( !all_classes )
		return false;

	for ( ; all_classes; all_classes = all_classes->m_next )
		store_table( all_classes->m_recv_table->m_table_name, all_classes->m_recv_table );

	return true;
}

void netvars::store_table( const std::string& name, c_recv_table* table, std::size_t offset ) {
	for ( auto i = 0; i < table->m_props_count; ++i ) {
		auto prop = &table->m_props[ i ];
		auto child = prop->m_data_table;

		if ( child && child->m_props_count > 0 )
			store_table( name, child, prop->m_offset + offset );

		if ( !m_offsets[ name ][ prop->m_prop_name ].m_offset ) {
			m_offsets[ name ][ prop->m_prop_name ].m_datamap_var = false;
			m_offsets[ name ][ prop->m_prop_name ].m_prop_ptr = prop;
			m_offsets[ name ][ prop->m_prop_name ].m_offset = static_cast< size_t >( prop->m_offset + offset );
		}
	}
}

int netvars::get_client_id( const std::string& network_name ) {
	return m_client_ids[ network_name ];
}

int netvars::get( const std::string& table, const std::string& prop ) {
	return m_offsets[ table ][ prop ].m_offset;
}

int netvars::get_offset( const char* name ) {
	const auto items = split( name, "->" );

	if ( items.empty( ) )
		return 0;

	return m_offsets[ items.front( ) ][ items.back( ) ].m_offset;
}