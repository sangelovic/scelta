// Copyright (c) 2017 Vittorio Romeo
// MIT License |  https://opensource.org/licenses/MIT
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

// clang-format off
// Usage of C++17: `__has_include`.
#if __has_include(<type_safe/optional.hpp>)
// clang-format on

#include "../../utils/optional_utils.hpp"
#include "../../utils/homogenizer.hpp"
#include "../../traits.hpp"
#include <type_safe/optional.hpp>

#define SCELTA_SUPPORT_OPTIONAL_TYPE_SAFE 1

namespace scelta::traits
{
    namespace adt
    {
        template <typename T>
        struct visit<::type_safe::basic_optional<T>> : impl::visit_optional_t
        {
        };
    }

    namespace optional
    {
        template <typename T>
        struct access<::type_safe::basic_optional<T>>
        {
            // clang-format off
            template <typename Optional>
            constexpr auto operator()(Optional&& o)
                SCELTA_RETURNS(
                    FWD(o).value()
                )
            // clang-format on
        };
    }
}

#endif