
#ifndef DEFINES_H
#define DEFINES_H


#define LTRUE 1
#define LFALSE 0

#define LPI 3.14159265358979323846f
#define LDEG2RAD(x) (x * 0.01745329251f)
#define LRAD2DEG(x) (x * 57.29577951308f)


#define LLOG(x) std::cout << __FILE__ << ':' << __LINE__ << ':' << __func__ << ": " << (x) << "\n"


#include <cstdint>


using i8 = int_fast8_t;
using i16 = int_least16_t;
using i32 = int_fast32_t;
using i64 = int_fast64_t;

using u8 = uint_fast8_t;
using u16 = uint_least16_t;
using u32 = uint_fast32_t;
using u64 = uint_fast64_t;

using f32 = float;
using f64 = double;

using b8 = i8;
using b32 = i32;


template<typename val = f32>
val generateRandom() {
    static std::uniform_real_distribution<val> distribution((val)0.0, (val)1.0);
    static std::mt19937 generator;
    return (val)distribution(generator);
}

template<typename val = f32>
val generateRandom(val min, val max) {
    return min + (max - min) * generateRandom();
}


#endif
