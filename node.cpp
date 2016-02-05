#include "node.h"
#include <iostream>

using namespace std;

Node::Node(TGate gT, const std::string& n, int st)
:sorted(false), gateType(gT), name(n), inputs(), outputs(), state(st)
{

}

Node::~Node(){              // this can be used if we want
}

void Node::addOutput(Wire *a){
    outputs.push_back(a); // Adds wire to outputs vector
}

void Node::addInput(Wire *a){
    inputs.push_back(a);    // adds wire to inputs vector
}

// writing code for the logical gates

void Node::eval(){
    switch (gateType){
        case UNDEFINED:
            break;
        case INPUT:
            break;
        case OUTPUT:
            state = getInput(0)->state;
            break;
        case AND:
           // state = 1;
            for (unsigned int i = 0; i < getNumInputs(); ++i) {
                state &= getInput(i)->state;
            }
            break;
        case NAND:
            state = 1;
            for (unsigned int i = 0; i < getNumInputs(); ++i) {
                state &= getInput(i)->state;

            }
            state = !state;
            break;
        case OR:
            state = 0;
            for (unsigned int i = 0; i < getNumInputs(); ++i) {
                state |= getInput(i)->state;
            }
            break;
        case NOR:
            state = 0;
            for (unsigned int i = 0; i < getNumInputs(); ++i) {
                state |= getInput(i)->state;
            }
            state = !state;
            break;
        case NOT:
                state = !getInput(0)->state;
            break;
        case XOR:
            state = 0;
            for (unsigned int i = 0; i < getNumInputs(); ++i) {
                state = state ^ getInput(i)->state;
            }
            break;
    }
}

unsigned int Node::getNumInputs() const{
    // Count number of elements in inputs vector and return
    return inputs.size();
}

unsigned int Node::getNumOutputs() const{
    // Count number of elements in outputs vector and return
    return outputs.size();
}

Node* Node::getInput(unsigned int i) const{
    return inputs.at(i)->getInput();    // returning inputs with
    // index i
}

Node* Node::getOutput(unsigned int i) const{
    return outputs.at(i)->getOutput();    // returning outputs with index i
}

const std::string& Node::getName() const{
    return name;
}

void Node::setState(int st){
    state = st;
}

int Node::getState(void) const{
    return state;
}

void Node::setSorted(bool x){
    sorted = x;                     // here we give true or false in bool
}

bool Node::getSorted() const{
    return sorted;
}

TGate Node::getGateType() const{
    return gateType;
}





