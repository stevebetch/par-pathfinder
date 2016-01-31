//-----------------------------------------------------------------------------
/** @file fringesearch.cpp
    @see fringesearch.h

    $Id: fringesearch.cpp,v 1.4 2003/07/25 17:43:23 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/fringesearch.cpp,v $
*/
//-----------------------------------------------------------------------------

#include "fringesearch.h"

#include "util.h"

using namespace std;
using namespace PathFind;

//-----------------------------------------------------------------------------

Fringe::Fringe()
{
    m_numberNodes = 0;
}

void Fringe::init(int numberNodes)
{
    m_nodes.resize(numberNodes);
    m_isInList.clear();
    m_isInList.resize(numberNodes, false);
    m_numberNodes = numberNodes;
    m_currentNode = NO_NODE;
    m_headNode = NO_NODE;
}

void Fringe::insertNode(int nodeId)
{
    if (m_isInList[nodeId])
        removeNode(nodeId);
    m_isInList[nodeId] = true;
    Node& newNode = getNode(nodeId);
    if (m_headNode != NO_NODE)
    {
        Node& current = getNode(m_currentNode);
        int next = current.m_next;
        newNode.m_previous = m_currentNode;
        newNode.m_next = next;
        if (next != NO_NODE)
            getNode(next).m_previous = nodeId;
        current.m_next = nodeId;
    }
    else
    {
        m_headNode = nodeId;
        newNode.m_previous = NO_NODE;
        newNode.m_next = NO_NODE;
    }
}

void Fringe::nextNode()
{
    assert(m_currentNode != NO_NODE);
    m_currentNode = getNode(m_currentNode).m_next;
    assert(m_currentNode == NO_NODE || m_isInList[m_currentNode]);
}

void Fringe::print(ostream& o) const
{
    o << "Fringe {\n";
    int nodeId = m_headNode;
    while (nodeId != NO_NODE)
    {
        o << nodeId << '\n';
        nodeId = getNode(nodeId).m_next;
    }
    o << "}\n";
}

void Fringe::removeNode(int nodeId)
{
    assert(nodeId != NO_NODE);
    assert(m_isInList[nodeId]);
    Node& node = getNode(nodeId);
    int previous = node.m_previous;
    int next = node.m_next;
    if (previous != NO_NODE)
        getNode(previous).m_next = next;
    else
        m_headNode = next;    
    if (next != NO_NODE)
        getNode(next).m_previous = previous;
    m_isInList[nodeId] = false;
}

void Fringe::startIteration()
{
    m_currentNode = m_headNode;
}

//-----------------------------------------------------------------------------
