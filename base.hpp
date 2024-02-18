#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <memory>
#include <unordered_map>
#include <any>
#include <cstdint>

class string: public std::string_view {
	public:
		using std::string_view::string_view;
		const char at(int64_t index) const {
			if(index < 0) {
				index += static_cast<int64_t>(size());
			}
			if(index < 0 || index >= size()) { throw std::runtime_error("Index " + std::to_string(index) +  " out of bounds for size " + std::to_string(size())); }
			return std::string_view::at(index);
		}
};

namespace vnd {
	template <typename T, int64_t N>
	class array: public std::array<T, N> {
		public:
			array(): std::array<T, N>() {};
			array(const std::vector<T>& vec) {
				if (vec.size() == N) {
					std::copy(vec.begin(), vec.end(), this->begin());
				} else {
					throw std::invalid_argument("Vector size does not match array size");
				}
			}
			array(std::initializer_list<T> init) : std::array<T, N>() {
				if (init.size() != N) {
					throw std::runtime_error("Initializer list size does not match array size.");
				}
				std::copy(init.begin(), init.end(), this->begin());
			}
			T& at(int64_t index) {
				if(index < 0) {
					index += N;
				}
				if(index < 0 || index >= N) { throw std::runtime_error("Index " + std::to_string(index) +  " out of bounds for size " + std::to_string(N)); }
				return std::array<T, N>::at(index);
			}
			const T& at(int64_t index) const {
				if(index < 0) {
					index += N;
				}
				if(index < 0 || index >= N) { throw std::runtime_error("Index " + std::to_string(index) +  " out of bounds for size " + std::to_string(N)); }
				return std::array<T, N>::at(index);
			}
	};
	template <typename T>
	class vector: public std::vector<T> {
		public:
			vector(): std::vector<T>() {};
			vector(std::initializer_list<T> init) : std::vector<T>(init) {}
			template <typename InputIt>
			vector(InputIt first, InputIt last) : std::vector<T>(first, last) {}
			T& at(int64_t index) {
				if(index < 0) {
					index += static_cast<int64_t>(this->size());
				}
				if(index < 0 || index >= static_cast<int64_t>(this->size())) { throw std::runtime_error("Index " + std::to_string(index) +  " out of bounds for size " + std::to_string(static_cast<int64_t>(this->size()))); }
				return std::vector<T>::at(index);
			}
			const T& at(int64_t index) const {
				if(index < 0) {
					index += static_cast<int64_t>(this->size());
				}
				if(index < 0 || index >= static_cast<int64_t>(this->size())) { throw std::runtime_error("Index " + std::to_string(index) +  " out of bounds for size " + std::to_string(static_cast<int64_t>(this->size()))); }
				return std::vector<T>::at(index);
			}
	};
	std::unordered_map<std::string, std::any> tmp;
}

int v_test() { return 0; }
int _testPar(int a, int b) { return a + b; }
size_t _testPar(string s) { return s.size(); }
class Object {
	public:
		int getC() { return c; };
		int getA() { return a; };
		void setA(int _a) { a = _a; };
		float getTest() { return test; }
		string getS() { return s; }
		void setS(string _s) { s = _s; }
		float f(double b) { return std::pow(b, 2); }
		std::string fs() { return std::string(); }
	private:
		const int c = 2;
		const float test = 0;
		int a;
		string s;
};
class Derived: public Object {
	public:
		Derived(): obj(std::make_shared<Object>()) {}
		Derived(std::shared_ptr<Object> _obj, bool derivedProperty): _derivedProperty(derivedProperty), obj(std::make_shared<Object>()) {}
		bool get_derivedProperty() { return _derivedProperty; }
		void set_derivedProperty(bool derivedProperty) { _derivedProperty = derivedProperty; }
		std::shared_ptr<Object> getObj() { return obj; }
		void setObj(std::shared_ptr<Object> _obj) { obj = _obj; }
		bool get_derivedConst() { return _derivedConst; }
		bool derivedFun(std::shared_ptr<Object> obj) { return obj->getS().empty(); }
		std::shared_ptr<Object> object() { return std::make_shared<Object>(); }
	private:
		const bool _derivedConst = true;
		bool _derivedProperty;
		std::shared_ptr<Object> obj;
};
std::shared_ptr<Object> _createObject() { return std::make_shared<Object>(); }
std::shared_ptr<Derived> _createDerived() { return std::make_shared<Derived>(); }