#include "wire.h"




Wire::Wire(Node* a, Node* b)
:input(a), output(b)
{
}

//virtual Wire::~Wire(){
//}

Node* Wire::getInput() const{
    return input;
}

Node* Wire::getOutput() const{
    return output;
}

