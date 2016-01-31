//-----------------------------------------------------------------------------
/** @file fringesearch.h
    IDA* like search keeping a list of the fringe nodes.

    $Id: fringesearch.h,v 1.3 2003/08/06 21:34:26 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/fringesearch.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_FRINGESEARCH_H
#define PATHFIND_FRINGESEARCH_H

#include <vector>
#include "marker.h"
#include "search.h"
#include "util.h"
#include <limits.h>

//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    /** Statically allocated linked list used in FringeSearch. */
    class Fringe
    {
    public:
        Fringe();
        
        int getCurrentNode() const
        {
            return m_currentNode;
        }
        
        void init(int numberNodes);
        
        void insertNode(int nodeId);
        
        void nextNode();
        
        void print(ostream& o) const;
        
        void removeCurrentNode()
        {
            removeNode(m_currentNode);
        }
        
        void startIteration();
        
    private:
        /** Node used in Fringe. */
        class Node
        {
        public:
            int m_next;
            
            int m_previous;
        };
        
        
        int m_currentNode;
        
        int m_numberNodes;
        
        int m_headNode;
        
        vector<bool> m_isInList;
        
        vector<Node> m_nodes;
        
        
        Node& getNode(int nodeId)
        {
            assert(nodeId >= 0 && nodeId < m_numberNodes);
            return m_nodes[nodeId];
        }
        
        const Node& getNode(int nodeId) const
        {
            assert(nodeId >= 0 && nodeId < m_numberNodes);
            return m_nodes[nodeId];
        }
        
        void removeNode(int nodeId);
    };

    /** IDA* like search keeping a list of the fringe nodes.
        This avoids re-expansion of interior nodes at each new
        iteration.

        %Statistics (see Search::createStatistics and Search::getStatistics):
        - "cpu_time"
        - "iterations"
        - "nodes_expanded"
        - "nodes_visited"
        - "path_cost"
        - "path_length"
    */
    template<class MARKER = MarkerFastClear>
    class FringeSearch
        : public Search
    {
    public:
        FringeSearch();

        StatisticsCollection createStatistics();

        bool findPath(const Environment& env, int start, int target);

        const vector<int>& getPath() const
        {
            return m_path;
        }

        const StatisticsCollection& getStatistics() const;

        const vector<char>& getVisitedNodes() const
        {
            return m_visitedNodes;
        }

    private:   
        /** Cache element for g-value used in FringeSearch. */
        class CacheElement
        {
        public:
            int m_gValue;
            
            int m_iteration;

            int m_parent;
        };


        int m_nodesExpanded;

        int m_nodesVisited;

        int m_target;

        const Environment* m_env;

        Fringe m_fringe;

        StatisticsCollection m_statistics;

        vector<CacheElement> m_cache;
        
        MARKER m_isCacheValid;
        
        vector<char> m_visitedNodes;

        vector<int> m_path;


        void addCache(int nodeId, int gValue, int iteration, int parent);

        bool checkCache(int nodeId, int gValue, int iteration) const;

        void constructPath(int start);

        void getFromCache(int nodeId, int& gValue, int& parent) const;

        void doIteration(int iteration, int fLimit, int& fMin);

        void init(int numberNodes);

        void markVisitedNode(int nodeId, int iteration);
    };

}

