#include <SimpleCSV.h>
#include <fstream>
using namespace std;

#include <iostream>

SimpleCSV::SimpleCSV(string f, char mode) : file_name(f), total_Lines(0), chart(nullptr)
{
	if ('r' == mode)
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
		// init chart
		total_Lines = findLineNumber();
		chart = new vector<string>[total_Lines];
		chart[0].push_back("");
		// fill the chart
		fillInChart();
	}
	else if ('w' == mode)
	{
		// pass
	}
	else throw "Unexpected mode!";
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
