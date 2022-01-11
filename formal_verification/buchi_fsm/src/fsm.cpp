//
// Created by kolek on 18.12.2021.
//

#include "fsm.h"

namespace model::fsm {

    std::ostream &operator<<(std::ostream &out, const State &state) {
        out << state.label();
      //  if (!state.sub_formulas().empty()) {
      ///      for (const auto& sub_formula : state.sub_formulas()) {
      ///          out << sub_formula << ' ';
      ///      }
       // }
       return out;
    }

    std::ostream &operator<<(std::ostream &out, const Transition &transition) {
        out << transition.source();
        out << " --[";

        bool separator = false;
        for (auto i = transition.symbol().begin(); i != transition.symbol().end(); i++) {
            out << (separator ? ", " : "") << *i;
            separator = true;
        }

        out << "]--> ";
        out << transition.target();

        return out;
    }

    void Automaton::add_state(const std::string &state_label) {
        State state(state_label);
        _states.insert({state_label, state});
    }

    void Automaton::add_state(const std::string &state_label,
                                     std::vector<model::ltl::Formula> sub_formulas) {
        State state(state_label, std::move(sub_formulas));
        _states.insert({state_label, state});
    }

    void Automaton::set_initial(const std::string &state_label) {
        _initial_states.insert(state_label);
    }

    void Automaton::set_final(const std::string &state_label, unsigned final_set_index) {
        _final_states[final_set_index].insert(state_label);
    }

    std::ostream& operator <<(std::ostream &out, const Automaton &automaton) {
        bool separator;

        //for (const auto& [label, state] : automaton._states) {
        //    out << label << ' ';
       // }
       // out << '\n';
        out << "S0 = {";

        for (const auto &state: automaton._initial_states) {
            out << (separator ? ", " : "") << state;
            separator = true;
        }
        out << "}" << std::endl;

        for (const auto &entry: automaton._final_states) {
            out << "F" << entry.first << " = {";
            separator = false;
            for (const auto &state: entry.second) {
                out << (separator ? ", " : "") << state;
                separator = true;
            }
            out << "}" << std::endl;
        }

        out << "T = {" << std::endl;
        separator = false;
        for (const auto &entry: automaton._transitions) {
            for (const auto &transition: entry.second) {
                out << (separator ? "\n" : "") << "  " << transition;
                separator = true;
            }
        }
        out << std::endl << "}";

        return out;
    }

}