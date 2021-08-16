#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include <libconfig.h++>
using std::string;
using std::ifstream;
using std::ofstream;
using libconfig::Config;

namespace WallpaperConfigConstants
{
	// Background Theme
	enum BackgroundTheme { dark = 0, light = 1 };

	// Font Face
	/* #0: normal size sans - serif font
	 * #1: small size sans - serif font
	 * #2: normal size sans - serif font(complex)
	 * #3: normal size serif font
	 * #4: normal size serif font(complex)
	 * #5: smaller version of serif font
	 * #6: hand - writing style font
	 * #7: more complex variant of #6
	 */

}

class WallpaperConfig
{
	Config cfg;
	char* wallpapaer_source_name;
	// text element list
	int number_text_elements;
	char** text_elements_list;

public:
	// need full path
	WallpaperConfig(const string &f);
	~WallpaperConfig();

	// accessor
	char* getWallpaperSource();
	int getBackgroundTheme() const;
	int getFontFace() const { return cfg.lookup("font"); }
	bool isItalic() const { return cfg.lookup("italic"); }
	// text elements
	char** getTextElements() const;

private:
	// Need C++17
	string wallpaperSourceCmdParser(const string& command);
};
