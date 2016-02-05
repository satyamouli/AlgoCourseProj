/*
 * node.hpp
 *
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann
 */

#ifndef NODE_H_
#define NODE_H_

#include "wire.h"

#include <string>
#include <vector>

//define _U (Undefined value) as integer value 2
const int _U = 2;

// The different gate types.
typedef enum
{
  UNDEFINED, INPUT, OUTPUT, AND, NAND, OR, NOR, NOT, XOR
} TGate;

/* Represents a gate in a circuit. */
class Node{
private:
  // Used for the topological sorting
  bool sorted;

  // Type of the Node
  TGate gateType;

  // Name of the gate (the name of the output in .bench file)
  std::string name;

  // Pointers to all Nodes that are inputs to this gate (e.g. all inputs of an
  // AND gate)
  std::vector< Wire * > inputs;

  // Pointers to all Nodes that use this gate as an input (used for the
  // topological sorting).
  std::vector < Wire * > outputs;

  // The current state of the gate (0, 1 or _U for undefined)
  int state;

public:
  // Constructor with initialization values
  Node(TGate gT, const std::string& n, int st = _U);

  // Destructor. Delete all output wires.
  virtual ~Node();

  // Add the pointer to Node a to the vector of Nodes that use the current Node.
  void addOutput(Wire *a);

  // Add the pointer to Node a to the inputs of the current Node
  void addInput(Wire *a);

  // Calculate a logic function (depending on gateType) with inputs from
  // "inputs" and update the state.
  void eval();



  // Return the number of inputs to this Node
  unsigned int getNumInputs() const;

  // Return the number of outputs to this Node
  unsigned int getNumOutputs() const;

  // Return the input node with index i
  Node *getInput(unsigned int i) const;

  // Return the output node with index i
  Node *getOutput(unsigned int i) const;

  // Get the name of the Node
  const std::string& getName() const;

  // Set the name of the Node
  void setState(int st);

  // Get the state of the Node
  int getState(void) const;

  // Set this Node as sorted
  void setSorted(bool x);

  // Return the sorted variable
  bool getSorted() const;

  // Get the type of the gate.
  TGate getGateType() const;
};

#endif /* NODE_H_ */
