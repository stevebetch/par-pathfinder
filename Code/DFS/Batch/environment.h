//-----------------------------------------------------------------------------
/** @file environment.h
    Search environment.

    $Id: environment.h,v 1.7 2003/06/09 21:15:04 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/environment.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_ENVIRONMENT_H
#define PATHFIND_ENVIRONMENT_H

#include <exception>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    /** Interface to search environment. */
    class Environment
    {
    public:
        /** Information about a successor of a node in the environment. */
        class Successor
        {
        public:
            Successor();
            
            Successor(int target, int cost)
                : m_target(target), m_cost(cost)
            { }
            
            int m_target;
            
            int m_cost;
        };
        
        virtual ~Environment();
        
        virtual int getHeuristic(int start, int target) const = 0;
        
        virtual int getMaxCost() const = 0;
        
        virtual int getMinCost() const = 0;
        
        virtual int getNumberNodes() const = 0;
        
        /** Generate successor nodes for the search.
            @param nodeId Current node
            @param lastNodeId
            Can be used to prune nodes,
            (is set to NO_NODE in Search::checkPathExists).
            @param result Resulting successors.
            Passed in as a reference to avoid dynamic memory allocation.
            The vector will be cleared and filled with the successors.
        */
        virtual void getSuccessors(int nodeId, int lastNodeId,
                                   vector<Successor>& result) const = 0;
        
        virtual bool isValidNodeId(int nodeId) const = 0;
    };        
}

#endif
