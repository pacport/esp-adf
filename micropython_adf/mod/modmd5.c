#include <string.h>
#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "esp32/rom/md5_hash.h"

// This is the function which will be called from Python as cexample.add_ints(a, b).
char dst[33];
static mp_obj_t cparser_md5(mp_obj_t srcs)
{
	unsigned char decrypt[16];
    unsigned int i = 0;
	char str_char[3];
    const char* src = mp_obj_str_get_str(srcs);
    typedef struct MD5Context MD5_CTX;
	MD5_CTX md5_ctx;
	MD5Init(&md5_ctx);
	MD5Update(&md5_ctx,(unsigned char*)src,strlen(src));
	MD5Final(decrypt,&md5_ctx);

	memset(dst, 0, 33);
	for(i = 0; i < 16; i++)
	{
		memset(str_char,0,3);
		sprintf(str_char,"%02x",decrypt[i]);
		strcat(dst,str_char);
	}
    return mp_obj_new_str(dst, strlen(dst));
}

// Define a Python reference to the function above.
static MP_DEFINE_CONST_FUN_OBJ_1(cparser_md5_obj, cparser_md5);


typedef struct _uint128 {
  uint64_t first;
  uint64_t second;
} uint128;

#define Uint128Low64(x)         (x).first
#define Uint128High64(x)        (x).second
// Hash function for a byte array.
uint64_t xHash64(const char *buf, size_t len);

// Hash function for a byte array.  For convenience, a 64-bit seed is also
// hashed into the result.
uint64_t xHash64WithSeed(const char *buf, size_t len, uint64_t seed);

// Hash function for a byte array.  For convenience, two seeds are also
// hashed into the result.
uint64_t xHash64WithSeeds(const char *buf, size_t len,
                           uint64_t seed0, uint64_t seed1);
unsigned long bswap_32(unsigned long i)
{
    unsigned int j;
    j =  (i << 24);
    j += (i <<  8) & 0x00FF0000;
    j += (i >>  8) & 0x0000FF00;
    j += (i >> 24);
    return j;
}

uint64_t bswap_64(uint64_t i)
{
    uint64_t j;
    j =  (i << 56);
    j += (i << 40)&0x00FF000000000000;
    j += (i << 24)&0x0000FF0000000000;
    j += (i <<  8)&0x000000FF00000000;
    j += (i >>  8)&0x00000000FF000000;
    j += (i >> 24)&0x0000000000FF0000;
    j += (i >> 40)&0x000000000000FF00;
    j += (i >> 56);
    return j;
}
static uint64_t UNALIGNED_LOAD64(const char *p) 
{
	uint64_t result;
	memcpy(&result, p, sizeof(result));
	return result;
}
static uint32_t UNALIGNED_LOAD32(const char *p)
{
	uint32_t result;
	memcpy(&result, p, sizeof(result));
	return result;
}

//#define bswap_32(x) _byteswap_ulong(x)
//#define bswap_64(x) _byteswap_uint64(x)

#ifdef WORDS_BIGENDIAN
#define uint32_in_expected_order(x) (bswap_32(x))
#define uint64_in_expected_order(x) (bswap_64(x))
#else
#define uint32_in_expected_order(x) (x)
#define uint64_in_expected_order(x) (x)
#endif

#if !defined(LIKELY)
#ifdef HAVE_BUILTIN_EXPECT
#define LIKELY(x) (__builtin_expect(!!(x), 1))
#else
#define LIKELY(x) (x)
#endif
#endif

static uint64_t Fetch64(const char *p)
{
	return uint64_in_expected_order(UNALIGNED_LOAD64(p));
}

static uint32_t Fetch32(const char *p)
{
	return uint32_in_expected_order(UNALIGNED_LOAD32(p));
}

// Some primes between 2^63 and 2^64 for various uses.
static const uint64_t k0 = 0xc3a5c85c97cb3127ULL;
static const uint64_t k1 = 0xb492b66fbe98f273ULL;
static const uint64_t k2 = 0x9ae16a3b2f90404fULL;

// Magic numbers for 32-bit hashing.  Copied from Murmur3.
static const uint32_t c1 = 0xcc9e2d51;
static const uint32_t c2 = 0x1b873593;

// A 32-bit to 32-bit integer hash copied from Murmur3.
static uint32_t fmix(uint32_t h)
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}
static uint32_t Rotate32(uint32_t val, int shift) 
{
  // Avoid shifting by 32: doing so yields an undefined result.
  return shift == 0 ? val : ((val >> shift) | (val << (32 - shift)));
}

