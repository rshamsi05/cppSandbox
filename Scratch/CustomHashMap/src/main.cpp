#include "linear_probed_map.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
  LinearProbedMap<std::string, int> map;

  // Testing Insert operation
  map.insert("james", 1);
  map.insert("conry", 3);
  std::cout << "Key James: " << map.get("james").value() << std::endl;

  // Testing remove operation
  map.remove("james");
  try {
    map.get("james");
  } catch (const std::out_of_range &e) {
    std::cout << "Caught expected exception: " << e.what() << std::endl;
  }

  // Testing different map type
  LinearProbedMap<std::string, std::string> map2;
  map2.insert("Tobey Maguire", "2002 Spiderman");
  map2.insert("Andre Garfield", "2012 Spiderman");
  map2.insert("Tom Holland", "2017 Spiderman");
  std::cout << "Tobey Maguire appeared in the: "
            << map2.get("Tobey Maguire").value() << std::endl;
  std::cout << "Andre Garfield appeared in the: "
            << map2.get("Andre Garfield").value() << std::endl;
  std::cout << "Tom Holland appeared in the: "
            << map2.get("Tom Holland").value() << std::endl;
  return 0;
}