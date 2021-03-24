#pragma once
#include <exception>
#include <json/json.h>
#include <string>
#include <fstream>
#include <ctime>
#include "generate.h"
using namespace Json;
using namespace std;
constexpr const char* DEFAULT_GROUPDATA_FILE = "group-data.json";
constexpr const char* DEFAULT_RUNTIMEDATA_FILE = "runtime-data.json";
class InfoIO
{
	string groupData, fnameGroupData;
	string runtimeData, fnameRuntimeData;

public:
	InfoIO(const string& file_full_path_groupdata, const string &file_full_path_runtimedata);
	InfoIO(const string &runtime_path,
		const string &file_rel_path_groupdata = DEFAULT_GROUPDATA_FILE,
		const string &file_rel_path_runtimedata = DEFAULT_RUNTIMEDATA_FILE);
	~InfoIO() {}

	void getUpdateTime(vector<int> &time);
	void getTodayDate(vector<int> &time);
	// group number starts from 1
	int getPreviousGroup(void);

	int readTotalGroups(void);
	void readGroupMembers(vector<string> &buf, int groupnum);

	void changeUpdateTime(vector<int> &time);
	void changePreviousGroup(int groupnum);
	
	void close(void);
};

