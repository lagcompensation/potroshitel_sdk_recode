#pragma once

#include "../sdk.h"
#include "../other/other.h"
#include "../interfaces/interfaces.h"

namespace netvars {
	struct netvar_data_t {
		bool m_datamap_var;
		c_recv_prop* m_prop_ptr;
		std::size_t m_offset;
	};

	inline std::unordered_map< std::string, int > m_client_ids;
	inline std::unordered_map< std::string, std::unordered_map< std::string, netvar_data_t > > m_offsets;

	void store_table( const std::string& name, c_recv_table* table, std::size_t offset = 0 );
	int get_client_id( const std::string& network_name );
	int get( const std::string& table, const std::string& prop );
	int get_offset( const char* name );

	bool parse( );
};