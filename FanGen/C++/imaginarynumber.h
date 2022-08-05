/*
Copyright 2022 the FanGen Athor(s). All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef FANGEN_IMAGINARYNUMBER_H_
#define FANGEN_IMAGINARYNUMBER_H_
#define EXPONENT_SIZE 32
#define BASE_SIZE 224
typedef unsigned long long ull;
typedef long long ll;
namespace fangen{
//High accuracy integer
//Nothing special
class SuperInt{
 public:
  ull *num_;
  ull length_;
  bool is_signed_;
  //(de)Constructor function.
  SuperInt(const ull& length, const bool& is_signed);
  SuperInt(const SuperInt& num);
  SuperInt(const SuperInt& num, ull changed_length);
  SuperInt(const ull& length, const bool& is_signed, const ull& value);
  ~SuperInt();
  //counting part
  //Two object operator
  friend SuperInt operator+(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator-(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator*(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator/(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator%(const SuperInt &,
                            const SuperInt &);
  //One object operator
  SuperInt operator+();
  SuperInt operator-();
  //Self add/subtract operator
  SuperInt& operator++();
  const SuperInt operator++(int);
  SuperInt& operator--();
  const SuperInt operator--(int);
  //giving value operator
  friend SuperInt& operator+=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator-=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator*=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator/=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator%=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator&=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator|=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator^=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator<<=(SuperInt &,
                              const SuperInt &);
  friend SuperInt& operator>>=(SuperInt &,
                              const SuperInt &);
  SuperInt& operator=(const SuperInt& num) {
    for (ull i = 0; i < this->length_; ++i) {
      this->num_[i] = num.num_[i];
    }
    return *this;
  }
  SuperInt& operator=(const ll& num) {
    for (ull i = 0; i < this->length_; ++i) {
      this->num_[i] = 0;
    }
    if (num < 0 && is_signed_) {
      this->num_[0] = (1ull << 63);
    }
    this->num_[this->length_ - 1] = num ^ ((num >> 32) << 32);
    this->num_[this->length_ - 2] = (unsigned int)(num >> 32) ^
                                  (unsigned int)((num >> 63) << 31);
    return *this;
  }
  //relation operator
  friend bool operator==(const SuperInt &,
                         const SuperInt &);
  friend bool operator!=(const SuperInt &,
                         const SuperInt &);
  friend bool operator<(const SuperInt &,
                        const SuperInt &);
  friend bool operator>(const SuperInt &,
                        const SuperInt &);
  friend bool operator<=(const SuperInt &,
                         const SuperInt &);
  friend bool operator>=(const SuperInt &,
                         const SuperInt &);
  //Position operator
  friend SuperInt operator^(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator|(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator&(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator~(const SuperInt &);
  friend SuperInt operator<<(const SuperInt &,
                            const SuperInt &);
  friend SuperInt operator>>(const SuperInt &,
                            const SuperInt &);
};
//Bigger float number.
//Use it just like float.
//Can't print the num.
class SuperFloat{
 public:
  //Basic part
  ull *base;
  ull *exponent;
  //The constructor function.
  SuperFloat();
  SuperFloat(const long long& num);
  SuperFloat(const SuperFloat& num);
  //The destructor function.
  ~SuperFloat();
  //Basic counting operation
  friend SuperFloat operator+(const SuperFloat &,
                              const SuperFloat &);
  friend SuperFloat operator-(const SuperFloat &,
                              const SuperFloat &);
  friend SuperFloat operator*(const SuperFloat &,
                              const SuperFloat &);
  friend SuperFloat operator/(const SuperFloat &,
                              const SuperFloat &);
  SuperFloat& operator=(const SuperFloat& num) {
    for (int i = 0; i < EXPONENT_SIZE; ++i) {
      this->exponent[i]=num.exponent[i];
    }
    for (int i = 0; i < BASE_SIZE; ++i) {
      this->base[i]=num.base[i];
    }
    return *this;
  }
  friend bool operator==(const SuperFloat &,
                         const SuperFloat &);
  friend bool operator!=(const SuperFloat &,
                         const SuperFloat &);
  friend bool operator<(const SuperFloat &,
                        const SuperFloat &);
  friend bool operator>(const SuperFloat &,
                        const SuperFloat &);
  friend bool operator<=(const SuperFloat &,
                         const SuperFloat &);
  friend bool operator>=(const SuperFloat &,
                         const SuperFloat &);
};
//Compare the size of two exponents.
inline int CompareExponent(bool* exponent1, bool* exponent2);
//Other more senior operation of SuperFloat
inline SuperFloat abs(SuperFloat num);
SuperFloat SuperPow(SuperFloat base, SuperFloat exponent);
SuperFloat SuperLog(SuperFloat num);  //logs base e

//Get a random number of SuperFloat
static int base_random_num = 214332;
SuperFloat Rand();
//affect the result of the next random number
//Can run this function at any time.
void AffectRand(SuperFloat affect_num);
//The class of the imaginary number
//Example:
//  ImaginaryNumber num1(angle,length);
//  ImaginaryNumber num3=1;
//  num1=1+num1;
//  ...
//The operation of imaginary number is almost the same as original number
//  like int,double.
//Notice: Can't compare imaginary number's size!
class ImaginaryNumber{
 private:
  
};
}

#endif