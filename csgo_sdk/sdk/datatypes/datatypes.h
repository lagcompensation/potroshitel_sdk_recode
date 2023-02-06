#pragma once

#include "../sdk.h"

struct vec2_t {
	vec2_t( ) = default;
	vec2_t( float i_x, float i_y ) {
		x = i_x;
		y = i_y;
	}

	__forceinline vec2_t operator+( const vec2_t& value ) const { return vec2_t( x + value.x, y + value.y ); }

	__forceinline vec2_t operator-( const vec2_t& value ) const { return vec2_t( x - value.x, y - value.y ); }

	__forceinline vec2_t operator+( float value ) const { return vec2_t( x + value, y + value ); }

	__forceinline vec2_t operator-( float value ) const { return vec2_t( x - value, y - value ); }

	__forceinline vec2_t operator/( float value ) const { return vec2_t( x / value, y / value ); }

	__forceinline vec2_t operator*( float value ) const { return vec2_t( x * value, y * value ); }

	__forceinline vec2_t operator-( ) const { return vec2_t( -x, -y ); }

	__forceinline vec2_t& operator-=( const vec2_t& value ) {
		x -= value.x;
		y -= value.y;

		return *this;
	}

	__forceinline vec2_t& operator+=( const vec2_t& value ) {
		x += value.x;
		y += value.y;

		return *this;
	}

	__forceinline vec2_t& operator/=( float value ) {
		x /= value;
		y /= value;

		return *this;
	}

	__forceinline vec2_t& operator*=( float value ) {
		x *= value;
		y *= value;

		return *this;
	}

	__forceinline bool operator==( const vec2_t& value ) const { return x == value.x && y == value.y; }

	__forceinline bool operator!=( const vec2_t& value ) const { return !( operator==( value ) ); }

	__forceinline vec2_t& normalize( ) {
		const auto l = length( );

		if ( l > 0.f ) {
			x /= l;
			y /= l;
		}

		return *this;
	}

	__forceinline vec2_t normalized( ) const {
		auto ret = *this;

		return ret.normalize( );
	}

	__forceinline float length_sqr( ) const { return x * x + y * y; }

	__forceinline float length( ) const { return sqrt( length_sqr( ) ); }

	__forceinline float dot_product( const vec2_t& value ) const { return x * value.x + y * value.y; }

	__forceinline float dot_product( const float* value ) const { return x * value[ 0 ] + y * value[ 1 ]; }

	__forceinline float dist_to( const vec2_t& value ) const { return ( *this - value ).length( ); }

	__forceinline bool is_valid( ) const { return isfinite( x ) && isfinite( y ); }

	__forceinline bool empty( ) const { return x == 0.f && y == 0.f; }

	float x = 0.f;
	float y = 0.f;
};

struct vec3_t {
	vec3_t( ) = default;
	vec3_t( float i_x, float i_y, float i_z ) {
		x = i_x;
		y = i_y;
		z = i_z;
	}

	__forceinline vec3_t operator+( const vec3_t& value ) const { return vec3_t( x + value.x, y + value.y, z + value.z ); }

	__forceinline vec3_t operator-( const vec3_t& value ) const { return vec3_t( x - value.x, y - value.y, z - value.z ); }

	__forceinline vec3_t operator-( float value ) const { return vec3_t( x - value, y - value, z - value ); }

	__forceinline vec3_t operator+( float value ) const { return vec3_t( x + value, y + value, z + value ); }

	__forceinline vec3_t operator/( float value ) const { return vec3_t( x / value, y / value, z / value ); }

	__forceinline vec3_t operator*( float value ) const { return vec3_t( x * value, y * value, z * value ); }

	__forceinline vec3_t operator-( ) const { return vec3_t( -x, -y, -z ); }

	__forceinline vec3_t& operator-=( const vec3_t& value ) {
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}

	__forceinline vec3_t& operator+=( const vec3_t& value ) {
		x += value.x;
		y += value.y;
		z += value.z;

		return *this;
	}

	__forceinline vec3_t& operator/=( const vec3_t& value ) {
		x /= value.x;
		y /= value.y;
		z /= value.z;

		return *this;
	}

	__forceinline vec3_t& operator*=( const vec3_t& value ) {
		x *= value.x;
		y *= value.y;
		z *= value.z;

		return *this;
	}

