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


#include "fsm.h"
#include "BuchiCreator.h"


using namespace model::ltl;
using namespace model::fsm;
using std::vector;
using std::shared_ptr;

const Formula &simplify(const Formula &f) {
    if (f.kind() == Formula::G) {
        return !U(P("true"), (simplify(!f.lhs())));
    } else if (f.kind() == Formula::F) {
        const Formula &s = simplify(f.lhs());
        return U(P("true"), s);
    } else if (f.kind() == Formula::R) {
        return !U(simplify(!f.lhs()), simplify(!f.rhs()));
    } else if (f.kind() == Formula::X && f.lhs().kind() == Formula::NOT) {
        const Formula &s = simplify(f.lhs().lhs());
        return !X(s);
    } else if (f.kind() == Formula::X && f.lhs().kind() == Formula::OR) {
        return X(simplify(f.lhs().lhs())) || X(simplify(f.lhs().rhs()));
    } else if (f.kind() == Formula::X) {
        const Formula &s = simplify(f.lhs());
        if (s.kind() == Formula::NOT)
            return !X(s.lhs());
        else
            return X(s);
    } else if (f.kind() == Formula::OR) {
        return simplify(f.lhs()) || simplify(f.rhs());
    } else if (f.kind() == Formula::AND) {
        return simplify(f.lhs()) && simplify(f.rhs());
    } else if (f.kind() == Formula::IMPL) {
        return simplify(f.lhs()) >> simplify(f.rhs());
    } else if (f.kind() == Formula::U) {
        return U(simplify(f.lhs()), simplify(f.rhs()));
    } else if (f.kind() == Formula::NOT) {
        return !simplify(f.lhs());
    }
    return f;
}



void process(const Formula& formula, Automaton& automaton) {
    const Formula& simplified_formula = simplify(formula);
    std::cout << "Formula: " << std::endl;
    std::cout << simplified_formula << std::endl << std::endl;
    Ltl2Buchi converter(simplified_formula);

    automaton = converter.getAutomaton();
}

int main() {

    //const Formula &formula = U(P("p") || P("q"), P("p") && P("q"));
    const Formula &formula = U(P("p") && !X(P("q")), P("p") && P("q"));


    Automaton buchi;
    process(formula, buchi);
    std::cout << buchi << '\n';

    return 0;
}

