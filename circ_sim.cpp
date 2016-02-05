/*
 * circ_sim.cpp
 *
 * Author     : Viktor Froese
 * Modified by: Matthias Kampmann
 */

#include "node.h"
#include "circuit.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc!=3)
    {
      cout << "Circuit Simulation for .bench files. " << endl
	   << "usage: circ_sim circuit.bench input_vectors.in" << endl;
      return 0;
    }

  ifstream input_file;
  input_file.open(argv[2]);
  if(input_file.fail())
    {
      cout << "Failed to open file :" << argv[2] << endl;
      return 1;
    }

  //Output file: strip .bench file extension and give the same name for out file
  std::string bench_file = argv[1];
  size_t lastindex = bench_file.find_last_of(".");
  string out_file_name = bench_file.substr(0, lastindex);
  ofstream out_file;
  out_file.open(out_file_name.append(".out"));

  Circuit circ;
  circ.readBenchFile(argv[1]);

  circ.topologicalSort();
  circ.sortInputs();
  circ.sortOutputs();

  string line;
  getline(input_file,line);
  cout << "inputs - outputs" << endl;
  out_file << "inputs - outputs" << endl;
  cout << circ.getInputNames() << " - " << circ.getOutputNames() << endl;
  out_file << circ.getInputNames() << " - " << circ.getOutputNames() << endl;

  while(!input_file.eof())
    {
      circ.setInputs(line);
      circ.eval();
      cout << line << "-" << circ.getOutputs() << endl;
      out_file << line << "-" << circ.getOutputs() << endl;
      getline(input_file,line);
    }
  input_file.close();
  out_file.close();

  return 0;
}

