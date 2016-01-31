//-----------------------------------------------------------------------------
/** @file example.cpp
    Example program using the pathfinding library.

    $Id: example.cpp,v 1.32 2003/07/25 17:43:23 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/example.cpp,v $
*/
//-----------------------------------------------------------------------------

#include <memory>
#include "pathfind.h"

using namespace std;
using namespace PathFind;

//-----------------------------------------------------------------------------

static const int s_numberRuns = 100;
static const int s_columns = 50;
static const int s_rows = 50;
static const float s_obstaclePercentage = 0.2;
static const long long int s_nodesLimit = 100000000L;

//-----------------------------------------------------------------------------

typedef enum {A_STAR, IDA_STAR, FRINGE} SearchAlgorithm;

//-----------------------------------------------------------------------------

void printHeader(SearchAlgorithm searchAlgorithm, Tiling::Type type)
{
    cout << "==============================================================\n";
    switch (searchAlgorithm)
    {
    case A_STAR:
        cout << "A_STAR";
        break;
    case IDA_STAR:
        cout << "IDA_STAR";
        break;
    case FRINGE:
        cout << "FRINGE";
        break;
    }
    cout << "  ";
    switch (type)
    {
    case Tiling::TILE:
        cout << "TILE";
        break;
    case Tiling::OCTILE:
        cout << "OCTILE";
        break;
    case Tiling::OCTILE_UNICOST:
        cout << "OCTILE_UNICOST";
        break;
    case Tiling::HEX:
        cout << "HEX";
        break;
    }
    cout << '\n';
    cout << "==============================================================\n";
}

void runExperiment(SearchAlgorithm searchAlgorithm, Tiling::Type type)
{
    printHeader(searchAlgorithm, type);
    auto_ptr<Search> search;
    switch (searchAlgorithm)
    {
    case A_STAR:
        search.reset(new AStar<>());
        break;
    case IDA_STAR:
        search.reset(new IDAStar(IDAStar::f_CACHING));
        break;
    case FRINGE:
        search.reset(new FringeSearch<>());
        break;
    }
    search->setNodesLimit(s_nodesLimit);
    SearchUtils searchUtils;
    StatisticsCollection statistics = search->createStatistics();
    for (int runIndex = 0; runIndex < s_numberRuns; ++runIndex)
    {
        // Create a tiling search environment
        Tiling tiling(type, s_rows, s_columns);
        tiling.setObstacles(s_obstaclePercentage, false);
        
        // Choose random start and target
        int start, target;
        searchUtils.findRandomStartTarget(tiling, start, target);
       // cout << "Run " << runIndex << ":\n";
        //cout<< "start, target: "<<start<<","<<target<<endl;
       // tiling.printFormatted(cout, start, target);
       // cout << '\n';
        
        // Do the search
        search->findPath(tiling, start, target);
        //cout << '\n';
        //const vector<int>& path = search->getPath();
        //tiling.printFormatted(cout, path);
        //cout << '\n';
        //tiling.printPathAndLabels(cout, path, search->getVisitedNodes());
        //cout << '\n';
        
        // Accumulate statistics
        const StatisticsCollection& searchStatistics = search->getStatistics();
        //searchStatistics.print(cout);
        //cout << '\n';
        statistics.add(searchStatistics);
        //statistics.print(cout);
        //cout << '\n';
    }
    statistics.print(cout);
}

int main()
{
    try
    {
        //srand(time(0));        
        runExperiment(A_STAR, Tiling::TILE);
        //runExperiment(A_STAR, Tiling::OCTILE);
        //runExperiment(A_STAR, Tiling::OCTILE_UNICOST);
        //runExperiment(A_STAR, Tiling::HEX);
        runExperiment(IDA_STAR, Tiling::TILE);
        //runExperiment(IDA_STAR, Tiling::OCTILE);
        //runExperiment(IDA_STAR, Tiling::OCTILE_UNICOST);
        //runExperiment(IDA_STAR, Tiling::HEX);
        runExperiment(FRINGE, Tiling::TILE);
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << '\n';
        return -1;
    }
    return 0;
}

//-----------------------------------------------------------------------------
