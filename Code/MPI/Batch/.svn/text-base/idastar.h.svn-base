//-----------------------------------------------------------------------------
/** @file idastar.h
    IDA* search.

    $Id: idastar.h,v 1.11 2003/08/06 21:34:26 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/idastar.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_IDASTAR_H
#define PATHFIND_IDASTAR_H

#include "search.h"
#include <climits>
//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    /** IDA* search algorithm.        
        Short desciption of IDA*:
        
        Each iteration is a depth-first search that keeps track of the cost
        f = g + h of each node generated. If a node is generated whose cost
        exceeds the threshold for that iteration, its path is cut off and
        the search backtracks. The cost threshold is initialized to the
        heuristic of the initial state and is increased in each iteration
        to the total cost of the lowest-cost node that was pruned during the
        previous iteration. The algorithm terminates when a goal state is
        reached whose total cost does not exceed the current threshold.

        %Statistics (see Search::createStatistics and Search::getStatistics):
        - "aborted"
        - "cpu_time"
        - "path_cost"
        - "path_length"
        - "branching_factor"
        - "nodes_expanded"
        - "nodes_visited"
        - "iterations"
    */
    class IDAStar
        : public Search
    {
    public:
        /** Caching strategy for f-values. */
        typedef enum { 
            /** No caching. */
            NO_CACHING, 

            /** Local caching (f-caching) */
            f_CACHING, 

            /** Caching of backed up f-values (F-caching) */
            F_CACHING 
        } Caching;

        IDAStar(Caching caching = NO_CACHING);

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
        /** Information for caching f-values. */
        class CacheNode 
        {
        public:
            int m_iter;

            int m_f;

            int m_g;
        };


        bool m_abortSearch;

        int m_target;

        int m_fLimit;

        Caching  m_caching;

        const Environment* m_env;

        long long int m_nodesExpanded;

        long long int m_nodesVisited;

        vector<char> m_visitedNodes;

        vector<CacheNode> m_cache;

        vector<int> m_path;

        vector<vector<Environment::Successor> > m_successorStack;

        StatisticsCollection m_statistics;

        Statistics& m_branchingFactor;

        void addCache(int nodeId, int f, int g, int iteration)
        {
            m_cache[nodeId].m_iter = iteration;
            m_cache[nodeId].m_f    = f;
            m_cache[nodeId].m_g    = g;
        }

        /** Check in cache.
            Check in cache if node has be visited before via a shorter path.
        */
        bool checkCache(int nodeId, int f, int g, int iteration, int& f_min);

        void findPathIdaStar(int start);

        void markVisitedNode(int nodeId, int iteration);

        bool searchPathIdaStar(int iteration, int node, int lastNode,
                               int depth, int g, int& f_min);
    };
}

//-----------------------------------------------------------------------------

#endif
