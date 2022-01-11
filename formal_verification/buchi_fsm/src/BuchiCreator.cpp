//
// Created by kolek on 09.12.2021.
//
#include <sstream>
#include "fsm.h"
#include "BuchiCreator.h"


using namespace model::ltl;


void AtomsStates::CreateTruthTable(std::vector<std::pair<bool, model::ltl::Formula>> states, size_t idx) {
    if (idx == states.size()) {
        truth_table.push_back(std::move(states));
        return ;
    }
    states[idx].first = false;
    CreateTruthTable(states, idx + 1);

    states[idx].first = true;
    CreateTruthTable(states, idx + 1);
}

AtomsStates::AtomsStates(const std::vector<Formula> &atoms)  {
    std::vector<std::pair<bool, Formula>> states;

    for(size_t i = 0; i < atoms.size(); ++i) {
        switch(atoms[i].kind()) {
            case Formula::ATOM:
                prop_to_idx[atoms[i].prop()] = i;
                break;
            case Formula::X: {
                std::stringstream ss;
                ss << atoms[i];
                prop_to_idx[ss.str()] = i;
                break;
            }
        }
    }

    std::for_each(atoms.begin(), atoms.end(),
                  [&](const Formula& elem) {
        states.push_back({false, elem});
    });


    CreateTruthTable(states, 0);

}


Ltl2Buchi::Ltl2Buchi(model::ltl::Formula formula1) : formula(std::move(formula1)) {
    FindAtoms(formula);
    CreateClosure(formula);
    AtomsStates atomsStates(atoms);
#ifdef DEBUG
    std::cout << "Atoms:\n";
    for (const auto& atom : atoms) {
        std::cout << atom << '\n';
    }
    std::cout << "Closure:\n";
    for (const auto& elem : closure) {
        std::cout << elem << '\n';
    }
    std::cout << "Atoms Truth Table\n";
    for (const auto& atoms_state : atomsStates) {
        for (const auto& [state, atom] : atoms_state) {
            std::cout <<  '{' <<  state  << ' ' << atom << "} ";
        }
        std::cout << '\n';
    }
#endif
    //traverse sub formulas and find unique unitls from simple -> to hard
    //post order traversal


    for (const auto& atoms_state : atomsStates) {
        _connectors.push_back({AddClassicConnectors(atoms_state, atomsStates), State::REGULAR});
    }
    _untils = FindUntils();
    _xs = FindXs();


    AddTempConnectorsAndCreateStates();
    AddInitAndFiniStates();
#ifdef DEBUG
    std::cout << "\nPrinting states after temp connectors saturation:\n";
    size_t idxx = 0;
    for (const auto& connectors : _connectors) {
        std::cout << idxx++ << ": " << connectors.state << " -> ";
        for (const auto & connector : connectors.connectors) {
            std::cout << connector << ", ";
        }
        std::cout << '\n';
    }
#endif


    AddEdges();

#ifdef DEBUG
    std::cout << buchi << '\n';
#endif

}



void Ltl2Buchi::FindAtoms(const Formula& formula1) {
    switch (formula1.kind()) {
        case Formula::ATOM:
            if (formula1.prop() != "true" && !_atoms_set.contains(formula1.prop())) {
                _atoms_set.insert(formula1.prop());
                atoms.push_back(formula1);
            }
            return ;
        case Formula::NOT:
            FindAtoms(formula1.arg());
            return ;
        case Formula::AND:
            FindAtoms(formula1.lhs());
            FindAtoms(formula1.rhs());
            return ;
        case Formula::OR:
            FindAtoms(formula1.lhs());
            FindAtoms(formula1.rhs());
            return ;
        case Formula::IMPL:
            FindAtoms(formula1.lhs());
            FindAtoms(formula1.rhs());
            return ;
        case Formula::X: {
            std::stringstream ss;
            ss << formula1;
            FindAtoms(formula1.arg());
            if (!_atoms_set.contains(ss.str())) {
                _atoms_set.insert(ss.str());
                atoms.push_back(formula1);
            }

            return;
        }
        case Formula::G:
            FindAtoms(formula1.arg());
            return ;
        case Formula::F:
            FindAtoms(formula1.arg());
            return ;
        case Formula::U:
            FindAtoms(formula1.lhs());
            FindAtoms(formula1.rhs());
            return ;
        case Formula::R:
            FindAtoms(formula1.lhs());
            FindAtoms(formula1.rhs());
            return ;
    }
}

