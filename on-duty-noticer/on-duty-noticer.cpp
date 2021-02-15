#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

// get base name
string getBaseName(const char* argv);
// under the same dir or its sub dir only 
void change_wallpaper(string base, const char *fname);

int main(int argc, char *argv[])
{
	// change the wallpaper
	change_wallpaper(getBaseName(argv[0]), "temp.png");
	cout << "Wallpaper is changed.\nThe program will quit in 10 seconds...";
	Sleep(1000 * 10);
	return 0;
}

string getBaseName(const char* argv)
{
	string path(argv);
	while ('\\' != path.back())
		path.pop_back();
	return path;
}

void change_wallpaper(string base, const char *fname)
{
	base += fname;
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0,
		(PVOID)base.c_str(),
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}