#undef PERMUTE3
#define PERMUTE3(a, b, c) do { std::swap(a, b); std::swap(a, c); } while (0)

#undef PERMUTE3_32
#define PERMUTE3_32(a, b, c) do { uint32_t t = a; a = c; c = b; b = t;} while (0)

#undef PERMUTE3_64
#define PERMUTE3_64(a, b, c) do { uint64_t t = a; a = c; c = b; b = t;} while (0)
static uint32_t Mur(uint32_t a, uint32_t h) 
{
  // Helper from Murmur3 for combining two 32-bit values.
  a *= c1;
  a = Rotate32(a, 17);
  a *= c2;
  h ^= a;
  h = Rotate32(h, 19);
  return h * 5 + 0xe6546b64;
}

uint64_t Hash128to64(const uint128 x)
{
   // Murmur-inspired hashing.
   const uint64_t kMul = 0x9ddfea08eb382d69ULL;
   uint64_t a = (Uint128Low64(x) ^ Uint128High64(x)) * kMul;
   a ^= (a >> 47);
   uint64_t b = (Uint128High64(x) ^ a) * kMul;
   b ^= (b >> 47);
   b *= kMul;
   return b;
}

static uint32_t Hash32Len13to24(const char *s, size_t len) 
{
  uint32_t a = Fetch32(s - 4 + (len >> 1));
  uint32_t b = Fetch32(s + 4);
  uint32_t c = Fetch32(s + len - 8);
  uint32_t d = Fetch32(s + (len >> 1));
  uint32_t e = Fetch32(s);
  uint32_t f = Fetch32(s + len - 4);
  uint32_t h = len;

  return fmix(Mur(f, Mur(e, Mur(d, Mur(c, Mur(b, Mur(a, h)))))));
}

static uint32_t Hash32Len0to4(const char *s, size_t len) 
{
  uint32_t b = 0;
  uint32_t c = 9;
  int i;
  for (i = 0; i < len; i++) {
    b = b * c1 + s[i];
    c ^= b;
  }
  return fmix(Mur(b, Mur(len, c)));
}

static uint32_t Hash32Len5to12(const char *s, size_t len) 
{
  uint32_t a = len, b = len * 5, c = 9, d = b;
  a += Fetch32(s);
  b += Fetch32(s + len - 4);
  c += Fetch32(s + ((len >> 1) & 4));
  return fmix(Mur(c, Mur(b, Mur(a, d))));
}

uint32_t xHash32(const char *s, size_t len) 
{
  if (len <= 24) {
    return len <= 12 ?
        (len <= 4 ? Hash32Len0to4(s, len) : Hash32Len5to12(s, len)) :
        Hash32Len13to24(s, len);
  }

  // len > 24
  uint32_t h = len, g = c1 * len, f = g;
  uint32_t a0 = Rotate32(Fetch32(s + len - 4) * c1, 17) * c2;
  uint32_t a1 = Rotate32(Fetch32(s + len - 8) * c1, 17) * c2;
  uint32_t a2 = Rotate32(Fetch32(s + len - 16) * c1, 17) * c2;
  uint32_t a3 = Rotate32(Fetch32(s + len - 12) * c1, 17) * c2;
  uint32_t a4 = Rotate32(Fetch32(s + len - 20) * c1, 17) * c2;
  h ^= a0;
  h = Rotate32(h, 19);
  h = h * 5 + 0xe6546b64;
  h ^= a2;
  h = Rotate32(h, 19);
  h = h * 5 + 0xe6546b64;
  g ^= a1;
  g = Rotate32(g, 19);
  g = g * 5 + 0xe6546b64;
  g ^= a3;
  g = Rotate32(g, 19);
  g = g * 5 + 0xe6546b64;
  f += a4;
  f = Rotate32(f, 19);
  f = f * 5 + 0xe6546b64;
  size_t iters = (len - 1) / 20;
  do {
    uint32_t a0 = Rotate32(Fetch32(s) * c1, 17) * c2;
    uint32_t a1 = Fetch32(s + 4);
    uint32_t a2 = Rotate32(Fetch32(s + 8) * c1, 17) * c2;
    uint32_t a3 = Rotate32(Fetch32(s + 12) * c1, 17) * c2;
    uint32_t a4 = Fetch32(s + 16);
    h ^= a0;
    h = Rotate32(h, 18);
    h = h * 5 + 0xe6546b64;
    f += a1;
    f = Rotate32(f, 19);
    f = f * c1;
    g += a2;
    g = Rotate32(g, 18);
    g = g * 5 + 0xe6546b64;
    h ^= a3 + a1;
    h = Rotate32(h, 19);
    h = h * 5 + 0xe6546b64;
    g ^= a4;
    g = bswap_32(g) * 5;
    h += a4 * 5;
    h = bswap_32(h);
    f += a0;
    PERMUTE3_32(f, h, g);
    s += 20;
  } while (--iters != 0);
  g = Rotate32(g, 11) * c1;
  g = Rotate32(g, 17) * c1;
  f = Rotate32(f, 11) * c1;
  f = Rotate32(f, 17) * c1;
  h = Rotate32(h + g, 19);
  h = h * 5 + 0xe6546b64;
  h = Rotate32(h, 17) * c1;
  h = Rotate32(h + f, 19);
  h = h * 5 + 0xe6546b64;
  h = Rotate32(h, 17) * c1;
  return h;
}

