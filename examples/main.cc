#include <arch/Backend.h>
#include <graph/MathTypes.h>

#include <fstream>
#include <iostream>

int main() {
  // write a computation graph
  auto a = Vector("a", 3);
  auto b = Vector("b", 3);

  auto c = a + b + static_cast<double>(0.5);

  auto d = Vector("d", 3);
  auto e = c + d + a;

  // print the graph
  std::string message = "{";
  Compute::print(&e, message);
  message += "}";

  std::fstream file("computation_graph.json", std::ios::out);
  file << message << std::endl;
  file.close();

  // load data to the graph
  std::unordered_map<std::string, Value*> data;

  Double a_vals({1.0, 2.0, 3.0});
  Double b_vals({4.0, 5.0, 6.0});
  Double d_vals({7.0, 8.0, 9.0});

  data["a"] = &a_vals;
  data["b"] = &b_vals;
  data["d"] = &d_vals;

  // evaluate the graph on CPU and print the result
  CPU instance;
  instance.evaluate(e, data);
  std::cout << "Result: " << e.toString() << std::endl;

  deleteGraph(e);

  return 0;
}