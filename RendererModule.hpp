#pragma once
#include <list>
#include <SDL.h>
#include "GBEmulator.hpp"


class RendererModule : public Module
{
	public:
		struct VideoMode
		{
			int	width;
			int	height;
		};

		enum	WindowMode
		{
			Window,
			Windowed,
			Fullscreen
		};

		RendererModule(GBEmulator &emu);
		virtual ~RendererModule();
		void				init() override;
		void				update() override;
		void				clear();
		void				flip();
		void				screenshot();
		SDL_Window			*getWindow();
		int					getWidth() const;
		int					getHeight() const;
		void				changeSize(int width, int height);
		void				changeWindowMode(std::string const &mode);
		void				setResolution(int width, int height);
		void				setWindowMode(WindowMode mode);
		WindowMode			getWindowMode() const;
		void				showCursor(bool value = true);
		bool				cursorIsVisible() const;
		void				enableVerticalSync(bool enable = true);
		void				updateWindow();
		static std::list<VideoMode>	getAvailableResolutions();
		static int			getNumMonitors();

	protected:
		GBEmulator			&_emu;
		bool				_cursorVisibility;
		bool				_screenshot;
		bool				_vsync;
		int					_frameRate;
		int					_width;
		int					_height;
		int					_maxwidth;
		int					_maxheight;
		WindowMode			_mode;
		SDL_Window			*_window;
		SDL_Renderer 		*_renderer;
		SDL_Texture			*_texture;
		std::string			_screenshotPath;
};
