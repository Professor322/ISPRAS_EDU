/*
 * Copyright 2021 ISP RAS (http://www.ispras.ru)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

#include "ltl.h"

namespace model::ltl {
    const bool Formula::equality_internal(const Formula &lhs, const Formula &rhs) const {
        if (lhs.kind() != rhs.kind()) {
            return false;
        }
        switch(lhs.kind()) {
            case ATOM:
                return lhs.prop() == rhs.prop();
            case NOT:
                return equality_internal(lhs.arg(), rhs.arg());
            case AND:
            case OR:
            case IMPL:
                return equality_internal(lhs.lhs(), rhs.lhs()) &&
                        equality_internal(lhs.rhs(), rhs.rhs());
            case X:
            case G:
            case F:
                return equality_internal(lhs.arg(), rhs.arg());
            case U:
            case R:
                return equality_internal(lhs.lhs(), rhs.lhs()) &&
                       equality_internal(lhs.rhs(), rhs.rhs());

        }
        return false;
    }

    const bool Formula::operator==(const Formula &rhs) const {
        return equality_internal(*this, rhs);
    }

std::ostream& operator <<(std::ostream &out, const Formula &formula) {
  switch (formula.kind()) {
  case Formula::ATOM:
    return out << formula.prop();
  case Formula::NOT:
    return out << "!(" << formula.arg() << ")";
  case Formula::AND:
    return out << "(" << formula.lhs() << ") && (" << formula.rhs() << ")";
  case Formula::OR:
    return out << "(" << formula.lhs() << ") || (" << formula.rhs() << ")";
  case Formula::IMPL:
    return out << "(" << formula.lhs() << ") -> (" << formula.rhs() << ")";
  case Formula::X:
    return out << "X(" << formula.arg() << ")";
  case Formula::G:
    return out << "G(" << formula.arg() << ")";
  case Formula::F:
    return out << "F(" << formula.arg() << ")";
  case Formula::U:
    return out << "(" << formula.lhs() << ") U (" << formula.rhs() << ")";
  case Formula::R:
    return out << "(" << formula.lhs() << ") R (" << formula.rhs() << ")";
  }

  return out;
}

} // namespace model::ltl
