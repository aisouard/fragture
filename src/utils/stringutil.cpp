#include <vector>
#include "public/ustring.h"
#include "utils/stringutil.h"

using Public::UStringIterator;

namespace Utils {
void StringUtil::Concat(const UStringVector &input, const UString &glue, UString &output) {
  UStringVector::const_iterator it = input.begin();

  while (it != input.end()) {
    output.append((*it));

    if (++it != input.end()) {
      output.append(glue);
    }
  }
}

void StringUtil::Tokenize(const UString &str, UStringVector &output) {
  UString word;
  UStringIterator iterator(str);

  while (iterator.hasNext()) {
    UChar c = iterator.current();

    if (c == ' ') {
      if (word.length()) {
        output.push_back(word);
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
    output.push_back(word);
  }
}
}
