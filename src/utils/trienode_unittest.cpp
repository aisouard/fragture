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

#include <string>
#include "gtest/gtest.h"
#include "utils/trienode.h"

using Utils::TrieNode;

TEST(TrieNode, InsertEmpty) {
  TrieNode<int*> *t = new TrieNode<int*>();

  int *i = new int;
  *i = 1;
  t->Insert("", i);

  EXPECT_EQ(t->GetValue(), i);
  delete t;
}

TEST(TrieNode, InsertAndFindShort) {
  TrieNode<std::string *> *t = new TrieNode<std::string *>();

  std::string *str = new std::string("hey");
  t->Insert("m", str);

  EXPECT_EQ(t->Find("l"), (void*)NULL);
  EXPECT_NE(t->Find("m"), (void*)NULL);
  EXPECT_EQ(t->Find("m")->GetValue(), str);

  delete t;
}

TEST(TrieNode, InsertAndFindExisting) {
  TrieNode<std::string *> *t = new TrieNode<std::string *>();

  std::string *first = new std::string("first");
  std::string *second = new std::string("second");

  t->Insert("m", first);
  EXPECT_EQ(t->Find("l"), (void*)NULL);
  EXPECT_NE(t->Find("m"), (void*)NULL);
  EXPECT_EQ(t->Find("m")->GetValue(), first);

  t->Insert("m", second);
  EXPECT_EQ(t->Find("l"), (void*)NULL);
  EXPECT_NE(t->Find("m"), (void*)NULL);
  EXPECT_EQ(t->Find("m")->GetValue(), second);

  delete t;
}

TEST(TrieNode, InsertAndFindLong) {
  TrieNode<std::string *> *t = new TrieNode<std::string *>();

  std::string *str = new std::string("hey");
  t->Insert("mapname", str);

  EXPECT_NE(t->Find("m"), (void*)NULL);
  EXPECT_EQ(t->Find("m")->GetValue(), (void*)NULL);
  EXPECT_NE(t->Find("ma"), (void*)NULL);
  EXPECT_EQ(t->Find("ma")->GetValue(), (void*)NULL);
  EXPECT_NE(t->Find("map"), (void*)NULL);
  EXPECT_EQ(t->Find("map")->GetValue(), (void*)NULL);
  EXPECT_NE(t->Find("mapn"), (void*)NULL);
  EXPECT_EQ(t->Find("mapn")->GetValue(), (void*)NULL);
  EXPECT_NE(t->Find("mapna"), (void*)NULL);
  EXPECT_EQ(t->Find("mapna")->GetValue(), (void*)NULL);
  EXPECT_NE(t->Find("mapnam"), (void*)NULL);
  EXPECT_EQ(t->Find("mapnam")->GetValue(), (void*)NULL);
  ASSERT_NE(t->Find("mapname"), (void*)NULL);
  ASSERT_EQ(t->Find("mapname")->GetValue(), str);

  delete t;
}

TEST(TrieNode, InsertAndFindDual) {
  TrieNode<std::string *> *t = new TrieNode<std::string *>();

  std::string *first = new std::string("first");
  std::string *second = new std::string("second");

  t->Insert("ball", first);
  t->Insert("balloon", second);

  ASSERT_EQ(t->Find("ball")->GetValue(), first);
  ASSERT_EQ(t->Find("balloon")->GetValue(), second);
  delete t;
}

TEST(TrieNode, InsertAndDelete) {
  TrieNode<std::string *> *t = new TrieNode<std::string *>();

  std::string *first = new std::string("first");
  std::string *second = new std::string("second");

  t->Insert("mapname", first);
  t->Insert("memory", second);

  ASSERT_EQ(t->Find("mapname")->GetValue(), first);
  ASSERT_EQ(t->Find("memory")->GetValue(), second);

  t->Delete("memory");
  ASSERT_EQ(t->Find("memory"), (void*)NULL);
  ASSERT_NE(t->Find("mapname"), (void*)NULL);
  ASSERT_EQ(t->Find("mapname")->GetValue(), first);
  delete t;
}
