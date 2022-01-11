/// @file lbt.C
/// The main program of lbt

/*
 *  Copyright © 2001 Heikki Tauriainen <Heikki.Tauriainen@hut.fi>
 *  Copyright © 2001 Marko Mäkelä <msmakela@tcs.hut.fi>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/** @mainpage LBT: LTL to Büchi Translator
 * @htmlonly
 * Please visit also the
 * <a href="http://www.tcs.hut.fi/maria/tools/lbt/">LBT home page</a>.
 * @endhtmlonly
 */

#include "LtlGraph.h"
#include <stdio.h>

/** Read an LTL formula from standard input
 * @param negation	flag: negate the formula
 * @return		the parsed formula, or NULL on error
 */
static class Ltl*
readFormula (bool negation)
{
  int ch;
  class Ltl *left, *right;
 loop:
  while ((ch = getchar ()) == ' ' || ch == '\n' || ch == '\r' ||
	 ch == '\t' || ch == '\v' || ch == '\f');
  switch (ch) {
  case 't':
  case 'f':
    return &LtlConstant::construct ((ch == 'f') == negation);
  case 'p':
    if (1 == scanf ("%u", &ch))
      return &LtlAtom::construct (ch, negation);
    fputs ("error in proposition number\n", stderr);
    return 0;
  case '!':
    negation = !negation;
    goto loop;
  case '&':
  case '|':
    if ((left = readFormula (negation)) && (right = readFormula (negation)))
      return &LtlJunct::construct ((ch == '&') != negation, *left, *right);
    return 0;
  case 'i':
    if ((left = readFormula (!negation)) && (right = readFormula (negation)))
      return &LtlJunct::construct (negation, *left, *right);
    return 0;
  case 'e':
  case '^' :
    if ((left = readFormula (false)) && (right = readFormula (false)))
      return &LtlIff::construct ((ch == 'e') != negation, *left, *right);
    return 0;
  case 'X':
    return (left = readFormula (negation))
      ? &LtlFuture::construct (LtlFuture::next, *left)
      : 0;
  case 'F':
  case 'G':
    return (left = readFormula (negation))
      ? &LtlFuture::construct ((ch == 'F') == negation
			       ? LtlFuture::globally
			       : LtlFuture::finally, *left)
      : 0;
  case 'U':
  case 'V':
    if ((left = readFormula (negation)) && (right = readFormula (negation)))
      return &LtlUntil::construct ((ch == 'U') == negation, *left, *right);
  case EOF:
    fputs ("unexpected end of file while parsing formula\n", stderr);
    return 0;
  default:
    fprintf (stderr, "unknown character 0x%02x\n", ch);
    return 0;
  }
}

/** Display the gates for arcs leaving a specific Büchi automaton state
 * @param gba		the generalized Büchi automaton
 * @param state		the state whose successor arcs are to be displayed
 */
static void
printGates (const class LtlGraph& gba,
	    unsigned state)
{
  for (LtlGraph::const_iterator n = gba.begin (); n != gba.end (); n++) {
    if (n->second.m_incoming.find (state) ==
	const_cast<std::set<unsigned>&>(n->second.m_incoming).end ())
      continue;
    const class BitVector& propositions = n->second.m_atomic;
    printf ("%u ", n->first);
    /** Previously encountered gate expression */
    const class LtlAtom* gate = 0;

    for (unsigned i = propositions.nonzero (); i; ) {
      if (gate)
	printf (gate->isNegated () ? "& ! p%u " : "& p%u ",
		gate->getValue ());
      gate = &static_cast<const class LtlAtom&>(Ltl::fetch (i - 1));
      if (i) i = propositions.findNext (i);
    }
    if (gate)
      printf (gate->isNegated () ? "! p%u\n" : "p%u\n", gate->getValue ());
    else
      puts ("t");
  }
  puts ("-1");
}

/** Translate a formula and output the automaton to standard output
 * @param formula	the formula to be translated
 */
static void
translateFormula (const class Ltl& formula)
{
  /** The generalized Büchi automaton */
  class LtlGraph gba (formula);
  /** acceptance set number and proposition */
  typedef std::pair<unsigned, const class Ltl*> acceptance_set_t;
  typedef std::map<const class Ltl*, acceptance_set_t> acceptance_map_t;
  acceptance_map_t acceptance_sets;

  /** number of states */
  unsigned numStates = 0;
  /** iterator to states */
  LtlGraph::const_iterator s;

  // construct the acceptance sets
  for (s = gba.begin (); s != gba.end (); s++) {
    numStates++;
    const class BitVector& temporal = s->second.m_old;
    for (unsigned i = temporal.nonzero (); i; ) {
      const class Ltl& f = Ltl::fetch (i - 1);
      switch (f.getKind ()) {
      case Ltl::Until:
	if (!static_cast<const class LtlUntil&>(f).isRelease ())
	  acceptance_sets.insert (std::pair<const class Ltl*,acceptance_set_t>
				  (&f, acceptance_set_t
				   (acceptance_sets.size (),
				    &static_cast<const class LtlUntil&>
				    (f).getRight ())));
	break;
      case Ltl::Future:
	if (static_cast<const class LtlFuture&>(f).getOp () ==
	    LtlFuture::finally)
	  acceptance_sets.insert (std::pair<const class Ltl*,acceptance_set_t>
				  (&f, acceptance_set_t
				   (acceptance_sets.size (),
				    &static_cast<const class LtlFuture&>
				    (f).getFormula ())));
	break;
      default:
	break;
      }
      if (i) i = temporal.findNext (i);
    }
  }

  if (numStates) {
    printf ("%u %u", numStates + 1, acceptance_sets.size ());
    puts ("\n0 1 -1");
    printGates (gba, 0);
  }
  else
    puts ("0 0");

  for (s = gba.begin (); s != gba.end (); s++) {
    printf ("%u 0", s->first);
    const class BitVector& temporal = s->second.m_old;

    // determine and display the acceptance sets the state belongs to
    for (acceptance_map_t::iterator a = acceptance_sets.begin ();
	 a != acceptance_sets.end (); a++) {
      /** flag: does the state belong to the acceptance set? */
      bool accepting = true;

      for (unsigned i = temporal.nonzero (); i; ) {
	const class Ltl* f = &Ltl::fetch (i - 1);
	if (f == a->second.second) {
	  accepting = true;
	  break;
	}
	else if (f == a->first)
	  accepting = false;
	if (i) i = temporal.findNext (i);
      }

      if (accepting)
	printf (" %u", a->second.first);
    }

    puts (" -1");
    printGates (gba, s->first);
  }
}

int main(int argc, char* argv[])
{
  if (argc > 1) {
    fputs ("usage: ", stderr);
    fputs (*argv, stderr);
    fputs (" < formula.txt > automaton.txt\n", stderr);
    return 1;
  }

  if (class Ltl* formula = readFormula (false)) {
    translateFormula (*formula);
    int ch;
    while ((ch = getchar ()) == ' ' || ch == '\n' || ch == '\r' ||
	   ch == '\t' || ch == '\v' || ch == '\f');
    if (ch != EOF) {
      fputs ("ignoring extraneous input: '", stderr);
      do putc (ch, stderr); while ((ch = getchar ()) != EOF);
      fputs ("'\n", stderr);
      return 2;
    }
  }
  else
    return 2;

  return 0;
}
