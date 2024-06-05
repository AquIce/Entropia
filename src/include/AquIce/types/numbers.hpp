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
	i8 stoi8(std::string str) {
		int tmp = std::stoi(str);
		if(tmp > _I8_MIN && tmp < _I8_MAX) {
			return (i8)tmp;
		} else {
			throw std::out_of_range("Value out of range for i8");
		}
	}

	i16 stoi16(std::string str) {
		int tmp = std::stoi(str);
		if(tmp > _I16_MIN && tmp < _I16_MAX) {
			return (i16)tmp;
		} else {
			throw std::out_of_range("Value out of range for i16");
		}
	}

	i32 stoi32(std::string str) {
		int tmp = std::stoi(str);
		if(tmp > _I32_MIN && tmp < _I32_MAX) {
			return (i32)tmp;
		} else {
			throw std::out_of_range("Value out of range for i32");
		}
	}

	i64 stoi64(std::string str) {
		long long tmp = std::stoll(str);
		if(tmp > _I64_MIN && tmp < _I64_MAX) {
			return (i64)tmp;
		} else {
			throw std::out_of_range("Value out of range for i64");
		}
	}

	u8 stou8(std::string str) {
		unsigned int tmp = std::stoul(str);
		if(tmp > _UI8_MAX && tmp < _UI8_MAX) {
			return (u8)tmp;
		} else {
			throw std::out_of_range("Value out of range for u8");
		}
	}

	u16 stou16(std::string str) {
		unsigned int tmp = std::stoul(str);
		if(tmp > 0 && tmp < _UI16_MAX) {
			return (u16)tmp;
		} else {
			throw std::out_of_range("Value out of range for u16");
		}
	}

	u32 stou32(std::string str) {
		unsigned int tmp = std::stoul(str);
		if(tmp > 0 && tmp < _UI32_MAX) {
			return (u32)tmp;
		} else {
			throw std::out_of_range("Value out of range for u32");
		}
	}

	u64 stou64(std::string str) {
		unsigned long long tmp = std::stoull(str);
		if(tmp > 0 && tmp < _UI64_MAX) {
			return (u64)tmp;
		} else {
			throw std::out_of_range("Value out of range for u64");
		}
	}

	f32 stof32(std::string str) {
		float tmp = std::stof(str);
		if(tmp > FLT_MIN && tmp < FLT_MAX) {
			return (f32)tmp;
		} else {
			throw std::out_of_range("Value out of range for f32");
		}
	}

	f64 stof64(std::string str) {
		double tmp = std::stod(str);
		if(tmp > DBL_MIN && tmp < DBL_MAX) {
			return (f64)tmp;
		} else {
			throw std::out_of_range("Value out of range for f64");
		}
	}

	template <typename T>
	bool is_i8(T value) {
		return value > _I8_MIN && value < _I8_MAX;
	}
	template <typename T>
	bool is_i16(T value) {
		return value > _I16_MIN && value < _I16_MAX;
	}
	template <typename T>
	bool is_i32(T value) {
		return value > _I32_MIN && value < _I32_MAX;
	}
	template <typename T>
	bool is_i64(T value) {
		return value > _I64_MIN && value < _I64_MAX;
	}

	template <typename T>
	bool is_u8(T value) {
		return value > 0 && value < _UI8_MAX;
	}
	template <typename T>
	bool is_u16(T value) {
		return value > 0 && value < _UI16_MAX;
	}
	template <typename T>
	bool is_u32(T value) {
		return value > 0 && value < _UI32_MAX;
	}
	template <typename T>
	bool is_u64(T value) {
		return value > 0 && value < _UI64_MAX;
	}

	template <typename T>
	bool is_f32(T value) {
		return value > FLT_MIN && value < FLT_MAX;
	}
	template <typename T>
	bool is_f64(T value) {
		return value > DBL_MIN && value < DBL_MAX;
	}
}

#endif