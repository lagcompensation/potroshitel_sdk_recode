#pragma once

#include "../datatypes/datatypes.h"

class c_variant;
class c_recv_table;
class c_recv_prop;
class c_recv_proxy_data;

/* ayo potroshitel wtf. */
class c_client_unknown;
class c_collideable;
class c_client_networkable;
class c_client_thinkable;
class c_client_renderable;
class c_base_entity;
class c_client_entity;
class c_base_handle;

using recv_var_proxy_fn = void( *)( const c_recv_proxy_data* data, void* struct_ptr, void* out_ptr );
using array_length_recv_proxy_fn = void( *)( void* struct_ptr, int object_id, int current_array_length );
using data_table_recv_var_proxy_fn = void( *)( const c_recv_prop* prop, void** out_ptr, void* data_ptr, int object_id );

using create_client_class_t = void *( * )( int ent_number, int serial_number );
using create_event_t = void *( * )( );

struct model_t {
	void* m_handle;
	char m_name[ 260 ];
	int m_load_flags;
	int m_server_count;
	int m_type;
	int m_flags;
	vec3_t m_mins;
	vec3_t m_maxs;
	float m_radius;
};

enum e_send_prop_type {
	_int = 0,
	_float,
	_vec,
	_vec_xy,
	_string,
	_array,
	_data_table,
	_int_64,
};

struct player_info_t {
	__int64 m_unknown;
	union {
		__int64 m_steam_id64;
		struct {
			__int32 m_xuid_low;
			__int32 m_xuid_high;
		};
	};

	char m_name[ 128 ];
	int m_used_id;
	char m_sz_steam_id[ 20 ];
	char m_pad_0x00A8[ 0x10 ];
	unsigned long m_steam_id;
	char m_friends_name[ 128 ];
	bool m_fake_player;
	bool m_is_hltv;
	unsigned int m_custom_files[ 4 ];
	unsigned char m_files_downloaded;
};

class c_variant {
public:
	union {
		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[ 3 ];
		__int64 m_int64;
	};

	e_send_prop_type m_type;
};

class c_recv_proxy_data {
public:
	const c_recv_prop* m_recv_prop;
	c_variant m_value;
	int m_element_index;
	int m_object_id;
};

class c_recv_prop {
public:
	char* m_prop_name;
	e_send_prop_type m_prop_type;
	int m_prop_flags;
	int m_buffer_size;
	int m_inside_of_array;
	const void* m_extra_data_ptr;
	c_recv_prop* m_array_prop;
	array_length_recv_proxy_fn m_array_length_proxy;
	recv_var_proxy_fn m_proxy_fn;
	data_table_recv_var_proxy_fn m_data_table_proxy_fn;
	c_recv_table* m_data_table;
	int m_offset;
	int m_element_stride;
	int m_elements_count;
	const char* m_parent_array_prop_name;
};

class c_recv_table {
public:
	c_recv_prop* m_props;
	int m_props_count;
	void* m_decoder_ptr;
	char* m_table_name;
	bool m_initialized;
	bool m_main_list;
};

class c_client_class {
public:
	create_client_class_t m_create_fn;
	create_event_t m_create_event_fn;
	char* m_network_name;
	c_recv_table* m_recv_table;
	c_client_class* m_next;
	int m_class_id;
};

class c_handle_entity {
public:
	virtual ~c_handle_entity( ) { }
	virtual void set_ref_handle( const c_base_handle& handle ) = 0;
	virtual const c_base_handle& get_handle( ) const = 0;
};

class c_client_unknown : public c_handle_entity {
public:
	virtual c_collideable* get_collideable( ) = 0;
	virtual c_client_networkable* get_client_networkable( ) = 0;
	virtual c_client_renderable* get_client_renderable( ) = 0;
	virtual c_client_entity* get_client_entity( ) = 0;
	virtual c_base_entity* get_base_entity( ) = 0;
	virtual c_client_thinkable* get_client_thinkable( ) = 0;
	virtual void* get_client_alpha_property( ) = 0;
};

