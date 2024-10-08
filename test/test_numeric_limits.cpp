///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#endif

#include "test.hpp"

#if !defined(TEST_MPF_50) && !defined(TEST_MPF) && !defined(TEST_BACKEND) && !defined(TEST_MPZ) &&           \
    !defined(TEST_CPP_DEC_FLOAT) && !defined(TEST_MPFR) && !defined(TEST_MPFR_50) && !defined(TEST_MPQ) &&   \
    !defined(TEST_TOMMATH) && !defined(TEST_CPP_INT) && !defined(TEST_MPFI_50) && !defined(TEST_FLOAT128) && \
    !defined(TEST_CPP_BIN_FLOAT)
#define TEST_MPF_50
#define TEST_MPF
#define TEST_BACKEND
#define TEST_MPZ
#define TEST_MPFR
#define TEST_MPFR_50
#define TEST_CPP_DEC_FLOAT
#define TEST_MPQ
#define TEST_TOMMATH
#define TEST_CPP_INT
#define TEST_MPFI_50
#define TEST_FLOAT128
#define TEST_CPP_BIN_FLOAT

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_MPF_50) || defined(TEST_MPF) || defined(TEST_MPZ) || defined(TEST_MPQ)
#include <nil/crypto3/multiprecision/gmp.hpp>
#endif
#ifdef TEST_BACKEND
#include <nil/crypto3/multiprecision/concepts/mp_number_archetypes.hpp>
#endif
#ifdef TEST_CPP_DEC_FLOAT
#include <nil/crypto3/multiprecision/cpp_dec_float.hpp>
#endif
#if defined(TEST_MPFR) || defined(TEST_MPFR_50)
#include <nil/crypto3/multiprecision/mpfr.hpp>
#endif
#if defined(TEST_MPFI_50)
#include <nil/crypto3/multiprecision/mpfi.hpp>
#endif
#ifdef TEST_TOMMATH
#include <nil/crypto3/multiprecision/tommath.hpp>
#endif
#ifdef TEST_CPP_INT
#include <nil/crypto3/multiprecision/cpp_int.hpp>
#endif
#ifdef TEST_FLOAT128
#include <nil/crypto3/multiprecision/float128.hpp>
#endif
#ifdef TEST_CPP_BIN_FLOAT
#include <nil/crypto3/multiprecision/cpp_bin_float.hpp>
#endif

#ifdef BOOST_MSVC
#pragma warning(disable : 4127)
#endif

#define PRINT(x) std::cout << BOOST_STRINGIZE(x) << " = " << std::numeric_limits<Number>::x << std::endl;

