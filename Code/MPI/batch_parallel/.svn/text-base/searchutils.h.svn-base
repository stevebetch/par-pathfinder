//-----------------------------------------------------------------------------
/** @file searchutils.h
    Utilities for running searches.

    $Id: searchutils.h,v 1.3 2003/06/09 20:39:51 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/searchutils.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_SEARCHUTILS_H
#define PATHFIND_SEARCHUTILS_H

#include "environment.h"
#include <cstdlib>
//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    /** Utility operations for running searches. */
    class SearchUtils
    {
    public:
        bool checkPathExists(const Environment& env, int start, int target);

        void findRandomStartTarget(const Environment& env,
                                   int& start, int &target);

    private:
        int m_target;

        const Environment* m_env;

        vector<bool> m_mark;

        vector<vector<Environment::Successor> > m_successorStack;

        bool searchPathExists(int node, int depth);
    };
}

//-----------------------------------------------------------------------------

#endif