class c_client_networkable {
public:
	virtual c_client_unknown* get_client_unknown( ) = 0;
	virtual void release( ) = 0;
	virtual c_client_class* get_client_class( ) = 0;
	virtual void notify_should_transmit( int state ) = 0;
	virtual void on_pre_data_changed( int update_type ) = 0;
	virtual void on_data_changed( int update_type ) = 0;
	virtual void pre_data_update( int update_type ) = 0;
	virtual void post_data_update( int update_type ) = 0;
	virtual void _unknown( void ) = 0;
	virtual bool is_dormant( void ) = 0;
	virtual int ent_index( void ) const = 0;
	virtual void receive_message( int class_id, void*& msg ) = 0;
	virtual void* get_data_table_base_ptr( ) = 0;
	virtual void set_destroyed_on_recreate_entities( void ) = 0;
};

class c_collideable {
public:
	virtual c_handle_entity* get_entity_handle( ) = 0;
	virtual vec3_t& get_mins( ) const = 0;
	virtual vec3_t& get_maxs( ) const = 0;
};

class c_client_thinkable {
public:
	virtual c_client_unknown* get_client_unknown( ) = 0;
	virtual void client_think( ) = 0;
	virtual void* get_think_handle( ) = 0;
	virtual void set_think_handle( void* hThink ) = 0;
	virtual void release( ) = 0;
};

class c_client_renderable {
public:
	virtual c_client_unknown* get_client_unknown( ) = 0;
	virtual vec3_t const& get_render_origin( void ) = 0;
	virtual vec3_t const& get_render_angles( void ) = 0;
	virtual bool should_draw( void ) = 0;
	virtual uint32_t render_flags( void ) = 0;
	virtual void unknown( void ) const {}
	virtual unsigned short get_shadow_handle( ) const = 0;
	virtual unsigned short& render_andle( ) = 0;
	virtual model_t* get_model( ) const = 0;
	virtual int draw_model( int flags, const uint32_t& instance ) = 0;
	virtual int get_body( ) = 0;
	virtual void get_color_modulation( float* color ) = 0;
	virtual bool lod_test( ) = 0;
	virtual bool setup_bones( matrix3x4_t* bone_to_world_out, int max_bones, uint32_t mask, float time ) = 0;
	virtual void setup_weights( const matrix3x4_t* bone_to_world_out, int flex_weight_count, float* flex_weights, float* flex_delayed_weights ) = 0;
	virtual void do_animation_events( void ) = 0;
	virtual void* get_pvs_notify_interface( ) = 0;
	virtual void get_render_bounds( vec3_t& mins, vec3_t& maxs ) = 0;
	virtual void get_render_bounds_world_space( vec3_t& mins, vec3_t& maxs ) = 0;
	virtual void get_shadow_render_bounds( vec3_t& mins, vec3_t& maxs, uint32_t shadow_type ) = 0;
	virtual bool should_receive_projected_textures( int flags ) = 0;
	virtual bool get_shadow_cast_distance( float* pDist, uint32_t shadow_type ) const = 0;
	virtual bool get_shadow_cast_direction( vec3_t, uint32_t shadow_type ) const = 0;
	virtual bool is_shadow_dirty( ) = 0;
	virtual void mark_shadow_dirty( bool dirty ) = 0;
	virtual c_client_renderable* get_shadow_parent( ) = 0;
	virtual c_client_renderable* first_shadow_child( ) = 0;
	virtual c_client_renderable* next_shadow_peer( ) = 0;
	virtual uint32_t shadow_cast_Type( ) = 0;
	virtual void create_model_instance( ) = 0;
	virtual unsigned short get_model_instance( ) = 0;
	virtual const matrix3x4_t& renderable_to_world_transform( ) = 0;
	virtual int lookup_attachment( const char* attachment_name ) = 0;
	virtual bool get_attachment( int number, vec3_t& origin, vec3_t& angles ) = 0;
	virtual bool get_attachment( int number, matrix3x4_t& matrix ) = 0;
	virtual float* get_render_clip_plane( void ) = 0;
	virtual int get_skin( ) = 0;
	virtual void on_threaded_draw_setup( ) = 0;
	virtual bool uses_flex_delayed_weights( ) = 0;
	virtual void record_tool_message( ) = 0;
	virtual bool should_draw_for_split_screen_user( int slot ) = 0;
	virtual uint8_t override_alpha_modulation( uint8_t alpha ) = 0;
	virtual uint8_t override_shadow_alpha_modulation( uint8_t alpha ) = 0;
};

