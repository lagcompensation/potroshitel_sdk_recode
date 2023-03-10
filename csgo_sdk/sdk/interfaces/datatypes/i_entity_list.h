#pragma once

class c_client_networkable;
class c_client_entity;
class c_base_handle;

class i_client_entity_list {
public:
	virtual c_client_networkable* get_client_networkable( int i ) = 0;
	virtual void* pad_0x1( void ) = 0;
	virtual void* pad_0x2( void ) = 0;
	virtual c_client_entity* get_client_entity( int i ) = 0;
	virtual c_client_entity* get_client_entity_from_handle( c_base_handle handle ) = 0;
	virtual int get_number_of_entities( bool include_non_networkable ) = 0;
	virtual int get_highest_entity_index( void ) = 0;
	virtual void set_max_entities( int max_entities ) = 0;
	virtual int get_max_entities( ) = 0;
};