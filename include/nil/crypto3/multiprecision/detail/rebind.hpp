///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

namespace nil {
    namespace crypto3 {
        namespace multiprecision {
            namespace backends {
                namespace detail {
                    template<class value_type, class my_allocator>
                    struct rebind {
                        using type = typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type>;
                    };
                }    // namespace detail
            }        // namespace backends
        }            // namespace multiprecision
    }                // namespace crypto3
}    // namespace nil
