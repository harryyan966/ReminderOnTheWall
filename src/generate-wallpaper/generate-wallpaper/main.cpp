#include <iostream>
#include <exception>
#include <string>
#include <libconfig.h++>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
libconfig::Config cfg;
bool getFont()
{
	return cfg.lookup("italic");
}

int main(int argc, char** argv)
{
	try
	{
		cfg.readFile("C:\\Users\\jossl\\github\\ReminderOnTheWall\\src\\static\\x64\\Debug\\bin\\settings.cfg");
		bool i = getFont();
		cout << i << endl;
	}
	catch (const libconfig::FileIOException& e)
	{
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
