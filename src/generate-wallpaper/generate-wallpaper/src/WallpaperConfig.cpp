#include "../headers/WallpaperConfig.h"
using namespace std;

WallpaperConfig::WallpaperConfig(const string& f) : cfg()
{
	cfg.readFile(f);
	wallpapaer_source_name = nullptr;
}

WallpaperConfig::~WallpaperConfig()
{
	cfg.~Config();
	if (nullptr != wallpapaer_source_name)
		delete[] wallpapaer_source_name;
}

char* WallpaperConfig::getWallpaperSource()
{
	string source = cfg.lookup("image_source");
	// command
	if ('<' == source[0])
	{
		string path = wallpaperSourceCmdParser(source.substr(1, source.find_last_of('>')));
		wallpapaer_source_name = new char[path.size() + 1];
		strcpy_s(wallpapaer_source_name, path.size() + 1, path.c_str());
	}
	else
	{
		wallpapaer_source_name = new char[source.size() + 1];
		strcpy_s(wallpapaer_source_name, source.size() + 1, source.c_str());
	}
	return wallpapaer_source_name;
}

int WallpaperConfig::getBackgroundTheme()
{
	string theme = cfg.lookup("background_theme");
	if ("dark" == theme) return WallpaperConfigConstants::BackgroundTheme::dark;
	else if ("light" == theme) return WallpaperConfigConstants::BackgroundTheme::light;
	return 0;	// default dark
}

int WallpaperConfig::getFontFace()
{
	return cfg.lookup("font");
}

bool WallpaperConfig::isItalic()
{
	return cfg.lookup("italic");
}

string WallpaperConfig::wallpaperSourceCmdParser(const string& command)
{
	string path("");
	// choose a random wallpaper under directory 'data/default_wallpaper/'
	// the program will run under 'bin/'
	if ("random")
	{
		int total_file = 0;
		for (const auto & entry : filesystem::directory_iterator("../data/default_wallpaper/"))
			total_file++;
		// randomly choose a file
		srand((unsigned int)time(NULL));
		int choice = rand() % total_file + 1;
		auto files = filesystem::directory_iterator("../data/default_wallpaper/");
		for (int i = 0; i < choice; i++, ++files)
		{
			path.assign((const char* const)files.operator*().path().c_str());
		}
	}
	else
		throw "Unknown Command!";
	return path;
}
