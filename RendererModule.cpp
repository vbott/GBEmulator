#include <SDL_image.h>
#include <string>
#include "RendererModule.hpp"


RendererModule::RendererModule(GBEmulator &emu)
	: _emu(emu), _cursorVisibility(true), _screenshot(false), _vsync(false), _frameRate(0), _width(0), _height(0),
	_maxwidth(0), _maxheight(0), _mode(Window), _window(nullptr)
{
	this->init();
}

RendererModule::~RendererModule()
{
	SDL_DestroyTexture(_texture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}

void				RendererModule::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL: failed to initialised");
	
	int imgflags = IMG_INIT_JPG | IMG_INIT_PNG;
	int res = IMG_Init(imgflags);
	if (res != imgflags)
	{
		if ((res & IMG_INIT_JPG) == 0)
			throw std::runtime_error("SDL_IMAGE: failed to initialise jpeg support");
		if ((res & IMG_INIT_PNG) == 0)
			throw std::runtime_error("SDL_IMAGE: failed to initialise png support");
	}
	std::list<RendererModule::VideoMode> tmp = this->getAvailableResolutions();
	if (!tmp.empty())
	{
		_maxwidth = tmp.front().width;
		_maxheight = tmp.front().height;
	}

	std::string available_res;
	for (auto &res : tmp)
		available_res += std::to_string(res.width) + "x" + std::to_string(res.height) + "  ";
	available_res.resize(available_res.size() - 1);

	SDL_DisplayMode		 mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	auto		resolution = std::to_string(mode.w) + "x" + std::to_string(mode.h);

	this->setResolution(1280, 720);

	_screenshotPath = "./screenshots/";
}

#include <iostream>
void				RendererModule::update()
{
	this->clear();
	SDL_UpdateTexture(_texture, NULL, _emu.getPixels(), 160 * 4);
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
	if (_screenshot)
	{
		_screenshot = false;
		this->screenshot();
	}
	this->flip();
}

void				RendererModule::clear()
{
	SDL_RenderClear(_renderer);
}

void				RendererModule::flip()
{
	SDL_RenderPresent(_renderer);
}

void				RendererModule::screenshot()
{
	int				w = this->getWidth();
	int				h = this->getHeight();
	unsigned int	*imageData = new unsigned int[w * h];

	/*glReadPixels(0, 0, this->getWidth(), this->getHeight(), GL_BGRA, GL_UNSIGNED_BYTE, imageData);
	Core::Dispatcher::get().pushTask([=] {
		unsigned int *tmpi = new unsigned int[w * h];
		for (int i = 0; i < h; ++i)
			::memcpy(tmpi + ((h - i - 1) * w), imageData + (i * w), w * sizeof(int));
		SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(tmpi, w, h, 32, w * sizeof(int), 0, 0, 0, 0);
		Net::Directory::create(_screenshotPath);
		std::string		tmp(_screenshotPath + "screenshot_" + Net::Clock::getTimeInStr("%Y-%m-%d_%H-%M-%S") + ".bmp");
		SDL_SaveBMP(surface, tmp.c_str());
		SDL_FreeSurface(surface);
		delete[] tmpi;
		delete[] imageData;
		Core::Dispatcher::get().pushReturnTask([=] {
			Core::Console::get() << *this << " Screenshot saved at : " + tmp << std::endl;
		});
	});*/
}

SDL_Window	*RendererModule::getWindow()
{
	return _window;
}

int					RendererModule::getWidth() const
{
	return _width;
}

int					RendererModule::getHeight() const
{
  	return _height;
}

void				RendererModule::changeSize(int width, int height)
{
	_width = width;
	_height = height;
}

void				RendererModule::setResolution(int width, int height)
{
	if (_window)
	{
		if (SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN)
		{
			SDL_SetWindowFullscreen(_window, 0);
			SDL_SetWindowSize(_window, width, height);
			SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
		}
		else
			SDL_SetWindowSize(_window, width, height);
		this->changeSize(width, height);
	}
	else
	{
		_width = width;
		_height = height;
		this->updateWindow();
	}
}

void				RendererModule::setWindowMode(WindowMode mode)
{
	if (mode != _mode)
	{
		_mode = mode;
		this->updateWindow();
	}
}

RendererModule::WindowMode	RendererModule::getWindowMode() const
{
	return _mode;
}

void				RendererModule::showCursor(bool value)
{
	SDL_ShowCursor(value);
	_cursorVisibility = value;
}

bool				RendererModule::cursorIsVisible() const
{
	return _cursorVisibility;
}

void				RendererModule::enableVerticalSync(bool enable)
{

}

std::list<RendererModule::VideoMode>	RendererModule::getAvailableResolutions()
{
	std::list<RendererModule::VideoMode>	ret;

	SDL_DisplayMode	mode, prev;
	prev.w = 0;
	prev.h = 0;
	for (auto i = 0; i < SDL_GetNumDisplayModes(0); ++i)
	{
		SDL_GetDisplayMode(0, i, &mode);
		if (mode.w >= 800 && mode.h >= 600 && prev.w * prev.h != mode.w * mode.h)
			ret.push_back({ mode.w, mode.h });
		prev = mode;
	}
	return ret;
}

int										RendererModule::getNumMonitors()
{
	return SDL_GetNumVideoDisplays();
}

void				RendererModule::updateWindow()
{
	int				flags = 0;

	if (_mode == Fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	else if (_mode == Windowed)
		flags = SDL_WINDOW_BORDERLESS;
	if (_window)
	{
		SDL_SetWindowFullscreen(_window, flags);
		SDL_SetWindowBordered(_window, (flags & SDL_WINDOW_BORDERLESS) ? SDL_FALSE : SDL_TRUE);
	}
	else
	{
		int monitor = 0;
		_window = SDL_CreateWindow("GBemulator", SDL_WINDOWPOS_UNDEFINED_DISPLAY(monitor), SDL_WINDOWPOS_UNDEFINED_DISPLAY(monitor), 160, 144,
			SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE*/ | flags);
		SDL_SetWindowMinimumSize(_window, 160, 144);
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		auto icon = IMG_Load("favicon.png");
		if (icon)
		{
			SDL_SetWindowIcon(_window, icon);
			SDL_FreeSurface(icon);
		}
		_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	}
}

void				RendererModule::changeWindowMode(std::string const &mode)
{
	if (mode == "fullscreen")
		this->setWindowMode(Fullscreen);
	else if (mode == "windowed")
		this->setWindowMode(Windowed);
	else
		this->setWindowMode(Window);
}
