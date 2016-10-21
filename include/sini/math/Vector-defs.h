// Constructor and function definitions for the SiNi vector template Vector.h
//
// This code has in many ways been inspired by or based on the Vector.hpp code in sfzCore,
// written by Peter Hillerstr�m (github.com/PetorSFZ) -- which is superior to this code.
// I've taken to writing very similar code for my own learning purposes, but this is not
// necessarily representative of the code I've gotten inspiration from.
//
// Simon Nilsson (sim.f.nilsson@gmail.com)

#pragma once
namespace sini {

	// CONSTRUCTORS
	// ================================================================================

	// Unless otherwise stated, initialize with all components 0
	template<typename T, size_t n>
	Vector<T, n>::Vector() noexcept {

		for (size_t i = 0; i < n; i++)
			components[i] = 0;
	}

	template<typename T>
	Vector<T, 2>::Vector() noexcept
		: x(T(0)),
		  y(T(0))
	{}

	template<typename T>
	Vector<T, 3>::Vector() noexcept
		: x(T(0)),
		  y(T(0)),
		  z(T(0))
	{}

	template<typename T>
	Vector<T, 4>::Vector() noexcept
		: x(T(0)),
		  y(T(0)),
		  z(T(0)),
		  w(T(0))
	{}
	// -----------------------------------------------------------------------------

	// Initialize with values
	template<typename T, size_t n>
	Vector<T, n>::Vector(const T* initArray) noexcept {

		for (size_t i = 0; i < n; i++)
			components[i] = initArray[i];
	}
	template<typename T, size_t n>
	template<typename T2>
	Vector<T, n>::Vector(const Vector<T2, n>& other) noexcept {

		for (size_t i = 0; i < n; i++)
			components[i] = static_cast<T>(other.components[i]);
	}
	template<typename T,size_t n>
	Vector<T, n>::Vector(T initVal) {

		for (size_t i = 0; i < n; i++)
			components[i] = initVal;
	}

	template<typename T>
	Vector<T, 2>::Vector(const T* initArray) noexcept
		: x(initArray[0]),
		  y(initArray[1])
	{}

	// 2D
	//----------------------------
	template<typename T>
	template<typename T2>
	Vector<T, 2>::Vector(const Vector<T2, 2>& other) noexcept
		: x(static_cast<T>(other.x)),
		  y(static_cast<T>(other.y))
	{}

	template<typename T>
	Vector<T, 2>::Vector(T initVal) noexcept
		: x(initVal),
		  y(initVal)
	{}

	template<typename T>
	Vector<T, 2>::Vector(T x, T y) noexcept
		: x(x),
		  y(y)
	{}


	// 3D
	//----------------------------
	template<typename T>
	Vector<T, 3>::Vector(const T* initArray) noexcept
		: x(initArray[0]),
		  y(initArray[1]),
		  z(initArray[2])
	{}

	template<typename T>
	template<typename T2>
	Vector<T, 3>::Vector(const Vector<T2, 3>& other) noexcept
		: x(static_cast<T>(other.x)),
		  y(static_cast<T>(other.y)),
		  z(static_cast<T>(other.z))
	{}

	template<typename T>
	Vector<T, 3>::Vector(T initVal) noexcept
		: x(initVal),
		  y(initVal),
		  z(initVal)
	{}

	template<typename T>
	Vector<T, 3>::Vector(T x, T y, T z) noexcept
		: x(x),
		  y(y),
		  z(z)
	{}

	// 4D
	//----------------------------
	template<typename T>
	Vector<T, 4>::Vector(const T* initArray) noexcept
		: x(initArray[0]),
		  y(initArray[1]),
		  z(initArray[2]),
		  w(initArray[3])
	{}

	template<typename T>
	template<typename T2>
	Vector<T, 4>::Vector(const Vector<T2, 4>& other) noexcept
		: x(static_cast<T>(other.x)),
		  y(static_cast<T>(other.y)),
		  z(static_cast<T>(other.z)),
		  w(static_cast<T>(other.w))
	{}

	template<typename T>
	Vector<T, 4>::Vector(T initVal) noexcept
		: x(initVal),
		  y(initVal),
		  z(initVal),
		  w(initVal)
	{}

	template<typename T>
	Vector<T, 4>::Vector(T x, T y, T z, T w) noexcept
		: x(x),
		  y(y),
		  z(z),
		  w(w)
	{}


	// Math functions
	// =============================================================================