//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    template<class MARKER>
    FringeSearch<MARKER>::FringeSearch()
        : m_statistics(createStatistics())
    {
    }
    
    template<class MARKER>
    void FringeSearch<MARKER>::addCache(int nodeId, int gValue, int iteration,
                                        int parent)
    {
        CacheElement& cacheElement = m_cache[nodeId];
        cacheElement.m_gValue = gValue;
        cacheElement.m_iteration = iteration;
        cacheElement.m_parent = parent;
        m_isCacheValid.set(nodeId);
    }

    template<class MARKER>
    bool FringeSearch<MARKER>::checkCache(int nodeId, int gValue,
                                          int iteration) const
    {
        if (! m_isCacheValid.get(nodeId))
            return false;
        const CacheElement& cacheElement = m_cache[nodeId];
        int gValueCached = cacheElement.m_gValue;
        return (gValue > gValueCached
                || (gValue == gValueCached
                    && iteration == cacheElement.m_iteration));
    }

    template<class MARKER>
    void FringeSearch<MARKER>::constructPath(int start)
    {
        m_path.clear();
        if (! m_isCacheValid.get(m_target))
            return;
        int nodeId = m_target;
        do
        {
            m_path.push_back(nodeId);
            nodeId = m_cache[nodeId].m_parent;
            assert(m_isCacheValid.get(nodeId));
        }
        while (nodeId != start);
        m_path.push_back(nodeId);
    }

    template<class MARKER>
    StatisticsCollection FringeSearch<MARKER>::createStatistics()
    {
        StatisticsCollection collection;
        collection.create("cpu_time");
        collection.create("iterations");
        collection.create("nodes_expanded");
        collection.create("nodes_visited");
        collection.create("path_cost");
        collection.create("path_length");
        return collection;
    }

    template<class MARKER>
    void FringeSearch<MARKER>::doIteration(int iteration, int fLimit,
                                           int& fMin)
    {
        m_fringe.startIteration();
        vector<Environment::Successor> successors;
        while (true)
        {
            int nodeId = m_fringe.getCurrentNode();
            if (nodeId == NO_NODE)
                return;
            ++m_nodesVisited;
            markVisitedNode(nodeId, iteration);
            int gValue;
            int lastNode;
            getFromCache(nodeId, gValue, lastNode);
            if (nodeId == m_target)
            {
                m_statistics.get("path_cost").add(gValue);
                return;
            }
            int fValue = gValue + m_env->getHeuristic(nodeId, m_target);
            if (fValue > fLimit)
            {
                if (fValue < fMin)
                    fMin = fValue;
                m_fringe.nextNode();
                continue;
            }
            m_env->getSuccessors(nodeId, lastNode, successors);
            int numberSuccessors = successors.size();
            // Reverse loop so that nodes are visited in same order as in IDA*
            for (int i = numberSuccessors; i--; )
            {
                const Environment::Successor& successor = successors[i];
                int targetNodeId = successor.m_target;
                int targetGValue = gValue + successor.m_cost;
                if (checkCache(targetNodeId, targetGValue, iteration))
                    continue;
                m_fringe.insertNode(targetNodeId);
                addCache(targetNodeId, targetGValue, iteration, nodeId);
                ++m_nodesExpanded;
            }
            m_fringe.removeCurrentNode();
            m_fringe.nextNode();
        }
    }

    template<class MARKER>
    bool FringeSearch<MARKER>::findPath(const Environment& env, int start,
                                        int target)
    {
        assert(env.isValidNodeId(start));
        assert(env.isValidNodeId(target));
        clock_t startTime = clock();
        m_env = &env;
        m_target = target;
        int numberNodes = env.getNumberNodes();
        init(numberNodes);
        m_nodesExpanded = 0;
        m_nodesVisited = 0;
        int iteration = 1;
        int fLimit = env.getHeuristic(start, target);
        m_fringe.insertNode(start);
        addCache(start, 0, 0, NO_NODE);
        while (! m_isCacheValid.get(m_target))
        {
            //cerr << "limit = " << fLimit << '\n';
            int fMin = INT_MAX;
            doIteration(iteration, fLimit, fMin);
            fLimit = fMin;
            ++iteration;
            //m_fringe.print(cerr);
        }
        constructPath(start);
        m_statistics.get("iterations").add(iteration);
        double timeDiff =
            static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
        m_statistics.get("nodes_visited").add(m_nodesVisited);
        m_statistics.get("nodes_expanded").add(m_nodesExpanded);
        m_statistics.get("path_length").add(m_path.size());
        m_statistics.get("cpu_time").add(timeDiff);
        return true;
    }

    template<class MARKER>
    void FringeSearch<MARKER>::getFromCache(int nodeId, int& gValue,
                                            int& parent) const
    {
        assert(m_isCacheValid.get(nodeId));
        const CacheElement& cacheElement = m_cache[nodeId];
        parent = cacheElement.m_parent;
        gValue = cacheElement.m_gValue;
    }

    template<class MARKER>
    const StatisticsCollection& FringeSearch<MARKER>::getStatistics() const
    {
        return m_statistics;
    }

    template<class MARKER>
    void FringeSearch<MARKER>::init(int numberNodes)
    {
        m_visitedNodes.resize(numberNodes);
        fill(m_visitedNodes.begin(), m_visitedNodes.end(), ' ');
        m_isCacheValid.init(numberNodes);
        m_cache.resize(numberNodes);
        m_fringe.init(numberNodes);
        m_statistics.clear();
    }

    template<class MARKER>
    void FringeSearch<MARKER>::markVisitedNode(int nodeId, int iteration)
    {
        if (m_visitedNodes[nodeId] != ' ')
            return;
        m_visitedNodes[nodeId] = getVisitedNodeLabel(iteration);
    }

}

//-----------------------------------------------------------------------------
#endif
