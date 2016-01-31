//-----------------------------------------------------------------------------
/** @file astar.cpp
    @see astar.h

    $Id: astar.cpp,v 1.29 2003/07/24 18:55:13 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/astar.cpp,v $
*/
//-----------------------------------------------------------------------------

#include "astar.h"

#include <iostream>
#include <math.h>
#include <memory>
#include <assert.h>
#include "util.h"

using namespace std;
using namespace PathFind;

//-----------------------------------------------------------------------------

AStarNode::Compare::~Compare()
{
    ;
}

bool AStarNode::Compare::operator()(const AStarNode& node1,
                                    const AStarNode& node2)
{
    int f1 = node1.m_f;
    int f2 = node2.m_f;
    if (f1 != f2)
        return (f1 < f2);
    int g1 = node1.m_g;
    int g2 = node2.m_g;
    return (g1 > g2);
}

//-----------------------------------------------------------------------------

void AStarNode::print(ostream& ostrm) const
{
    ostrm << "id:" << m_nodeId << '(' << m_g << ',' << m_h << ',' << m_f 
          << ',' << m_parent << ')';
}

//-----------------------------------------------------------------------------

void AStarClosed::add(const AStarNode& node)
{
    m_list.push_back(node);
}

vector<int> AStarClosed::constructPath(int start, int target)
{
    vector<int> result;
    int nodeId = target;
    while (true)
    {
        result.push_back(nodeId);
        if (nodeId == start)
            break;
        const AStarNode* node = search(nodeId);
        assert(node != 0);
        nodeId = node->m_parent;
    }
    assert(result.size() > 0);
    assert(*result.begin() == target);
    assert(*(result.end() - 1) == start);
    return result;
}

void AStarClosed::init(int maxNodeId)
{
    m_list.clear();
}

void AStarClosed::print(ostream& ostrm) const
{
   ostrm << "Closed {\n";
   for (list<AStarNode>::const_iterator i = m_list.begin();
        i != m_list.end(); ++i) 
   {
       i->print(ostrm);
       ostrm << '\n';
   }   
   ostrm << "}\n";
}

void AStarClosed::remove(int nodeId)
{
    for (list<AStarNode>::iterator i = m_list.begin();
         i != m_list.end(); ++i)
        if (i->m_nodeId == nodeId)
        {
            m_list.erase(i);
            return;
        }
}

const AStarNode* AStarClosed::search(int nodeId) const
{
    for (list<AStarNode>::const_iterator i = m_list.begin();
         i != m_list.end(); ++i)
        if (i->m_nodeId == nodeId)
            return &(*i);
    return 0;
}

//-----------------------------------------------------------------------------
