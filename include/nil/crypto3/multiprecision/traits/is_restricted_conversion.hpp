///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <nil/crypto3/multiprecision/traits/explicit_conversion.hpp>
#include <nil/crypto3/multiprecision/detail/number_base.hpp>

namespace nil {
    namespace crypto3 {
        namespace multiprecision {
            namespace detail {

                template<class From, class To>
                struct is_lossy_conversion {
                    using type = typename std::conditional<
                        ((number_category<From>::value == number_kind_floating_point) &&
                         (number_category<To>::value == number_kind_integer))
                            /* || ((number_category<From>::value == number_kind_floating_point) &&
                               (number_category<To>::value == number_kind_rational))*/
                            || ((number_category<From>::value == number_kind_rational) &&
                                (number_category<To>::value == number_kind_integer)) ||
                            ((number_category<From>::value == number_kind_fixed_point) &&
                             (number_category<To>::value == number_kind_integer)) ||
                            (number_category<From>::value == number_kind_unknown) ||
                            (number_category<To>::value == number_kind_unknown),
                        std::integral_constant<bool, true>, std::integral_constant<bool, false>>::type;
                    static constexpr const bool value = type::value;
                };

                template<typename From, typename To>
                struct is_restricted_conversion {
                    using type = typename std::conditional<
                        ((is_explicitly_convertible<From, To>::value && !std::is_convertible<From, To>::value) ||
                         is_lossy_conversion<From, To>::value),
                        std::integral_constant<bool, true>, std::integral_constant<bool, false>>::type;
                    static constexpr const bool value = type::value;
                };

            }    // namespace detail
        }        // namespace multiprecision
    }            // namespace crypto3
}    // namespace nil
