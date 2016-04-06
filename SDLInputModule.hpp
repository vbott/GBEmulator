#pragma once
#include <map>
#include <array>
#include "GBEmulator.hpp"

class SDLInputModule : public Module
{
public:
	SDLInputModule(GBEmulator &emu);
	virtual ~SDLInputModule();

	void	init() override;
	void 	update() override;

private:
	bool	openJoystick(int id);
	void	closeJoystick(int id);
	void	closeJoysticks();
	uint8_t	getJoystickId(int id) const;
	//void	resetJoystickAxis(int axis, int joystickId);

	GBEmulator	&_emu;
	std::map<int, uint8_t>							_joystickMapping;
	std::array<SDL_GameController*, 8>				_joysticks;
	bool	_ctrl;
	bool	_alt;
	bool	_shift;
	bool	_system;
	bool	_capslock;
	bool	_numlock;
};
