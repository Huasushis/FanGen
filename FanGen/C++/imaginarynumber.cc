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
#include "imaginarynumber.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

// The realization of SuperInt
SuperInt::SuperInt(const ull &length, const bool &is_signed)
    : length_(MAX(length, 2)), is_signed_(is_signed) {
    num_ = new ull[length];
    for (ull i = 0; i < length; ++i) {
        num_[i] = 0;
    }
}

SuperInt::SuperInt(const SuperInt &num) {
    num_ = new ull[num.length_];
    length_ = num.length_;
    is_signed_ = num.is_signed_;
    for (ull i = 0; i < length_; ++i) {
        num_[i] = num.num_[i];
    }
}

SuperInt::SuperInt(const SuperInt &num, ull changed_length) {
    if (changed_length < num.length_) {
        changed_length = num.length_;
    }
    num_ = new ull[changed_length];
    length_ = changed_length;
    is_signed_ = num.is_signed_;
    for (ull i = 0; i < changed_length - num.length_; ++i) {
        num_[i] = 0;
    }
    for (ull i = 0; i < num.length_; ++i) {
        num_[i + changed_length - num.length_] = num.num_[i];
    }
    if (is_signed_) {
        if (num.num_[0] & (1ull << 63)) {
            num_[changed_length - num.length_] ^= (1ull << 63);
            num_[0] |= (1ull << 63);
        }
    }
}

SuperInt::SuperInt(const ull &length, const bool &is_signed,
                           const ull &value)
    : length_(MAX(length, 2)), is_signed_(is_signed) {
    num_ = new ull[length_];
    for (ull i = 0; i < length_; ++i) {
        num_[i] = 0;
    }
    for (ull i = 0; i < length_; ++i) {
        num_[i] = 0;
    }
    if (value & (1ull << 63) && is_signed_) {
        num_[0] = (1ull << 63);
    }
    num_[length_ - 1] = value ^ ((value >> 32) << 32);
    num_[length_ - 2] = (unsigned int)(value >> 32);
    if (is_signed_) {
        num_[length_ - 2] ^= (unsigned int)((value >> 63) << 31);
    }
}

SuperInt::~SuperInt() {
    delete[] num_;
    num_ = 0;
}

// add function
SuperInt operator+(const fangen::SuperInt &num1,
                           const fangen::SuperInt &num2) {
    fangen::SuperInt sum_number(MAX(num1.length_, num2.length_),
                                num1.is_signed_ | num2.is_signed_);
    for (ull i = sum_number.length_ - 1; i >= 0; --i) {
        sum_number.num_[i] = num1.num_[i] + num2.num_[i];
        if (i) {
            sum_number.num_[i - 1] |= (sum_number.num_[i] >> 32);
        }
        sum_number.num_[i] ^= ((sum_number.num_[i] >> 32) << 32);
    }
    return sum_number;
}

/*fangen::SuperInt operator-(const fangen::SuperInt &num1,
                           const fangen::SuperInt &num2) {
  fangen::SuperInt opposite_number(num2);
  const fangen::SuperInt tmp_number(num2.length_, 0, 1);
  opposite_number = num2;
  for (ull i = 0; i < opposite_number.length_; ++i) {
    opposite_number.num_[i] = ~opposite_number.num_[i];
  }
  const fangen::SuperInt const_opposite_number(opposite_number);
  opposite_number = const_opposite_number + tmp_number;
  const fangen::SuperInt ans_opposite_number(opposite_number);
  //fangen::SuperInt tmpnum1;
  return num1 + ans_opposite_number;
  return num1 + num2;
}*/

// The basic high accuracy template
// So no more description.

// The realization of SuperFloat
SuperFloat::SuperFloat() {
    base = new ull[BASE_SIZE];
    exponent = new ull[EXPONENT_SIZE];
    for (int i = 0; i < BASE_SIZE; ++i) {
        base[i] = 0;
    }

    for (int i = 0; i < EXPONENT_SIZE; ++i) {
        exponent[i] = 0;
    }
}

SuperFloat::SuperFloat(const fangen::SuperFloat &num) {
    base = new ull[BASE_SIZE];
    exponent = new ull[EXPONENT_SIZE];
    for (int i = 0; i < BASE_SIZE; ++i) {
        base[i] = num.base[i];
    }

    for (int i = 0; i < EXPONENT_SIZE; ++i) {
        exponent[i] = num.exponent[i];
    }
}

SuperFloat::SuperFloat(const long long &num) {
    base = new ull[BASE_SIZE];
    exponent = new ull[EXPONENT_SIZE];
    for (int i = 0; i < BASE_SIZE; ++i) {
        base[i] = 0;
    }
    for (int i = 0; i < EXPONENT_SIZE; ++i) {
        exponent[i] = 0;
    }
    base[0] = num;
}

// Xigou Function
SuperFloat::~SuperFloat() {
    delete[] base;
    delete[] exponent;
    base = 0;
    exponent = 0;
}

