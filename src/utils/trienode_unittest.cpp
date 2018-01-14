#include "gtest/gtest.h"
#include "trienode.h"

using namespace Utils;

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