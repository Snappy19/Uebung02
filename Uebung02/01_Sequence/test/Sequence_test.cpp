/*#include <gtest/gtest.h>

#include "../Sequence.h"
#include "../InvalidCharacter.h"

#include "../DNA.h"
#include "../RNA.h"
#include "../Peptide.h"

using namespace Alphabet;

template<typename Alphabet>
class SequenceTest : public ::testing::Test
{
	public:
		SequenceTest() {}
};

template<typename Alphabet>
Sequence<Alphabet> buildTestSequence();

template<>
Sequence<DNA> buildTestSequence<DNA>() {
	return Sequence<DNA>::fromString("AGCTgaccTG");
}

template<>
Sequence<RNA> buildTestSequence<RNA>() {
	return Sequence<RNA>::fromString("AuCUgaccUg");
}

template<>
Sequence<Peptide> buildTestSequence<Peptide>() {
	return Sequence<Peptide>::fromString("ArdntLkQPFFgiHHM");
}

typedef ::testing::Types<DNA, RNA, Peptide> Alphabets;
TYPED_TEST_CASE(SequenceTest, Alphabets);

TYPED_TEST(SequenceTest, Sequence)
{
	Sequence<TypeParam> seq;

	EXPECT_EQ(0, seq.size());
	EXPECT_EQ(seq.begin(), seq.end());
}

TYPED_TEST(SequenceTest, resize)
{
	auto seq1 = buildTestSequence<TypeParam>();
	seq1.resize(4);

	auto seq2 = buildTestSequence<TypeParam>();

	EXPECT_EQ(4, seq1.size());
	EXPECT_EQ(seq2[0], seq1[0]);
	EXPECT_EQ(seq2[1], seq1[1]);
	EXPECT_EQ(seq2[2], seq1[2]);
	EXPECT_EQ(seq2[3], seq1[3]);
}

TYPED_TEST(SequenceTest, clear)
{
	auto seq1 = buildTestSequence<TypeParam>();
	EXPECT_NE(0, seq1.size());
	EXPECT_NE(seq1.begin(), seq1.end());

	seq1.clear();

	EXPECT_EQ(0, seq1.size());
	EXPECT_EQ(seq1.begin(), seq1.end());
}

TYPED_TEST(SequenceTest, Iterators_Exist)
{
	Sequence<TypeParam> seq;

	EXPECT_EQ(seq.begin(), seq.end());
}

TYPED_TEST(SequenceTest, ConstIterators_Exist)
{
	const Sequence<TypeParam> seq;

	EXPECT_EQ(seq.begin(), seq.end());
}

TYPED_TEST(SequenceTest, CBegin_Exist)
{
	const Sequence<TypeParam> seq;

	EXPECT_EQ(seq.cbegin(), seq.cend());
}

TYPED_TEST(SequenceTest, BracketOperator)
{
	auto seq = buildTestSequence<TypeParam>();

	for(size_t i = 0; i < seq.size(); ++i) {
		EXPECT_EQ(seq[i], seq[i]);
	}
}

TYPED_TEST(SequenceTest, ConstBracketOperator)
{
	const auto seq = buildTestSequence<TypeParam>();

	for(size_t i = 0; i < seq.size(); ++i) {
		EXPECT_EQ(seq[i], seq[i]);
	}
}

TYPED_TEST(SequenceTest, ToString)
{
	const auto seq = buildTestSequence<TypeParam>();

	auto str = seq.toString();

	ASSERT_EQ(seq.size(), str.size());

	for(size_t i = 0; i < seq.size(); ++i) {
		EXPECT_EQ(TypeParam::toChar(seq[i]), str[i]);
		EXPECT_EQ(seq[i], TypeParam::toCharacter(str[i]));
	}
}

TYPED_TEST(SequenceTest, Iteration)
{
	auto seq = buildTestSequence<TypeParam>();
	const auto str = seq.toString();

	ASSERT_EQ(seq.size(), str.size());

	auto str_begin = str.begin();
	auto seq_begin = seq.begin();

	for(; str_begin != str.end(); ++seq_begin, ++str_begin) {
		EXPECT_EQ(TypeParam::toCharacter(*str_begin), *seq_begin);
	}

	EXPECT_EQ(seq_begin, seq.end());
}

TYPED_TEST(SequenceTest, ConstIteration)
{
	const auto seq = buildTestSequence<TypeParam>();
	const auto str = seq.toString();

	ASSERT_EQ(seq.size(), str.size());

	auto str_begin = str.begin();
	auto seq_begin = seq.begin();

	for(; str_begin != str.end(); ++seq_begin, ++str_begin) {
		EXPECT_EQ(TypeParam::toCharacter(*str_begin), *seq_begin);
	}

	EXPECT_EQ(seq_begin, seq.end());
}

TYPED_TEST(SequenceTest, compare)
{
	auto seq1 = Sequence<TypeParam>::fromString("AGCAAGCA");
	auto seq2 = Sequence<TypeParam>::fromString("AGCA");

	EXPECT_FALSE(seq1.compare(seq2, 0));
	EXPECT_FALSE(seq1.compare(seq2, 1));
	EXPECT_FALSE(seq1.compare(seq2, 2));
	EXPECT_FALSE(seq1.compare(seq2, 3));
	EXPECT_TRUE (seq1.compare(seq2, 4));
	EXPECT_FALSE(seq1.compare(seq2, 5));
	EXPECT_FALSE(seq1.compare(seq2, 6));
	EXPECT_FALSE(seq1.compare(seq2, 7));
	EXPECT_FALSE(seq1.compare(seq2, 8));
}

TYPED_TEST(SequenceTest, compare_first_empty)
{
	Sequence<TypeParam> seq1;
	auto seq2 = buildTestSequence<TypeParam>();

	EXPECT_FALSE(seq1.compare(seq2, 0));
}

TYPED_TEST(SequenceTest, compare_second_empty)
{
	auto seq1 = buildTestSequence<TypeParam>();
	Sequence<TypeParam> seq2;

	for(size_t i = 0; i <= seq1.size(); ++i) {
		EXPECT_FALSE(seq1.compare(seq2, i));
	}
}

TYPED_TEST(SequenceTest, overlap_equal)
{
	auto seq1 = buildTestSequence<TypeParam>();
	auto seq2 = buildTestSequence<TypeParam>();

	EXPECT_EQ(seq1.size(), seq1.overlap(seq2));
	EXPECT_EQ(seq1.size(), seq2.overlap(seq1));
}

TYPED_TEST(SequenceTest, overlap_one_character)
{
	auto seq1 = Sequence<TypeParam>::fromString("AAAAAA");
	auto seq2 = Sequence<TypeParam>::fromString("AAAAAA");

	EXPECT_EQ(seq1.size(), seq1.overlap(seq2));
	EXPECT_EQ(seq1.size(), seq2.overlap(seq1));
}

TYPED_TEST(SequenceTest, overlap_empty)
{
	auto seq1 = Sequence<TypeParam>::fromString("AGCCA");
	auto seq2 = Sequence<TypeParam>::fromString("GACC");

	EXPECT_EQ(0, seq1.overlap(seq2));
	EXPECT_EQ(0, seq2.overlap(seq1));
}

TYPED_TEST(SequenceTest, overlap_two_matches)
{
	auto seq1 = Sequence<TypeParam>::fromString("GACCAACCA");
	auto seq2 = Sequence<TypeParam>::fromString("ACCAACCA");

	EXPECT_EQ(8, seq1.overlap(seq2));
	EXPECT_EQ(0, seq2.overlap(seq1));
}

TYPED_TEST(SequenceTest, overlap)
{
	auto seq1 = Sequence<TypeParam>::fromString("GACCAAGCA");
	auto seq2 = Sequence<TypeParam>::fromString("AGCAGCAA");

	EXPECT_EQ(4, seq1.overlap(seq2));
	EXPECT_EQ(0, seq2.overlap(seq1));
}

TYPED_TEST(SequenceTest, push_back)
{
	auto seq1 = buildTestSequence<TypeParam>();
	size_t len = seq1.size();

	const auto G = TypeParam::toCharacter('G');

	seq1.push_back(G);

	EXPECT_EQ(len + 1, seq1.size());
	EXPECT_EQ(G, seq1[seq1.size() - 1]);
}

TYPED_TEST(SequenceTest, comment)
{
	auto seq = buildTestSequence<TypeParam>();

	EXPECT_EQ("", seq.getComment());

	std::string comment = "sdlfjbsdfb";
	seq.setComment(comment);
	EXPECT_EQ(comment, seq.getComment());
	seq.setComment("");
	EXPECT_EQ("", seq.getComment());
}

TYPED_TEST(SequenceTest, input_operator)
{
	std::stringstream ss;

	std::string str = "AGCCCGCCAAGGAAC";

	ss << str;

	Sequence<TypeParam> seq;

	ASSERT_NO_THROW(ss >> seq);

	EXPECT_EQ(str, seq.toString());
}

TYPED_TEST(SequenceTest, input_operator_invalid)
{
	std::stringstream ss;

	std::string str = "AGCCCGCCAÖÄÄa%§AGGAAC";

	ss << str;

	Sequence<TypeParam> seq;

	EXPECT_THROW(ss >> seq, InvalidCharacter);
}

TYPED_TEST(SequenceTest, output_operator)
{
	std::stringstream ss;
	ss << buildTestSequence<TypeParam>();

	std::string str;
	ss >> str;

	Sequence<TypeParam> seq = buildTestSequence<TypeParam>();

	EXPECT_EQ(str, seq.toString());
}

//
// DNA
//
TEST(Sequence_DNA, fromString_UpperCase)
{
	const std::string str = "AGTCNCC";
	ASSERT_NO_THROW(Sequence<DNA>::fromString(str));
	auto seq1 = Sequence<DNA>::fromString(str);

	ASSERT_EQ(7, seq1.size());
	EXPECT_EQ(DNA::Characters::A, seq1[0]);
	EXPECT_EQ(DNA::Characters::G, seq1[1]);
	EXPECT_EQ(DNA::Characters::T, seq1[2]);
	EXPECT_EQ(DNA::Characters::C, seq1[3]);
	EXPECT_EQ(DNA::Characters::N, seq1[4]);
	EXPECT_EQ(DNA::Characters::C, seq1[5]);
	EXPECT_EQ(DNA::Characters::C, seq1[6]);
}

TEST(Sequence_DNA, fromString_LowerCase)
{
	const std::string str = "accgntaa";
	ASSERT_NO_THROW(Sequence<DNA>::fromString(str));
	auto seq1 = Sequence<DNA>::fromString(str);

	ASSERT_EQ(8, seq1.size());
	EXPECT_EQ(DNA::Characters::a, seq1[0]);
	EXPECT_EQ(DNA::Characters::c, seq1[1]);
	EXPECT_EQ(DNA::Characters::c, seq1[2]);
	EXPECT_EQ(DNA::Characters::g, seq1[3]);
	EXPECT_EQ(DNA::Characters::N, seq1[4]);
	EXPECT_EQ(DNA::Characters::t, seq1[5]);
	EXPECT_EQ(DNA::Characters::a, seq1[6]);
	EXPECT_EQ(DNA::Characters::a, seq1[7]);
}

TEST(Sequence_DNA, fromString_MixedCase)
{
	const std::string str = "GaCTntNgAc";
	ASSERT_NO_THROW(Sequence<DNA>::fromString(str));
	auto seq1 = Sequence<DNA>::fromString(str);

	ASSERT_EQ(10, seq1.size());
	EXPECT_EQ(DNA::Characters::G, seq1[0]);
	EXPECT_EQ(DNA::Characters::a, seq1[1]);
	EXPECT_EQ(DNA::Characters::C, seq1[2]);
	EXPECT_EQ(DNA::Characters::T, seq1[3]);
	EXPECT_EQ(DNA::Characters::N, seq1[4]);
	EXPECT_EQ(DNA::Characters::t, seq1[5]);
	EXPECT_EQ(DNA::Characters::N, seq1[6]);
	EXPECT_EQ(DNA::Characters::g, seq1[7]);
	EXPECT_EQ(DNA::Characters::A, seq1[8]);
	EXPECT_EQ(DNA::Characters::c, seq1[9]);
}

TEST(Sequence_DNA, fromString_Invalid)
{
	EXPECT_THROW(Sequence<DNA>::fromString("ÄdsfwAATGC"), InvalidCharacter);
}

TEST(Sequence_DNA, statistics)
{
	const auto stats = buildTestSequence<DNA>().statistics();

	ASSERT_EQ(4, stats.size());
	EXPECT_EQ(2, stats.find(DNA::Characters::A)->second);
	EXPECT_EQ(2, stats.find(DNA::Characters::T)->second);
	EXPECT_EQ(3, stats.find(DNA::Characters::G)->second);
	EXPECT_EQ(3, stats.find(DNA::Characters::C)->second);
}

//
// RNA
//
TEST(Sequence_RNA, fromString_UpperCase)
{
	ASSERT_NO_THROW(Sequence<RNA>::fromString("AGUCCC"));
	auto seq1 = Sequence<RNA>::fromString("AGUCCC");

	ASSERT_EQ(6, seq1.size());
	EXPECT_EQ(RNA::Characters::A, seq1[0]);
	EXPECT_EQ(RNA::Characters::G, seq1[1]);
	EXPECT_EQ(RNA::Characters::U, seq1[2]);
	EXPECT_EQ(RNA::Characters::C, seq1[3]);
	EXPECT_EQ(RNA::Characters::C, seq1[4]);
	EXPECT_EQ(RNA::Characters::C, seq1[5]);
}

TEST(Sequence_RNA, fromString_LowerCase)
{
	ASSERT_NO_THROW(Sequence<RNA>::fromString("accguaa"));
	auto seq1 = Sequence<RNA>::fromString("accguaa");

	ASSERT_EQ(7, seq1.size());
	EXPECT_EQ(RNA::Characters::A, seq1[0]);
	EXPECT_EQ(RNA::Characters::C, seq1[1]);
	EXPECT_EQ(RNA::Characters::C, seq1[2]);
	EXPECT_EQ(RNA::Characters::G, seq1[3]);
	EXPECT_EQ(RNA::Characters::U, seq1[4]);
	EXPECT_EQ(RNA::Characters::A, seq1[5]);
	EXPECT_EQ(RNA::Characters::A, seq1[6]);
}

TEST(Sequence_RNA, fromString_MixedCase)
{
	ASSERT_NO_THROW(Sequence<RNA>::fromString("GaCUugAc"));
	auto seq1 = Sequence<RNA>::fromString("GaCUugAc");

	ASSERT_EQ(8, seq1.size());
	EXPECT_EQ(RNA::Characters::G, seq1[0]);
	EXPECT_EQ(RNA::Characters::A, seq1[1]);
	EXPECT_EQ(RNA::Characters::C, seq1[2]);
	EXPECT_EQ(RNA::Characters::U, seq1[3]);
	EXPECT_EQ(RNA::Characters::U, seq1[4]);
	EXPECT_EQ(RNA::Characters::G, seq1[5]);
	EXPECT_EQ(RNA::Characters::A, seq1[6]);
	EXPECT_EQ(RNA::Characters::C, seq1[7]);
}

TEST(Sequence_RNA, fromString_Invalid)
{
	EXPECT_THROW(Sequence<RNA>::fromString("ÄdsfwAAUGC"), InvalidCharacter);
}

TEST(Sequence_RNA, statistics)
{
	const auto stats = buildTestSequence<RNA>().statistics();

	ASSERT_EQ(4, stats.size());
	EXPECT_EQ(2, stats.find(RNA::Characters::A)->second);
	EXPECT_EQ(3, stats.find(RNA::Characters::U)->second);
	EXPECT_EQ(2, stats.find(RNA::Characters::G)->second);
	EXPECT_EQ(3, stats.find(RNA::Characters::C)->second);
}

//
// Peptide
//
TEST(Sequence_Peptide, fromString_UpperCase)
{
	ASSERT_NO_THROW(Sequence<Peptide>::fromString("AQKLRNPGF"));
	auto seq1 = Sequence<Peptide>::fromString("AQKLRNPGF");

	ASSERT_EQ(9, seq1.size());
	EXPECT_EQ(Peptide::Characters::Ala, seq1[0]);
	EXPECT_EQ(Peptide::Characters::Gln, seq1[1]);
	EXPECT_EQ(Peptide::Characters::Lys, seq1[2]);
	EXPECT_EQ(Peptide::Characters::Leu, seq1[3]);
	EXPECT_EQ(Peptide::Characters::Arg, seq1[4]);
	EXPECT_EQ(Peptide::Characters::Asn, seq1[5]);
	EXPECT_EQ(Peptide::Characters::Pro, seq1[6]);
	EXPECT_EQ(Peptide::Characters::Gly, seq1[7]);
	EXPECT_EQ(Peptide::Characters::Phe, seq1[8]);
}

TEST(Sequence_Peptide, fromString_LowerCase)
{
	ASSERT_NO_THROW(Sequence<Peptide>::fromString("kmpdsag"));
	auto seq1 = Sequence<Peptide>::fromString("kmpdsag");

	ASSERT_EQ(7, seq1.size());
	EXPECT_EQ(Peptide::Characters::Lys, seq1[0]);
	EXPECT_EQ(Peptide::Characters::Met, seq1[1]);
	EXPECT_EQ(Peptide::Characters::Pro, seq1[2]);
	EXPECT_EQ(Peptide::Characters::Asp, seq1[3]);
	EXPECT_EQ(Peptide::Characters::Ser, seq1[4]);
	EXPECT_EQ(Peptide::Characters::Ala, seq1[5]);
	EXPECT_EQ(Peptide::Characters::Gly, seq1[6]);
}

TEST(Sequence_Peptide, fromString_MixedCase)
{
	ASSERT_NO_THROW(Sequence<Peptide>::fromString("IfSCcgAL"));
	auto seq1 = Sequence<Peptide>::fromString("IfSCcgAL");

	ASSERT_EQ(8, seq1.size());
	EXPECT_EQ(Peptide::Characters::Ile, seq1[0]);
	EXPECT_EQ(Peptide::Characters::Phe, seq1[1]);
	EXPECT_EQ(Peptide::Characters::Ser, seq1[2]);
	EXPECT_EQ(Peptide::Characters::Cys, seq1[3]);
	EXPECT_EQ(Peptide::Characters::Cys, seq1[4]);
	EXPECT_EQ(Peptide::Characters::Gly, seq1[5]);
	EXPECT_EQ(Peptide::Characters::Ala, seq1[6]);
	EXPECT_EQ(Peptide::Characters::Leu, seq1[7]);
}

TEST(Sequence_Peptide, fromString_Invalid)
{
	EXPECT_THROW(Sequence<Peptide>::fromString("ÄdsfwAAUGC"), InvalidCharacter);
}

TEST(Sequence_Peptide, statistics)
{
	const auto stats = buildTestSequence<Peptide>().statistics();

	ASSERT_EQ(14, stats.size());
	EXPECT_EQ(1, stats.find(Peptide::Characters::Ala)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Arg)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Asp)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Asn)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Thr)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Leu)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Lys)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Gln)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Pro)->second);
	EXPECT_EQ(2, stats.find(Peptide::Characters::Phe)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Gly)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Ile)->second);
	EXPECT_EQ(2, stats.find(Peptide::Characters::His)->second);
	EXPECT_EQ(1, stats.find(Peptide::Characters::Met)->second);
}

*/
