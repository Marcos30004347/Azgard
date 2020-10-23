#ifndef AZGARD_MATH
#define AZGARD_MATH

namespace Azgard {
float log (float a);
float lerp(float a, float b, float w);
float max(float a, float b);
float min(float a, float b);
float exp2(float x);
double exp_64(const double x) noexcept;
double fast_exp(const double x) noexcept;
float exp(float a);
long long binpow(long long a, long long b);
float abs(float a);
float pow(float x, float y);
float rsqrt(float a);
float sqrt(float a);
float acos(float x);
float asin(float x);
float atan2(float y, float x);
float atan(float x);
// Returns bits from offset b of length c in the bitfield a.
int bitfieldExtract(int a, int b, int c);
// Returns the result of inserting bits B at offset C of length D in the bitfield A.
int bitfieldInsert(int a, int b, int c, int d);
// Returns the reverse of the bitfield x.
int bitfieldReverse(int x);
float frac(float v);
int floor(float v);
// Returns the ceiling or smallest integer not less than a scalar or each vector component.
int ceil(float v);
// Clamps x between a and b
float clamp(float x, float a, float b);
float cosh(float x);
float cos(float x) noexcept;
// Returns the scalar or vector converted from radians to degrees.
float degrees(float a);
float fmod(float a, float b);
float sign(float x);
float sinh(float x);
double sin(double x);
float saturate(float x);
float smoothstep(float a, float b, float x);
float step(float a, float x);
float tanh(float x);
float tan(float a);

float log2(float x);
}



#endif