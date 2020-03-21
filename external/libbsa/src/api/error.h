/*  libbsa

    A library for reading and writing BSA files.

    Copyright (C) 2012-2013    WrinklyNinja

    This file is part of libbsa.

    libbsa is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    libbsa is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libbsa.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef __LIBBSA_ERROR_H__
#define __LIBBSA_ERROR_H__

#include <exception>
#include <string>

namespace libbsa {
    class error : public std::exception {
    public:
        error(const unsigned int code, const std::string& what) : _code(code), _what(what) {}
        ~error() throw() {};

        unsigned int code() const { return _code; }
        const char * what() const throw() { return _what.c_str(); }
    private:
        std::string _what;
        unsigned int _code;
    };
}

#endif
