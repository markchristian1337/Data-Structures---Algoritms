#include <iostream>
#include <cfloat>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "unorderedLinkedList.h"

#include "msTreeType.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: cluster \"A=<file>;C=<file>\"" << std::endl;
		return -1;
	}

	ArgumentManager am(argc, argv);
	string infile = am.get("A");
	string outfile = am.get("C");

	ifstream readfile;														//input file
	ofstream outputfile;													//output file

	readfile.open(infile.c_str(), ios::in);
	outputfile.open(outfile.c_str(), ios::out);

	int howbig = 0;
	string line;
	int i = 0;
	while (!readfile.eof()) {
		getline(readfile, line);
		if (line == "") {
			howbig = i;
			break;
		}
		else {
			i++;
		}
	};
	while (!readfile.eof()) {
		getline(readfile, line);
		if (line == "") {
			break;
		}
	};
	int cluster = 0, clusterCount= 1;
	readfile >> cluster;

	if (cluster < 1 || !readfile || cluster > howbig) {
		outputfile << "";
	}
	else {
		msTreeType<int> msGraph(howbig);
		readfile.clear();
		readfile.seekg(0, ios::beg);


		msGraph.createSpanningGraph(readfile, outputfile);
		msGraph.minimumSpanning(0);
		msGraph.adjustTree();
		//msGraph.breadthFirstTraversal();

		while (clusterCount< cluster) {
			//msGraph.printTreeAndWeight();
			msGraph.needToCut();
			//msGraph.minimumSpanning(0);
			msGraph.adjustTree();
			clusterCount++;
		}

		msGraph.breadthFirstTraversal(outputfile);
	}

	readfile.close();
  	outputfile.close();
	system("pause");
	return 0;
}
