#include <SDL.h>
#include <unordered_map>
#include <cstring>
#include <string>
#include <iostream>
#include "SDLInputModule.hpp"
#include "RendererModule.hpp"

SDLInputModule::SDLInputModule(GBEmulator &emu) : _emu(emu) , _ctrl(false), _alt(false), _shift(false), _system(false), _capslock(false), _numlock(false)
{
	::memset(_joysticks.data(), 0, sizeof(_joysticks));
}

SDLInputModule::~SDLInputModule()
{
	this->closeJoysticks();
}

void			SDLInputModule::init()
{
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
	//Core::Console::get() << *this << " read gamepad mapping file and add " << SDL_GameControllerAddMappingsFromFile("resources/conf/gamecontrollerdb.txt") << " definitions" << std::endl;
}

bool			SDLInputModule::openJoystick(int id)
{
	auto		joy = SDL_GameControllerOpen(id);
	
	if (joy)
	{
		for (int i = 0; i < 8; ++i)
			if (_joysticks[i] == nullptr)
			{
				_joysticks[i] = joy;
				_joystickMapping[SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(joy))] = i;

				auto	name = std::string(SDL_GameControllerName(joy));
				if (!name.empty())
					name = "'" + name + "' ";
				std::cout << " gamepad " << name << "plugged and attributed to player " << (i + 1) << std::endl;
				break;
			}
	}
	else
		std::cout << " gamepad was plugged but was not recognized" << std::endl;

	return joy != nullptr;
}

void			SDLInputModule::closeJoystick(int id)
{
	auto		it = _joystickMapping.find(id);
	if (it != _joystickMapping.end())
	{
		if (SDL_GameControllerGetAttached(_joysticks[it->second]))
			SDL_GameControllerClose(_joysticks[it->second]);
		std::cout << " gamepad attributed to player " << (it->second + 1) << " was unplugged" << std::endl;
		_joysticks[it->second] = nullptr;
		_joystickMapping.erase(it);
	}
}

void			SDLInputModule::closeJoysticks()
{
	for (auto joy : _joysticks)
	{
		if (joy && SDL_GameControllerGetAttached(joy))
			SDL_GameControllerClose(joy);
	}
	::memset(_joysticks.data(), 0, sizeof(_joysticks));
	_joystickMapping.clear();
}

uint8_t			SDLInputModule::getJoystickId(int id) const
{
	auto		it = _joystickMapping.find(id);

	if (it == _joystickMapping.end())
		return 0;
	return it->second + 1;
}

void			SDLInputModule::update()
{
	SDL_Event ev;
  
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_CONTROLLERAXISMOTION:
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				break;
			case SDL_CONTROLLERBUTTONUP:
				break;
			case SDL_CONTROLLERDEVICEADDED:
				if (!this->openJoystick(ev.cdevice.which))
					continue;
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				this->closeJoystick(ev.cdevice.which);
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_MOUSEWHEEL:
				break;
			case SDL_TEXTINPUT:
				continue;
			case SDL_QUIT:
				break;
			case SDL_WINDOWEVENT:
				switch (ev.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						break;
					default:
						continue;
				}
				break;
			default:
				continue;
		}
		_emu.processInput(ev);
	}
}