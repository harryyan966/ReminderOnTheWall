#pragma once

#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::fstream;
using std::vector;
using std::to_string;

class SimpleCSV
{
	string file_name;
	string content;

	int total_Lines;
	vector<string>* chart;

public:
	SimpleCSV(string f);
	~SimpleCSV() {
		if (nullptr != chart) delete[] chart;
	}

	// accessors
	const vector<string>* getChart() const { return chart; }
	int getTotalLines() const { return total_Lines; }
	/* get the number of cell from a certain row
	 * @param i index of a row
	 * @ret amount of cells in this row (without the last vacant cell)
	 */
	int getRowLength(int i) const { return chart[i].size() - 1; }
	/* get the value from a certain cell
	 * @ret the value in the cell
	 */
	string getCell(int row, int column) const {
		if (row > getTotalLines() || column > getRowLength(row))
			throw string("Index Out of Range!\nWhen accessing the cell (") +
					to_string(row) + "," + to_string(column) + ")\n";
		return chart[row][column];
	}

	// mutators
	/* set the selected cell to a certain value
	 * @param val the value is to set;
	 */
	void setCell(int row, int column, string val)
	{
		if (row > getTotalLines() || column > getRowLength(row))
			throw string("Index Out of Range!\nWhen accessing the cell (") +
			to_string(row) + "," + to_string(column) + ")\n";
		chart[row][column] = val;
	}
	/* update the file with data in the chart */
	void writeContent();

private:
	int findLineNumber();
	void fillInChart();
	string chart2str(const vector<string>* cht);

};
