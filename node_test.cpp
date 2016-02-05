/*
 * node_test.cpp
 *
 * Created on : 05.04.2013
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann
 */

#include "node.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
// #include <typeinfo>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Main started"<<endl;
  // Build the circuit.
  Node *b = new Node(INPUT, "B");
  Node *a = new Node(INPUT, "A");
  Node *Cin = new Node(INPUT, "Cin");
  Node *d = new Node(XOR, "D");
  Wire *w = new Wire(a,d);
  d->addInput(w);
  a->addOutput(w);
  w = new Wire(b, d);
  d->addInput(w);
  b->addOutput(w);

//  for (unsigned  int j=0;j<d->getNumInputs();j++)
//    cout << "getInputs: " << d->getInput(j)->getName()<< endl;

 // cout << "getInputs: " << typeid(d->getInput(0)).name() << endl; // to know
  // the type

  Node *e = new Node(AND, "E");
  w = new Wire(d, e);
  e->addInput(w);
  d->addOutput(w);
  w = new Wire(Cin, e);
  e->addInput(w);
  Cin->addOutput(w);



//  for (unsigned  int j=0;j<d->getNumOutputs();j++)
//    cout << "getOutput: " << d->getOutput(j)->getName()<< endl;

  Node *f = new Node(AND, "F");
  w = new Wire(a, f);
  f->addInput(w);
  a->addOutput(w);
  w = new Wire(b, f);
  f->addInput(w);
  b->addOutput(w);

  Node *s = new Node(XOR, "S");
  w = new Wire(d, s);
  s->addInput(w);
  d->addOutput(w);
  w = new Wire(Cin, s);
  s->addInput(w);
  Cin->addOutput(w);

  Node *Cout = new Node(OR, "Cout");
  w = new Wire(e, Cout);
  Cout->addInput(w);
  e->addOutput(w);
  w = new Wire(f, Cout);
  Cout->addInput(w);
  f->addOutput(w);

  Node *out_s = new Node(OUTPUT, "S");
  w = new Wire(s, out_s);
  out_s->addInput(w);
  s->addOutput(w);

  Node *out_Cout = new Node(OUTPUT,"Cout");
  w = new Wire(Cout, out_Cout);
  out_Cout->addInput(w);
  Cout->addOutput(w);

  vector< Node * > inputs;
  vector< Node * > gates;
  vector< Node * > outputs;

  inputs.push_back(a);
  inputs.push_back(b);
  inputs.push_back(Cin);
  gates.push_back(d);
  gates.push_back(e);
  gates.push_back(f);
  gates.push_back(Cout);
  gates.push_back(s);
  outputs.push_back(out_s);
  outputs.push_back(out_Cout);

  // Initialize random seed
  srand(time(NULL));

  // Simulate circuit for 5 random inputs
  cout << "inputs - outputs" << endl;
  for(unsigned int j=0;j<inputs.size();j++)
    {
      cout << inputs[j]->getName() << ";";
    }
  cout << " - ";

  for(unsigned int j=0;j<outputs.size();j++)
    {
      cout << outputs[j]->getName() << ";";
    }
  cout << endl;

  for(int i=0;i<10;i++)
    {
      for(unsigned int j=0;j<inputs.size();j++)
	{
	  inputs[j]->setState(rand()%2);
	  cout << inputs[j]->getState();
	}
      cout <<" - ";

      for(unsigned int j=0;j<gates.size();j++)
	{
	  gates[j]->eval();
	}

      for(unsigned int j=0;j<outputs.size();j++)
	{
	  outputs[j]->eval();
	}

      for(unsigned int j=0;j<outputs.size();j++)
	{
	  cout << outputs[j]->getState();
	}
      cout << endl;
  }

  // Clean up.
  for(unsigned int i = 0; i < outputs.size(); i++)
    {
      Node *output = outputs[i];
      outputs[i] = 0;
      delete output;
    }
  outputs.clear();

  for(unsigned int i = 0; i < gates.size(); i++)
    {
      Node *gate = gates[i];
      gates[i] = 0;
      delete gate;
    }
  gates.clear();

  for(unsigned int i = 0; i < inputs.size(); i++)
    {
      Node *input = inputs[i];
      inputs[i] = 0;
      delete input;
    }
  inputs.clear();

  return 0;
}
