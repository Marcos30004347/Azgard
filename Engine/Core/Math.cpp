#include <cmath>
// TODO: add cmath implementantion

namespace Azgard {

inline float fmaf(float a, float b, float c) {
    return (a*b) + c;
}

float log2(float x)
{
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
}

float log(float v) {
  return std::log(v);
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
  return std::exp2(x);
}

double exp_64(const double x) noexcept {
    // Based on Schraudolph 1999, A Fast, Compact Approximation of the Exponential Function.
    // - Adapted to use 64-bit integer; reduces staircase effect.
    // - Valid for x in approx range (-700, 700).
    union{double d_; long i_;} uid; //This could be moved to the thread scope.
    //BBBD(sizeof(uid)!=8)
    uid.i_ = long(double((long(1) << 52) / log(2.0)) * x + double((long(1) << 52) * 1023 - 0)); //c=0 for 1.0 at zero.
    return uid.d_;
}

double fast_exp(const double x) noexcept {
    // Based on Schraudolph 1999, A Fast, Compact Approximation of the Exponential Function.
    // - See the improved fast_exp_64 implementation below!
    // - Valid for x in approx range (-700, 700).
    union{double d_; int i_[2];} uid; //This could be moved to the thread scope.
    //BBBD(sizeof(uid)!=8)
    uid.i_[0] = 0;
    uid.i_[1] = int(double((1<<20) / log(2.0)) * x + double((1<<20) * 1023 - 0)); //c=0 for 1.0 at zero.
    return uid.d_;
}

float exp(float a) {
  return std::exp(a);
  // return exp_64(a);
  // return std::exp(a);
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
float abs(float a) {
  return max(-a, a);
}

float pow(float x, float y) {
    return exp(x * log(y));
}

float rsqrt(float a) {
    return pow(a, -0.5);
}

float sqrt(float a)
{
    return 1.0 / rsqrt(a);
}

float acos(float x) {
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
}

float asin(float x) {
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
}


float atan2(float y, float x)
{
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
}

float atan(float x) {
    return atan2(x, float(1));
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

float frac(float v) {
   return v - (long)v;
}

int floor(float v) {
    return static_cast<int>(v - frac(v));
}

// Returns the ceiling or smallest integer not less than a scalar or each vector component.
int ceil(float v)
{
  return -floor(-v);
}

// Clamps x between a and b
float clamp(float x, float a, float b)
{
  return max(a, min(b, x));
}

float cosh(float x) {
  return 0.5 * (exp(x)+exp(-x));
}

float cos(float x) noexcept {
    constexpr float tp = 1./(3.141592653589793);
    x *= tp;
    x -= float(.25) + floor(x + float(.25));
    x *= float(16.) * (abs(x) - float(.5));
    x += float(.225) * x * (abs(x) - float(1.));
    return x;
}

// Returns the scalar or vector converted from radians to degrees.
float degrees(float a) {
  return 57.29577951 * a;
}

float fmod(float a, float b)
{
  float c = frac(abs(a/b))*abs(b);
  return (a < 0) ? -c : c;   /* if ( a < 0 ) c = 0-c */
}


float sign(float x) {
  return (x > 0) - (x < 0);
}

float sinh(float x)
{
  return 0.5 * (exp(x)-exp(-x));
}

double sin(double x) {
    return cos(x - 1.570796326794897);
}

float saturate(float x)
{
  return max(0, min(1, x));
}

float smoothstep(float a, float b, float x)
{
    float t = saturate((x - a)/(b - a));
    return t*t*(3.0 - (2.0*t));
}

float step(float a, float x)
{
  return x >= a;
}

float tanh(float x)
{
  float exp2x = exp(2*x);
  return (exp2x - 1) / (exp2x + 1);
}

float tan(float a) {
  return sin(a)/cos(a);
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
