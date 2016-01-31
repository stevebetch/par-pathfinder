//-----------------------------------------------------------------------------
/** @file util.cpp
    @see util.h

    $Id: util.cpp,v 1.4 2003/06/27 17:55:36 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/util.cpp,v $
*/
//-----------------------------------------------------------------------------

#include "util.h"

#include <sstream>

using namespace std;
using namespace PathFind;

//-----------------------------------------------------------------------------

ReadError::ReadError(int line, const string& info)
{
    ostringstream s;
    s << "Read error line " << line << ": " << info << ends;
    setMessage(s.str());
}

//-----------------------------------------------------------------------------

LineReader::LineReader(istream& in)
    : m_lineNumber(0),
      m_in(in)
{
}

Error LineReader::createError(const string& message)
{
    ostringstream out;
    out << "Line " << m_lineNumber << ": " << message << ends;
    return Error(out.str());
}

std::string LineReader::readLine()
{
    char buffer[MAX_LINE];
    m_in.getline(buffer, MAX_LINE);
    if (! m_in)
        throw Error("Unexpected end of stream.");
    ++m_lineNumber;
    return string(buffer);
}

//-----------------------------------------------------------------------------

char PathFind::getVisitedNodeLabel(int iteration)
{
    char label;
    if (iteration < 10)
        label = ('0' + iteration);
    else if (iteration <= 36)
        label = ('a' + iteration - 10);
    else
        label = '+';
    return label;
}

//-----------------------------------------------------------------------------
