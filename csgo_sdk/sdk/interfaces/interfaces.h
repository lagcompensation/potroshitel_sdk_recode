#pragma once

#include "../sdk.h"

namespace interfaces {
	class c_interface_reg {
	private:
		using instantiate_interface_fn = void* ( * )( );
	public:
		instantiate_interface_fn m_create_fn;
		const char* m_name;
		c_interface_reg* m_next;
	};

	template<typename T>
	static T* get_interface( const char* module_name, const char* interface_name, bool exact = false ) {
		T* i_interface = nullptr;
		c_interface_reg* m_interface_reg_list;

		int part_match_len = strlen( interface_name );
		DWORD interface_fn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( module_name ), "CreateInterface" ) );

		if ( !interface_fn )
			return nullptr;

		unsigned int jmp_start = ( unsigned int )( interface_fn ) + 4;
		unsigned int jmp_target = jmp_start + *( unsigned int* )( jmp_start + 1 ) + 5;

		m_interface_reg_list = **reinterpret_cast< c_interface_reg*** >( jmp_target + 6 );

		for ( c_interface_reg* curr = m_interface_reg_list; curr; curr = curr->m_next ) {
			if ( exact ) {
				if ( strcmp( curr->m_name, interface_name ) == 0 )
					i_interface = reinterpret_cast< T* >( curr->m_create_fn( ) );
			}
			else {
				if ( !strncmp( curr->m_name, interface_name, part_match_len ) && std::atoi( curr->m_name + part_match_len ) > 0 )
					i_interface = reinterpret_cast< T* >( curr->m_create_fn( ) );
			}
		}

		return i_interface;
	}

	inline i_client_dll* m_client_dll;
	inline i_engine_client* m_engine_client;
	inline i_client_entity_list* m_entity_list;
	inline i_global_vars* m_global_vars;

	void parse( );
};