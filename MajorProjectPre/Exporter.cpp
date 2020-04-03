#include "Exporter.h"


#pragma region Constructors


Exporter::Exporter(const std::string& outputFile)
	: filename(outputFile) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void Exporter::Open(std::string filename)
{
	out.open(filename);
}

void Exporter::Close()
{
	out.close();
}

void Exporter::PrintHeading()
{
	out << "Test Number" << ",";
	out << "Compression Level" << ",";
	out << "No. Tests" << ",";
	out << "Accuracy" << "\n\n";
}

void Exporter::AddData(int testNumber, float compressionLevel, int numberOfTests, float data)
{
	exportData.push_back(ExportData(testNumber, compressionLevel, numberOfTests, data));
}

void Exporter::Write()
{
	Open(filename);

	PrintHeading();

	for (int i = 0; i < exportData.size(); i++)
	{
		out << exportData[i].testNumber << ",";
		out << exportData[i].compressionLevel << ",";
		out << exportData[i].numberOfTests << ",";
		out << exportData[i].data << "\n";
	}

}

#pragma endregion