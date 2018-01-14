#include "gtest/gtest.h"
#include "stringutil.h"

using namespace Utils;

TEST(StringUtil_Tokenize, SingleWord) {
  UStringVector output;

  StringUtil::Tokenize("hello", output);

  ASSERT_EQ(output.size(), 1);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
}

TEST(StringUtil_Tokenize, TwoWords) {
  UStringVector output;

  StringUtil::Tokenize("hello world!", output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesMiddle) {
  UStringVector output;

  StringUtil::Tokenize("hello     world!", output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesEnding) {
  UStringVector output;

  StringUtil::Tokenize("hello world!   ", output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesBoth) {
  UStringVector output;

  StringUtil::Tokenize("hello     world!   ", output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsHangul) {
  UStringVector output;

  StringUtil::Tokenize("연인이나 친구", output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("연인이나"));
  ASSERT_EQ(output[1], UString::fromUTF8("친구"));
}

TEST(StringUtil_Tokenize, ThreeWordsDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice\"", output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice"));
}

TEST(StringUtil_Tokenize, ThreeWordsSingleDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice", output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice"));
}

TEST(StringUtil_Tokenize, ThreeWordsDoubleQuotesWhitespaces) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice  to meet   you\"", output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice  to meet   you"));
}

TEST(StringUtil_Tokenize, EscapedDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("\\\"hello world \\\" \"nice to \\\"meet\\\" you\"", output);

  ASSERT_EQ(output.size(), 4);
  ASSERT_EQ(output[0], UString::fromUTF8("\"hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("\""));
  ASSERT_EQ(output[3], UString::fromUTF8("nice to \"meet\" you"));
}

TEST(StringUtil_Tokenize, DoubleQuotesEscapedDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice to \\\"meet\\\" you\"", output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice to \"meet\" you"));
}