// Bitwise right rotate.  Normally this will compile to a single
// instruction, especially if the shift is a manifest constant.
 static uint64_t Rotate(uint64_t val, int shift) {
  // Avoid shifting by 64: doing so yields an undefined result.
  return shift == 0 ? val : ((val >> shift) | (val << (64 - shift)));
}

 static uint64_t ShiftMix(uint64_t val) {
  return val ^ (val >> 47);
}

 static uint64_t HashLen16(uint64_t u, uint64_t v) {
  uint128 t;
  t.first = u;
  t.second = v;
  return Hash128to64(t);
}

 static uint64_t HashLen16_3a(uint64_t u, uint64_t v, uint64_t mul) {
  // Murmur-inspired hashing.
  uint64_t a = (u ^ v) * mul;
  a ^= (a >> 47);
  uint64_t b = (v ^ a) * mul;
  b ^= (b >> 47);
  b *= mul;
  return b;
}

 static uint64_t HashLen0to16(const char *s, size_t len) {
  if (len >= 8) {
    uint64_t mul = k2 + len * 2;
    uint64_t a = Fetch64(s) + k2;
    uint64_t b = Fetch64(s + len - 8);
    uint64_t c = Rotate(b, 37) * mul + a;
    uint64_t d = (Rotate(a, 25) + b) * mul;
    return HashLen16_3a(c, d, mul);
  }
  if (len >= 4) {
    uint64_t mul = k2 + len * 2;
    uint64_t a = Fetch32(s);
    return HashLen16_3a(len + (a << 3), Fetch32(s + len - 4), mul);
  }
  if (len > 0) {
    uint8_t a = s[0];
    uint8_t b = s[len >> 1];
    uint8_t c = s[len - 1];
    uint32_t y = (uint32_t)(a) + ((uint32_t)(b) << 8);
    uint32_t z = len + ((uint32_t)(c) << 2);
    return ShiftMix(y * k2 ^ z * k0) * k2;
  }
  return k2;
}

// This probably works well for 16-byte strings as well, but it may be overkill
// in that case.
 static uint64_t HashLen17to32(const char *s, size_t len) {
  uint64_t mul = k2 + len * 2;
  uint64_t a = Fetch64(s) * k1;
  uint64_t b = Fetch64(s + 8);
  uint64_t c = Fetch64(s + len - 8) * mul;
  uint64_t d = Fetch64(s + len - 16) * k2;
  return HashLen16_3a(Rotate(a + b, 43) + Rotate(c, 30) + d,
                   a + Rotate(b + k2, 18) + c, mul);
}

// Return a 16-byte hash for 48 bytes.  Quick and dirty.
// Callers do best to use "random-looking" values for a and b.
 uint128 WeakHashLen32WithSeeds(
    uint64_t w, uint64_t x, uint64_t y, uint64_t z, uint64_t a, uint64_t b) {
  a += w;
  b = Rotate(b + a + z, 21);
  uint64_t c = a;
  a += x;
  a += y;
  b += Rotate(a, 44);

  uint128 r;
  r.first = (uint64_t)(a + z);
  r.second = (uint64_t)(b + c);
  return r;
}

// Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
 uint128 WeakHashLen32WithSeeds_3a(
    const char* s, uint64_t a, uint64_t b) {
  return WeakHashLen32WithSeeds(Fetch64(s),
                                Fetch64(s + 8),
                                Fetch64(s + 16),
                                Fetch64(s + 24),
                                a,
                                b);
}


