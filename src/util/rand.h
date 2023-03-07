/** 
 * @file 
 * @brief Random number generator
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see RandomGroup
*/

#ifndef _RAND_H
#define _RAND_H

/**
 * @addtogroup RandomGroup
 * @details The cRandom library replaces and extends the standard random number generator. A 64-bit number is used as seed, 
 * which ensures sufficient randomness of the number. The limited randomness of the standard 32-bit generator can be observed, 
 * for example, when generating terrain - it will appear as waves in the terrain. You can either use the global variable Rand 
 * and the functions belonging to it, or create another local generator cRandom. The following functions refer to the global 
 * Rand generator. It is recommended to use the RandInitSeed() function when starting the program to ensure the generator is 
 * non-repeating.
 * @{
*/

/// Random Generator
class cRandom
{
private:

	// random generator seed
	u64 m_Seed;

public:

	/// Shift random generator seed
	inline void Shift()
	{
		m_Seed = m_Seed*214013 + 2531011;
	}

	/// Get random number seed
	inline u64 Seed() const { return m_Seed; }

	/// Set random number seed
	inline void SetSeed(u64 seed) { m_Seed = seed; }

	/// Set random seed from ROSC counter
	void InitSeed();

	u8 U8();		///< Generate integer random number in full range
	u16 U16(); 		///< Generate integer random number in full range
	u32 U32();		///< Generate integer random number in full range
	u64 U64();		///< Generate integer random number in full range

	inline s8 S8() { return (s8)this->U8(); }		///< Generate integer random number in full range
	inline s16 S16() { return (s16)this->U16(); }	///< Generate integer random number in full range
	inline s32 S32() { return (s32)this->U32(); }	///< Generate integer random number in full range
	inline s64 S64() { return (s64)this->U64(); }	///< Generate integer random number in full range

	/// Generate float random number in range 0 (including) to 1 (excluding)
	float Float();

	/// Generate double random number in range 0 (including) to 1 (excluding)
	double Double();

	
	u8 U8Max(u8 max);		///< Generate random number in range 0 to MAX (including)
	u16 U16Max(u16 max);	///< Generate random number in range 0 to MAX (including)
	u32 U32Max(u32 max);	///< Generate random number in range 0 to MAX (including)
	u64 U64Max(u64 max);	///< Generate random number in range 0 to MAX (including)

	s8 S8Max(s8 max);		///< Generate random number in range 0 to MAX (including)
	s16 S16Max(s16 max);	///< Generate random number in range 0 to MAX (including)
	s32 S32Max(s32 max);	///< Generate random number in range 0 to MAX (including)
	s64 S64Max(s64 max);	///< gGenerate random number in range 0 to MAX (including)

