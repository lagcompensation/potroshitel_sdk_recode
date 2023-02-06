#include "context.h"

BOOL WINAPI DllMain( const HINSTANCE module, const DWORD reason_for_call, const LPVOID reversed ) {
	DisableThreadLibraryCalls( module );

	if ( reason_for_call == DLL_PROCESS_ATTACH ) {
		auto thread = CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )( context::on_dll_attach ), module, 0, 0 );

		if ( thread )
			CloseHandle( thread );
	}

	return TRUE;
}

void context::on_dll_attach( const HINSTANCE module ) {
	if ( !AllocConsole( ) )
		return;

	FILE* file;
	if ( freopen_s( &file, "CONOUT$", "w", stdout ) )
		return;

	SetConsoleTitle( "debug" );

	while ( !( GetModuleHandleA( "serverbrowser.dll" ) ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

#ifdef _DEBUG
	std::printf( "parse interfaces...\n" );
#endif
	{
		interfaces::parse( );
	}

#ifdef _DEBUG
	std::printf( "parse netvars...\n" );
#endif
	{
		netvars::parse( );
	}

#ifdef _DEBUG
	std::printf( "done...\n" );
#endif

#ifdef _DEBUG
	/* for test some shitty stuff. */
	if ( interfaces::m_engine_client ) {
		if ( interfaces::m_engine_client->is_in_game( ) ) {
			std::printf( "is_in_game: true.\n" );
		}
		else if ( interfaces::m_engine_client->is_connected( ) ) {
			std::printf( "is_connected: true.\n" );
		}
	}
#endif

#ifdef _DEBUG
	Beep( 600, 600 );
	Beep( 500, 500 );
	Beep( 300, 400 );
#endif

	while ( !( GetKeyState( VK_END ) ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

	/* destroy stuff here. */

#ifdef _DEBUG
	Beep( 600, 600 );
	Beep( 500, 500 );
	Beep( 300, 400 );
#endif

	FreeLibraryAndExitThread( module, 0 );
}