	// Scalar product
	template<size_t n>
	float dot(const Vector<int32_t, n>& v1, const Vector<int32_t, n>& v2) {

		float sum = 0.0f;
		for (size_t i = 0; i < n; i++)
			sum += v1.components[i] * v2.components[i];
		return sum;
	}
	template<size_t n>
	float dot(const Vector<float, n>& v1, const Vector<float, n>& v2) {

		float sum = 0.0f;
		for (size_t i = 0; i < n; i++)
			sum += v1.components[i] * v2.components[i];
		return sum;
	}
	template<size_t n>
	double dot(const Vector<double, n>& v1, const Vector<double, n>& v2) {

		double sum = 0.0;
		for (size_t i = 0; i < n; i++)
			sum += v1.components[i] * v2.components[i];
		return sum;
	}

	// Cross product
	template<typename T>
	Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2) {

		return Vector<T, 3>(v1.y*v2.z - v1.z*v2.y,
							v1.z*v2.x - v1.x*v1.z,
							v1.x*v2.y - v1.y*v2.x);
	}

	// Vector norm
	template<size_t n>
	float norm(const Vector<int32_t, n>& v, int32_t N) {

		if (N == 2) return length(v);
		else {
			float sum = 0.0f;
			for (size_t i = 0; i < n; i++)
				sum += std::pow(static_cast<float>(v.components[i]), N);

			return std::pow(sum, 1.0f / static_cast<float>(N));
		}
	}
	template<size_t n>
	float norm(const Vector<float, n>& v, int32_t N) {

		if (N == 2) return length(v);
		else {
			float sum = 0.0f;
			for (size_t i = 0; i < n; i++)
				sum += std::pow(v.components[i], N);
			
			return std::pow(sum, 1.0f / static_cast<float>(N));
		}
	}
	template<size_t n>
	double norm(const Vector<double, n>& v, int32_t N) {

		if (N == 2) return length(v);
		else {
			double sum = 0.0;
			for (size_t i = 0; i < n; i++)
				sum += std::pow(v.components[i], N);

			return std::pow(sum, 1.0 / static_cast<double>(N));
		}
	}
	// The Euclidean length is the same as the 2-norm
	template<size_t n>
	float length(const Vector<int32_t, n>& v) {

		return std::sqrt(static_cast<float>(dot(v, v)));
	}
	template<typename T, size_t n>
	T length(const Vector<T, n>& v) {

		return T(std::sqrt(dot(v, v)));
	}

	// Squared norm
	// By default normPowered is the same as lengthSquared, but not when choosing
	// an arbitrary norm (p-norm, p != 2)
	template<typename T, size_t n>
	T normPowered(const Vector<T, n>& v, int32_t N) {

		T sum = T(0);
		for (size_t i = 0; i < n; i++)
			sum += static_cast<T>(std::pow(v.components[i], N));
		return sum;
	}
	template<typename T, size_t n>
	T lengthSquared(const Vector<T, n>& v) {

		return T(dot(v, v));
	}


	// Abs
	template<typename T, size_t n>
	Vector<T, n> abs(const Vector<T, n>& v) {

		Vector<T, n> temp = v;
		for (size_t i = 0; i < n; i++) {
			if (temp.components[i] < 0) temp.components[i] *= T(-1);
		}
		return temp;
	}


	// Returns a normalized version of the vector
	// There are special restrictions for integer vectors if the result is to be a
	// vector of integers. Better to cast to float for more expected behaviour.
	template<size_t n>
	Vector<int32_t, n> normalizeInt(const Vector<int32_t, n>& v) {

		// Only one component can be non-zero
		size_t nonzeros = 0, index;
		for (size_t i = 0; i < n; i++) {
			if (v.components[i] != 0) {
				nonzeros++;
				index = i;
			}
		}
		assert(nonzeros == 1);
		Vector<int32_t, n> temp = v;
		temp.components[index] /= abs(temp.components[index]);
		return temp;
	}
	template<size_t n>
	Vector<float, n> normalize(const Vector<int32_t, n>& v) {

		float norm_2 = length(v);
		assert(norm_2 > 0);

		Vector<float, n> temp = v;
		return temp /= norm_2;
	}
	template<typename T, size_t n>
	Vector<T, n> normalize(const Vector<T, n>& v) {

		T norm_2 = length(v);
		assert(norm_2 > 0);

		Vector<T, n> temp = v;
		return temp /= norm_2;
	}

	// Hash function taken from sfzCore: Vector.inl, hashing algorithm is the same
	// as hash_combine from boost
	template<typename T, size_t n>
	size_t hash(const Vector<T, n>& v) noexcept {

		std::hash<T> hasher;
		size_t hash = 0;
		for (size_t i = 0; i < n; i++)
			hash ^= hasher(v.components[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		return hash;
	}


	// Operators
	// =============================================================================

	// Equality
	template<typename T, size_t n>
	bool operator== (const Vector<T, n>& left, const Vector<T, n>& right) {

		for (size_t i = 0; i < n; i++)
			if (left.components[i] != right.components[i]) return false;
		return true;
	}

	// Inequality
	template<typename T, size_t n>
	bool operator!= (const Vector<T, n>& left, const Vector<T, n>& right) {
		return !(left == right);
	}

	// Addition
	template<typename T, size_t n>
	Vector<T, n>& operator+= (Vector<T, n>& left, const Vector<T, n>& right) {

		for (size_t i = 0; i < n; i++)
			left.components[i] += right.components[i];
		return left;
	}
	template<typename T, size_t n>
	Vector<T, n> operator+ (const Vector<T, n>& left, const Vector<T, n>& right) {

		Vector<T, n> temp = left;
		return temp += right;
	}

	// Subtraction
	template<typename T, size_t n>
	Vector<T, n>& operator-= (Vector<T, n>& left, const Vector<T, n>& right) {

		for (size_t i = 0; i < n; i++)
			left.components[i] -= right.components[i];
		return left;
	}
	template<typename T, size_t n>
	Vector<T, n> operator- (const Vector<T, n>& left, const Vector<T, n>& right) {

		Vector<T, n> temp = left;
		return temp -= right;
	}

	// Multiplication with scalar
	template<typename T, size_t n>
	Vector<T, n> operator*= (Vector<T, n>& vector, T scalar) {

		for (size_t i = 0; i < n; i++)
			vector.components[i] *= scalar;
		return vector;
	}
	template<typename T, size_t n>
	Vector<T, n> operator* (const Vector<T, n>& vector, T scalar) {

		Vector<T, n> temp = vector;
		return temp *= scalar;
	}
	template<typename T, size_t n>
	Vector<T, n> operator* (T scalar, const Vector<T, n>& vector) {

		return vector*scalar;
	}

	// Pointwise multiplication
	template<typename T, size_t n>
	Vector<T, n>& operator*= (Vector<T, n>& left, const Vector<T, n>& right) {

		for (size_t i = 0; i < n; i++)
			left.components[i] *= right.components[i];
		return left;
	}
	template<typename T, size_t n>
	Vector<T, n> operator* (const Vector<T, n>& left, const Vector<T, n>& right) {

		Vector<T, n> temp = left;
		return left *= right;
	}

	// Division with scalar
	template<typename T, size_t n>
	Vector<T, n>& operator/= (Vector<T, n>& vector, T scalar) {

		for (size_t i = 0; i < n; i++)
			vector.components[i] /= scalar;
		return vector;
	}
	template<typename T, size_t n>
	Vector<T, n> operator/ (const Vector<T, n>& vector, T scalar) {

		Vector<T, n> temp = vector;
		return temp /= scalar;
	}

	// Indexation (access to vector components)
	//General vector
	template<typename T, size_t n>
	T& Vector<T, n>::operator[] (const size_t index) noexcept {

		assert(index < n);
		return components[index];
	}
	template<typename T, size_t n>
	T Vector<T, n>::operator[] (const size_t index) const noexcept {

		assert(index < n);
		return components[index];
	}
	// 2D vector
	template<typename T>
	T& Vector<T, 2>::operator[] (const size_t index) noexcept {

		assert(index < 2);
		return components[index];
	}
	template<typename T>
	T Vector<T, 2>::operator[] (const size_t index) const noexcept {

		assert(index < 2);
		return components[index];
	}
	// 3D vector
	template<typename T>
	T& Vector<T, 3>::operator[] (const size_t index) noexcept {

		assert(index < 3);
		return components[index];
	}
	template<typename T>
	T Vector<T, 3>::operator[] (const size_t index) const noexcept {

		assert(index < 3);
		return components[index];
	}
	// 4D vector
	template<typename T>
	T& Vector<T, 4>::operator[] (const size_t index) noexcept {

		assert(index < 4);
		return components[index];
	}
	template<typename T>
	T Vector<T, 4>::operator[] (const size_t index) const noexcept {

		assert(index < 4);
		return components[index];
	}

} // namespace sini

// Hasher specialization in std
namespace std {

	template<typename T, size_t n>
	struct hash<sini::Vector<T,n>> {
		size_t operator() (const sini::Vector<T,n>& vector) const { return sini::hash(vector); }
	};
}