void Ltl2Buchi::CreateClosure(const Formula& formula1) {
    switch (formula1.kind()) {
        case Formula::ATOM:
            if (formula1.prop() == "true")
                closure.push_back(formula1);
            return ;
        case Formula::NOT:
            CreateClosure(formula1.arg());
            closure.push_back(formula1);
           // closure.push_back(!formula1);
            return ;
        case Formula::AND:
            CreateClosure(formula1.lhs());
            CreateClosure(formula1.rhs());
            closure.push_back(formula1);
            //closure.push_back(!formula1);
            return ;
        case Formula::OR:
            CreateClosure(formula1.lhs());
            CreateClosure(formula1.rhs());
            closure.push_back(formula1);
          //  closure.push_back(!formula1);
            return ;
        case Formula::IMPL:
            CreateClosure(formula1.lhs());
            CreateClosure(formula1.rhs());
            closure.push_back(formula1);
          //  closure.push_back(!formula1);
            return ;
        case Formula::X:
            CreateClosure(formula1.arg());
            closure.push_back(formula1);
            return ;
        case Formula::G:
            CreateClosure(formula1.arg());
            closure.push_back(formula1);
           // closure.push_back(!formula1);
            return ;
        case Formula::F:

            CreateClosure(formula1.arg());
            closure.push_back(formula1);
           // closure.push_back(!formula1);
            return ;
        case Formula::U:
            CreateClosure(formula1.lhs());
            CreateClosure(formula1.rhs());
            closure.push_back(formula1);
           // closure.push_back(!formula1);
            return ;
        case Formula::R:
            CreateClosure(formula1.lhs());
            CreateClosure(formula1.rhs());
            closure.push_back(formula1);
           // closure.push_back(!formula1);
            return ;
    }

}

bool Ltl2Buchi::isTrueClassic(const model::ltl::Formula &formula1,
                       const std::vector<std::pair<bool, model::ltl::Formula>> &atoms_state,
                       const AtomsStates& atomsStates) {
    switch(formula1.kind()) {
        case Formula::ATOM:
            if (formula1.prop() == "true") {
                return true;
            }
            return atoms_state[atomsStates.GetPropIdx(formula1.prop())].first;
        case Formula::NOT:
            if (formula1.arg().kind() == Formula::U)
                return false;
            return !isTrueClassic(formula1.arg(), atoms_state, atomsStates);
        case Formula::AND:
            return isTrueClassic(formula1.lhs(), atoms_state, atomsStates) &&
                    isTrueClassic(formula1.rhs(), atoms_state, atomsStates);
        case Formula::OR:
            return isTrueClassic(formula1.lhs(), atoms_state, atomsStates) ||
                    isTrueClassic(formula1.rhs(), atoms_state, atomsStates);
        case Formula::IMPL:
            return !isTrueClassic(formula1.lhs(), atoms_state, atomsStates) ||
            isTrueClassic(formula1.rhs(), atoms_state, atomsStates);
        case Formula::X: {
            std::stringstream ss;
            ss << formula1;
            return atoms_state[atomsStates.GetPropIdx(ss.str())].first;
        }
        default:
            return false;

    }
}
//Add Classic and temporal connectors + build states
std::vector<Formula> Ltl2Buchi::AddClassicConnectors(const std::vector<std::pair<bool, model::ltl::Formula>>& atoms_state,
                           const AtomsStates& atomsStates) {

    std::vector<Formula> result;
    for (const auto& atom_state : atoms_state) {
        if (atom_state.first) {

            result.push_back(atom_state.second);
        }
    }


    for (const auto& sub_formula : closure) {
            if (isTrueClassic(sub_formula, atoms_state, atomsStates)) {
                result.push_back(sub_formula);
            }
        }

#ifdef DEBUG
    for (const auto& elem : result) {
        std::cout << elem << ' ';
    }
    std::cout << "\n";
#endif
    return result;
}


std::vector<Formula> Ltl2Buchi::FindUntils() {
    std::vector<Formula> res;

    std::for_each(closure.begin(), closure.end(), [&res](const Formula& elem) {
        if (elem.kind() == Formula::U)
            res.push_back(elem);
    });

    return res;
}

std::vector<Formula> Ltl2Buchi::FindXs() {
    std::vector<Formula> res;

    std::for_each(closure.begin(), closure.end(), [&res](const Formula& elem) {
        if (elem.kind() == Formula::X)
            res.push_back(elem);
    });

    return res;
}

