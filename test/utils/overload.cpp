// Copyright (c) 2017 Vittorio Romeo
// MIT License |  https://opensource.org/licenses/MIT
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include "./test_utils.hpp"
#include <scelta/utils/overload.hpp>

TEST_MAIN()
{
    // nothing
    {
        auto f = scelta::overload();
        (void)f;
    }

    // lvalue_0
    {
        auto l = [](int x) { return x + 1; };
        auto f = scelta::overload(l);

        EXPECT_EQ(f(1), 2);
    }

    // lvalue_1
    {
        auto l0 = [](int x) { return x + 1; };
        auto l1 = [](char x) { return x; };
        auto f = scelta::overload(l0, l1);

        EXPECT_EQ(f(1), 2);
        EXPECT_EQ(f('a'), 'a');
    }

    // lvalue_makes_copy
    {
        auto l = [k = 0]() mutable
        {
            ++k;
            return k;
        };
        auto f = scelta::overload(l);

        EXPECT_EQ(f(), 1);
        EXPECT_EQ(f(), 2);
        EXPECT_EQ(f(), 3);

        EXPECT_EQ(l(), 1);
    }

    // rvalue_0
    {
        auto f = scelta::overload([](int x) { return x + 1; });

        EXPECT_EQ(f(1), 2);
    }

    // rvalue_1
    {
        auto f = scelta::overload(
            [](int x) { return x + 1; }, [](char x) { return x; });

        EXPECT_EQ(f(1), 2);
        EXPECT_EQ(f('a'), 'a');
    }

    // non-ref overload
    {
        auto l0([i = 0](float) mutable { return i++; });
        auto l1([i = 0](char) mutable { return i++; });

        auto f = scelta::overload(l0, l1);

        EXPECT_EQ(f(0.f), 0);
        EXPECT_EQ(f(0.f), 1);
        EXPECT_EQ(f(0.f), 2);
        EXPECT_EQ(f('a'), 0);
        EXPECT_EQ(f('a'), 1);
        EXPECT_EQ(f('a'), 2);

        EXPECT_EQ(l0(0.f), 0);
        EXPECT_EQ(l1('a'), 0);
    }

    {
        int a;
        int b;
        auto f = scelta::overload(         //
            [&](int) -> int& { return a; }, //
            [&](auto) -> int& { return b; });

        EXPECT_EQ(&f(0), &a);
        EXPECT_EQ(&f('a'), &b);
    }

    /*
    // ref overload
    {
        auto l0([i = 0](float) mutable { return i++; });
        auto l1([i = 0](char) mutable { return i++; });

        auto f = scelta::ref_overload(l0, l1);

        EXPECT_EQ(f(0.f), 0);
        EXPECT_EQ(f(0.f), 1);
        EXPECT_EQ(f(0.f), 2);
        EXPECT_EQ(f('a'), 0);
        EXPECT_EQ(f('a'), 1);
        EXPECT_EQ(f('a'), 2);

        EXPECT_EQ(l0(0.f), 3);
        EXPECT_EQ(l1('a'), 3);
    }
    */
}