class c_client_entity : public c_client_unknown, public c_client_renderable, public c_client_networkable, public c_client_thinkable {
public:
	virtual void release( void ) = 0;
};

class c_base_handle {
protected:
	unsigned long m_index;
public:
	c_base_handle( ) { m_index = INVALID_EHANDLE_INDEX; }
	c_base_handle( const c_base_handle& other ) { m_index = other.m_index; }
	c_base_handle( unsigned long value ) { m_index = value; }
	c_base_handle( int entry, int serial_num ) { init( entry, serial_num ); }

	__forceinline void init( int entry, int serial_num ) { m_index = static_cast< unsigned long >( entry | ( serial_num << NUM_SERIAL_NUM_SHIFT_BITS ) ); }
	__forceinline void term( ) { m_index = INVALID_EHANDLE_INDEX; }

	__forceinline bool is_valid( ) const { return m_index != INVALID_EHANDLE_INDEX; }

	__forceinline int get_entry_index( ) const { return is_valid( ) ? m_index & ENT_ENTRY_MASK : NUM_ENT_ENTRIES - 1; }

	__forceinline int get_serial_number( ) const { return m_index >> NUM_SERIAL_NUM_SHIFT_BITS; }

	__forceinline int to_int( ) const { return m_index; }

	__forceinline bool operator!=( const c_base_handle& other ) const { return m_index != other.m_index; }

	__forceinline bool operator==( const c_base_handle& other ) const { return m_index == other.m_index; }

	__forceinline bool operator==( c_handle_entity* entity ) const { return get( ) == entity; };

	__forceinline bool operator!=( c_handle_entity* entity ) const { return get( ) != entity; }

	__forceinline bool operator<( const c_base_handle& other ) const { return m_index < other.m_index; }

	__forceinline bool operator<( c_handle_entity* entity ) const { return m_index < ( entity ? entity->get_handle( ).m_index : INVALID_EHANDLE_INDEX ); }

	__forceinline c_base_handle& operator=( c_handle_entity* entity ) { return set( entity ); }

	__forceinline c_base_handle& set( c_handle_entity* entity ) {
		if ( entity )
			*this = entity->get_handle( );
		else
			m_index = INVALID_EHANDLE_INDEX;

		return *this;
	}

	c_handle_entity* get( ) const;
};

class c_net_channel_info {
public:
	enum {
		e_generic = 0,
		e_local_player,
		e_other_players,
		e_entites,
		e_sounds,
		e_events,
		e_user_messages,
		e_entity_messages,
		e_voice,
		e_stringtable,
		e_move,
		e_string_cmd,
		e_signon,
		e_total,
	};

	virtual const char* get_name( void ) const = 0;
	virtual const char* get_address( void ) const = 0;
	virtual float		get_time( void ) const = 0;
	virtual float		get_time_connected( void ) const = 0;
	virtual int			get_buffer_size( void ) const = 0;
	virtual int			get_data_rate( void ) const = 0;

	virtual bool		is_loop_back( void ) const = 0;
	virtual bool		is_timing_out( void ) const = 0;
	virtual bool		is_play_back( void ) const = 0;

	virtual float		get_latency( int flow ) const = 0;
	virtual float		get_average_latency( int flow ) const = 0;
	virtual float		get_average_loss( int flow ) const = 0;	
	virtual float		get_average_choke( int flow ) const = 0;
	virtual float		get_average_data( int flow ) const = 0;
	virtual float		get_average_packets( int flow ) const = 0;
	virtual int			get_total_data( int flow ) const = 0;
	virtual int			get_sequence_number( int flow ) const = 0;
	virtual bool		is_valid_packet( int flow, int frame_number ) const = 0;
	virtual float		get_packet_time( int flow, int frame_number ) const = 0;
	virtual int			get_packet_bytes( int flow, int frame_number, int group ) const = 0;
	virtual bool		get_stream_progress( int flow, int* received, int* total ) const = 0; 
	virtual float		get_since_last_time_recieved( void ) const = 0;
	virtual	float		get_command_interpolation_ammount( int flow, int frame_number ) const = 0;
	virtual void		get_packet_response_latency( int flow, int frame_number, int* latency_ms, int* choke ) const = 0;
	virtual void		get_remote_framerate( float* frame_time, float* frame_time_deviation ) const = 0;

	virtual float		get_timeout_seconds( ) const = 0;
};