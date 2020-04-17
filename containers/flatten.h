//
// Created by Petr on 17.04.2020.
//

#ifndef UTILITIES_FLATTEN_H
#define UTILITIES_FLATTEN_H

#include <algorithm>
#include <iterator>

template <typename ContainerOut, typename IterBegin, typename IterEnd> ContainerOut flatten(IterBegin &&begin, IterEnd &&end) {
  ContainerOut result;
  for (; begin != end; ++begin) {
    result.insert(std::end(result), std::begin(*begin), std::end(*begin));
  }
  return result;
}

template <typename ContainerOut, typename ContainerIn> inline ContainerOut flatten(ContainerIn &&container) {
  return flatten<ContainerOut>(std::begin(container), std::end(container));
}

#endif // UTILITIES_FLATTEN_H