	__forceinline vec3_t& operator/=( float value ) {
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	__forceinline vec3_t& operator*=( float value ) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	__forceinline bool operator==( const vec3_t& value ) const { return x == value.x && y == value.y && z == value.z; }

	__forceinline bool operator!=( const vec3_t& value ) const { return !( operator==( value ) ); }

	__forceinline float& operator[]( int i ) { return reinterpret_cast< float* >( this )[ i ]; }

	__forceinline const float operator[]( int i ) const { return reinterpret_cast< const float* >( this )[ i ]; }

	__forceinline vec3_t& normalize( ) {
		const auto l = length( );

		if ( l > 0.f ) {
			x /= l;
			y /= l;
			z /= l;
		}

		return *this;
	}

	__forceinline vec3_t normalized( ) const {
		auto ret = *this;

		return ret.normalize( );
	}

	__forceinline float length_sqr( ) const { return x * x + y * y + z * z; }

	__forceinline float length( ) const { return std::sqrt( length_sqr( ) ); }

	__forceinline float length_2d( ) const { return std::sqrt( x * x + y * y ); }

	__forceinline float dot_product( const vec3_t& value ) const { return x * value.x + y * value.y + z * value.z; }

	__forceinline float dot_product( const float* value ) const { return x * value[ 0 ] + y * value[ 1 ] + z * value[ 2 ]; }

	__forceinline vec3_t cross_product( const vec3_t& value ) const { return vec3_t( y * value.z - z * value.y, z * value.x - x * value.z, x * value.y - y * value.x ); }

	__forceinline float dist_to( const vec3_t& value ) const { return ( *this - value ).length( ); }

	__forceinline float dist_to_2d( const vec3_t& value ) const { return ( *this - value ).length_2d( ); }

	__forceinline bool is_valid( ) const { return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z ); }

	__forceinline bool empty( ) const { return x == 0.f && y == 0.f && z == 0.f; }

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

struct vec4_t : public vec3_t {
	vec4_t( ) = default;
	vec4_t( float i_x, float i_y, float i_z, float i_w ) {
		x = i_x;
		y = i_y;
		z = i_z;
		w = i_w;
	}

	vec4_t( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;
	}

	vec4_t( const vec2_t& value0, const vec2_t& value1 ) {
		x = value0.x;
		y = value0.y;
		z = value1.x;
		w = value1.y;
	}

