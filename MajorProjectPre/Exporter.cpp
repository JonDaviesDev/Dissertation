#include "Exporter.h"


#pragma region Constructors


Exporter::Exporter(const std::string& outputFile)
	: filename(outputFile)
{
	Open(filename);
}

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
	out << "Test Number", "Compression Level", "No. Tests", "Accuracy", "\n\n";
}

void Exporter::AddData(int testNumber, float compressionLevel, int numberOfTests, float data)
{
	exportData.push_back(ExportData(testNumber, compressionLevel, numberOfTests, data));
}

void Exporter::Write(int iteration)
{
	out << exportData[iteration].testNumber << "," << exportData[iteration].compressionLevel << "," <<
		exportData[iteration].numberOfTests << "," << exportData[iteration].data << "\n";
}

#pragma endregion