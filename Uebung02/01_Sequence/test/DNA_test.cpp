/*#include <gtest/gtest.h>

#include "../DNA.h"
#include "../InvalidCharacter.h"

using namespace Alphabet;

TEST(DNA, toCharacter)
{
	ASSERT_NO_THROW(DNA::toCharacter('A'));
	ASSERT_NO_THROW(DNA::toCharacter('T'));
	ASSERT_NO_THROW(DNA::toCharacter('G'));
	ASSERT_NO_THROW(DNA::toCharacter('C'));
	ASSERT_NO_THROW(DNA::toCharacter('a'));
	ASSERT_NO_THROW(DNA::toCharacter('t'));
	ASSERT_NO_THROW(DNA::toCharacter('g'));
	ASSERT_NO_THROW(DNA::toCharacter('c'));
	ASSERT_NO_THROW(DNA::toCharacter('n'));
	ASSERT_NO_THROW(DNA::toCharacter('N'));

	EXPECT_EQ(DNA::Characters::A, DNA::toCharacter('A'));
	EXPECT_EQ(DNA::Characters::T, DNA::toCharacter('T'));
	EXPECT_EQ(DNA::Characters::G, DNA::toCharacter('G'));
	EXPECT_EQ(DNA::Characters::C, DNA::toCharacter('C'));
	EXPECT_EQ(DNA::Characters::a, DNA::toCharacter('a'));
	EXPECT_EQ(DNA::Characters::t, DNA::toCharacter('t'));
	EXPECT_EQ(DNA::Characters::g, DNA::toCharacter('g'));
	EXPECT_EQ(DNA::Characters::c, DNA::toCharacter('c'));
	EXPECT_EQ(DNA::Characters::N, DNA::toCharacter('N'));
	EXPECT_EQ(DNA::Characters::N, DNA::toCharacter('n'));

	EXPECT_THROW(DNA::toCharacter('h'), InvalidCharacter);
	EXPECT_THROW(DNA::toCharacter('\0'), InvalidCharacter);
	EXPECT_THROW(DNA::toCharacter(' '), InvalidCharacter);
	EXPECT_THROW(DNA::toCharacter('3'), InvalidCharacter);
	EXPECT_THROW(DNA::toCharacter('U'), InvalidCharacter);
	EXPECT_THROW(DNA::toCharacter('w'), InvalidCharacter);
}

TEST(DNA, toChar)
{
	EXPECT_EQ('A', DNA::toChar(DNA::Characters::A));
	EXPECT_EQ('T', DNA::toChar(DNA::Characters::T));
	EXPECT_EQ('G', DNA::toChar(DNA::Characters::G));
	EXPECT_EQ('C', DNA::toChar(DNA::Characters::C));
	EXPECT_EQ('a', DNA::toChar(DNA::Characters::a));
	EXPECT_EQ('t', DNA::toChar(DNA::Characters::t));
	EXPECT_EQ('g', DNA::toChar(DNA::Characters::g));
	EXPECT_EQ('c', DNA::toChar(DNA::Characters::c));
	EXPECT_EQ('N', DNA::toChar(DNA::Characters::N));
}

*/