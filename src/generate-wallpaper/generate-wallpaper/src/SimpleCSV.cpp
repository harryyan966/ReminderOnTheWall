#include "../headers/SimpleCSV.h"
using namespace std;

SimpleCSV::SimpleCSV(const string& f) : file_name(f), total_Lines(0), chart(nullptr)
{
	ifstream fp(f, ios::binary);
	// find file length
	fp.seekg(0, ios::end);
	int flength = fp.tellg();
	fp.seekg(0, ios::beg);
	// read file
	char buffer = 0;
	int i = 0;
	while (i < flength)
	{
		fp.read(&buffer, sizeof(char));
		// LF only
		if ('\r' == buffer) {
			flength--;
			continue;
		}
		content.push_back(buffer);
		i++;
	}
	fp.close();
	// init chart
	total_Lines = findLineNumber();
	if (0 == total_Lines && flength != 0)	// the special
		total_Lines = 1;
	chart = new vector<string>[total_Lines];
	chart[0].push_back("");
	// fill the chart
	fillInChart();
}

void SimpleCSV::writeContent()
{
	content = chart2str(chart);
	ofstream fp = ofstream(file_name, ios::binary);
	for (int i = 0; i < content.size(); i++)
	{
		if ('\n' == content[i])
			fp.write("\r", sizeof(char));
		fp.write(&content[i], sizeof(char));
	}
	fp.close();
}

int SimpleCSV::findLineNumber()
{
	int n = 0;
	for (int i = 0; i < content.size(); i++)
		if ('\n' == content[i])
			n++;
	return n;
}

void SimpleCSV::fillInChart()
{
	int row = 0;
	int column = 0;
	char a = 0;
	for (int i = 0; i < content.size(); i++)
	{
		switch (content[i])
		{
		case '"':
			++i;
			while (true)
			{
				if ('"' == content[i] && '"' == content[i + 1])
					i++;
				else if ('"' == content[i])
					break;
				chart[row][column] += content[i];
				i++;
			}
			break;
		case ',':
			column++;
			chart[row].push_back("");
			break;
		case '\n':
			row++;
			column = 0;
			if (row < total_Lines)
				chart[row].push_back("");
			break;
		default:
			chart[row][column] += content[i];
			break;
		}
	}
}

string SimpleCSV::chart2str(const vector<string>* cht)
{
	string str = "";
	for (int i = 0; i < this->getTotalLines(); i++)
	{
		int row_length = cht[i].size();
		// if there is an empty cell at the back
		if (cht[i][cht[i].size() - 1].empty()) row_length--;	// discard the empty cell at the back
		for (int j = 0; j < row_length; j++)
		{
			if (-1 != cht[i][j].find(",") || -1 != cht[i][j].find("\""))
			{
				str += "\"";
				for (int k = 0; k < cht[i][j].size(); k++)
				{
					if ('"' == cht[i][j][k])
						str += "\"\"";
					else
						str += cht[i][j][k];
				}
				str += "\"";
			}
			else
				str += cht[i][j];
			str += ",";
		}
		str += "\n";
	}
	return str;
}
