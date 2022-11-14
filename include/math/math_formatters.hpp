#ifndef ATG_PALACE_ENGINE_MATH_FORMATTERS_HPP
#define ATG_PALACE_ENGINE_MATH_FORMATTERS_HPP

#include "../../dependencies/math/include/atg_math.h"
#include "../formatting/formatting.hpp"

template<class CharT>
struct palace::format::formatter<atg_math::ivec2, CharT>
    : palace::format::formatter<int, CharT> {
    template<typename FormatContext>
    auto format(const atg_math::ivec2 &v, FormatContext &ctx) {
        return format_to(ctx.out(), "[{}, {}]", v.x(), v.y());
    }
};

#endif /* ATG_PALACE_ENGINE_MATH_FORMATTERS_HPP */