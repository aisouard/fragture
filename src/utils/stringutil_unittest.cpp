/*
 * Copyright 2018 Axel Isouard <axel@isouard.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "gtest/gtest.h"
#include "utils/stringutil.h"

using Utils::StringUtil;

TEST(StringUtil_Concat, SingleWord) {
  UStringVector input;
  UString output;

  input.push_back("hello");
  StringUtil::Concat(input, ",", &output);

  ASSERT_EQ(output, UString::fromUTF8("hello"));
}

TEST(StringUtil_Concat, TwoWords) {
  UStringVector input;
  UString output;

  input.push_back("hello");
  input.push_back("world");
  StringUtil::Concat(input, ",", &output);

  ASSERT_EQ(output, UString::fromUTF8("hello,world"));
}

TEST(StringUtil_Tokenize, SingleWord) {
  UStringVector output;

  StringUtil::Tokenize("hello", &output);

  ASSERT_EQ(output.size(), 1);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
}

TEST(StringUtil_Tokenize, TwoWords) {
  UStringVector output;

  StringUtil::Tokenize("hello world!", &output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesMiddle) {
  UStringVector output;

  StringUtil::Tokenize("hello     world!", &output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesEnding) {
  UStringVector output;

  StringUtil::Tokenize("hello world!   ", &output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsWhiteSpacesBoth) {
  UStringVector output;

  StringUtil::Tokenize("hello     world!   ", &output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world!"));
}

TEST(StringUtil_Tokenize, TwoWordsHangul) {
  UStringVector output;

  StringUtil::Tokenize("연인이나 친구", &output);

  ASSERT_EQ(output.size(), 2);
  ASSERT_EQ(output[0], UString::fromUTF8("연인이나"));
  ASSERT_EQ(output[1], UString::fromUTF8("친구"));
}

TEST(StringUtil_Tokenize, ThreeWordsDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice\"", &output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice"));
}

TEST(StringUtil_Tokenize, ThreeWordsSingleDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice", &output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice"));
}

TEST(StringUtil_Tokenize, ThreeWordsDoubleQuotesWhitespaces) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice  to meet   you\"", &output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice  to meet   you"));
}

TEST(StringUtil_Tokenize, EscapedDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("\\\"hello world \\\" \"nice to \\\"meet\\\" you\"",
                       &output);

  ASSERT_EQ(output.size(), 4);
  ASSERT_EQ(output[0], UString::fromUTF8("\"hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("\""));
  ASSERT_EQ(output[3], UString::fromUTF8("nice to \"meet\" you"));
}

TEST(StringUtil_Tokenize, DoubleQuotesEscapedDoubleQuotes) {
  UStringVector output;

  StringUtil::Tokenize("hello world \"nice to \\\"meet\\\" you\"", &output);

  ASSERT_EQ(output.size(), 3);
  ASSERT_EQ(output[0], UString::fromUTF8("hello"));
  ASSERT_EQ(output[1], UString::fromUTF8("world"));
  ASSERT_EQ(output[2], UString::fromUTF8("nice to \"meet\" you"));
}
