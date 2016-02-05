/*
 * fulladder.cpp
 *
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann
 */

#include"circuit.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string string2int(int number);

int main(int argc, char* argv[]) {
  Circuit circ;
  Node *p[10];
  p[0] = circ.addInput("X");
  p[1] = circ.addInput("Y");
  p[2] = circ.addInput("C");
  p[3] = circ.addGate(AND, "D");
  p[4] = circ.addGate(XOR, "E");
  p[5] = circ.addGate(AND, "F");
  p[6] = circ.addGate(XOR, "G");
  p[7] = circ.addGate(OR, "H");
  p[8] = circ.addOutput("Cout");
  p[9] = circ.addOutput("S");

  circ.addWire(p[0], p[3]);
  circ.addWire(p[1], p[3]);
  circ.addWire(p[0], p[4]);
  circ.addWire(p[1], p[4]);
  circ.addWire(p[3], p[7]);
  circ.addWire(p[4], p[5]);
  circ.addWire(p[2], p[5]);
  circ.addWire(p[4], p[6]);
  circ.addWire(p[2], p[6]);
  circ.addWire(p[5], p[7]);
  circ.addWire(p[7], p[8]);
  circ.addWire(p[6], p[9]);

  cout << circ.getInputNames() << "-" << circ.getOutputNames() << endl;
  for(int i=0;i<2;i++)
    {
      for(int j=0;j<2;j++)
	{
	  for(int k=0;k<2;k++)
	    {
	      string input;
	      input=string2int(i);      // here we convert int to string
	      input+=string2int(j);
	      input+=string2int(k);
	      circ.setInputs(input);
	      circ.eval();
	      cout << circ.getInputStates() << "-" << circ.getOutputs() << endl;
	    }
	}
    }
}

string string2int(int number)
{
  stringstream ss;//create a stringstream
  ss << number;//add number to the stream // used delimeter for
    // seperation
  return ss.str();//return a string with the contents of the stream
}
