/*
 * wire.hpp
 *
 * Defines the Wire class.
 *
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann

gm */
#ifndef WIRE_H_
#define WIRE_H_

// Forward declaration.
class Node;

/* A wire connects two gates. */
class Wire
{
private:
  // Gate driving the wire.
  Node* input;

  // Gate driven by the wire.
  Node* output;

public:
  // Constructur.
  Wire(Node* a, Node* b);

  Node *getInput() const;
  Node *getOutput() const;
};

#endif /* WIRE_H_ */