template<class Number>
void test_specific(const std::integral_constant<int, nil::crypto3::multiprecision::number_kind_floating_point>&) {
    Number minv, maxv;
    minv = (std::numeric_limits<Number>::min)();
    maxv = (std::numeric_limits<Number>::max)();
    BOOST_CHECK((boost::math::isnormal)(minv));
    BOOST_CHECK((boost::math::isnormal)(maxv));
    BOOST_CHECK((boost::math::isnormal)(log(minv)));
    BOOST_CHECK((boost::math::isnormal)(log(maxv)));
    BOOST_CHECK((boost::math::isnormal)(sqrt(minv)));
    BOOST_CHECK((boost::math::isnormal)(sqrt(maxv)));

    if (std::numeric_limits<Number>::is_specialized) {
        if (std::numeric_limits<Number>::has_quiet_NaN) {
            BOOST_TEST((boost::math::isnan)(std::numeric_limits<Number>::quiet_NaN()));
            BOOST_TEST(FP_NAN == (boost::math::fpclassify)(std::numeric_limits<Number>::quiet_NaN()));
            BOOST_TEST(!(boost::math::isfinite)(std::numeric_limits<Number>::quiet_NaN()));
            BOOST_TEST(!(boost::math::isnormal)(std::numeric_limits<Number>::quiet_NaN()));
            BOOST_TEST(!(boost::math::isinf)(std::numeric_limits<Number>::quiet_NaN()));
        }
        if (std::numeric_limits<Number>::has_signaling_NaN) {
            BOOST_TEST((boost::math::isnan)(std::numeric_limits<Number>::signaling_NaN()));
            BOOST_TEST(FP_NAN == (boost::math::fpclassify)(std::numeric_limits<Number>::signaling_NaN()));
            BOOST_TEST(!(boost::math::isfinite)(std::numeric_limits<Number>::signaling_NaN()));
            BOOST_TEST(!(boost::math::isnormal)(std::numeric_limits<Number>::signaling_NaN()));
            BOOST_TEST(!(boost::math::isinf)(std::numeric_limits<Number>::signaling_NaN()));
        }
        if (std::numeric_limits<Number>::has_infinity) {
            BOOST_TEST((boost::math::isinf)(std::numeric_limits<Number>::infinity()));
            BOOST_TEST(FP_INFINITE == (boost::math::fpclassify)(std::numeric_limits<Number>::infinity()));
            BOOST_TEST(!(boost::math::isfinite)(std::numeric_limits<Number>::infinity()));
            BOOST_TEST(!(boost::math::isnormal)(std::numeric_limits<Number>::infinity()));
            BOOST_TEST(!(boost::math::isnan)(std::numeric_limits<Number>::infinity()));
        }
        if (std::numeric_limits<Number>::has_denorm == std::denorm_present) {
            BOOST_TEST(FP_SUBNORMAL == (boost::math::fpclassify)(std::numeric_limits<Number>::denorm_min()));
            BOOST_TEST(FP_SUBNORMAL == (boost::math::fpclassify)((std::numeric_limits<Number>::min)() / 2));
            BOOST_TEST((boost::math::isfinite)(std::numeric_limits<Number>::denorm_min()));
            BOOST_TEST(!(boost::math::isnormal)(std::numeric_limits<Number>::denorm_min()));
            BOOST_TEST(!(boost::math::isinf)(std::numeric_limits<Number>::denorm_min()));
            BOOST_TEST(!(boost::math::isnan)(std::numeric_limits<Number>::denorm_min()));
            BOOST_TEST(0 == std::numeric_limits<Number>::denorm_min() / 2);
            BOOST_TEST(0 != (std::numeric_limits<Number>::min)() / 2);
            BOOST_TEST(0 != std::numeric_limits<Number>::denorm_min());
        }
    }
    Number n = 0;
    BOOST_TEST((boost::math::fpclassify)(n) == FP_ZERO);
    BOOST_TEST((boost::math::isfinite)(n));
    BOOST_TEST(!(boost::math::isnormal)(n));
    BOOST_TEST(!(boost::math::isinf)(n));
    BOOST_TEST(!(boost::math::isnan)(n));
    n = 2;
    BOOST_TEST((boost::math::fpclassify)(n) == FP_NORMAL);
    BOOST_TEST((boost::math::isfinite)(n));
    BOOST_TEST((boost::math::isnormal)(n));
    BOOST_TEST(!(boost::math::isinf)(n));
    BOOST_TEST(!(boost::math::isnan)(n));

    if (std::numeric_limits<Number>::round_style == std::round_to_nearest) {
        BOOST_CHECK_EQUAL(std::numeric_limits<Number>::round_error(), 0.5);
    } else if (std::numeric_limits<Number>::round_style != std::round_indeterminate) {
        // Round error is 1.0:
        BOOST_CHECK_EQUAL(std::numeric_limits<Number>::round_error(), 1);
    } else {
        // Round error is presumably somewhere between 0.5 and 1:
        BOOST_CHECK((std::numeric_limits<Number>::round_error() <= 1) &&
                    (std::numeric_limits<Number>::round_error() >= 0.5));
    }
}

template<class Number>
void test_specific(const std::integral_constant<int, nil::crypto3::multiprecision::number_kind_integer>&) {
    if (std::numeric_limits<Number>::is_modulo) {
        if (!std::numeric_limits<Number>::is_signed) {
            BOOST_TEST(1 + (std::numeric_limits<Number>::max)() == 0);
            BOOST_TEST(--Number(0) == (std::numeric_limits<Number>::max)());
        }
    }
}

template<class Number, class T>
void test_specific(const T&) {
}

