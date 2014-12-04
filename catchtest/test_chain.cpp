#include "helpers.hpp"
#include <chain.hpp>

#include <vector>
#include <list>
#include <string>
#include <vector>
#include <iterator>
#include <utility>

#include "catch.hpp"

using iter::chain;
using itertest::SolidInt;
using Vec = const std::vector<char>;

TEST_CASE("chain three strings", "[chain]") {
    std::string s1{"abc"};
    std::string s2{"mno"};
    std::string s3{"xyz"};
    auto ch = chain(s1, s2, s3);

    Vec v(std::begin(ch), std::end(ch));
    Vec vc{'a','b','c','m','n','o','x','y','z'};

    REQUIRE( v == vc );
}

TEST_CASE("chain with different container types", "[chain]") {
    std::string s1{"abc"};
    std::list<char> li{'m', 'n', 'o'};
    std::vector<char> vec{'x', 'y', 'z'};
    auto ch = chain(s1, li, vec);

    Vec v(std::begin(ch), std::end(ch));
    Vec vc{'a','b','c','m','n','o','x','y','z'};

    REQUIRE( v == vc );
}

TEST_CASE("chain handles empty containers", "[chain]") {
    std::string emp;
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    Vec vc{'a', 'b', 'c'};

    SECTION("Empty container at front") {
        auto ch = chain(emp, a, b, c);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }

    SECTION("Empty container at back") {
        auto ch = chain(a, b, c, emp);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }

    SECTION("Empty container in middle") {
        auto ch = chain(a, emp, b, emp, c);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }

    SECTION("Consecutive empty containers at front") {
        auto ch = chain(emp, emp, a, b, c);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }

    SECTION("Consecutive empty containers at back") {
        auto ch = chain(a, b, c, emp, emp);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }

    SECTION("Consecutive empty containers in middle") {
        auto ch = chain(a, emp, emp, b, emp, emp, c);
        Vec v(std::begin(ch), std::end(ch));

        REQUIRE( v == vc );
    }
}

TEST_CASE("chain with only empty containers", "[chain]") {
    std::string emp{};
    SECTION("one empty container") {
        auto ch = chain(emp);
        REQUIRE_FALSE( std::begin(ch) != std::end(ch) );
    }

    SECTION("two empty containers") {
        auto ch = chain(emp, emp);
        REQUIRE_FALSE( std::begin(ch) != std::end(ch) );
    }

    SECTION("three empty containers") {
        auto ch = chain(emp, emp, emp);
        REQUIRE_FALSE( std::begin(ch) != std::end(ch) );
    }
}

TEST_CASE("Chain doesn't move or copy elements of iterable", "[chain]") {
    constexpr SolidInt arr[] = {{6}, {7}, {8}};
    for (auto&& i : chain(arr, arr)) {
        (void)i;
    }
}
