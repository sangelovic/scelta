// Copyright (c) 2017 Vittorio Romeo
// MIT License |  https://opensource.org/licenses/MIT
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include "../test_utils.hpp"
#include <scelta/meta/replace_all.hpp>

struct A
{
};

struct B
{
};

template <typename...>
struct bag
{
};

TEST_MAIN()
{
    using namespace scelta::meta;

    // Sanity checks.
    SA_SAME((A), (A));
    SA_SAME((B), (B));
    SA_SAME((bag<>), (bag<>));

    SA_SAME((replace_all_t<A, B, bag<>>), (bag<>));
    SA_SAME((replace_all_t<A, B, bag<A>>), (bag<B>));
    SA_SAME((replace_all_t<A, B, bag<B>>), (bag<B>));

    SA_SAME((replace_all_t<A, B, bag<A, A>>), (bag<B, B>));
    SA_SAME((replace_all_t<A, B, bag<B, A>>), (bag<B, B>));

    SA_SAME((replace_all_t<A, B, bag<A, bag<A>>>), (bag<B, bag<B>>));
    SA_SAME((replace_all_t<A, B, bag<A, bag<A, bag<A>>>>),
        (bag<B, bag<B, bag<B>>>));

    SA_SAME((replace_all_t<A, B, bag<A, bag<A, A, bag<A, A>>>>),
        (bag<B, bag<B, B, bag<B, B>>>));

    // Pointers/refs/qualifiers are NOT implicitly replaced
    SA_NOT_SAME((replace_all_t<A, B, bag<A*>>), (bag<B*>));
    SA_NOT_SAME((replace_all_t<A, B, bag<A&>>), (bag<B&>));
    SA_NOT_SAME((replace_all_t<A, B, bag<const A>>), (bag<const B>));

    SA_SAME((replace_all_t<A*, B*, bag<A*>>), (bag<B*>));
    SA_SAME((replace_all_t<const A, const B, bag<const A>>), (bag<const B>));

    // Pointers/refs/qualifiers are implicitly replaced
    SA_SAME((replace_all_copy_cv_ptr_ref_t<A, B, bag<A*>>), (bag<B*>));
    SA_SAME((replace_all_copy_cv_ptr_ref_t<A, B, bag<A&>>), (bag<B&>));
    SA_SAME((replace_all_copy_cv_ptr_ref_t<A, B, bag<const A>>), (bag<const B>));
}
