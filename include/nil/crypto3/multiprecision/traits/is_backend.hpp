///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <nil/crypto3/multiprecision/detail/number_base.hpp>

namespace nil {
    namespace crypto3 {
        namespace multiprecision {
            namespace detail {

                template<class T>
                struct has_signed_types {
                    template<class U>
                    static double check(U*, typename U::signed_types* = 0);
                    static char check(...);
                    static T* get();
                    static constexpr bool value = sizeof(check(get())) == sizeof(double);
                };
                template<class T>
                struct has_unsigned_types {
                    template<class U>
                    static double check(U*, typename U::unsigned_types* = 0);
                    static char check(...);
                    static T* get();
                    static constexpr bool value = sizeof(check(get())) == sizeof(double);
                };
                template<class T>
                struct has_float_types {
                    template<class U>
                    static double check(U*, typename U::float_types* = 0);
                    static char check(...);
                    static T* get();
                    static constexpr bool value = sizeof(check(get())) == sizeof(double);
                };

                template<class T>
                struct is_backend {
                    static constexpr const bool value =
                        has_signed_types<T>::value && has_unsigned_types<T>::value && has_float_types<T>::value;
                };

                template<class Backend>
                struct other_backend {
                    using type = typename std::conditional<std::is_same<number<Backend>, number<Backend, et_on>>::value,
                                                           number<Backend, et_off>, number<Backend, et_on>>::type;
                };

                template<class B, class V>
                struct number_from_backend {
                    using type = typename std::conditional<std::is_convertible<V, number<B>>::value, number<B>,
                                                           typename other_backend<B>::type>::type;
                };

                template<bool b, class T, class U>
                struct is_first_backend_imp {
                    static constexpr const bool value = false;
                };
                template<class T, class U>
                struct is_first_backend_imp<true, T, U> {
                    static constexpr const bool value = std::is_convertible<U, number<T, et_on>>::value ||
                                                        std::is_convertible<U, number<T, et_off>>::value;
                };

                template<class T, class U>
                struct is_first_backend : is_first_backend_imp<is_backend<T>::value, T, U> { };

                template<bool b, class T, class U>
                struct is_second_backend_imp {
                    static constexpr const bool value = false;
                };
                template<class T, class U>
                struct is_second_backend_imp<true, T, U> {
                    static constexpr const bool value = (std::is_convertible<T, number<U, et_on>>::value ||
                                                         std::is_convertible<T, number<U, et_off>>::value) &&
                                                        !is_first_backend<T, U>::value;
                };

                template<class T, class U>
                struct is_second_backend : is_second_backend_imp<is_backend<U>::value, T, U> { };

            }    // namespace detail
        }        // namespace multiprecision
    }            // namespace crypto3
}    // namespace nil
