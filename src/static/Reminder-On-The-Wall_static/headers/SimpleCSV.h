#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::fstream;
using std::vector;

class SimpleCSV
{
	string file_name;
	string content;

	int total_Lines;
	vector<string>* chart;

public:
	SimpleCSV(string f, char mode);
	~SimpleCSV() {
		if (nullptr != chart) delete[] chart;
	}

	// accessors
	int getTotalLines() const { return total_Lines; }
	const vector<string>* getChart() const { return chart; }

private:
	int findLineNumber();
	void fillInChart();

};
