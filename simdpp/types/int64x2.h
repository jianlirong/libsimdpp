/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X2_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64X2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 2x 64-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint64<2> : public int128 {
public:

    using element_type = uint64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64x2;
    using uint_vector_type = uint64x2;
    using mask_type = mask_int64x2;

    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    gint64<2>() = default;
    gint64<2>(const gint64x2 &) = default;
    gint64<2> &operator=(const gint64x2 &) = default;

    /// @{
    /// Construct from base type
    gint64<2>(const int128& d) : int128(d) {}
    gint64<2>& operator=(int128 d) { int_bits<16>::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    gint64<2>(__m128i d) : int128(d) {}
    gint64<2>& operator=(__m128i d) { int_bits<16>::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    gint64<2>(uint64x2_t d) : int128(d) {}
    gint64<2>( int64x2_t d) : int128(d) {}
    gint64<2>& operator=(uint64x2_t d) { int_bits<16>::operator=(d); return *this; }
    gint64<2>& operator=( int64x2_t d) { int_bits<16>::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    gint64<2>(__vector uint32_t d) : int128(d) {}
    gint64<2>(__vector  int32_t d) : int128(d) {}
    gint64<2>& operator=(__vector uint32_t d) { int_bits<16>::operator=(d); return *this; }
    gint64<2>& operator=(__vector  int32_t d) { int_bits<16>::operator=(d); return *this; }
#endif
    /// @}

     /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit gint64<2>(const float64x2& d);
    gint64<2>& operator=(const float64x2& d) { operator=(gint64x2(d)); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint64_t& operator[](unsigned i) const  { return u64(i); }
          uint64_t& operator[](unsigned i)        { return u64(i); }
#endif
#endif
};

/** Class representing 2x 64-bit signed integer vector
*/
template<>
class int64<2> : public gint64x2 {
public:

    using element_type = int64_t;

    int64<2>() = default;
    int64<2>(const int64x2 &) = default;
    int64<2> &operator=(const int64x2 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int64<2>(__m128i d) : gint64x2(d) {}
    int64<2>& operator=(__m128i d) { gint64x2::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int64<2>(int64x2_t d) : gint64x2(d) {}
    int64<2>& operator=(int64x2_t d) { gint64x2::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    int64<2>(__vector  int32_t d) : gint64x2(d) {}
    int64<2>& operator=(__vector  int32_t d) { gint64x2::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int64<2>(const int128& d) : gint64x2(d) {}
    int64<2>(gint64x2 d) : gint64x2(d) {}
    int64<2>& operator=(int128 d) { gint64x2::operator=(d); return *this; }
    int64<2>& operator=(gint64x2 d) { gint64x2::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit int64<2>(const float64x2& d) : gint64x2(d) {}
    int64<2>& operator=(const float64x2& d) { gint64x2::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int64_t& operator[](unsigned i) const  { return i64(i); }
          int64_t& operator[](unsigned i)        { return i64(i); }
#endif
#endif

    /** Creates a signed int64x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        @endcode
    */
    static int64x2 zero() { return int64x2::make_const(0); }

    /** Creates a signed int64x4 vector from a value loaded from memory.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static int64x2 load_broadcast(const int64_t* v0);

    /** Creates a signed int64x4 vector from a value stored in a core register.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int64x2 set_broadcast(int64_t v0);

    /** Creates a signed int64x4 vector from a value known at compile-time

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
    */
    static int64x2 make_const(int64_t v0);

    /** Creates a signed int64x4 vector from two values known at compile-time

        @code
            | 0  1  |
        r = [ v0 v1 ]
        @endcode
    */
    static int64x2 make_const(int64_t v0, int64_t v1);
};

/** Class representing 2x 64-bit unsigned integer vector
*/
template<>
class uint64<2> : public gint64x2 {
public:

    uint64<2>() = default;
    uint64<2>(const uint64x2 &) = default;
    uint64<2> &operator=(const uint64x2 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint64<2>(__m128i d) : gint64x2(d) {}
    uint64<2>& operator=(__m128i d) { gint64x2::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint64<2>(uint64x2_t d) : gint64x2(d) {}
    uint64<2>& operator=(uint64x2_t d) { gint64x2::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    uint64<2>(__vector uint32_t d) : gint64x2(d) {}
    uint64<2>& operator=(__vector uint32_t d) { gint64x2::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint64<2>(const int128& d) : gint64x2(d) {}
    uint64<2>(gint64x2 d) : gint64x2(d) {}
    uint64<2>& operator=(int128 d) { gint64x2::operator=(d); return *this; }
    uint64<2>& operator=(gint64x2 d) { gint64x2::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit uint64<2>(const float64x2& d) : gint64x2(d) {}
    uint64<2>& operator=(const float64x2& d) { gint64x2::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint64_t& operator[](unsigned i) const  { return u64(i); }
          uint64_t& operator[](unsigned i)        { return u64(i); }
#endif
#endif

    /** Creates an unsigned int64x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        @endcode
    */
    static uint64x2 zero() { return uint64x2::make_const(0); }

    /** Creates a int64x4 vector from a value loaded from memory.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static uint64x2 load_broadcast(const uint64_t* v0);

    /** Creates an unsigned int64x4 vector from a value stored in a core
        register.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint64x2 set_broadcast(uint64_t v0);

    /** Creates an unsigned int64x4 vector from a value known at compile-time

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
    */
    static uint64x2 make_const(uint64_t v0);

    /** Creates an unsigned int64x4 vector from two values known at
        compile-time

        @code
            | 0  1  |
        r = [ v0 v1 ]
        @endcode
    */
    static uint64x2 make_const(uint64_t v0, uint64_t v1);

};

/// Class representing mask for 2x 64-bit integer vector
template<>
class mask_int64<2> {
public:
    static constexpr unsigned length = 2;

    mask_int64<2>() = default;
    mask_int64<2>(const mask_int64x2 &) = default;
    mask_int64<2> &operator=(const mask_int64x2 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if SIMDPP_USE_SSE2
    mask_int64<2>(__m128i d) : d_(d) {}
#elif SIMDPP_USE_NEON
    mask_int64<2>(uint64x2_t d) : d_(d) {}
    mask_int64<2>( int64x2_t d) : d_(d) {}
#endif
#if SIMDPP_USE_NULL
#else
    mask_int64<2>(gint64x2 d) : d_(d) {}
#endif
#endif

    /// Access the underlying type
    operator gint64x2() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& operator[](unsigned id) { return b_[id]; }
    const bool& operator[](unsigned id) const { return b_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_NULL
    bool b_[8];
#else
    gint64x2 d_;
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
