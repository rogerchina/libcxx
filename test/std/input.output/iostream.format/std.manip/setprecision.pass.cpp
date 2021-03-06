//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <iomanip>

// T5 setprecision(int n);

#include <iomanip>
#include <cassert>

template <class CharT>
struct testbuf
    : public std::basic_streambuf<CharT>
{
    testbuf() {}
};

int main()
{
    {
        testbuf<char> sb;
        std::istream is(&sb);
        is >> std::setprecision(10);
        assert(is.precision() == 10);
    }
    {
        testbuf<char> sb;
        std::ostream os(&sb);
        os << std::setprecision(10);
        assert(os.precision() == 10);
    }
    {
        testbuf<wchar_t> sb;
        std::wistream is(&sb);
        is >> std::setprecision(10);
        assert(is.precision() == 10);
    }
    {
        testbuf<wchar_t> sb;
        std::wostream os(&sb);
        os << std::setprecision(10);
        assert(os.precision() == 10);
    }
}
