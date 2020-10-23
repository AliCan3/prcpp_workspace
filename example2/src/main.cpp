#include "function.h"
#include "string"
#include "iostream"

int main(int argc, char* argv[]) {
  if(argc != 3){
    std::cout << "Expected 2 parameters. Got: " << argc - 1 << std ::endl;
    return EXIT_FAILURE;
  }
  const int param1 = std::stoi(argv[1]);
  const int param2 = std::stoi(argv[2]);

  if (param2 <= 0){
    std::cerr << "Expected second parameter to be bigger then zero. Got" <<
    param2 << std::endl;
    return EXIT_FAILURE;
  }
  const auto result = static_cast<float>(param1) / static_cast<float>(param2);
  std::cout<< result << std::endl;
  Function("example2");
  return EXIT_SUCCESS;
}
