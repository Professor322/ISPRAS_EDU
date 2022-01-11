/**
 * @file lbt2dot.c
 * This filter converts an lbt-generated automaton to a GraphViz digraph
 * @author Marko.Makela@hut.fi (Marko Mäkelä)
 */
/*
 *
 *  Copyright © 2001  Marko Mäkelä <Marko.Makela@hut.fi>
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
#include<ctype.h>
#include<stdio.h>
#include<limits.h>

/** Copy a gate condition from standard input to standard output
 * @return	zero if everything is ok; nonzero on error
 */
static int
parseGate (void)
{
  int ch;
 loop:
  while (isspace (ch = fgetc (stdin)));
  fputc (ch, stdout);
  switch (ch) {
  case 't':
  case 'f':
    return 0;
  case '|':
  case '&':
  case 'i':
  case 'e':
    if (parseGate ())
      return 1;
  case '!':
    goto loop;
  case 'p':
    if (1 != fscanf (stdin, "%d", &ch)) {
      fputs ("error in proposition number\n", stderr);
      return 1;
    }
    fprintf (stdout, "%d", ch);
    return 0;
  case EOF:
    fputs ("unexpected end of file while parsing formula\n", stderr);
    return 2;
  default:
    fprintf (stderr, "unknown character 0x%02x", ch);
    return 2;
  }
}

/** The main program
 * @param argc	number of command-line arguments
 * @param argv	the command-line arguments
 */
int
main (int argc, char** argv)
{
  /** State counter */
  unsigned i;
  /** Generic number */
  unsigned num;
  /** a character */
  int ch;

  if (2 != fscanf (stdin, "%u%u", &i, &num)) {
  parseError:
    fputs ("error in automaton\n", stderr);
  semanticError:
    return 1;
  }

  fputs ("digraph g {\n", stdout);

  while (i--) {
    /** separator between acceptance set entries */
    const char* separator = "\\n";
    /** the state number */
    unsigned state;
    /* read the state number and "initial state" flag */
    if (2 != fscanf (stdin, "%u%u", &state, &num) || num > 1)
      goto parseError;
    fprintf (stdout, "%u", state);
    fputs ("[", stdout);
    if (num) /* initial state */
      fputs ("style=filled,", stdout);
    fprintf (stdout, "label=\"%u", state);

    /* acceptance sets that the state belongs to */
    for (;;) {
      while (isspace (ch = fgetc (stdin)));
      if (ch == '-') {
	if (1 != fscanf (stdin, "%u", &num) || 1 != num) {
	  fputs ("unexpected data after '-'\n", stderr);
	  goto semanticError;
	}
	break;
      }
      ungetc (ch, stdin);
      if (!isdigit (ch) || 1 != fscanf (stdin, "%u", &num))
	goto parseError;
      fprintf (stdout, "%s%u", separator, num);
      separator = ",";
    }

    fputs ("\"];\n", stdout);

    /* transitions */
    for (;;) {
      while (isspace (ch = fgetc (stdin)));
      if (ch == '-') {
	if (1 != fscanf (stdin, "%u", &num) || 1 != num) {
	  fputs ("unexpected data after '-'\n", stderr);
	  goto semanticError;
	}
	break;
      }
      ungetc (ch, stdin);
      if (!isdigit (ch) || 1 != fscanf (stdin, "%u", &num))
	goto parseError;
      fprintf (stdout, "%u->%u[label=\"", state, num);
      if (parseGate ())
	goto parseError;
      fputs ("\"];\n", stdout);
    }
  }

  fputs ("}\n", stdout);

  while (isspace (ch = fgetc (stdin)));

  if (ch != EOF) {
    fputs ("extraneous non-whitespace data at end of input\n", stderr);
    goto semanticError;
  }

  return 0;
}
