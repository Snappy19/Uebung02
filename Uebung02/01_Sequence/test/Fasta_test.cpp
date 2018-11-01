/*#include <gtest/gtest.h>

#include "../Sequence.h"
#include "../Fasta.h"
#include "../DNA.h"

using namespace Alphabet;

TEST(Fasta_DNA, read_single_line)
{
	std::stringstream ss(">SomeSequence\nAAGTTCAGTTAGACGTTTAGGC");
	Sequence<DNA> seq;

	ss >> fromFasta(seq);

	EXPECT_EQ("SomeSequence", seq.getComment());
	EXPECT_EQ("AAGTTCAGTTAGACGTTTAGGC", seq.toString());
}

TEST(Fasta_DNA, read_multi_line)
{
	std::stringstream ss(">SomeSequence\nagtCCCttaTGgTAAc\ncgttgtgAAC");
	Sequence<DNA> seq;

	ss >> fromFasta(seq);

	EXPECT_EQ("SomeSequence", seq.getComment());
	EXPECT_EQ("agtCCCttaTGgTAAccgttgtgAAC", seq.toString());
}

TEST(Fasta_DNA, read_multiple_multi_line)
{
	std::stringstream ss(
		">SomeSequence\nagtCCCttaTGgTAAc\ncgttgtgAAC\n"
		">SomeSequence2\nGACTGGAGaTGgTAAc\ncgttgtgAAC"
	);

	Sequence<DNA> seq1;
	Sequence<DNA> seq2;

	ss >> fromFasta(seq1) >> fromFasta(seq2);

	EXPECT_EQ("SomeSequence", seq1.getComment());
	EXPECT_EQ("agtCCCttaTGgTAAccgttgtgAAC", seq1.toString());
	EXPECT_EQ("SomeSequence2", seq2.getComment());
	EXPECT_EQ("GACTGGAGaTGgTAAccgttgtgAAC", seq2.toString());
}

TEST(Fasta_DNA, invalid_header)
{
	std::stringstream ss("BlaBlub\nAAGTC");

	Sequence<DNA> seq1;

	EXPECT_THROW(ss >> fromFasta(seq1), ParsingException);
}

TEST(Fasta_DNA, empty_sequence)
{
	std::stringstream ss(">BlaBlub\n");
	Sequence<DNA> seq;

	ss >> fromFasta(seq);

	EXPECT_EQ("", seq.toString());
	EXPECT_EQ("BlaBlub", seq.getComment());
}

TEST(Fasta_DNA, empty_sequence2)
{
	std::stringstream ss(">BlaBlub");
	Sequence<DNA> seq;

	ss >> fromFasta(seq);

	EXPECT_EQ("", seq.toString());
	EXPECT_EQ("BlaBlub", seq.getComment());
}

TEST(Fasta_DNA, empty_sequence3)
{
	std::stringstream ss(">");
	Sequence<DNA> seq;

	ss >> fromFasta(seq);

	EXPECT_EQ("", seq.toString());
	EXPECT_EQ("", seq.getComment());
}

TEST(Fasta_DNA, read_write)
{
	auto seq1 = Sequence<DNA>::fromString("AATggaTTGCCACTGT");
	seq1.setComment("sequence");

	Sequence<DNA> seq2;

	std::stringstream ss;

	ss << toFasta(seq1);
	ss >> fromFasta(seq2);

	EXPECT_EQ(seq1, seq2);
	EXPECT_EQ(seq1.getComment(), seq2.getComment());
}
*/