void Ltl2Buchi::AddTempConnectorsAndCreateStates() {


    for (const auto& until : _untils) {
        std::vector<std::vector<Formula>> new_connectors;
        for (auto& connectors : _connectors) {
            auto& vec_con = connectors.connectors;
            auto lhs_found = std::find(vec_con.begin(), vec_con.end(), until.lhs());
            auto rhs_found = std::find(vec_con.begin(), vec_con.end(), until.rhs());
            if (rhs_found != vec_con.end()) {
#ifdef DEBUG
                std::cout << "Add\n";
#endif
                vec_con.push_back(until);
            } else if (lhs_found != vec_con.end()) {
#ifdef DEBUG
                std::cout << "Double" << '\n';
#endif
                std::vector<Formula> new_connector(vec_con);
                new_connector.push_back(until);
                new_connectors.push_back(new_connector);
                vec_con.push_back(!until);
        }

    }
        for (const auto& new_connector : new_connectors)
            _connectors.push_back({new_connector, Ltl2Buchi::REGULAR});

    }

    const std::string label_prefix = "s";
    size_t idx = 0;
    for (auto& connectors : _connectors) {
        connectors.label = label_prefix + std::to_string(idx);
        buchi.add_state(connectors.label);
        idx++;
    }

}

void Ltl2Buchi::AddInitAndFiniStates() {
    const std::string label_prefix = "s";


    for (auto& connectors : _connectors) {
        const auto &connectors_var_i = connectors.connectors;
        if (std::find(connectors_var_i.begin(), connectors_var_i.end(), formula) != connectors_var_i.end()) {
            connectors.state = Ltl2Buchi::INIT;
            buchi.set_initial(connectors.label);
        }
    }
    size_t fini_idx = 1;
    for (const auto& until : _untils) {
        for (auto& connectors : _connectors) {
            const auto& connectors_var_i = connectors.connectors;
            if (std::find(connectors_var_i.begin(), connectors_var_i.end(), until.rhs()) != connectors_var_i.end() ||
                    std::find(connectors_var_i.begin(), connectors_var_i.end(), until) == connectors_var_i.end() ||
                    std::find(connectors_var_i.begin(), connectors_var_i.end(), !until) != connectors_var_i.end()) {
                connectors.state = Ltl2Buchi::FINI;
                buchi.set_final(connectors.label, fini_idx);
            }
        }
        fini_idx++;
    }
}


void Ltl2Buchi::AddEdges() {
#ifdef DEBUG
    std::cout << "Print transitions\n";
#endif
    size_t idx = 0;
    for (auto &connectors_i: _connectors) {
        const auto &connectors_var = connectors_i.connectors;
        std::vector<Formula> transitions;
        //analyze for untils
        for (const auto &until: _untils) {
            bool u_present = std::find(connectors_var.begin(),
                                       connectors_var.end(),
                                       until) != connectors_var.end();
            bool u_rhs_present = std::find(connectors_var.begin(),
                                           connectors_var.end(),
                                           until.rhs()) != connectors_var.end();
            bool u_lhs_present = std::find(connectors_var.begin(),
                                           connectors_var.end(),
                                           until.lhs()) != connectors_var.end();

            if (u_present && u_lhs_present && !u_rhs_present) {
                transitions.push_back(until);
            } else if (!u_present && !u_rhs_present && u_lhs_present)
                transitions.push_back(!until);
        }
        //analyze for X
        for (const auto& x : _xs) {
            bool x_present = std::find(connectors_var.begin(),
                                       connectors_var.end(),
                                       x) != connectors_var.end();
            if (x_present) {
                transitions.push_back(x.arg());
            } else {
                transitions.push_back(!x.arg());
            }
        }

        connectors_i.transitions = std::move(transitions);
#ifdef DEBUG
        std::cout << idx++ << ": ";
        if (connectors_i.transitions.empty()) {
            std::cout << "any";
        }
        for (const auto& transition : connectors_i.transitions) {
            std::cout << transition << ' ';
        }
        std::cout << '\n';
#endif
    }

    for (const auto& connectors_i : _connectors) {
        for (const auto& connectors_j : _connectors) {

            if (std::all_of(connectors_i.transitions.begin(), connectors_i.transitions.end(),
                            [&connectors_j](const Formula& formula1) {
                bool try_reverse = false;
                if (formula1.kind() == Formula::NOT) {
                    try_reverse = std::find(connectors_j.connectors.begin(),
                                     connectors_j.connectors.end(), formula1.arg())
                                     == connectors_j.connectors.end();
                }
                return try_reverse || std::find(connectors_j.connectors.begin(),
                                 connectors_j.connectors.end(), formula1)
                                 != connectors_j.connectors.end();
            })) {
                std::set<std::basic_string<char>> symbols;
                std::for_each(connectors_i.connectors.begin(), connectors_i.connectors.end(),
                              [&symbols](const Formula& formula1) {
                    if (formula1.kind() == Formula::ATOM && formula1.prop() != "true") {
                        symbols.insert(formula1.prop());
                    }
                });
                buchi.add_trans(connectors_i.label, symbols, connectors_j.label);
            }

        }
    }


}

model::fsm::Automaton Ltl2Buchi::getAutomaton() {
    return buchi;
}
