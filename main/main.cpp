#include <launcher/main.h>
int main( int argc, char** argv ) {
	return launcher();
}

#ifndef _DEBUG
int __stdcall WinMain( HINSTANCE hin, HINSTANCE prev, LPSTR lp, int cmd ) {
	return main( 1, &lp );
}
#endif // ~_DEBUG