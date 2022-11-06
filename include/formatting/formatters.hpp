#ifndef ATG_PALACE_ENGINE_FORMATTERS_HPP
#define ATG_PALACE_ENGINE_FORMATTERS_HPP

#include "formatting.hpp"

#include "../math/math.hpp"

template<class CharT>
struct palace::format::formatter<palace::math::ivec2, CharT>
    : palace::format::formatter<int, CharT> {
    template<typename FormatContext>
    auto format(const palace::math::ivec2 &v, FormatContext &ctx) {
        return format_to(ctx.out(), "[{}, {}]", v.x(), v.y());
    }
};

#define PALACE_ENUM_FORMATTER_BEGIN(namespace_name, enum_name)                 \
    template<class CharT>                                                      \
    struct palace::format::formatter<namespace_name::enum_name, CharT>         \
        : public palace::format::formatter<std::string_view, CharT> {          \
        template<typename FormatContext>                                       \
        auto format(const namespace_name::enum_name &value,                    \
                    FormatContext &ctx) {                                      \
            std::string_view name = "Unknown";                                 \
            using FullEnumName = namespace_name::enum_name;                    \
            switch (value) {
#define PALACE_ENUM_FORMATTER_CUSTOM_ENTRY(enum_value, enum_name)              \
    case FullEnumName::enum_value:                                             \
        name = enum_name;                                                      \
        break;
#define PALACE_ENUM_FORMATTER_ENTRY(enum_value)                                \
    PALACE_ENUM_FORMATTER_CUSTOM_ENTRY(enum_value, #enum_value)
#define PALACE_ENUM_FORMATTER_END()                                            \
    }                                                                          \
    return palace::format::formatter<std::string_view, CharT>::format(name,    \
                                                                      ctx);    \
    }                                                                          \
    }                                                                          \
    ;


#endif /* ATG_PALACE_ENGINE_FORMATTERS_HPP */
