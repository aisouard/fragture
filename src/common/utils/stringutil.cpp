/*
 * Copyright 2018 Axel Isouard <axel@isouard.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <vector>
#include "common/types/ustring.h"
#include "common/utils/stringutil.h"

using Common::Types::UString;
using Common::Types::UStringIterator;
using Common::Types::UStringVector;

namespace Common {
namespace Utils {
void StringUtil::Concat(const UStringVector &input, const UString &glue,
                        UString *output) {
  UStringVector::const_iterator it = input.begin();

  while (it != input.end()) {
    output->append((*it));

    if (++it != input.end()) {
      output->append(glue);
    }
  }
}

void StringUtil::Tokenize(const UString &str, UStringVector *output) {
  UString word;
  UStringIterator iterator(str);

  while (iterator.hasNext()) {
    UChar c = iterator.current();

    if (c == ' ') {
      if (word.length()) {
        output->push_back(word);
        word.remove();
      }

      iterator.next();
      continue;
    }

    if (c == '\\') {
      switch (iterator.next()) {
        case '"':
          word.append('"');
          break;
        default:
          break;
      }

      iterator.next();
      continue;
    }

    if (c == '"') {
      iterator.next();

      while (iterator.hasNext()) {
        if (iterator.current() == '"') {
          break;
        }

        if (iterator.current() == '\\') {
          switch (iterator.next()) {
            case '"':
              word.append('"');
              break;
            default:
              break;
          }

          continue;
        }

        word.append(iterator.current());
        iterator.next();
      }
      continue;
    }

    word.append(c);
    iterator.next();
  }

  if (word.length()) {
    output->push_back(word);
  }
}
}  // namespace Utils
}  // namespace Common
