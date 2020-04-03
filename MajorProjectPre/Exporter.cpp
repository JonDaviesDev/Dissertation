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
	out << "Accuracy" << ",";
	out << "No. Orginial Characters" << ",";
	out << "Matched Characters" << "\n\n";
}

void Exporter::AddData(int testNumber, float compressionLevel, int numberOfTests, float data, int originalCharacterCount, int MatchedCharaterCount)
{
	exportData.push_back(ExportData(testNumber, compressionLevel, numberOfTests, data, originalCharacterCount, MatchedCharaterCount));
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
		out << exportData[i].data << ",";
		out << exportData[i].originalCharacterCount << ",";
		out << exportData[i].matchedCharacterCount << "\n";
	}

}

#pragma endregion