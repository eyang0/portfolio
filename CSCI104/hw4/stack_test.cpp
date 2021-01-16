#include "stack.h"
#include "gtest/gtest.h"
#include <string>

using namespace std;

class StackTest : public testing::Test {
protected:

	StackTest() {
	}

	virtual ~StackTest() {
	}

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		s_int.push(1);
		s_int.push(2);
		s_int.push(3);

		s_bool.push(true);
		s_bool.push(false);

		
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	Stack<int> s_int;
	Stack<char> s_char;
	Stack<bool> s_bool;
};


TEST_F(StackTest, SizeNominal) {
	EXPECT_EQ(3, s_int.size());
	EXPECT_EQ(2, s_bool.size());
	EXPECT_EQ(0, s_char.size());
}


TEST_F(StackTest, EmptyNominal) {
	EXPECT_EQ(false, s_int.empty());
	EXPECT_EQ(true, s_char.empty());
}

TEST_F(StackTest, TopNominal) {
	EXPECT_THROW(s_char.top(), std::underflow_error);
	EXPECT_EQ(3, s_int.top());
}

TEST_F(StackTest, PopNominal) {
	EXPECT_THROW(s_char.pop(), std::underflow_error);
	s_int.pop();
	EXPECT_EQ(2, s_int.top());
	s_int.pop();
	EXPECT_EQ(1, s_int.top());
	s_int.pop();
	EXPECT_EQ(true, s_int.empty());
	EXPECT_THROW(s_int.pop(), std::underflow_error);
}


TEST_F(StackTest, PushNominal) {
	Stack<string> s_string;
	EXPECT_EQ(0, s_string.size());
	s_string.push("Bob");
	EXPECT_EQ("Bob", s_string.top());
	s_string.push("Jim");
	EXPECT_EQ("Jim", s_string.top());
	s_string.push("John");
	s_string.push("Tom");
	EXPECT_EQ(4, s_string.size());
}


