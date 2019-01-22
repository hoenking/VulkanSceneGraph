#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

// we can't implement the anonymous union/structs combination without causing warnings, so disabled them for just this header
#if defined(__GNUC__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpedantic"
#endif
#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#    pragma clang diagnostic ignored "-Wnested-anon-types"
#endif

#include <vsg/core/type_name.h>

#include <cmath>

namespace vsg
{

    template<typename T>
    struct t_vec2
    {
        using value_type = T;

        union
        {
            value_type value[2];
            struct
            {
                value_type x, y;
            };
            struct
            {
                value_type r, g;
            };
            struct
            {
                value_type s, t;
            };
        };

        constexpr t_vec2() :
            value{} {}
        constexpr t_vec2(const t_vec2& v) :
            value{v.x, v.y} {}
        constexpr t_vec2(value_type in_x, value_type in_y) :
            value{in_x, in_y} {}

        constexpr std::size_t size() const { return 2; }

        value_type& operator[](std::size_t i) { return value[i]; }
        value_type operator[](std::size_t i) const { return value[i]; }

        template<typename R>
        t_vec2& operator=(const t_vec2<R>& rhs)
        {
            value[0] = static_cast<value_type>(rhs[0]);
            value[1] = static_cast<value_type>(rhs[1]);
            return *this;
        }

        T* data() { return value; }
        const T* data() const { return value; }

        void set(value_type in_x, value_type in_y)
        {
            x = in_x;
            y = in_y;
        }
    };

    using vec2 = t_vec2<float>;
    using dvec2 = t_vec2<double>;
    using ubvec2 = t_vec2<std::uint8_t>;

    VSG_type_name(vsg::vec2);
    VSG_type_name(vsg::dvec2);
    VSG_type_name(vsg::ubvec2);


    template<typename T>
    constexpr t_vec2<T> operator-(t_vec2<T> const& lhs, t_vec2<T> const& rhs)
    {
        return t_vec2<T>(lhs[0] - rhs[0], lhs[1] - rhs[1]);
    }

    template<typename T>
    constexpr t_vec2<T> operator-(t_vec2<T> const& v)
    {
        return t_vec2<T>(-v[0], -v[1]);
    }

    template<typename T>
    constexpr t_vec2<T> operator+(t_vec2<T> const& lhs, t_vec2<T> const& rhs)
    {
        return t_vec2<T>(lhs[0] + rhs[0], lhs[1] + rhs[1]);
    }

    template<typename T>
    constexpr t_vec2<T> operator*(t_vec2<T> const& lhs, T rhs)
    {
        return t_vec2<T>(lhs[0]*rhs, lhs[1]*rhs);
    }

    template<typename T>
    constexpr t_vec2<T> operator/(t_vec2<T> const& lhs, T rhs)
    {
        T inv = 1.0/rhs;
        return t_vec2<T>(lhs[0]*inv, lhs[1]*inv);
    }

    template<typename T>
    constexpr T length(t_vec2<T> const& v)
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1]);
    }

    template<typename T>
    constexpr t_vec2<T> normalize(t_vec2<T> const& v)
    {
        T inverse_len = 1.0 / length(v);
        return t_vec2<T>(v[0] * inverse_len, v[1] * inverse_len);
    }

    template<typename T>
    constexpr T dot(t_vec2<T> const& lhs, t_vec2<T> const& rhs)
    {
        return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2]*rhs[2];
    }

} // namespace vsg

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif
#if defined(__GNUC__)
#    pragma GCC diagnostic pop
#endif
