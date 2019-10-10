#pragma once

#include <macrofree_demo/build_config.h>
#include <macrofree_demo/sha256_openssl.h>

#include <type_traits>
#include <tuple>

namespace macrofree_demo
{

template<bool crypto, bool cng>
struct sha256_implementations_table
{
    using type = std::tuple<>;
};

template<bool cng>
struct sha256_implementations_table<true, cng>
{
    using type = std::tuple<sha256_openssl>;
};

using sha256_implementations =
    typename sha256_implementations_table<have_crypto, have_cng>::type;

}

// See also: doctest TYPE_TO_STRING

namespace doctest
{
namespace detail
{

template<class T>
char const* type_to_string();

template<>
constexpr char const* type_to_string<macrofree_demo::sha256_openssl>()
{
    return "<sha256_openssl>";
}

}
}
