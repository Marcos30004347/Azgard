#include <cmath>
// TODO: add cmath implementantion

#define AZG_USE_STANDART_MATH 1

namespace Azgard {

inline float fmaf(float a, float b, float c) {
  #ifdef AZG_USE_STANDART_MATH
  return std::fmaf(a,b,c);
  #else
  return (a*b) + c;
  #endif
}

float log2(float x)
{
  #ifdef AZG_USE_STANDART_MATH
  return std::log(x);
  #else
  // a*(x-1)^2 + b*(x-1) approximates log2(x) when 0.75 <= x < 1.5
  const float a =  -.6296735;
  const float b =   1.466967;
  float signif, fexp;
  int exp;
  float lg2;
  union { float f; unsigned int i; } ux1, ux2;
  int greater;
  ux1.f = x;
  exp = (ux1.i & 0x7F800000) >> 23; 

  greater = ux1.i & 0x00400000;
  if (greater) {
      ux2.i = (ux1.i & 0x007FFFFF) | 0x3f000000;
      signif = ux2.f;
      fexp = exp - 126;
      signif = signif - 1.0;
      lg2 = fexp + a*signif*signif + b*signif;
  } else {
      ux2.i = (ux1.i & 0x007FFFFF) | 0x3f800000;
      signif = ux2.f;
      fexp = exp - 127;
      signif = signif - 1.0;
      lg2 = fexp + a*signif*signif + b*signif;
  }
  return(lg2);
  #endif

}

float log(float v) {
  #ifdef AZG_USE_STANDART_MATH
  return std::log(v);
  #else 
  #error log avaliable only as standart, try compile with AZG_USE_STANDART_MATH defined.
  #endif
}

float lerp(float a, float b, float w) {
  return a + w*(b-a);
}

float max(float a, float b) {
  return float(a > b ? a : b);
}

float min(float a, float b) {
  return float(a < b ? a : b);
}

float exp2(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::exp2(x);
  #else 
  #error exp2 avaliable only as standart, try compile with AZG_USE_STANDART_MATH defined.
  #endif
}


float exp(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::exp(x);
  #else 
  #error exp avaliable only as standart, try compile with AZG_USE_STANDART_MATH defined.
  #endif
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

float abs(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::abs(x);
  #else 
  return max(-a, a);
  #endif
}

float pow(float x, float y) {
  #ifdef AZG_USE_STANDART_MATH
  return std::pow(x, y);
  #else 
  return exp(x * log(y));
  #endif
}

float rsqrt(float a) {

    return pow(a, -0.5);
}

float sqrt(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::sqrt(x);
  #else 
  return 1.0 / rsqrt(a);
  #endif
}

float acos(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::acos(x);
  #else
  float negate = float(x < 0);
  x = abs(x);
  float ret = -0.0187293;
  ret = ret * x;
  ret = ret + 0.0742610;
  ret = ret * x;
  ret = ret - 0.2121144;
  ret = ret * x;
  ret = ret + 1.5707288;
  ret = ret * sqrt(1.0-x);
  ret = ret - 2 * negate * ret;
  return negate * 3.14159265358979 + ret;
  #endif

}

float asin(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::asin(x);
  #else
  float negate = float(x < 0);
  x = abs(x);
  float ret = -0.0187293;
  ret *= x;
  ret += 0.0742610;
  ret *= x;
  ret -= 0.2121144;
  ret *= x;
  ret += 1.5707288;
  ret = 3.14159265358979*0.5 - sqrt(1.0 - x)*ret;
  return ret - 2 * negate * ret;
  #endif
}


float atan2(float x, float y) {
  #ifdef AZG_USE_STANDART_MATH
  return std::atan2(x, y);
  #else
  float t0, t1, t2, t3, t4;

  t3 = abs(x);
  t1 = abs(y);
  t0 = max(t3, t1);
  t1 = min(t3, t1);
  t3 = float(1) / t0;
  t3 = t1 * t3;

  t4 = t3 * t3;
  t0 =         - float(0.013480470);
  t0 = t0 * t4 + float(0.057477314);
  t0 = t0 * t4 - float(0.121239071);
  t0 = t0 * t4 + float(0.195635925);
  t0 = t0 * t4 - float(0.332994597);
  t0 = t0 * t4 + float(0.999995630);
  t3 = t0 * t3;

  t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
  t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
  t3 = (y < 0) ? -t3 : t3;

  return t3;

  #endif

}

float atan(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::atan(x);
  #else
  return atan2(x, float(1));
  #endif
}


// Returns bits from offset b of length c in the bitfield a.
int bitfieldExtract(int a, int b, int c) {
    unsigned int mask = ~(0xffffffff << c);
    if (b > 0)
        return (a >> (b - 1)) & mask;
    else
        return a & mask;
}

// Returns the result of inserting bits B at offset C of length D in the bitfield A.
int bitfieldInsert(int a, int b, int c, int d)
{
  unsigned int mask = ~(0xffffffff << d) << c;
  mask = ~mask;
  a &= mask;
  return a | (b << c);
}

// Returns the reverse of the bitfield x.
int bitfieldReverse(int x)
{
  int res = 0;
  int i, shift, mask;

  for(i = 0; i < 32; i++) {
    mask = 1 << i;
    shift = 32 - 2*i - 1;
    mask &= x;
    mask = (shift > 0) ? mask << shift : mask >> -shift;
    res |= mask;
  }

  return res;
}

float frac(float x) {
  return x - (long)x;
}

int floor(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::floor(x);
  #else
  return static_cast<int>(x - frac(x));
  #endif
}

// Returns the ceiling or smallest integer not less than a scalar or each vector component.
int ceil(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::ceil(x);
  #else
  return -floor(-x);
  #endif
}

// Clamps x between a and b
float clamp(float x, float a, float b) {
  return max(a, min(b, x));
}

float cosh(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::cosh(x);
  #else
  return 0.5 * (exp(x)+exp(-x));
  #endif
}

float cos(float x) noexcept {
  #ifdef AZG_USE_STANDART_MATH
  return std::cos(x);
  #else
  constexpr float tp = 1./(3.141592653589793);
  x *= tp;
  x -= float(.25) + floor(x + float(.25));
  x *= float(16.) * (abs(x) - float(.5));
  x += float(.225) * x * (abs(x) - float(1.));
  return x;
  #endif
}

// Returns the scalar or vector converted from radians to degrees.
float degrees(float a) {
  return 57.29577951 * a;
}

float fmod(float a, float b) {
  #ifdef AZG_USE_STANDART_MATH
  return std::fmod(a, b);
  #else
  float c = frac(abs(a/b))*abs(b);
  return (a < 0) ? -c : c;   /* if ( a < 0 ) c = 0-c */
  #endif
}


bool sign(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::signbit(x);
  #else
  return ((x > 0) - (x < 0)) != -1;
  #endif
}

float sinh(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::sinh(x);
  #else
  return 0.5 * (exp(x)-exp(-x));
  #endif
}

double sin(double x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::sin(x);
  #else
  return cos(x - 1.570796326794897);
  #endif
}

float saturate(float x) {
  return max(0, min(1, x));
}

float smoothstep(float a, float b, float x) {
    float t = saturate((x - a)/(b - a));
    return t*t*(3.0 - (2.0*t));
}

float step(float a, float x) {
  return x >= a;
}

float tanh(float x) {
  #ifdef AZG_USE_STANDART_MATH
  return std::tanh(x);
  #else
  float exp2x = exp(2*x);
  return (exp2x - 1) / (exp2x + 1);
  #endif
}

float tan(float a) {
  #ifdef AZG_USE_STANDART_MATH
  return std::tan(a);
  #else
  return sin(a)/cos(a);
  #endif
}

}

/**
// https://github.com/nsf/sseculling

// Native Culling
for (int i = 0; i < 6; i++) {
    const Plane &p = planes[i];
    if (dot(p.n, s.center) + p.d < -s.radius)
        return true;
}
return false; 
 
 */
