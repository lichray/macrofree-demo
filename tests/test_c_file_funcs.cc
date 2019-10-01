#include <doctest/doctest.h>

#include <macrofree_demo/c_file_funcs.h>

#include <memory>
#include <stdio.h>

using namespace macrofree_demo;

TEST_CASE("unique_ptr")
{
    char fn[] = "testcase-unique_ptr-tmp.txt";
    using c_file_ptr = std::unique_ptr<FILE, c_file_deleter>;

    WHEN("a file is created")
    {
        auto fp = c_file_ptr(xfopen(fn, "w"));
        fp.reset();

        THEN("we can open the file")
        {
            REQUIRE_NOTHROW(c_file_ptr(xfopen(fn, "r")));
        }

        ::remove(fn);
    }

    WHEN("the file is not created")
    {
        THEN("we cannot open the file")
        {
            REQUIRE_THROWS_AS(c_file_ptr(xfopen(fn, "r")), std::system_error);
        }
    }
}
