#pragma once

class i_global_vars;

class i_client_dll {
public:
	virtual int connect( void* factory, i_global_vars* globals ) = 0;
	virtual int disconnect( ) = 0;
	virtual int init( void* factory, i_global_vars* globals ) = 0;
	virtual void post_init( ) = 0;
	virtual void shutdown( ) = 0;
	virtual void level_init_pre_entity( char const* map_name ) = 0;
	virtual void level_init_post_entity( ) = 0;
	virtual void level_shutdown( ) = 0;
	virtual c_client_class* get_all_classes( ) = 0;
};