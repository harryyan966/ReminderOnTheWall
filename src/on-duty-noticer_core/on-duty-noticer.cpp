#include <iostream>
#include <string>
#include <io.h>
#include "generate.h"
#include "InfoIO.h"
using namespace std;
constexpr int DEFAULT_RESOLUTION[1][2] = {
	{ 1920, 1080 }
};	// extendable
#define DEFAULT_FONTCOLOR (cv::Scalar(255, 255, 255))
constexpr const char *DEFAULT_FONT = "隶书";
constexpr int FONTSZ_GROUPMEMBERS = 72;
constexpr int FONTSZ_DATE = 144;
constexpr int FONTSZ_GROUPNUM = 216;
constexpr int POS_DATE[2] = { 510, 225 };
constexpr int POS_GROUPNUM[2] = { 580, 400 };
constexpr int POS_GROUPMEMBERS[4][2] = {
	{ 675, 550 },
	{ 675, 425 },
	{ 675, 290 },
	{ 675, 145 }
};

int main_process(int argc, char *argv[]);
int main(int argc, char *argv[])
{
	try {
        return main_process(argc, argv);
	}
	catch (const std::exception& e) {
		cout << "\n+--------------------------------------+\n";
		cout <<   "*           An Error Occurs!           *\n";
		cout <<   "+--------------------------------------+\n";
		Sleep(500);
		cout << "Information:\n";
		cout << e.what();
		cout << "\n\n";
		cout << "The program will quit in 30 seconds...\n";
		Sleep(1000 * 30);	// Sleep 30 seconds...
		return -1;
	}
	return 0;	// I guess, this would never be reached
}

int main_process(int argc, char *argv[])
{
	int present_group = -1;		// this is initialized because we don't know
								// if it's necessary to update the wallpaper
	vector<int> present_time;
    vector<string> group_members;
    // Read Information
	{
		InfoIO  data(argv[0]);
		vector<int> update_time;
		int previous_group = data.getPreviousGroup();
		int total_group = data.readTotalGroups();
		data.getUpdateTime(update_time);
		data.getTodayDate(present_time);
		if (update_time == present_time)
		{
			cout << "It's not the time to change the on-duty group\n";
			cout << "\n\nThe program is going to quit in 5 seconds...\n";
			goto END;
		}
		// get present group
		present_group = previous_group == (total_group - 1) ? 0 : previous_group + 1;
		data.readGroupMembers(group_members, present_group);
		// change runtime info
		data.changePreviousGroup(present_group);
		data.changeUpdateTime(present_time);
		data.close();
	}
	// generate output data
	// change the wallpaper
	{
        string str_group_members;
        int position_group_members[2];
		string str_date;
		string str_groupnum;
		// str_group_members
		int group_members_num = group_members.size();
		for (int i = 0; i < group_members_num - 1; i++)
			str_group_members += group_members[i] + ", ";
		str_group_members += group_members.back();
		// position_group_members
		position_group_members[0] = POS_GROUPMEMBERS[group_members_num - 3][0];
		position_group_members[1] = POS_GROUPMEMBERS[group_members_num - 3][1];
		if (3 == group_members_num) position_group_members[1] += (22 - str_group_members.size()) / 2 * 35;
		else if (4 == group_members_num) position_group_members[1] += (30 - str_group_members.size()) / 2 * 35;
		else if (5 == group_members_num) position_group_members[1] += (38 - str_group_members.size()) / 2 * 35;
		else if (6 == group_members_num) position_group_members[1] += (46 - str_group_members.size()) / 2 * 35;
		// str_date
		str_date += to_string(present_time[0]) + "年";		// Year
		str_date += to_string(present_time[1] + 1) + "月";	// Month
		str_date += to_string(present_time[2]) + "日";		// Date
		// str_groupnum
		str_groupnum += to_string(present_group + 1) + "组值日";

		// generate the wallpaper
		string file_name = generate::ChangeWallpaper::getBaseName(argv[0]) + "wallpaper.png";
		if (-1 == _access(file_name.c_str(), 4)/* readable */)
		{
            file_name = generate::ChangeWallpaper::getBaseName(argv[0]) + "wallpaper.jpg";
			if (-1 == _access(file_name.c_str(), 4)/* readable */)
				throw std::runtime_error(string("No supported image file!\n") +
					"The image file should be under the executable directory,\n" +
					"and name it as \"wallpaper.png\" or \"wallpaper.jpg\".\n");
		}
		generate::ChangeWallpaper obj(file_name.c_str());
		obj.resize(1920, 1080);
		obj.changeBrightness(-65);
		// put text
		obj.putTextZH(str_date.c_str(), cv::Point(POS_DATE[0], POS_DATE[1]),				// The Date
			DEFAULT_FONTCOLOR, FONTSZ_DATE, DEFAULT_FONT);									// 
		obj.putTextZH(str_groupnum.c_str(), cv::Point(POS_GROUPNUM[0], POS_GROUPNUM[1]),	// The On-Duty Group
			DEFAULT_FONTCOLOR, FONTSZ_GROUPNUM, DEFAULT_FONT);								//
		obj.putTextZH(str_group_members.c_str(),											// The Group Members
			cv::Point(position_group_members[1], position_group_members[0]),				// 
			DEFAULT_FONTCOLOR, FONTSZ_GROUPMEMBERS, DEFAULT_FONT);							// 
		
		// set the wallpaper
		obj.save(argv[0], "temp.png");
		obj.changeWallpaper(argv[0], "temp.png");
	}

	cout << "Wallpaper is changed.\n\n\nThe program will quit in 5 seconds...\n";
END:
	Sleep(1000 * 5);
	return 0;
}
