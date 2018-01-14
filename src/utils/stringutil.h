#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include "public/ustring.h"

using Public::UString;
using Public::UStringVector;

namespace Utils {
class StringUtil {
public:
  static void Concat(const UStringVector &input, const UString &glue, UString &output);
  static void Tokenize(const UString &str, UStringVector &output);
};
}

#endif //STRINGUTIL_H
