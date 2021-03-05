#include "InfoIO.h"

InfoIO::InfoIO(const string& file_full_path_groupdata, const string& file_full_path_runtimedata)
	: groupData(""), runtimeData(""),
	fnameGroupData(file_full_path_groupdata), fnameRuntimeData(file_full_path_runtimedata)
{
	ifstream fpGroupData(file_full_path_groupdata, ios::in),
		fpRuntimeData(file_full_path_runtimedata, ios::in);
	if (!fpGroupData.is_open())
		throw exception(("Read \"" + file_full_path_groupdata + "\" failed").c_str());
	if (!fpRuntimeData.is_open())
		throw exception(("Read \"" + file_full_path_runtimedata + "\" failed").c_str());

	string temp;
	while (getline(fpGroupData, temp))
		groupData += temp + "\r\n";
	while (getline(fpRuntimeData, temp))
		runtimeData += temp + "\r\n";

	fpGroupData.close();
	fpRuntimeData.close();
}

InfoIO::InfoIO(const string& runtime_path, const string& file_rel_path_groupdata, const string& file_rel_path_runtimedata)
	: groupData(""), runtimeData("")
{
	string file_full_path_groupdata(generate::ChangeWallpaper::getBaseName(runtime_path.c_str()) + file_rel_path_groupdata);
	string file_full_path_runtimedata(generate::ChangeWallpaper::getBaseName(runtime_path.c_str()) + file_rel_path_runtimedata);
	this->fnameGroupData = file_full_path_groupdata;
	this->fnameRuntimeData = file_full_path_runtimedata;

	ifstream fpGroupData(file_full_path_groupdata, ios::in),
		fpRuntimeData(file_full_path_runtimedata, ios::in);
	if (!fpGroupData.is_open())
		throw exception(("Read \"" + file_full_path_groupdata + "\" failed").c_str());
	if (!fpRuntimeData.is_open())
		throw exception(("Read \"" + file_full_path_runtimedata + "\" failed").c_str());

	string temp;
	while (getline(fpGroupData, temp))
		groupData += temp + "\r\n";
	while (getline(fpRuntimeData, temp))
		runtimeData += temp + "\r\n";

	fpGroupData.close();
	fpRuntimeData.close();
}

void InfoIO::getUpdateTime(vector<int> &temp)
{
	Json::String errs;
	Json::Value root;
	Json::CharReaderBuilder readerBuilder;
	std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
	if (!reader->parse(this->runtimeData.c_str(),
		this->runtimeData.c_str() + this->runtimeData.length(), &root, &errs)
		|| !errs.empty())
		throw std::runtime_error("JSON read error!\nMessage:\n" + errs);
	
	// date should be yyyy-mm-dd
	if (3 != root["UpdateTime"].size())
		throw std::runtime_error("Date format error!");
	temp.clear();
	temp.push_back(root["UpdateTime"][0].asInt());
	temp.push_back(root["UpdateTime"][1].asInt() - 1);
	temp.push_back(root["UpdateTime"][2].asInt());
}

void InfoIO::getTodayDate(vector<int> &temp)
{
	time_t now = time(0);
	tm *gmtm = new tm;
	localtime_s(gmtm, &now);
	temp.clear();
	temp.push_back(gmtm->tm_year + 1900);
	temp.push_back(gmtm->tm_mon);
	temp.push_back(gmtm->tm_mday);
	delete gmtm;
}

int InfoIO::getPreviousGroup(void)
{
	Json::String errs;
	Json::Value root;
	Json::CharReaderBuilder readerBuilder;
	std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
	if (!reader->parse(this->runtimeData.c_str(),
		this->runtimeData.c_str() + this->runtimeData.length(), &root, &errs)
		|| !errs.empty())
		throw std::runtime_error("JSON read error!\nMessage:\n" + errs);
	
	return root["PreviousGroup"].asInt();
}

int InfoIO::readTotalGroups(void)
{
	Json::String errs;
	Json::Value root;
	Json::CharReaderBuilder readerBuilder;
	std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
	if (!reader->parse(this->groupData.c_str(),
		this->groupData.c_str() + this->groupData.length(), &root, &errs)
		|| !errs.empty())
		throw std::runtime_error("JSON read error!\nMessage:\n" + errs);

	return root["TotalGroups"].asInt();
}

void InfoIO::readGroupMembers(vector<string>& temp, int groupnum)
{
	Json::String errs;
	Json::Value root;
	Json::CharReaderBuilder readerBuilder;
	std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
	if (!reader->parse(this->groupData.c_str(),
		this->groupData.c_str() + this->groupData.length(), &root, &errs)
		|| !errs.empty())
		throw std::runtime_error("JSON read error!\nMessage:\n" + errs);

	temp.clear();
	unsigned int count = root["Groups"][groupnum].size();
	for (unsigned int i = 0; i < count; i++)
		temp.push_back(root["Groups"][groupnum][i].asString());
}

void InfoIO::changeUpdateTime(vector<int>& time)
{
	Json::Value root, data;
    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream stream;

	root["UpdateTime"][0] = time.at(0);	// year
	root["UpdateTime"][1] = time.at(1) + 1;	// month
	root["UpdateTime"][2] = time.at(2);	// date
	// copy previous group
	root["PreviousGroup"] = this->getPreviousGroup();
	// write
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &stream);	// write to stream 
	this->runtimeData = stream.str();
}

void InfoIO::changePreviousGroup(int groupnum)
{
	Json::Value root, data;
    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream stream;

	root["PreviousGroup"] = groupnum;
	// copy update time
	vector<int> date;
	this->getUpdateTime(date);
	root["UpdateTime"][0] = date[0];	// year
	root["UpdateTime"][1] = date[1];	// month
	root["UpdateTime"][2] = date[2];	// date
	// write
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    jsonWriter->write(root, &stream);	// write to stream 
	this->runtimeData = stream.str();
}

void InfoIO::close(void)
{
	ofstream fpGroupData(this->fnameGroupData, ios::trunc);
	ofstream fpRuntimeData(this->fnameRuntimeData, ios::trunc);
	if (!fpGroupData.is_open())
		throw exception(("Write \"" + this->fnameGroupData + "\" failed").c_str());
	if (!fpRuntimeData.is_open())
		throw exception(("Write \"" + this->fnameRuntimeData + "\" failed").c_str());
	while (string::npos != this->groupData.find("\r\n"))
		this->groupData.replace(this->groupData.find("\r\n"), 1, "");
	fpGroupData << this->groupData;
	fpRuntimeData << this->runtimeData;
	fpGroupData.close();
	fpRuntimeData.close();
}
