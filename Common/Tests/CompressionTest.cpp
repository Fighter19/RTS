#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>

#include "Compression.h"

const char *testData =
	R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. 
Ut enim ad minim veniam, quis nostrud exercitation ullamco 
laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure
dolor in reprehenderit in voluptate velit esse cillum dolore eu
fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, 
sunt in culpa qui officia deserunt mollit anim id est laborum.)";

class CompressionTest : public ::testing::TestWithParam<CompressionType> {};

TEST_P(CompressionTest, CompressData) {
	CompressionType format = GetParam();
	Int inputLength = strlen(testData);
	Int maxCompressedSize = CompressionManager::getMaxCompressedSize(inputLength, format);
	EXPECT_GT(maxCompressedSize, 0) << "Max compressed size should be greater than 0 for format: " << format;
	UnsignedByte *compressedData = new UnsignedByte[maxCompressedSize];
	Int compressedSize =
		CompressionManager::compressData(format, (void *)testData, strlen(testData), compressedData, maxCompressedSize);
	EXPECT_GT(compressedSize, 0) << "Compression failed for format: " << format;
	CompressionType detectedType = CompressionManager::getCompressionType(compressedData, compressedSize);
	EXPECT_EQ(detectedType, format) << "Detected compression type does not match expected type for format: " << format;
	delete[] compressedData;
}

TEST_P(CompressionTest, DecompressData) {
	CompressionType format = GetParam();
	Int inputLength = strlen(testData);
	Int maxCompressedSize = CompressionManager::getMaxCompressedSize(inputLength, format);
	UnsignedByte *compressedData = new UnsignedByte[maxCompressedSize];
	Int compressedSize =
		CompressionManager::compressData(format, (void *)testData, inputLength, compressedData, maxCompressedSize);

	EXPECT_GT(compressedSize, 0) << "Compression failed for format: " << format;

	Int decompressedSize = CompressionManager::getUncompressedSize(compressedData, compressedSize);
	UnsignedByte *decompressedData = new UnsignedByte[decompressedSize];
	decompressedSize =
		CompressionManager::decompressData(compressedData, compressedSize, decompressedData, decompressedSize);

	EXPECT_EQ(decompressedSize, inputLength) << "Decompression size mismatch for format: " << format;
	EXPECT_EQ(memcmp(decompressedData, testData, inputLength), 0)
		<< "Decompressed data does not match original data for format: " << format;

	delete[] compressedData;
	delete[] decompressedData;
}

TEST_P(CompressionTest, CompressionTypeNames) {
	CompressionType format = GetParam();
	const char *name = CompressionManager::getCompressionNameByType(format);
	EXPECT_NE(name, nullptr) << "Compression type name should not be null for format: " << format;
	EXPECT_GT(strlen(name), 0) << "Compression type name should not be empty for format: " << format;
}

INSTANTIATE_TEST_CASE_P(CompressionTests, CompressionTest, ::testing::Range(COMPRESSION_REFPACK, COMPRESSION_MAX),
						[](const testing::TestParamInfo<CompressionTest::ParamType> &info) {
							// Can use info.param here to generate the test suffix
							std::string name = "CompressionTest_";
							name += CompressionManager::getCompressionNameByType(info.param);
							// Remove any whitespaces
							name.erase(std::remove_if(name.begin(), name.end(), isspace), name.end());
							// And any brackets
							name.erase(
								std::remove_if(name.begin(), name.end(), [](char c) { return c == '(' || c == ')'; }),
								name.end());
							return name;
						});