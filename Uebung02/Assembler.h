#ifndef BIOINFO1_ASSEMBLER_H
#define BIOINFO1_ASSEMBLER_H

#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

class Assembler
{
  public:
  	
	using Seq = Sequence<Alphabet::DNA>;
	using OGraph = Graph<Seq>;

	/**
	 * Creates an overlap-graph that contains the passed sequences as nodes.
	 */
	Assembler(const std::vector<Assembler::Seq>& sequences);

	// erstellt overlap-graphen, methode overlap verwenden. Kante wird nur erzeugt wenn overlap > 0;
};

#endif // BIOINFO1_ASSEMBLER_H

