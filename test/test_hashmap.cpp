#include "THashMap.cpp"
#include "THashMapList.cpp"
#include <gtest.h>

using namespace std;

TEST(THashMap, can_create_map)
{
    THashMap<string, int> a;
    EXPECT_EQ(0,a.GetCount());
}

TEST(THashMap, can_add_item)
{
    THashMap<string, int> a;
    a.Add("hello", 444);
    EXPECT_EQ(444,a["hello"]);
}

TEST(THashMap, can_find_item)
{
    THashMap<string, int> a;
    a.Add("hello", 444);
    a.Add("world", 555);
    a.Add("rain", 3);
    EXPECT_EQ(3,a.Find("rain"));
}

TEST(THashMap, can_delete_item)
{
    THashMap<string, int> a;
    a.Add("hello", 444);
    a.Add("world", 555);
    a.Add("rainy", 34);
    a.Add("day", 77);
    a.Delete("world");
    ASSERT_ANY_THROW(a.Find("world"));
}

TEST(THashMap, unexpected_indexation_wont_cause_error)
{
    THashMap<string, int> a;
    a.Add("hello", 444);
    a.Add("world", 555);
    a.Add("rainy", 34);
    ASSERT_NO_THROW(a["some key"]);
}

TEST(THashMapList, can_create_map)
{
    THashMapList<string, int> a;
    EXPECT_EQ(0,a.GetCount());
}

TEST(THashMapList, can_add_item)
{
    THashMapList<string, int> a;
    a.Add("hello", 444);
    EXPECT_EQ(444,a["hello"]);
}

TEST(THashMapList, can_find_item)
{
    THashMapList<string, int> a;
    a.Add("hhhh", 444);
    a.Add("www", 555);
    a.Add("qqq", 3);
    EXPECT_EQ(3,a.Find("qqq"));
}

TEST(THashMapList, can_delete_item)
{
    THashMapList<string, int> a;
    a.Add("hhhh", 444);
    a.Add("www", 555);
    a.Add("qqq", 3);
    a.Delete("qqq");
    ASSERT_NO_THROW(a.Find("qqq"));
}

TEST(THashMapList, unexpected_indexation_wont_cause_error)
{
    THashMapList<string, int> a;
    a.Add("hello", 444);
    a.Add("world", 555);
    a.Add("rainy", 34);
    ASSERT_NO_THROW(a["some key"]);
}