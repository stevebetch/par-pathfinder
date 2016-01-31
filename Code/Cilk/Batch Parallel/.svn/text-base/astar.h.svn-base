//-----------------------------------------------------------------------------
/** @file astar.h
    A* search algorithm.

    $Id: astar.h,v 1.23 2003/08/06 21:34:26 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/astar.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_ASTAR_H
#define PATHFIND_ASTAR_H

#include <list>
#include <memory>
#include <queue>
#include <set>
#include "marker.h"
#include <assert.h>
#include "search.h"
#include <cilk/cilk.h>
//-----------------------------------------------------------------------------

namespace PathFind
{
    
    using namespace std;    

    /** Node used in implementation of AStar. */
    class AStarNode
    {
    public:
        /** Function object for comparing nodes in the open queue. */
        class Compare
        {
        public:
            virtual ~Compare();
            
            bool operator()(const AStarNode& node1,
                            const AStarNode& node2);
        };
        
        int m_nodeId;
        
        int m_parent;
        
        int m_g;
        
        int m_h;
        
        int m_f;
        
        AStarNode()
        {
        }
        
        AStarNode(int nodeId, int parent, int g, int h)
            : m_nodeId(nodeId),
              m_parent(parent),
              m_g(g),
              m_h(h),
              m_f(g + h)
        {
        }
        
        void print(ostream& ostrm) const;
    };
    
    /** Closed list implementation using a list. */
    class AStarClosed
    {
    public:
        void add(const AStarNode& node);
        
        vector<int> constructPath(int start, int target);

        void init(int maxNodeId);
        
        void print(ostream& ostrm) const;
        
        void remove(int nodeId);
        
        const AStarNode* search(int nodeId) const;
        
    private:
        list<AStarNode> m_list;            
    };
    
    /** Closed list implementation using lookup table. */
    template<class MARKER>
    class AStarClosedLookup
    {
    public:
        AStarClosedLookup();
        
        void add(const AStarNode& node);
        
        vector<int> constructPath(int start, int target);

        void init(int maxNodeId);
        
        void print(ostream& ostrm) const;
        
        void remove(int nodeId);
        
        const AStarNode* search(int nodeId) const;
        
    private:
        int m_maxNodeId;
        
        MARKER m_marker;
        
        vector<AStarNode> m_nodes;            
    };
    
    /** Open queue for AStar. */
    template<class MARKER>
    class AStarOpen
    {
    public:
        AStarOpen();
        
        void init(int numberNodes);
        
        void insert(const AStarNode& node);
        
        bool isEmpty() const
        {
            return (m_nodes.size() == 0);
        }
        
        AStarNode pop();
        
        void print(ostream& ostrm) const;
        
        bool  remove(int nodeId);
        
        const AStarNode* search(int nodeId) const;
        
    private:
        typedef multiset<AStarNode, AStarNode::Compare> NodeSet;
        
        typedef NodeSet::const_iterator NodeSetConstIterator;
        
        typedef NodeSet::iterator NodeSetIterator;
        
        int m_numberNodes;
        
        MARKER m_marker;
        
        /** Iterator in m_nodes by nodeId. */
        vector<NodeSetIterator> m_lookupTable;
        
        NodeSet m_nodes;
    };

    /** A* search engine.

        Pseudo algorithm for basic A* algorithm:
        @verbatim
        priorityqueue Open
        list Closed

        AStarSearch
            s.g = 0 // s is the start node
            s.h = GoalDistEstimate(s)
            s.f = s.g + s.h
            s.parent = null
            push s on Open
            while Open is not empty
                pop node n from Open // n has the lowest f
                if n is a goal node
                    construct path
                    return success
                for each successor n' of n
                    newg = n.g + cost(n,n')
                    if n' is in Open or Closed
                       if n'.g <= newg skip
                       remove n' from Open or Closed
                    n'.parent = n
                    n'.g = newg
                    n'.h = GoalDistEstimate(n')
                    n'.f = n'.g + n'.h
                    push n' on Open
                push n onto Closed
            return failure // if no path found
        @endverbatim

        This class is implemented as a template class taking
        the following template parameters:
        - MARKER Marker class to use (see @ref marker)
        - CLOSED Closed list class to use

        %Statistics (see Search::createStatistics and Search::getStatistics):
        - "cpu_time"
        - "path_cost"
        - "path_length"
        - "nodes_expanded"
        - "nodes_visited"
        - "branching_factor"
    */
    template<class MARKER = MarkerFastClear,
             class CLOSED = AStarClosedLookup<MARKER> >
    class AStar
        : public Search
    {
    public:
        AStar();
        
        StatisticsCollection createStatistics();
        
        bool findPath(const Environment& env, int start, int target);

        const vector<int>& getPath() const
        {
            return m_path;
        }

        const StatisticsCollection& getStatistics() const;

        /** Get a vector with 'x' char labels for each visited node. */
        const vector<char>& getVisitedNodes() const
        {
            return m_visitedNodes;
        }

        void setNodesLimit(long long int nodesLimit)
        {
            m_nodesLimit = nodesLimit;
        }

        int getPathCost() const
        {
            return m_pathCost;
        }

    private:
        int m_pathCost;

        int m_target;

        const Environment* m_env;

        long long int m_nodesExpanded;

        long long int m_nodesVisited;

        CLOSED m_closed;

        vector<char> m_visitedNodes;

        vector<int> m_path;

        AStarOpen<MARKER> m_open;

        StatisticsCollection m_statistics;

        Statistics& m_branchingFactor;

        /** Find a node in open or closed lists. */
        const AStarNode* findNode(int nodeId);

        void findPathAStar(int start);

        /** Construct path and set statistics after target node was found. */
        void finishSearch(int start, const AStarNode& node);

        AStarNode getBestNodeFromOpen();
    };

} // namespace PathFind