template<class Number>
void test() {
    typedef typename std::conditional<std::numeric_limits<Number>::is_specialized,
                                      typename nil::crypto3::multiprecision::number_category<Number>::type,
                                      std::integral_constant<int, 500>    // not a number type
                                      >::type fp_test_type;

    test_specific<Number>(fp_test_type());

    //
    // Note really a test just yet, but we can at least print out all the values:
    //
    std::cout << "numeric_limits values for type " << typeid(Number).name() << std::endl;

    PRINT(is_specialized);
    if (std::numeric_limits<Number>::is_integer) {
        std::cout << std::hex << std::showbase;
    }
    std::cout << "max()"
              << " = " << (std::numeric_limits<Number>::max)() << std::endl;
    if (std::numeric_limits<Number>::is_integer) {
        std::cout << std::dec;
    }
    std::cout << "max()"
              << " = " << (std::numeric_limits<Number>::max)() << std::endl;
    std::cout << "min()"
              << " = " << (std::numeric_limits<Number>::min)() << std::endl;
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS
    PRINT(lowest());
#endif
    PRINT(digits);
    PRINT(digits10);
#if !defined(BOOST_NO_CXX11_NUMERIC_LIMITS) || defined(PRINT_MAX_DIGITS10)
    PRINT(max_digits10);
#endif
    PRINT(is_signed);
    PRINT(is_integer);
    PRINT(is_exact);
    PRINT(radix);
    PRINT(epsilon());
    PRINT(round_error());
    PRINT(min_exponent);
    PRINT(min_exponent10);
    PRINT(max_exponent);
    PRINT(max_exponent10);
    PRINT(has_infinity);
    PRINT(has_quiet_NaN);
    PRINT(has_signaling_NaN);
    PRINT(has_denorm);
    PRINT(has_denorm_loss);
    PRINT(infinity());
    PRINT(quiet_NaN());
    PRINT(signaling_NaN());
    PRINT(denorm_min());
    PRINT(is_iec559);
    PRINT(is_bounded);
    PRINT(is_modulo);
    PRINT(traps);
    PRINT(tinyness_before);
    PRINT(round_style);
}

int main() {
#ifdef TEST_BACKEND
    test<
        nil::crypto3::multiprecision::number<nil::crypto3::multiprecision::concepts::number_backend_float_architype>>();
#endif
#ifdef TEST_MPF_50
    test<nil::crypto3::multiprecision::mpf_float_50>();
#endif
#ifdef TEST_MPF
    nil::crypto3::multiprecision::mpf_float::default_precision(1000);
    /*
    nil::crypto3::multiprecision::mpf_float r;
    r.precision(50);
    BOOST_TEST(r.precision() >= 50);
    */
    BOOST_TEST(nil::crypto3::multiprecision::mpf_float::default_precision() == 1000);
    test<nil::crypto3::multiprecision::mpf_float>();
#endif
#ifdef TEST_MPZ
    test<nil::crypto3::multiprecision::mpz_int>();
#endif
#ifdef TEST_MPQ
    test<nil::crypto3::multiprecision::mpq_rational>();
#endif
#ifdef TEST_CPP_DEC_FLOAT
    test<nil::crypto3::multiprecision::cpp_dec_float_50>();
    test<nil::crypto3::multiprecision::cpp_dec_float_100>();
#endif
#ifdef TEST_MPFR
    test<nil::crypto3::multiprecision::mpfr_float>();
#endif
#ifdef TEST_MPFR_50
    test<nil::crypto3::multiprecision::mpfr_float_50>();
#endif
#ifdef TEST_MPFI_50
    test<nil::crypto3::multiprecision::mpfi_float_50>();
    test<nil::crypto3::multiprecision::mpfi_float>();
#endif
#ifdef TEST_TOMMATH
    test<nil::crypto3::multiprecision::tom_int>();
#endif
#ifdef TEST_CPP_INT
    test<nil::crypto3::multiprecision::cpp_int>();
    test<nil::crypto3::multiprecision::int256_t>();
    test<nil::crypto3::multiprecision::uint512_t>();
    test<nil::crypto3::multiprecision::number<nil::crypto3::multiprecision::cpp_int_backend<
        200, 200, nil::crypto3::multiprecision::unsigned_magnitude, nil::crypto3::multiprecision::checked, void>>>();
    test<nil::crypto3::multiprecision::number<nil::crypto3::multiprecision::cpp_int_backend<
        70, 70, nil::crypto3::multiprecision::signed_magnitude, nil::crypto3::multiprecision::unchecked, void>>>();
#endif
#ifdef TEST_FLOAT128
    test<nil::crypto3::multiprecision::float128>();
#endif
#ifdef TEST_CPP_BIN_FLOAT
    test<nil::crypto3::multiprecision::cpp_bin_float_50>();
#endif
    return boost::report_errors();
}
