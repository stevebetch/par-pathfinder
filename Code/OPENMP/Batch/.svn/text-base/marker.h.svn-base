//-----------------------------------------------------------------------------
/** @file marker.h
    Classes for marking node IDs.
    @see marker

    $Id: marker.h,v 1.3 2003/08/06 21:34:26 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/marker.h,v $
*/
//-----------------------------------------------------------------------------
/** @page marker Marker Classes

    Marker classes are classes for marking node IDs.
    The classes have different properties with respect to memory usage
    and time for clearing.
    They have identical interfaces to be used as replacable template
    parameters for other classes.

    Currently implemented marker classes are:
    - PathFind::MarkerBoolVector
    - PathFind::MarkerFastClear
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_MARKER_H
#define PATHFIND_MARKER_H
#include <assert.h>
#include <algorithm>
#include <vector>

//-----------------------------------------------------------------------------

namespace PathFind
{

    using namespace std;
    
    /** Array for marking node IDs.
        Uses a vector<bool> which is usually implemented in the standard
        library as a bitarray by template specialization.
        @see @ref marker
    */
    class MarkerBoolVector
    {
    public:
        MarkerBoolVector()
        {
            m_numberNodes = 0;
        }
        
        bool get(int nodeId) const
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            return m_array[nodeId];
        }
        
        void init(int numberNodes)
        {
            m_numberNodes = numberNodes;
            m_array.clear();
            m_array.resize(numberNodes, false);
        }
        
        void set(int nodeId)
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            m_array[nodeId] = true;
        }
        
        void unset(int nodeId)
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            m_array[nodeId] = false;
        }
        
    private:
        int m_numberNodes;
        
        vector<bool> m_array;
    };
    
    /** Array for marking node IDs.
        Stores a counter for marked indices which is incremented after each
        clear(), so clear() takes constant time.
        @see @ref marker
    */
    class MarkerFastClear
    {
    public:
        MarkerFastClear()
        {
            m_numberNodes = 0;
        }

        bool get(int nodeId) const
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            return (m_array[nodeId] == m_counter);
        }

        void init(int numberNodes)
        {
            if (m_numberNodes == numberNodes)
            {
                ++m_counter;
                return;
            }
            m_numberNodes = numberNodes;
            m_array.resize(numberNodes);
            fill(m_array.begin(), m_array.end(), -1);
            m_counter = 0;

        }

        void set(int nodeId)
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            m_array[nodeId] = m_counter;
        }

        void unset(int nodeId)
        {
            assert(nodeId >= 0);
            assert(nodeId < m_numberNodes);
            m_array[nodeId] = -1;
        }

    private:
        int m_counter;

        int m_numberNodes;

        vector<int> m_array;
    };

//-----------------------------------------------------------------------------

} // namespace PathFind

#endif // PATHFIND_UTIL_H