	/// Generate decimal random number in range 0 (including) to MAX (excluding)
	float FloatMax(float max);
	/// Generate decimal random number in range 0 (including) to MAX (excluding)
	double DoubleMax(double max);

	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	u8 U8MinMax(u8 min, u8 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	u16 U16MinMax(u16 min, u16 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	u32 U32MinMax(u32 min, u32 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	u64 U64MinMax(u64 min, u64 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	s8 S8MinMax(s8 min, s8 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	s16 S16MinMax(s16 min, s16 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	s32 S32MinMax(s32 min, s32 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	s64 S64MinMax(s64 min, s64 max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	float FloatMinMax(float min, float max);
	/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
	double DoubleMinMax(double min, double max);
};

/// Gaussian random float number generator
class cGaussFRandom
{
private:

	// linear random number generator
	cRandom m_Rand;

	// cached Gaussian number
	float m_Cache;
	Bool m_CacheOK;

public:

	/// Get random number seed
	inline u64 Seed() const { return m_Rand.Seed(); }
	/// Set random number seed
	inline void SetSeed(u64 seed)
	{
		m_Rand.SetSeed(seed);
		m_CacheOK = False;
	}

	/// Generate Gaussian random number (mean = center, sigma = width)
	float Gauss(float mean = 0, float sigma = 1);
};

/// Gaussian random double number generator
class cGaussDRandom
{
private:

	// linear random number generator
	cRandom m_Rand;

	// cached Gaussian number
	double m_Cache;
	Bool m_CacheOK;

public:

	/// Get random number seed
	inline u64 Seed() const { return m_Rand.Seed(); }
	/// Set random number seed
	inline void SetSeed(u64 seed)
	{
		m_Rand.SetSeed(seed);
		m_CacheOK = False;
	}

	/// Generate Gaussian random number (mean = center, sigma = width)
	double Gauss(double mean = 0, double sigma = 1);
};

/// Global random generator
extern cRandom Rand;

/// Global Gaussian random float number generator
extern cGaussFRandom GaussFRand;

/// Global Gaussian random double number generator
extern cGaussDRandom GaussDRand;

/// Get random generator seed
inline u64 RandSeed() { return Rand.Seed(); }
/// Set random generator seed
inline void RandSetSeed(u64 seed) { Rand.SetSeed(seed); }

/// Set random seed from ROSC counter
inline void RandInitSeed() { Rand.InitSeed(); }

/// Generate integer random number in full range
inline u8 RandU8() { return Rand.U8(); }
/// Generate integer random number in full range
inline u16 RandU16() { return Rand.U16(); }
/// Generate integer random number in full range
inline u32 RandU32() { return Rand.U32(); }
/// Generate integer random number in full range
inline u64 RandU64() { return Rand.U64(); }
/// Generate integer random number in full range
inline s8 RandS8() { return Rand.S8(); }
/// Generate integer random number in full range
inline s16 RandS16() { return Rand.S16(); }
/// Generate integer random number in full range
inline s32 RandS32() { return Rand.S32(); }
/// Generate integer random number in full range
inline s64 RandS64() { return Rand.S64(); }

/// Generate float random number in range 0 (including) to 1 (excluding)
inline float RandFloat() { return Rand.Float(); }

/// Generate double random number in range 0 (including) to 1 (excluding)
inline double RandDouble() { return Rand.Double(); }

/// Generate random number in range 0 to MAX (including)
inline u8 RandU8Max(u8 max) { return Rand.U8Max(max); }
/// Generate random number in range 0 to MAX (including)
inline u16 RandU16Max(u16 max) { return Rand.U16Max(max); }
/// Generate random number in range 0 to MAX (including)
inline u32 RandU32Max(u32 max) { return Rand.U32Max(max); }
/// Generate random number in range 0 to MAX (including)
inline u64 RandU64Max(u64 max) { return Rand.U64Max(max); }
/// Generate random number in range 0 to MAX (including)
inline s8 RandS8Max(s8 max) { return Rand.S8Max(max); }
/// Generate random number in range 0 to MAX (including)
inline s16 RandS16Max(s16 max) { return Rand.S16Max(max); }
/// Generate random number in range 0 to MAX (including)
inline s32 RandS32Max(s32 max) { return Rand.S32Max(max); }
/// Generate random number in range 0 to MAX (including)
inline s64 RandS64Max(s64 max) { return Rand.S64Max(max); }

/// Generate decimal random number in range 0 (including) to MAX (excluding)
inline float RandFloatMax(float max) { return Rand.FloatMax(max); }
/// Generate decimal random number in range 0 (including) to MAX (excluding)
inline double RandDoubleMax(double max) { return Rand.DoubleMax(max); }

/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline u8 RandU8MinMax(u8 min, u8 max) { return Rand.U8MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline u16 RandU16MinMax(u16 min, u16 max) { return Rand.U16MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline u32 RandU32MinMax(u32 min, u32 max) { return Rand.U32MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline u64 RandU64MinMax(u64 min, u64 max) { return Rand.U64MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline s8 RandS8MinMax(s8 min, s8 max) { return Rand.S8MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline s16 RandS16MinMax(s16 min, s16 max) { return Rand.S16MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline s32 RandS32MinMax(s32 min, s32 max) { return Rand.S32MinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline s64 RandS64MinMax(s64 min, s64 max) { return Rand.S64MinMax(min, max); }

/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline float RandFloatMinMax(float min, float max) { return Rand.FloatMinMax(min, max); }
/// Generate random number in range MIN to MAX (including). If MIN > MAX, then number is generated out of interval.
inline double RandDoubleMinMax(double min, double max) { return Rand.DoubleMinMax(min, max); }

/// Generate Gaussian random number (mean = center, sigma = width)
inline float RandGaussF(float mean = 0, float sigma = 1) { return GaussFRand.Gauss(mean, sigma); }
/// Generate Gaussian random number (mean = center, sigma = width)
inline double RandGaussD(double mean = 0, double sigma = 1) { return GaussDRand.Gauss(mean, sigma); }

/// 1D coordinate noise generator (output -1..+1)
float Noise1D(int x, int seed);

/// 2D coordinate noise generator (output -1..+1)
float Noise2D(int x, int y, int seed);

/// 3D coordinate noise generator (output -1..+1)
float Noise3D(int x, int y, int z, int seed);

/// Interpolated 1D noise (output -1..+1, scale = 1...)
float SmoothNoise1D(float x, int scale, int seed);

/// Interpolated 2D noise (output -1..+1, scale = 1...)
float SmoothNoise2D(float x, float y, int scale, int seed);

/// @}

#endif // _RAND_H
