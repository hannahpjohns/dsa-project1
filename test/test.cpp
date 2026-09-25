#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <format>
#include <sstream>

#include "tree.h"

//using namespace std;
// Hannah Johns
// UFID 70480080

//
// TEST_CASE("Test 1", "[flag]"){
// 	Tree test = Tree();
//
// 	SECTION("letters") {
// 		test.insert(12322423, "test"); //isn't testing letters
//
// 	}
// 	SECTION("7-digit") {
// 		test.insert(1234567, "test");
//
// 	}
// 	SECTION("9-digit") {
// 		test.insert(123456789), 'test';
// 	}
// 	SECTION("duplicate") {
// 		test.insert(12345678);
// 		test.insert(12345678);
// 	}
//
//
//
// }

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 11111111;
	int two = 22222222;
	int three = 33333333;
	Tree test = Tree();
	std::vector<int> expectedOutput = {two, one, three};

	SECTION("RR") {
		test.insert(one, "test1");
		test.insert(two, "test2");
		test.insert(three, "test3");

		test.printLevelcount();
		// should equal 2


		//REQUIRE(count == 2);
	};

	SECTION("LL") {
		test.insert(three, "test 3");
		test.insert(two, "test 2");
		test.insert(one, "test 1");

		test.printLevelcount();
	};
	SECTION("LR") {
		test.insert(three, "test 3");
		test.insert(one, "test 1");
		test.insert(two, "test 2");
		test.printLevelcount();
	};
	SECTION("RL") {
		test.insert(one, "test 1");
		test.insert(three, "test 3");
		test.insert(two, "test 2");
		test.printLevelcount();
	};


}


TEST_CASE("Delete Inorder", "[flag]"){
	Tree test = Tree();

	for(int j = 0; j < 100; j++) {
		test.insert(10000000 + j, "test");
	}
	for(int i = 0; i < 90; i++) {
		test.removeInorder(100 - i);
	}

	std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

	test.printInorder();
	buffer << "[end]";

	std::cout.rdbuf(oldCoutBuffer);
	INFO("inorder: " << buffer.str());
	REQUIRE(false);        // fails → Catch prints the INFO above


}

// TEST_CASE("Large Tree", "[flag]"){
// 	Tree inputTree;
// 	std::vector<string> expectedOutput, actualOutput;
// 	int start = 10000000;
//
// 	for(int i = 0; i < 100; i++)
// 	{
// 		start += i;
// 		if (std::count(expectedOutput.begin(), expectedOutput.end(), start) == 0)
// 		{
// 			expectedOutput.push_back("true");
// 			inputTree.insert(start, std::format("test{}", i));
// 		}
// 	}
//
// 	actualOutput = inputTree.inOrder();
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE_FALSE(expectedOutput == actualOutput);    //This assertion can be wrong. Don't use
// 	std::sort(expectedOutput.begin(), expectedOutput.end());
// 	REQUIRE(expectedOutput == actualOutput);
//
// }
