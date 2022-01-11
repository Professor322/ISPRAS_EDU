//
// Created by kolek on 09.12.2021.
//

#ifndef BUCHI_FSM_BUCHICREATOR_H
#define BUCHI_FSM_BUCHICREATOR_H

#include "fsm.h"
#include "ltl.h"
#include <algorithm>
#include <tuple>
#include <set>
#include <unordered_map>
#include <list>



class AtomsStates final {
private:
    using atoms_state = std::vector<std::pair<bool, model::ltl::Formula>>;
    std::vector<atoms_state> truth_table;
    std::unordered_map<std::string, size_t> prop_to_idx;

    void CreateTruthTable(std::vector<std::pair<bool, model::ltl::Formula>> states, size_t idx);
public:
    AtomsStates() = default;
    AtomsStates(const std::vector<model::ltl::Formula>& atoms);

    size_t GetPropIdx(const std::string& prop) const { return prop_to_idx.at(prop); }
    auto begin() const { return truth_table.begin(); }
    auto end() const {return truth_table.end(); }
};


class Ltl2Buchi final {

private:
    enum State {
        REGULAR,
        FINI,
        INIT
    };
    struct saturation {
        std::vector<model::ltl::Formula> connectors;
        Ltl2Buchi::State state;
        std::vector<model::ltl::Formula> transitions;
        std::string label;
    };

    model::ltl::Formula formula;
    std::vector<model::ltl::Formula> atoms;
    std::set<std::string> _atoms_set;
    std::vector<model::ltl::Formula> closure;
    std::list<saturation> _connectors;
    std::vector<model::ltl::Formula> _untils;
    std::vector<model::ltl::Formula> _xs;
    model::fsm::Automaton buchi;

    bool isTrueClassic(const model::ltl::Formula& formula1,
            const std::vector<std::pair<bool, model::ltl::Formula>>& atoms_state,
            const AtomsStates& atomsStates);
    void FindAtoms(const model::ltl::Formula& formula);
    void CreateClosure(const model::ltl::Formula& formula);
    std::vector<model::ltl::Formula> AddClassicConnectors(const std::vector<std::pair<bool, model::ltl::Formula>>& atoms_state,
                                                          const AtomsStates& atomsStates);
    void AddTempConnectorsAndCreateStates();
    void AddInitAndFiniStates();
    void AddEdges();
    std::vector<model::ltl::Formula> FindUntils();
    std::vector<model::ltl::Formula> FindXs();
public:
    Ltl2Buchi(model::ltl::Formula formula);
    model::fsm::Automaton getAutomaton();
};



#endif //BUCHI_FSM_BUCHICREATOR_H
