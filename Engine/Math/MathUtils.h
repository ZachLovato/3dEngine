#pragma once
#include <cmath>
#include <glm.hpp>
#include <gtx/compatibility.hpp>
#include <gtx/norm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtx/color_space.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/euler_angles.hpp>
#include <gtc/quaternion.hpp>

namespace math
{
	constexpr float Pi = 3.14159265359f; // 180
	constexpr float TwoPi = 6.28318530718f; // 360
	constexpr float HalfPi = 1.57079632679f; // 90

	constexpr float DegToRad(float degrees)
	{
		return degrees * (Pi / 180);
	}

	constexpr float RadToDeg(float radians)
	{
		return radians * (180 / Pi);
	}

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}

	template <typename T>
	T Lerp(T min, T max, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return min + ((max - min) * t);
	}

	template <typename T>
	T Normalize(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}

	template <typename T>
	T Remap(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return Lerp(outMin, outMax, Normalize(value, inMin, inMax));
	}

	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));
		
		return value;
	}
}

