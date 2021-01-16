#include "heap.h"
#include "gtest/gtest.h"
#include <string>

using namespace std;

class HeapTest : public testing::Test {
protected:

	HeapTest() {
	}

	virtual ~HeapTest() {
	}

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		//h_int.push(24);
		//h_int.push(20);
		//h_int.push(12);
		//h_int.push(5);
		//h_int.push(3);
		//h_int.push(9);

		//h_str.push('a');
		//h_str.push('f');

		
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	//Heap<int> h_int(5);
	//Heap<char> h_char(2);
	//Heap<string, std::greater<string>> h_str;
};

TEST_F(HeapTest, Basic) {
	Heap<int> h_int(5);
	h_int.push(24);
	h_int.push(1);

	EXPECT_EQ(1, h_int.top());
	h_int.pop();
	EXPECT_EQ(24, h_int.top());
	h_int.pop();
	EXPECT_EQ(true, h_int.empty());

}

TEST_F(HeapTest, constructor)
{
	Heap<string> testH(3);
	std::greater<string> c1;
	Heap<string, std::greater<string>> testH2(3, c1);
	testH.push("albert");
	testH.push("beta");
	testH2.push("alpha");
	testH2.push("beta");
	EXPECT_EQ("albert", testH.top());
	testH.pop();
	EXPECT_EQ("beta", testH.top());
	testH.pop();
	EXPECT_THROW(testH.top(), std::logic_error);
	testH2.pop();
	testH2.pop();
	EXPECT_THROW(testH2.pop(), std::logic_error);
}



TEST_F(HeapTest, empty)
{
	Heap<int> h_int(5);
	h_int.push(24);

	Heap<char> h_char(2);

	Heap<string, std::greater<string>> h_str(4);
	h_str.push("air");
	h_str.push("earth");
	h_str.push("zinc");

	EXPECT_EQ("zinc", h_str.top());

	EXPECT_EQ(false, h_str.empty());
	EXPECT_EQ(false, h_int.empty());
	EXPECT_EQ(true, h_char.empty());
}

TEST_F(HeapTest, adding)
{
	Heap<int> h_int(5);
	h_int.push(24);

	h_int.push(20);
	EXPECT_EQ(h_int.top(), 20);

	h_int.push(12);
	EXPECT_EQ(h_int.top(), 12);
	h_int.push(13);
	EXPECT_EQ(h_int.top(), 12);
	h_int.push(3);
	EXPECT_EQ(h_int.top(), 3);
	h_int.push(9);
	EXPECT_EQ(h_int.top(), 3);
	h_int.push(1);
	EXPECT_EQ(h_int.top(), 1);

	h_int.pop();
	EXPECT_EQ(h_int.top(), 3);


}