//-----------------------------------------------------------------------------

namespace PathFind
{
    
    using namespace std;

    template<class MARKER, class CLOSED>
    AStar<MARKER, CLOSED>::AStar()
        : m_statistics(createStatistics()),
          m_branchingFactor(m_statistics.get("branching_factor"))
    {
    }

    template<class MARKER, class CLOSED>
    StatisticsCollection AStar<MARKER, CLOSED>::createStatistics()
    {
        StatisticsCollection collection;
        collection.create("cpu_time");
        collection.create("path_cost");
        collection.create("path_length");
        collection.create("branching_factor");
        collection.create("nodes_expanded");
        collection.create("nodes_visited");
        return collection;
    }
    
    template<class MARKER, class CLOSED>
    const AStarNode* AStar<MARKER, CLOSED>::findNode(int nodeId)
    {
        const AStarNode* result = 0;
        result = m_open.search(nodeId);
        if (result != 0)
            return result;
        result = m_closed.search(nodeId);
        return result;
    }

    template<class MARKER, class CLOSED>
    bool AStar<MARKER, CLOSED>::findPath(const Environment& env, int start,
                                         int target)
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
        m_visitedNodes.resize(env.getNumberNodes());
        fill(m_visitedNodes.begin(), m_visitedNodes.end(), ' ');
        findPathAStar(start);
        double timeDiff =
            static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
        m_statistics.get("cpu_time").add(timeDiff);
        m_statistics.get("nodes_expanded").add(m_nodesExpanded);
        m_statistics.get("nodes_visited").add(m_nodesVisited);
        m_statistics.get("path_length").add(m_path.size());
        return true;
    }

    template<class MARKER, class CLOSED>
    void AStar<MARKER, CLOSED>::findPathAStar(int start)
    {
        int numberNodes = m_env->getNumberNodes();
        m_closed.init(numberNodes);
        m_open.init(numberNodes);
        int heuristic = m_env->getHeuristic(start, m_target);
        m_pathCost = -1;
        AStarNode startNode(start, NO_NODE, 0, heuristic);
        m_open.insert(startNode);
        vector<Environment::Successor> successors;
        while (! m_open.isEmpty())
        {
            //m_open.print(cout);
            AStarNode node = getBestNodeFromOpen();
            //cout << '[';  node.print(cout); cout << ']' << endl;
            if (node.m_nodeId == m_target)
            {
                finishSearch(start, node);
                return;
            }
            ++m_nodesExpanded;
            m_env->getSuccessors(node.m_nodeId, NO_NODE, successors);
            m_branchingFactor.add(successors.size());
            int cont=1;
            int leng=successors.size();
            cilk_for (int k=0; k<leng; ++k)
            {
                
                int newg = node.m_g + successors[k].m_cost;
                int target = successors[k].m_target;
                const AStarNode* targetAStarNode = findNode(target);
                if (targetAStarNode != 0)
                {
                    if (newg >= targetAStarNode->m_g)
                        cont=0;
                    if (! m_open.remove(target) && cont==1)
                        m_closed.remove(target);
                }
                if(cont==1){
                int newHeuristic = m_env->getHeuristic(target, m_target);
                AStarNode newAStarNode(target, node.m_nodeId, newg,
                                       newHeuristic);
                m_open.insert(newAStarNode);
                }
            }
            m_closed.add(node);
            //closed.print(cout);
        }
    }

    template<class MARKER, class CLOSED>
    void AStar<MARKER, CLOSED>::finishSearch(int start, const AStarNode& node)
    {
        m_closed.add(node);
        m_path = m_closed.constructPath(start, m_target);
        m_pathCost = node.m_f;
        m_statistics.get("path_cost").add(m_pathCost);
    }
    
    template<class MARKER, class CLOSED>
    AStarNode AStar<MARKER, CLOSED>::getBestNodeFromOpen()
    {
        assert(! m_open.isEmpty());
        AStarNode result = m_open.pop();
        int nodeId = result.m_nodeId;
        assert(nodeId >= 0);
        ++m_nodesVisited;
        m_visitedNodes[nodeId] = '+';
        return result;
    }
    
    template<class MARKER, class CLOSED>
    const StatisticsCollection& AStar<MARKER, CLOSED>::getStatistics() const
    {
        return m_statistics;
    }
    
    template<class MARKER>
    AStarClosedLookup<MARKER>::AStarClosedLookup()
    {
        m_maxNodeId = 0;
        init(0);
    }
    
    template<class MARKER>
    void AStarClosedLookup<MARKER>::add(const AStarNode& node)
    {
        int nodeId = node.m_nodeId;
        assert(nodeId >= 0);
        assert(nodeId < m_maxNodeId);
        assert(m_marker.get(nodeId) == false);
        m_marker.set(nodeId);
        m_nodes[nodeId] = node;
    }
    
    template<class MARKER>
    vector<int> AStarClosedLookup<MARKER>::constructPath(int start, int target)
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

    template<class MARKER>
    void AStarClosedLookup<MARKER>::init(int maxNodeId)
    {
        assert(maxNodeId >= 0);
        m_nodes.resize(maxNodeId);
        m_marker.init(maxNodeId);
        m_maxNodeId = maxNodeId;
    }
    
    template<class MARKER>
    void AStarClosedLookup<MARKER>::remove(int nodeId)
    {
        assert(nodeId >= 0);
        assert(nodeId < m_maxNodeId);
        assert(m_marker.get(nodeId) == true);
        m_marker.unset(nodeId);
    }
    
    template<class MARKER>
    const AStarNode* AStarClosedLookup<MARKER>::search(int nodeId) const
    {
        assert(nodeId >= 0);
        assert(nodeId < m_maxNodeId);
        if (! m_marker.get(nodeId))
            return 0;
        const AStarNode* result = &m_nodes[nodeId];
        return result;
    }
    
    template<class MARKER>
    AStarOpen<MARKER>::AStarOpen()
    {
        init(0);
    }
    
    template<class MARKER>
    void AStarOpen<MARKER>::init(int numberNodes)
    {
        m_marker.init(numberNodes);
        m_lookupTable.resize(numberNodes);
        m_numberNodes = numberNodes;
        m_nodes.clear();
    }

    template<class MARKER>
    void AStarOpen<MARKER>::insert(const AStarNode& node)
    {
        int nodeId = node.m_nodeId;
        assert(nodeId < m_numberNodes);
        assert(m_marker.get(nodeId) == false);
        m_marker.set(nodeId);
        NodeSetIterator pos = m_nodes.insert(node);
        m_lookupTable[nodeId] = pos;
    }

    template<class MARKER>
    AStarNode AStarOpen<MARKER>::pop()
    {
        assert(! isEmpty());
        AStarNode result = *(m_nodes.begin());
        m_nodes.erase(m_nodes.begin());
        int nodeId = result.m_nodeId;
        assert(nodeId < m_numberNodes);
        assert(m_marker.get(nodeId) == true);
        m_marker.unset(nodeId);
        return result;
    }

    template<class MARKER>
    void AStarOpen<MARKER>::print(ostream& ostrm) const
    {
        ostrm << "Open {\n"; 
        for (NodeSetConstIterator i = m_nodes.begin(); i != m_nodes.end(); ++i)
        {
            i->print(ostrm);
            ostrm << '\n';
        }   
        ostrm << "}\n";
    }

    template<class MARKER>
    bool AStarOpen<MARKER>::remove(int nodeId)
    {
        assert(nodeId >= 0);
        assert(nodeId < m_numberNodes);
        if (! m_marker.get(nodeId))
            return false;
        NodeSetIterator pos = m_lookupTable[nodeId];
        m_nodes.erase(pos);
        m_marker.unset(nodeId);
        return true;
    }

    template<class MARKER>
    const AStarNode* AStarOpen<MARKER>::search(int nodeId) const
    {
        assert(nodeId >= 0);
        assert(nodeId < m_numberNodes);
        if (m_marker.get(nodeId))
            return &(*m_lookupTable[nodeId]);
        return 0;
    }

} // namespace PathFind

//-----------------------------------------------------------------------------

#endif
