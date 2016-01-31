//-----------------------------------------------------------------------------
/** @file idastar.cpp
    @see idastar.h

    $Id: idastar.cpp,v 1.14 2003/07/16 21:22:01 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/idastar.cpp,v $
*/
//-----------------------------------------------------------------------------

#include "idastar.h"

#include <iostream>
#include <math.h>
#include "util.h"
#include <assert.h>

using namespace std;
using namespace PathFind;

//-----------------------------------------------------------------------------

IDAStar::IDAStar(Caching caching)
    : m_caching(caching),
      m_statistics(createStatistics()),
      m_branchingFactor(m_statistics.get("branching_factor"))
{
}

bool IDAStar::checkCache(int nodeId, int f, int g, int iteration, int& fMin)
{
    if (m_cache[nodeId].m_iter > 0) 
    {
        if ((m_cache[nodeId].m_g < g) ||
            ((m_cache[nodeId].m_g == g) && 
             (m_cache[nodeId].m_iter == iteration)))
        {
            fMin = INT_MAX;
            return true;
        }

        if ( m_caching == F_CACHING )
        {
            // Check if backed-up F-value causes an early termination.
            if ( m_cache[nodeId].m_f > m_fLimit )
            {
                fMin = m_cache[nodeId].m_f;
                return true;
            }
        }

    }
    return false;
}

StatisticsCollection IDAStar::createStatistics()
{
    StatisticsCollection collection;
    collection.create("aborted");
    collection.create("cpu_time");
    collection.create("path_cost");
    collection.create("path_length");
    collection.create("branching_factor");
    collection.create("nodes_expanded");
    collection.create("nodes_visited");
    collection.create("iterations");
    return collection;
}

bool IDAStar::findPath(const Environment& env, int start, int target)
{
    assert(env.isValidNodeId(start));
    assert(env.isValidNodeId(target));
    clock_t startTime = clock();
    m_statistics.clear();
    m_nodesExpanded = 0;
    m_nodesVisited = 0;
    m_env = &env;
    m_target = target;
    m_path.clear();
    m_abortSearch = false;
    m_visitedNodes.resize(env.getNumberNodes());
    fill(m_visitedNodes.begin(), m_visitedNodes.end(), ' ');
    if ( m_caching != NO_CACHING )
    {
        m_cache.clear();
        m_cache.resize(env.getNumberNodes());
    }
    findPathIdaStar(start);
    m_statistics.get("aborted").add(m_abortSearch ? 1 : 0);
    double timeDiff =
        static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
    m_statistics.get("cpu_time").add(timeDiff);
    m_statistics.get("nodes_expanded").add(m_nodesExpanded);
    m_statistics.get("nodes_visited").add(m_nodesVisited);
    m_statistics.get("path_length").add(m_path.size());
    return true;
}

void IDAStar::findPathIdaStar(int start)
{
    const int maxFLimit = m_env->getNumberNodes() * m_env->getMaxCost();
    int heuristic = m_env->getHeuristic(start, m_target);
    m_fLimit = heuristic;
    int minCost = m_env->getMinCost();
    unsigned int expectedMaxDepth =
        static_cast<unsigned int>(heuristic / minCost);
    if (m_successorStack.size() < expectedMaxDepth)
        m_successorStack.resize(expectedMaxDepth);
    int iteration = 1;

    while (true)
    {
        //cerr << "limit = " << m_fLimit << '\n';
        int fMin = INT_MAX;
        searchPathIdaStar(iteration, start, NO_NODE, 0, 0, fMin);
        if (m_path.size() > 0)
            break;
        if (fMin > maxFLimit)
            break;
        m_fLimit = fMin;
        ++iteration;
    }
    m_statistics.get("iterations").add(iteration);
}

const StatisticsCollection& IDAStar::getStatistics() const
{
    return m_statistics;
}

void IDAStar::markVisitedNode(int nodeId, int iteration)
{
    if (m_visitedNodes[nodeId] != ' ')
        return;
    m_visitedNodes[nodeId] = getVisitedNodeLabel(iteration);
}

bool IDAStar::searchPathIdaStar(int iteration, int node, int lastNode,
                                int depth, int g, int& fMin)
{
    ++m_nodesVisited;
    markVisitedNode(node, iteration);
    if (m_nodesLimit >= 0 && m_nodesVisited > m_nodesLimit)
    {
        m_abortSearch = true;
        fMin = INT_MAX;
        return false;
    }
    int f = g + m_env->getHeuristic(node, m_target);
    if (f > m_fLimit)
    {
        fMin = f;
        return false;
    }
    if (node == m_target)
    {
        m_statistics.get("path_cost").add(f);
        m_path.push_back(node);
        fMin = f;
        return true;
    }

    if (m_caching != NO_CACHING)
    {
        if (checkCache(node, f, g, iteration, fMin))
        {
            return false;
        }
        addCache(node, f, g, iteration);
    }

    ++m_nodesExpanded;
    assert(depth >= 0);
    if (m_successorStack.size() < static_cast<unsigned int>(depth + 1))
        m_successorStack.resize(depth + 1);
    vector<Environment::Successor>& successors = m_successorStack[depth];
    m_env->getSuccessors(node, lastNode, successors);
    int numberSuccessors = successors.size();
    m_branchingFactor.add(numberSuccessors);
    fMin = INT_MAX;
    for (int i = 0; i < numberSuccessors; ++i)
    {
        // Get reference on edge again, because resize could have changed it.
        const Environment::Successor& successor = m_successorStack[depth][i];
        int targetNodeId = successor.m_target;
        int fMinChild;
        if (targetNodeId == lastNode)
            continue;
        if (searchPathIdaStar(iteration, targetNodeId, node, depth + 1,
                              g + successor.m_cost, fMinChild))
        {
            if ( fMinChild < fMin )
                fMin = fMinChild;
            m_path.push_back(node);
            return true;
        }
        if ( fMinChild < fMin )
            fMin = fMinChild;

        if (m_abortSearch)
            return false;
    }

    if ( m_caching == F_CACHING ) 
    {
        if ( fMin > m_cache[node].m_f )
            m_cache[node].m_f = fMin;
    }
    
    return false;
}

//-----------------------------------------------------------------------------
