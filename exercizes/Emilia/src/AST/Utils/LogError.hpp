#ifndef LOG_ERROR_HPP
#define LOG_ERROR_HPP

#include <string>
#include <iostream>

inline const void LogErrorV(const std::string Str) {
  std::cerr << Str << std::endl;
}

#endif // !LOG_ERROR_HPP