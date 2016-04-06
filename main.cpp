#include <string>
#include <iostream>
#include "GBEmulator.hpp"
#include "RendererModule.hpp"
#include "SDLInputModule.hpp"


#if defined (_WIN32)
#include <windows.h>
#include <direct.h>
#define chdir _chdir
#define Pause() system("Pause")
#undef main
#else
#define Pause()
#endif

int	main(int ac, char **av)
{
	#if defined (WIN32)
	std::string		path(GetCommandLine());

	if (path[0] == '"')
		path = path.substr(1, path.size() - 3);
	path = path.substr(0, path.rfind('\\'));
	_chdir(path.c_str());
	#else
	std::string		path = av[0];
	path = path.substr(0, path.rfind('/'));
	chdir(path.c_str());
	{
		char buffer[256];
		getcwd(buffer, 256);
		path.assign(buffer);
	}
	#endif

	try
	{
		GBEmulator emulator;
		emulator.addModule<SDLInputModule>(emulator);
		//emulator.addModule<LogicModule>(emulator);
		emulator.addModule<RendererModule>(emulator);
		emulator.run();
		return 1;
	}
	catch (std::exception &e)
	{
		std::cerr << "Unhandled std::exception : " << e.what() << std::endl;
		Pause();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unhandled Exception" << std::endl;
		Pause();
		return 1;
	}
}

#if defined (WIN32)
int	CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	main(__argc, __argv);
}
#endif