// Return an 8-byte hash for 33 to 64 bytes.
 static uint64_t HashLen33to64(const char *s, size_t len) {
  uint64_t mul = k2 + len * 2;
  uint64_t a = Fetch64(s) * k2;
  uint64_t b = Fetch64(s + 8);
  uint64_t c = Fetch64(s + len - 24);
  uint64_t d = Fetch64(s + len - 32);
  uint64_t e = Fetch64(s + 16) * k2;
  uint64_t f = Fetch64(s + 24) * 9;
  uint64_t g = Fetch64(s + len - 8);
  uint64_t h = Fetch64(s + len - 16) * mul;
  uint64_t u = Rotate(a + g, 43) + (Rotate(b, 30) + c) * 9;
  uint64_t v = ((a + g) ^ d) + f + 1;
  uint64_t w = bswap_64((u + v) * mul) + h;
  uint64_t x = Rotate(e + f, 42) + c;
  uint64_t y = (bswap_64((v + w) * mul) + g) * mul;
  uint64_t z = e + f + c;
  a = bswap_64((x + z) * mul + y) + b;
  b = ShiftMix((z + a) * mul + d + h) * mul;
  return b + x;
}

 uint64_t xHash64(const char *s, size_t len) {
  if (len <= 32) {
    if (len <= 16) {
      return HashLen0to16(s, len);
    } else {
      return HashLen17to32(s, len);
    }
  } else if (len <= 64) {
    return HashLen33to64(s, len);
  }

  // For strings over 64 bytes we hash the end first, and then as we
  // loop we keep 56 bytes of state: v, w, x, y, and z.
  uint64_t temp;
  uint64_t x = Fetch64(s + len - 40);
  uint64_t y = Fetch64(s + len - 16) + Fetch64(s + len - 56);
  uint64_t z = HashLen16(Fetch64(s + len - 48) + len, Fetch64(s + len - 24));
  uint128 v = WeakHashLen32WithSeeds_3a(s + len - 64, len, z);
  uint128 w = WeakHashLen32WithSeeds_3a(s + len - 32, y + k1, x);
  x = x * k1 + Fetch64(s);

  // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
  len = (len - 1) & ~(size_t)(63);
  do {
    x = Rotate(x + y + v.first + Fetch64(s + 8), 37) * k1;
    y = Rotate(y + v.second + Fetch64(s + 48), 42) * k1;
    x ^= w.second;
    y += v.first + Fetch64(s + 40);
    z = Rotate(z + w.first, 33) * k1;
    v = WeakHashLen32WithSeeds_3a(s, v.second * k1, x + w.first);
    w = WeakHashLen32WithSeeds_3a(s + 32, z + w.second, y + Fetch64(s + 16));


    temp = z;
    z = x;
    x = temp;


    s += 64;
    len -= 64;
  } while (len != 0);
  return HashLen16(HashLen16(v.first, w.first) + ShiftMix(y) * k1 + z,
                   HashLen16(v.second, w.second) + x);
}

 uint64_t xHash64WithSeed(const char *s, size_t len, uint64_t seed) {
  return xHash64WithSeeds(s, len, k2, seed);
}

 uint64_t xHash64WithSeeds(const char *s, size_t len,
                           uint64_t seed0, uint64_t seed1) {
  return HashLen16(xHash64(s, len) - seed0, seed1);
}

char flashStr[32];
static mp_obj_t flashid_hash(mp_obj_t strs)
{
    
    
    const char* str = mp_obj_str_get_str(strs);
    uint64_t flashid = xHash64WithSeed(str, strlen(str), 0);
    sprintf(flashStr, "%016llX", flashid);
    return mp_obj_new_str(flashStr, strlen(flashStr));
}


static MP_DEFINE_CONST_FUN_OBJ_1(flashid_hash_obj, flashid_hash);



// Define all attributes of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
static  mp_rom_map_elem_t md5_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_md5) },
    { MP_ROM_QSTR(MP_QSTR_cparser_md5), MP_ROM_PTR(&cparser_md5_obj) },
    { MP_ROM_QSTR(MP_QSTR_flashid_hash), MP_ROM_PTR(&flashid_hash_obj) },
};
static MP_DEFINE_CONST_DICT(example_module_globals, md5_module_globals_table);

// Define module object.
const mp_obj_module_t md5_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&example_module_globals,
};


// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_md5, md5_user_cmodule);