//-----------------------------------------------------------------------------
/** @file tiling.h
    Search environment using tilings and obstacles.

    $Id: tiling.h,v 1.35 2003/06/13 19:25:06 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/tiling.h,v $
*/
//-----------------------------------------------------------------------------
/** @page tilingfileformat Tiling file format
    The file format for tilings is as follows:

    @verbatim
    type tile|octile|octile_unicost|hex
    height <height>
    width <width>
    map
    <obstacle map using one line per row and one character per column.>
    <The character '@' means obstacle, '.' means no obstacle.>
    @endverbatim

    Example:

    @verbatim
    type tile
    height 10
    width 20
    map
    ....................
    ....................
    ...........@........
    ...@@@@@@@@@..@.....
    ..............@.....
    ...@@@@@@@@@..@.....
    ...@.......@..@.....
    ...@.......@..@.....
    ...........@........
    ....................
    @endverbatim

    @see @ref tilinghexgridmapping
*/
/** @page tilinghexgridmapping Tiling hex grid mapping
    Hex grids use the following mapping between (column,row) to nodes:

    @image html hexgrid.png "Hex grid mapping of (column,row)"

    @see @ref tilinghexgridmappingascii
*/
/** @page tilinghexgridmappingascii Tiling hex grid mapping (ASCII version)
    Hex grids use the following mapping between (column,row) to nodes:

    @verbatim
     ___     ___
    /0,0\___/2,0\___
    \___/1,0\___/3,0\
    /0,1\___/2,1\___/
    \___/1,1\___/3,1\
    /0,2\___/2,2\___/
    \___/1,2\___/3,2\
        \___/   \___/
    @endverbatim    
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_TILING_H
#define PATHFIND_TILING_H

#include <math.h>
#include "environment.h"
#include "graph.h"
#include "util.h"
#include <cstdlib>

#ifndef map_H_
#define map_H_

#include "map.h"
#endif

//-----------------------------------------------------------------------------

namespace PathFind
{
    const int COST_ONE = 100;

    const int COST_SQRT2 = 142;

    /** Generic edge data for Tiling::TilingGraph. */
    class TilingEdgeInfo
    {
    public:
        TilingEdgeInfo(int cost)
            : m_cost(cost)
        {
            assert(cost == COST_ONE || cost == COST_SQRT2);
        }

        int getCost() const
        {
            return m_cost;
        }

    private:
        int m_cost;
    };
    
    /** Generic node data for Tiling::TilingGraph. */
    class TilingNodeInfo
    {
    public:
        TilingNodeInfo();

        TilingNodeInfo(bool isObstacle, int row, int column);

        int getColumn() const
        {
            return m_column;
        }

        int getRow() const
        {
            return m_row;
        }

        bool isObstacle() const
        {
            return m_isObstacle;
        }

        void setObstacle(bool isObstacle)
        {
            m_isObstacle = isObstacle;
        }

    private:
        bool m_isObstacle;

        int m_column;

        int m_row;
    };

    /** %Search environment implementing a regular grid.
        Nodes can be blocked. Edge costs are uniform.
    */
    class Tiling
        : public Environment
    {
    public:
        typedef enum {
            /** Hex grid type.
                @see @ref tilinghexgridmapping
            */
            HEX,

            /** Octiles with cost 1 to adjacent and sqrt(2) to diagonal. */
            OCTILE,

            /** Octiles with uniform cost 1 to adjacent and diagonal. */
            OCTILE_UNICOST,

            /** Tile grid type. */
            TILE
        } Type;

        Tiling(Type type, int rows, int columns);
        
        Tiling(mapClass& Map) ;

        Tiling(const Tiling & tiling, int horizOrigin, int vertOrigin,
               int width, int height);

        /** Construct tiling from a file.
            @exception ReadError
            Reading failed or syntax error in file.
            @see @ref tilingfileformat
        */
        Tiling(LineReader& reader);

        void clearObstacles();

        int getHeuristic(int start, int target) const;

        int getMaxCost() const;

        int getMinCost() const;

        int getNodeId(int row, int column) const
        {
            assert(row >= 0 && row < m_rows);
            assert(column >= 0 && column < m_columns);
            return row * m_columns + column;
        }

        int getNumberNodes() const;

        void getSuccessors(int nodeId, int lastNodeId,
                           vector<Successor>& result) const;

        bool isValidNodeId(int nodeId) const;

        void printFormatted(ostream& o) const;

        void printFormatted(ostream& o, int start, int target) const;

        void printFormatted(ostream& o, const vector<int>& path) const;
        
        void printFormatted(mapClass& Map, const vector<int>& path) const;

        /** Print formatted map with char labels.
            Space characters are not printed on the map.
        */
        void printLabels(ostream& o, const vector<char>& labels) const;

        void printPathAndLabels(ostream& o, const vector<int>& path,
                                const vector<char>& labels) const;

        void setObstacles(float obstaclePercentage, bool avoidDiag=false);

        int getWidth() const
        {
            return m_columns;
        }

        int getHeight() const
        {
            return m_rows;
        }

        TilingNodeInfo & getNodeInfo(int nodeId) const
        {
            return (TilingNodeInfo &)m_graph.getNodeInfo(nodeId);
        }

        Type getType() const
        {
            return m_type;
        }

    private:
        typedef Graph<TilingNodeInfo, TilingEdgeInfo>::Edge TilingEdge;

        typedef Graph<TilingNodeInfo, TilingEdgeInfo> TilingGraph;

        typedef Graph<TilingNodeInfo, TilingEdgeInfo>::Node TilingNode;


        int m_columns;

        int m_maxEdges;

        int m_rows;

        Type m_type;

        TilingGraph m_graph;


        void addOutEdge(int nodeId, int row, int col, int cost);

        bool conflictDiag(int row, int col, int roff, int coff );

        void createEdges();

        void createNodes();

        vector<char> getCharVector() const;

        static int getMaxEdges(Type type);

        void init(Type type, int rows, int columns);

        void printFormatted(ostream& o, const vector<char>& chars) const;

        bool pruneNode(int targetNodeId, int lastNodeId) const;

        /** Read obstacles from a file.
            @exception ReadError Reading failed or syntax error in file.
        */
        void readObstacles(LineReader& reader);
    };
}

//-----------------------------------------------------------------------------

#endif
