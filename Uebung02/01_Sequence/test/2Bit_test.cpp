/*#include <gtest/gtest.h>

#include "../Sequence.h"
#include "../2Bit.h"
#include "../DNA.h"
#include "../ParsingException.h"

using namespace Alphabet;

class membuf : public std::basic_streambuf<char>
{
  public:
	membuf(const uint8_t* p, size_t l)
	{
		setg((char*)p, (char*)p, (char*)p + l);
	}
};

class memstream : public std::istream
{
  public:
	memstream(const uint8_t* p, size_t l)
	    : std::istream(&_buffer), _buffer(p, l)
	{
		rdbuf(&_buffer);
	}

  private:
	membuf _buffer;
};

TEST(TwoBit_DNA, read_single_line)
{
	// This encodes the sequence:
	// GACT     GGCT     CG
	// 00011110 00001110 11000000
	const uint8_t array[] = {0x3e, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63,
	                         0x65, 0x3a, 0x31, 0x2d, 0x31, 0x30, 0x0a, 0x50,
	                         0x1e, 0x0e, 0xc0, 0x00, 0x00, 0x00};

	memstream ss(array, 23);

	Sequence<DNA> seq;
	ss >> from2Bit(seq);

	EXPECT_EQ("sequence", seq.getComment());
	EXPECT_EQ("GACTGGCTCG", seq.toString());
}

TEST(TwoBit_DNA, invalid_size)
{
	const uint8_t array[] = {0x3e, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63,
	                         0x65, 0x3a, 0x31, 0x2d, 0x32, 0x30, 0x0a, 0x50,
	                         0x1e, 0x0e, 0xc0, 0x00, 0x00, 0x00};

	memstream ss(array, 23);

	Sequence<DNA> seq;
	EXPECT_THROW(ss >> from2Bit(seq), ParsingException);
}

TEST(TwoBit_DNA, read_multiple)
{
	// This encodes the sequences:
	// AACG     CGCT     AC
	// 00011110 00001110 01110000
	// GCTA     GT
	// 00111001 00100000
	const uint8_t array[] = {
	    0x3e, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x65, 0x3a, 0x31,
	    0x2d, 0x31, 0x30, 0x0a, 0x50, 0x5c, 0xce, 0x70, 0x00, 0x00, 0x00,
	    0x3e, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x65, 0x3a, 0x31,
	    0x2d, 0x36, 0x0a, 0x50, 0x39, 0x20, 0x00, 0x00};

	memstream ss(array, 41);

	Sequence<DNA> seq1, seq2;
	ASSERT_NO_THROW(ss >> from2Bit(seq1));
	ASSERT_NO_THROW(ss >> from2Bit(seq2));

	EXPECT_EQ("sequence", seq1.getComment());
	EXPECT_EQ("AACGCGCTAC", seq1.toString());
	EXPECT_EQ("sequence", seq2.getComment());
	EXPECT_EQ("GCTAGT",     seq2.toString());
}

TEST(TwoBit_DNA, write)
{
	auto seq = Sequence<DNA>::fromString("AGTCC");
	seq.setComment("sequence");

	const unsigned char array[19] = {0x3e, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e,
	                                 0x63, 0x65, 0x3a, 0x31, 0x2d, 0x35, 0x0a,
	                                 0x50, 0x4b, 0xc0, 0x00, 0x00};

	std::stringstream ss;
	ss << to2Bit(seq);

	for(size_t i = 0; i < 19; ++i) {
		ASSERT_EQ(array[i], ss.get());
	}
}

*/