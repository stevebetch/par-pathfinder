//-----------------------------------------------------------------------------
/** @file util.h
    General utilities.

    $Id: util.h,v 1.7 2003/06/27 17:55:36 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/util.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_UTIL_H
#define PATHFIND_UTIL_H

#include <iostream>
#include <string>
#include "error.h"
#include "math.h"

//-----------------------------------------------------------------------------

namespace PathFind
{
    /** Exception thrown by LineReader. */
    class ReadError
        : public Error
    {
    public:
        ReadError(int line, const string& info);
    };

    /** Wrapper class around std::istream for reading line by line.
        Allows keeping track of the line number for generating meaningful
        error messages.
    */
    class LineReader
    {
    public:
        static const int MAX_LINE = 2048;

        LineReader(std::istream& in);

        /** Creates a new error with a message and the current line number */
        Error createError(const string& message);

        int getLineNumber()
        {
            return m_lineNumber;
        }

        /** Read next line.
            @exception ReadError Reading failed.
        */
        std::string readLine();

    private:
        int m_lineNumber;

        std::istream& m_in;
    };

    /** Get a label useful for implementations of Search::getVisitedNodes.
        The char label is built with the iteration number and uses
        '0'-'9', 'a'-'z' if the iteration number is less than 37,
        '+' otherwise.
     */
    char getVisitedNodeLabel(int iteration);
}

//-----------------------------------------------------------------------------

#endif
