//-----------------------------------------------------------------------------
/** @file error.h
    Base exception class.

    $Id: error.h,v 1.4 2003/06/09 20:39:51 emarkus Exp $
    $Source: /usr/cvsroot/project_pathfind/error.h,v $
*/
//-----------------------------------------------------------------------------

#ifndef PATHFIND_ERROR_H
#define PATHFIND_ERROR_H

#include <exception>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

namespace PathFind
{
    using namespace std;

    /** Base class for exceptions. */
    class Error
        : public exception
    {
    public:
        Error()
        { }

        Error(const string& what)
            : m_message(what)
        { }

        ~Error() throw();
        
        void setMessage(const string& message)
        {
            m_message = message;
        }

        const char* what() const throw()
        {
            return m_message.c_str();
        }
        
    private:
        string m_message;
    };
}

//-----------------------------------------------------------------------------

#endif
