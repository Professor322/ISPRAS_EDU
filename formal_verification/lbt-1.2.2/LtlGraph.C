// -*- c++ -*-
/// @file LtlGraph.C
/*
 * This file is based on code originally written by Mauno Rönkkö,
 * Copyright © 1998 Mauno Rönkkö <mronkko@abo.fi>.
 *
 * Modifications by Heikki Tauriainen <Heikki.Tauriainen@hut.fi>
 * and Marko Mäkelä <Marko.Makela@hut.fi>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifdef __GNUC__
# pragma implementation
#endif // __GNUC__
#include "LtlGraph.h"
#include <stack>

/// An empty formula set
static const class BitVector e;

LtlGraph::LtlGraph (const class Ltl& formula) :
  m_next (1), m_nodes ()
{
  std::stack<class LtlGraphNode*> nodes_to_expand;

  std::set<unsigned> incoming;
  incoming.insert (0);

  class BitVector new_set (formula.m_num + 1);
  new_set.assign_true (formula.m_num);

  nodes_to_expand.push (new class LtlGraphNode (incoming, new_set, e, e, e));

expand_next_node:
  while (!nodes_to_expand.empty ())
  {
    class LtlGraphNode& node = *nodes_to_expand.top ();
    if (unsigned p = node.m_new.nonzero ()) {
      p--;
      node.m_old.assign_true (p);
      node.m_new.assign_false (p);
      Ltl::fetch (p).expand (node, nodes_to_expand);
      continue;
    }

    nodes_to_expand.pop ();
    // no new propositions: merge the node with the graph
    // search for an existing node having the same 'old' and 'next' sets
    for (iterator i = m_nodes.begin (); i != m_nodes.end (); i++) {
      if (i->second.m_old == node.m_old && i->second.m_next == node.m_next) {
	// merge the node with an existing one
	i->second.m_incoming.insert (node.m_incoming.begin(),
				     node.m_incoming.end());
	delete &node;
	goto expand_next_node;
      }
    }

    // a genuinely new node: insert it to the graph and expand further
    m_nodes.insert (std::pair<unsigned,class LtlGraphNode> (m_next, node));
    std::set<unsigned> incoming;
    incoming.insert (m_next++);
    nodes_to_expand.push (new class LtlGraphNode (incoming, node.m_next, e,
						  e, e));
    delete &node;
  }
}