	__forceinline vec4_t& operator=( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	__forceinline vec4_t& operator=( const vec4_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};


struct ALIGN16 vec4a_t : public vec3_t {
	vec4a_t( ) = default;
	vec4a_t( float i_x, float i_y, float i_z ) {
		x = i_x;
		y = i_y;
		z = i_z;
	}

	vec4a_t( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
	}

	__forceinline vec4a_t& operator=( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	__forceinline vec4a_t& operator=( const vec4a_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};

struct qangle_t {
	qangle_t( ) = default;
	qangle_t( float ix, float iy, float iz ) {
		x = ix;
		y = iy;
		z = iz;
	}

	float x = 0.f, y = 0.f, z = 0.f;

	__forceinline qangle_t operator+( const qangle_t& value ) const { return qangle_t( x + value.x, y + value.y, z + value.z ); }

	__forceinline qangle_t operator-( const qangle_t& value ) const { return qangle_t( x - value.x, y - value.y, z - value.z ); }

	__forceinline qangle_t operator-( float value ) const { return qangle_t( x - value, y - value, z - value ); }

	__forceinline qangle_t operator+( float value ) const { return qangle_t( x + value, y + value, z + value ); }

	__forceinline qangle_t operator/( float value ) const { return qangle_t( x / value, y / value, z / value ); }

	__forceinline qangle_t operator*( float value ) const { return qangle_t( x * value, y * value, z * value ); }

	__forceinline qangle_t& operator-=( const qangle_t& value ) {
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}

	__forceinline qangle_t& operator+=( const qangle_t& value ) {
		x += value.x;
		y += value.y;
		z += value.z;

		return *this;
	}

	__forceinline qangle_t& operator/=( float value ) {
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	__forceinline qangle_t& operator*=( float value ) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	__forceinline bool operator==( const qangle_t& value ) const { return x == value.x && y == value.y && z == value.z; }

	__forceinline bool operator!=( const qangle_t& value ) const { return !( operator==( value ) ); }

	qangle_t& normalize( ) {
		x = remainderf( x, 360.f );
		y = remainderf( y, 360.f );
		z = remainderf( z, 360.f );

		return *this;
	}

	__forceinline qangle_t normalized( ) const {
		auto ret = *this;

		return ret.normalize( );
	}

	__forceinline float length_sqr( ) const { return x * x + y * y + z * z; }

	__forceinline float length( ) const { return std::sqrt( length_sqr( ) ); }

	__forceinline float length_2d( ) const { return std::sqrt( x * x + y * y ); }

	__forceinline bool is_valid( ) const { return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z ); }

	__forceinline bool empty( ) const { return x == 0.f && y == 0.f && z == 0.f; }
};

struct matrix3x4_t {
	matrix3x4_t( ) = default;
	matrix3x4_t( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23 ) {
		m_value[ 0 ][ 0 ] = m00;
		m_value[ 0 ][ 1 ] = m01;
		m_value[ 0 ][ 2 ] = m02;
		m_value[ 0 ][ 3 ] = m03;

		m_value[ 1 ][ 0 ] = m10;
		m_value[ 1 ][ 1 ] = m11;
		m_value[ 1 ][ 2 ] = m12;
		m_value[ 1 ][ 3 ] = m13;

		m_value[ 2 ][ 0 ] = m20;
		m_value[ 2 ][ 1 ] = m21;
		m_value[ 2 ][ 2 ] = m22;
		m_value[ 2 ][ 3 ] = m23;
	}

	matrix3x4_t( const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& origin ) {
		m_value[ 0 ][ 0 ] = x_axis.x;
		m_value[ 0 ][ 1 ] = y_axis.x;
		m_value[ 0 ][ 2 ] = z_axis.x;
		m_value[ 0 ][ 3 ] = origin.x;

		m_value[ 1 ][ 0 ] = x_axis.y;
		m_value[ 1 ][ 1 ] = y_axis.y;
		m_value[ 1 ][ 2 ] = z_axis.y;
		m_value[ 1 ][ 3 ] = origin.y;

		m_value[ 2 ][ 0 ] = x_axis.z;
		m_value[ 2 ][ 1 ] = y_axis.z;
		m_value[ 2 ][ 2 ] = z_axis.z;
		m_value[ 2 ][ 3 ] = origin.z;
	}

	__forceinline vec3_t get_column( int column ) const { return vec3_t( m_value[ 0 ][ column ], m_value[ 1 ][ column ], m_value[ 2 ][ column ] ); }

	__forceinline void set_column( const vec3_t& value, int column ) {
		m_value[ 0 ][ column ] = value.x;
		m_value[ 1 ][ column ] = value.y;
		m_value[ 2 ][ column ] = value.z;
	}

	__forceinline void add_to_column( const vec3_t& value, int column ) {
		m_value[ 0 ][ column ] += value.x;
		m_value[ 1 ][ column ] += value.y;
		m_value[ 2 ][ column ] += value.z;
	}

	__forceinline matrix3x4_t operator+( const matrix3x4_t& value ) const {
		return matrix3x4_t(
			m_value[ 0 ][ 0 ] + value[ 0 ][ 0 ], m_value[ 0 ][ 1 ] + value[ 0 ][ 1 ], m_value[ 0 ][ 2 ] + value[ 0 ][ 2 ], m_value[ 0 ][ 3 ] + value[ 0 ][ 3 ],
			m_value[ 1 ][ 0 ] + value[ 1 ][ 0 ], m_value[ 1 ][ 1 ] + value[ 1 ][ 1 ], m_value[ 1 ][ 2 ] + value[ 1 ][ 2 ], m_value[ 1 ][ 3 ] + value[ 1 ][ 3 ],
			m_value[ 2 ][ 0 ] + value[ 2 ][ 0 ], m_value[ 2 ][ 1 ] + value[ 2 ][ 1 ], m_value[ 2 ][ 2 ] + value[ 2 ][ 2 ], m_value[ 2 ][ 3 ] + value[ 2 ][ 3 ]
		);
	}

	__forceinline matrix3x4_t operator*( const matrix3x4_t& value ) const {
		return matrix3x4_t(
			m_value[ 0 ][ 0 ] * value[ 0 ][ 0 ] + m_value[ 0 ][ 1 ] * value[ 1 ][ 0 ] + m_value[ 0 ][ 2 ] * value[ 2 ][ 0 ],
			m_value[ 0 ][ 0 ] * value[ 0 ][ 1 ] + m_value[ 0 ][ 1 ] * value[ 1 ][ 1 ] + m_value[ 0 ][ 2 ] * value[ 2 ][ 1 ],
			m_value[ 0 ][ 0 ] * value[ 0 ][ 2 ] + m_value[ 0 ][ 1 ] * value[ 1 ][ 2 ] + m_value[ 0 ][ 2 ] * value[ 2 ][ 2 ],
			m_value[ 0 ][ 0 ] * value[ 0 ][ 3 ] + m_value[ 0 ][ 1 ] * value[ 1 ][ 3 ] + m_value[ 0 ][ 2 ] * value[ 2 ][ 3 ] + m_value[ 0 ][ 3 ],
			m_value[ 1 ][ 0 ] * value[ 0 ][ 0 ] + m_value[ 1 ][ 1 ] * value[ 1 ][ 0 ] + m_value[ 1 ][ 2 ] * value[ 2 ][ 0 ],
			m_value[ 1 ][ 0 ] * value[ 0 ][ 1 ] + m_value[ 1 ][ 1 ] * value[ 1 ][ 1 ] + m_value[ 1 ][ 2 ] * value[ 2 ][ 1 ],
			m_value[ 1 ][ 0 ] * value[ 0 ][ 2 ] + m_value[ 1 ][ 1 ] * value[ 1 ][ 2 ] + m_value[ 1 ][ 2 ] * value[ 2 ][ 2 ],
			m_value[ 1 ][ 0 ] * value[ 0 ][ 3 ] + m_value[ 1 ][ 1 ] * value[ 1 ][ 3 ] + m_value[ 1 ][ 2 ] * value[ 2 ][ 3 ] + m_value[ 1 ][ 3 ],
			m_value[ 2 ][ 0 ] * value[ 0 ][ 0 ] + m_value[ 2 ][ 1 ] * value[ 1 ][ 0 ] + m_value[ 2 ][ 2 ] * value[ 2 ][ 0 ],
			m_value[ 2 ][ 0 ] * value[ 0 ][ 1 ] + m_value[ 2 ][ 1 ] * value[ 1 ][ 1 ] + m_value[ 2 ][ 2 ] * value[ 2 ][ 1 ],
			m_value[ 2 ][ 0 ] * value[ 0 ][ 2 ] + m_value[ 2 ][ 1 ] * value[ 1 ][ 2 ] + m_value[ 2 ][ 2 ] * value[ 2 ][ 2 ],
			m_value[ 2 ][ 0 ] * value[ 0 ][ 3 ] + m_value[ 2 ][ 1 ] * value[ 1 ][ 3 ] + m_value[ 2 ][ 2 ] * value[ 2 ][ 3 ] + m_value[ 2 ][ 3 ]
		);
	}

	__forceinline matrix3x4_t operator*( float value ) const {
		return matrix3x4_t(
			m_value[ 0 ][ 0 ] * value,
			m_value[ 0 ][ 1 ] * value,
			m_value[ 0 ][ 2 ] * value,
			m_value[ 0 ][ 3 ] * value,
			m_value[ 1 ][ 0 ] * value,
			m_value[ 1 ][ 1 ] * value,
			m_value[ 1 ][ 2 ] * value,
			m_value[ 1 ][ 3 ] * value,
			m_value[ 2 ][ 0 ] * value,
			m_value[ 2 ][ 1 ] * value,
			m_value[ 2 ][ 2 ] * value,
			m_value[ 2 ][ 3 ] * value
		);
	}

	__forceinline vec3_t operator*( const vec3_t& value ) const {
		return vec3_t(
			m_value[ 0 ][ 0 ] * value.x + m_value[ 0 ][ 1 ] * value.y + m_value[ 0 ][ 2 ] * value.z + m_value[ 0 ][ 3 ],
			m_value[ 1 ][ 0 ] * value.x + m_value[ 1 ][ 1 ] * value.y + m_value[ 1 ][ 2 ] * value.z + m_value[ 1 ][ 3 ],
			m_value[ 2 ][ 0 ] * value.x + m_value[ 2 ][ 1 ] * value.y + m_value[ 2 ][ 2 ] * value.z + m_value[ 2 ][ 3 ]
		);
	}

	__forceinline vec4_t& operator[]( int i ) { return m_value.at( i ); }

	__forceinline const vec4_t& operator[]( int i ) const { return m_value.at( i ); }

	std::array<vec4_t, 3u> m_value = {};
};

struct v_matrix {
	__forceinline vec4_t& operator[]( int i ) { return m_value.at( i ); }

	__forceinline const vec4_t& operator[]( int i ) const { return m_value.at( i ); }

	std::array<vec4_t, 4u> m_value = {};
};