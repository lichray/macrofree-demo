#pragma once

#include <stdio.h>
#include <system_error>

namespace macrofree_demo
{

inline FILE* xfopen(char const* fn, char const* mode)
{
#if !defined(_WIN32)
    auto fp = ::fopen(fn, mode);
#else
    FILE* fp;
    fopen_s(&fp, fn, mode);
#endif
    if (fp == nullptr)
        throw std::system_error(errno, std::system_category());

    return fp;
}

struct c_file_deleter
{
    void operator()(FILE* fp) const { ::fclose(fp); }
};

}
