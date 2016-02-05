#include <string.h>
#include "circuit.h"
#include <boost/algorithm/string.hpp>

#define toDigit(c) (c - '0')    // Convert character of digit to a number


Circuit::Circuit()
        :gates(), inputs(), outputs()
{
}

Circuit::~Circuit(){        // virtual is a class define
}


// to read the the bench_files

int Circuit::readBenchFile(std::string filename){
    std::ifstream input_file;
    input_file.open(filename);
    if(input_file.fail())
    {
        return 1;
    }
    std::string line;
    while(std::getline(input_file, line)){
        saveGates(parse(line));
    }

    input_file.close();

    createWires();

    return 0;
}


Node* Circuit::getNode(unsigned int i) const{
    return nullptr;
}

// Set the states of the input Nodes.
int Circuit::setInputs(const std::string& inputstring){
    unsigned int i = 0;
    for(char c : inputstring){
        if(isdigit(c)){
            inputs.at(i)->setState(toDigit(c));
            i++;
        }
    }
    return 0;
}


// Get the names of all gates (separated by ";")
std::string Circuit::getGateNames(){
    std::string gate_names = "";
    for (unsigned int i = 0; i < gates.size(); ++i) {
        gate_names += gates.at(i)->getName() + ";";
    }
    return gate_names;
}

// Get the state values of all gates and add them to one string.
// (e.g. "0010010")
std::string Circuit::getGateStates() const{
    std::string gate_states = "";
    for (unsigned int i = 0; i < gates.size(); ++i) {
        gate_states += std::to_string(gates.at(i)->getState());
    }
    return gate_states;
}
std::string Circuit::getOutputNames() const{
    std::string output_names = "";
    for (unsigned int i = 0; i < outputs.size() ; ++i) {
        output_names += outputs.at(i)->getName() + ";";
    }
    return output_names;
}
std::string Circuit::getOutputStates() const{
    std::string output_states = "";
    for (unsigned int i = 0; i < outputs.size(); ++i) {
        output_states += std::to_string(outputs.at(i)->getState());
    }
    return output_states;
}
std::string Circuit::getInputNames() const{
    std::string input_names = "";
    for (unsigned int i = 0; i < inputs.size(); ++i) {
        input_names += inputs.at(i)->getName() + ";";
    }
    return input_names;
}
std::string Circuit::getInputStates() const{
    std::string input_states = "";
    for (unsigned int i = 0; i < inputs.size(); ++i) {
        input_states += std::to_string(inputs.at(i)->getState());
    }
    return input_states;
}

// Create an input node with name "name" and return the pointer to it.
Node* Circuit::addInput(const std::string& name){
    Node *input_node;
    input_node = new Node(INPUT, name);
    inputs.push_back(input_node);
    return input_node;
}

// Create an output node with name "name" and return the pointer to it.
Node* Circuit::addOutput(const std::string& name){
    Node *output_node;
    output_node = new Node(OUTPUT, name);
    outputs.push_back(output_node);
    return output_node;
}

// Create a new node of type t and name "name" and return the pointer to it.
Node* Circuit::addGate(TGate t, const std::string& name){
    Node *gate_node;
    gate_node = new Node(t, name);
    gates.push_back(gate_node);
    return gate_node;
}

// Connects the output of the first Node to the input of the second Node.
void Circuit::addWire(Node* output, Node* input){
    Wire *new_wire;
    new_wire = new Wire(output, input);
    input->addInput(new_wire);
    output->addOutput(new_wire);
}

// Connect the output with name A.
void Circuit::addWire(const std::string& output, const std::string& input){
}

// Update the results of all gates and outputs with the currently assigned
// inputs
void Circuit::eval(){
    for (unsigned int i = 0; i < sorted_gates.size(); ++i) {
        sorted_gates.at(i)->eval();
    }

}

// Topological sorting (for the mixed circuits)
void Circuit::topologicalSort(){
    for (unsigned int k = 0; k < inputs.size(); ++k) {
        inputs.at(k)->setSorted(false);
    }
    for (unsigned int k = 0; k < outputs.size(); ++k) {
        outputs.at(k)->setSorted(false);
    }
    for (unsigned int k = 0; k < gates.size(); ++k) {
        gates.at(k)->setSorted(false);
    }

    for (unsigned int j = 0; j < outputs.size() ; ++j) {
        DFS(outputs.at(j));
    }
}

// Alphabetical sorting (for the mixed circuits)
void Circuit::sortInputs(){
    std::sort(inputs.begin(), inputs.end(), sortNodes);
}

// Alphabetical sorting (for the mixed circuits)
void Circuit::sortOutputs(){
    std::sort(outputs.begin(), outputs.end(), sortNodes);
}

