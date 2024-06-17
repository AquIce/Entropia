#ifndef __AQUICE_TYPES_NUMBERS__
#define __AQUICE_TYPES_NUMBERS__

#include <string>
#include <stdexcept>
#include <cstdint>
#include <cfloat>

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define f32 float
#define f64 double

namespace types {

	/**
	 * Extract an I8 from a string
	 * @param str The source string
	 * @return The I8 value
	 */
	i8 stoi8(std::string str);

	/**
	 * Extract an I16 from a string
	 * @param str The source string
	 * @return The I16 value
	 */
	i16 stoi16(std::string str);

	/**
	 * Extract an I32 from a string
	 * @param str The source string
	 * @return The I32 value
	 */
	i32 stoi32(std::string str);

	/**
	 * Extract an I64 from a string
	 * @param str The source string
	 * @return The I8 value
	 */
	i64 stoi64(std::string str);

	/**
	 * Extract an U8 from a string
	 * @param str The source string
	 * @return The U8 value
	 */
	u8 stou8(std::string str);

	/**
	 * Extract an U16 from a string
	 * @param str The source string
	 * @return The U16 value
	 */
	u16 stou16(std::string str);

	/**
	 * Extract an U32 from a string
	 * @param str The source string
	 * @return The U32 value
	 */
	u32 stou32(std::string str);

	/**
	 * Extract an U64 from a string
	 * @param str The source string
	 * @return The U64 value
	 */
	u64 stou64(std::string str);

	/**
	 * Extract an F32 from a string
	 * @param str The source string
	 * @return The F32 value
	 */
	f32 stof32(std::string str);

	/**
	 * Extract an F64 from a string
	 * @param str The source string
	 * @return The F64 value
	 */
	f64 stof64(std::string str);
}

#endif