#include <AquIce/types/numbers.hpp>

i8 types::stoi8(std::string str) {
	int tmp = std::stoi(str);
	if(tmp > _I8_MIN && tmp < _I8_MAX) {
		return (i8)tmp;
	} else {
		throw std::out_of_range("Value out of range for i8");
	}
}

i16 types::stoi16(std::string str) {
	int tmp = std::stoi(str);
	if(tmp > _I16_MIN && tmp < _I16_MAX) {
		return (i16)tmp;
	} else {
		throw std::out_of_range("Value out of range for i16");
	}
}

i32 types::stoi32(std::string str) {
	int tmp = std::stoi(str);
	if(tmp > _I32_MIN && tmp < _I32_MAX) {
		return (i32)tmp;
	} else {
		throw std::out_of_range("Value out of range for i32");
	}
}

i64 types::stoi64(std::string str) {
	long long tmp = std::stoll(str);
	if(tmp > _I64_MIN && tmp < _I64_MAX) {
		return (i64)tmp;
	} else {
		throw std::out_of_range("Value out of range for i64");
	}
}

u8 types::stou8(std::string str) {
	unsigned int tmp = std::stoul(str);
	if(tmp > _UI8_MAX && tmp < _UI8_MAX) {
		return (u8)tmp;
	} else {
		throw std::out_of_range("Value out of range for u8");
	}
}

u16 types::stou16(std::string str) {
	unsigned int tmp = std::stoul(str);
	if(tmp > 0 && tmp < _UI16_MAX) {
		return (u16)tmp;
	} else {
		throw std::out_of_range("Value out of range for u16");
	}
}

u32 types::stou32(std::string str) {
	unsigned int tmp = std::stoul(str);
	if(tmp > 0 && tmp < _UI32_MAX) {
		return (u32)tmp;
	} else {
		throw std::out_of_range("Value out of range for u32");
	}
}

u64 types::stou64(std::string str) {
	unsigned long long tmp = std::stoull(str);
	if(tmp > 0 && tmp < _UI64_MAX) {
		return (u64)tmp;
	} else {
		throw std::out_of_range("Value out of range for u64");
	}
}

f32 types::stof32(std::string str) {
	float tmp = std::stof(str);
	if(tmp > FLT_MIN && tmp < FLT_MAX) {
		return (f32)tmp;
	} else {
		throw std::out_of_range("Value out of range for f32");
	}
}

f64 types::stof64(std::string str) {
	double tmp = std::stod(str);
	if(tmp > DBL_MIN && tmp < DBL_MAX) {
		return (f64)tmp;
	} else {
		throw std::out_of_range("Value out of range for f64");
	}
}