// Remove white spaces at the start and end of str
std::string Circuit::trim(std::string &str) {
    if(str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}

// To upper case
void Circuit::toUpper(const std::string &str){
}

// Split a string by the delimiter and return the array of split parts.
std::vector<std::string> Circuit::splitString(const std::string& str, char delim){
    std::vector<std::string> s;
    s.push_back("S");
    return s;
}

//avoiding comments and spaces in the bench file
std::string Circuit::stripCommentAndSpace(std::string &str) {
    size_t position;
    position = str.find_first_of("#");
    if(position <= str.length())
        str.erase(position, str.length());
//    std::cout<<position << std::endl;
// the following statements are used to remove spaces in bench files
    std::string temp = trim(str);
    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
    return temp;
}


// Parse bench file to read inputs, outputs, and gates
std::vector<std::string> Circuit::parse(std::string &str) {
    std::vector<std::string> v;
    std::string temp = stripCommentAndSpace(str);
    boost::split(v, temp, boost::is_any_of("=,()"));

    return v;
}

// Save gate objects <name, object> to create wires later.
int Circuit::saveGates(std::vector<std::string> vec) {
    if (vec.size() == 3){
        if (boost::iequals(vec.at(0), "INPUT")){
            input_names.insert(std::pair<std::string, Node*>(vec.at(1), addInput(vec.at(1))));
        }
        else if (boost::iequals(vec.at(0), "OUTPUT")){
            output_names.insert(std::pair<std::string, Node*>(vec.at(1), addOutput(vec.at(1))));
        }
    }
    else if (vec.size() > 3){
        TGate t_gate = UNDEFINED;
        if (boost::iequals(vec.at(1), "AND"))
            t_gate = AND;
        else if (boost::iequals(vec.at(1), "NAND"))
            t_gate = NAND;
        else if (boost::iequals(vec.at(1), "OR"))
            t_gate = OR;
        else if (boost::iequals(vec.at(1), "NOR"))
            t_gate = NOR;
        else if (boost::iequals(vec.at(1), "NOT"))
            t_gate = NOT;
        else if (boost::iequals(vec.at(1), "XOR"))
            t_gate = XOR;

        std::vector<std::string> params;
        for (unsigned int i = 2; i < vec.size(); ++i) {
            if (!vec.at(i).empty()){
                params.push_back(vec.at(i));
            }
        }

        std::map<Node*, std::vector<std::string>> inner;
        inner.insert(std::pair<Node*, std::vector<std::string>>(addGate
                                                                        (t_gate, vec.at(0)), params));

        gate_names.insert(std::pair<std::string, std::map<Node*,
                std::vector<std::string>>>(vec.at(0), inner));

    }
    return 0;
}

// Get node object: seaerch by gate (node) name
Node *Circuit::getNode(std::string &name) {
    if(gate_names.find(name) != gate_names.end())
        for (auto const& node : gate_names[name])
            return node.first;
    if(input_names.find(name) != input_names.end())
        return input_names[name];
//    if(output_names.find(name) != output_names.end())
//        return output_names[name];
    return nullptr;
}

// Create wires between gates (nodes)
int Circuit::createWires(void) {
    for (auto const& node : gate_names){
        for(auto const& params : node.second){
            Node* wire_to;
            wire_to = params.first;
            std::vector<std::string> curr_node_params = params.second;
            for(unsigned int i = 0; i<curr_node_params.size(); ++i){
                Node* wire_from;
                wire_from = getNode(curr_node_params.at(i));
                addWire(wire_from, wire_to);
//                std::cout << wire_to->getName() << "->" << wire_to<< std::endl;
            }
        }
    }
    for (auto const& out_node : output_names){
//        std::cout << out_node.first << "->" << out_node.second << std::endl;
        std::string name = out_node.first;
        Node* wire_from;
        wire_from = getNode(name);
        addWire(wire_from, out_node.second);
    }
    return 0;
}

// Depth First Search for topological sort
int  Circuit::DFS(Node *node) {
    if(!node->getSorted()){
        Stack.push(node);
        node->setSorted(true);
    }

    for (unsigned int i = 0; i < node->getNumInputs(); ++i) {
        if (!node->getInput(i)->getSorted()) {
            DFS(node->getInput(i));
        }
        if(Stack.empty())
            return 0;
    }

    Stack.pop();
    sorted_gates.push_back(node);
    if (!Stack.empty())
        DFS(Stack.top());
    return 0;
}

// Compare node names to sort (used in std:sort -> alphabatical sort)
bool Circuit::sortNodes(Node* node1, Node* node2) {
    std::string n1, n2;
    n1 = node1->getName();
    n2 = node2->getName();
    boost::to_upper(n1);
    boost::to_upper(n2);
    return  n1.compare(n2) < 0;
}