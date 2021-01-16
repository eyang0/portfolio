#include "deque.h"
#include "gtest/gtest.h"
#include <string>

using namespace std;

class DequeTest : public testing::Test {
protected:

	DequeTest() {
	}

	virtual ~DequeTest() {
	}

	virtual void SetUp() {
		d_int.push_back(1);
		d_int.push_back(2);
		d_int.push_front(3);

		d_bool.push_back(true);
		d_bool.push_back(true);
		d_bool.push_back(false);

		
	}

	virtual void TearDown() {
	}

	Deque<int> d_int;
	Deque<char> d_char;
	Deque<bool> d_bool;
};


TEST_F(DequeTest, ConstructorNominal) {
	Deque<string> construct_test1;
	Deque<string> construct_test2(4);

	EXPECT_EQ(0, construct_test1.size());
}

TEST_F(DequeTest, SizeNominal) {
	EXPECT_EQ(3, d_int.size());
	EXPECT_EQ(0, d_char.size());
}


TEST_F(DequeTest, EmptyNominal) {
	EXPECT_EQ(false, d_int.empty());
	EXPECT_EQ(true, d_char.empty());
}


TEST_F(DequeTest, AccessNominal1) {
	EXPECT_EQ(3, d_int[0]);
	EXPECT_EQ(2, d_int[2]);
}

TEST_F(DequeTest, AccessNominal2) {
	d_int[0] = 20; //changing value from 1 to 20
	EXPECT_EQ(20, d_int[0]);
}


TEST_F(DequeTest, AccessOffNominal) {
	EXPECT_THROW(d_int[6], std::range_error);
	EXPECT_THROW(d_int[-2], std::range_error);
	EXPECT_THROW(d_char[2], std::range_error);
}


TEST_F(DequeTest, Push_BackNominal) {
	Deque<string> d_string(3);
	EXPECT_EQ(0, d_string.size());
	d_string.push_back("Bob");
	EXPECT_EQ("Bob", d_string[0]);
	d_string.push_back("Jim");
	d_string.push_back("John");

	d_string.push_back("Tom");
	/* since capacity was initialized at 3 and now we have size 4,
	we know that dynamic resizing worked after adding "Tom"*/
	EXPECT_EQ(4, d_string.size());
}

TEST_F(DequeTest, Push_FrontNominal) {
	EXPECT_EQ(0, d_char.size());
	d_char.push_front('a');
	EXPECT_EQ(1, d_char.size());
	EXPECT_EQ('a', d_char[0]);
	d_char.push_front('b');
	EXPECT_EQ(2, d_char.size());
	EXPECT_EQ('b', d_char[0]);
	d_char.push_back('c');
	EXPECT_EQ('c', d_char[2]);
	EXPECT_EQ(3, d_char.size());
}

TEST_F(DequeTest, Pop_BackNominal) {
	EXPECT_EQ(3, d_bool.size());
	d_bool.pop_back();
	EXPECT_EQ(true, d_bool[1]);
	EXPECT_EQ(2, d_bool.size());
	EXPECT_THROW(d_bool[2], std::range_error);
}


TEST_F(DequeTest, Pop_FrontNominal) {
	d_bool.pop_front();
	EXPECT_EQ(2, d_bool.size());
	EXPECT_EQ(true, d_bool[0]);
	d_bool.pop_front();
	EXPECT_EQ(false, d_bool[0]);
	d_bool.pop_front();
	EXPECT_EQ(true, d_bool.empty());
	int temp_size = d_bool.size();
	d_bool.pop_front();
	EXPECT_EQ(temp_size, d_bool.size());
}



