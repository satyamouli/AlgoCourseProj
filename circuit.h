/*
 * circuit.hpp
 *
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include "node.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <algorithm>

/** Describes a logic circuit as a set of connected gates. */
class Circuit
{
private:
    std::map <std::string, Node*> input_names;
    std::map <std::string, Node*> output_names;
    std::map <std::string, std::map<Node*, std::vector<std::string>>>
            gate_names;
    std::stack<Node *> Stack;
    std::vector<Node *> sorted_gates;
public:
  // Vector with pointers to all gates
  std::vector< Node * > gates;

  // Vector with pointers to inputs of the circuit
  std::vector< Node * > inputs;

  // Vector with pointers to outputs of the circuit
  std::vector< Node * > outputs;


public:
  // Constructor.
  Circuit();

  // Destructor (delete all nodes that were created with new)
  virtual ~Circuit();

  // Read the benchfile and generate inputs, outputs and gates accordingly.
  int readBenchFile(std::string filename);  // here std is missing

  // Get pointer to Node with index i. 0<=i<size of inputs+gates+outputs
  Node *getNode(unsigned int i) const;

  // Set the states of the input Nodes.
  int setInputs(const std::string& inputstring);

  // Get the states of the outputs.
  std::string getOutputs() const { return getOutputStates(); }

  // Get the names of all gates (separated by ";")
  std:: string getGateNames();

  // Get the state values of all gates and add them to one string.
  // (e.g. "0010010")
  std::string getGateStates() const;
  std::string getOutputNames() const;
  std::string getOutputStates() const;
  std::string getInputNames() const;
  std::string getInputStates() const;

  // Create an input node with name "name" and return the pointer to it.
  Node *addInput(const std::string& name);

  // Create an output node with name "name" and return the pointer to it.
  Node *addOutput(const std::string& name);

  // Create a new node of type t and name "name" and return the pointer to it.
  Node *addGate(TGate t, const std::string& name);

  // Connects the output of the first Node to the input of the second Node.
  void addWire(Node* output, Node* input);

  // Connect the output with name A.
  void addWire(const std::string& output, const std::string& input);

  // Update the results of all gates and outputs with the currently assigned
  // inputs
  void eval();

  // Topological sorting (for the mixed circuits)
  void topologicalSort();
  // Alphabetical sorting (for the mixed circuits)
  void sortInputs();

  // Alphabetical sorting (for the mixed circuits)
  void sortOutputs();

  // Remove white spaces at the start and end of str
  static std::string trim(std::string &str);

  // To upper case
  static void toUpper(const std::string &str);

  // Split a string by the delimiter and return the array of split parts.
  static std::vector<std::string> splitString(const std::string& str,
					      char delim);
// for  striping # comments  and spaces
private:
    std::string stripCommentAndSpace(std::string&);
    std::vector<std::string> parse(std::string&);
    int saveGates(std::vector<std::string>);
    int createWires(void);
    Node *getNode(std::string &name);

    // for topological sort using DFS
    int DFS(Node *);

    // for alpha sort
    static bool sortNodes(Node* ,Node*);

};



#endif /* CIRCUIT_H_ */
