#include "primer/orset.h"
#include <algorithm>
#include <string>
#include <vector>
#include "common/exception.h"
#include "fmt/format.h"

namespace bustub {

template <typename T>
auto ORSet<T>::Contains(const T &elem) const -> bool {
  // for(auto elem:elements_set_){
  //   if(elem==elem.first)return true;
  // }
  // return false;
  auto it = std::lower_bound(elements_set_.begin(), elements_set_.end(), std::pair(elem, static_cast<uid_t>(0)));
  // if (it != elements_set_.end() && (*it).first == elem){return true;}
  // return false;
  return static_cast<bool>(it != elements_set_.end() && (*it).first == elem);
}

template <typename T>
void ORSet<T>::Add(const T &elem, uid_t uid) {
  auto it1 = std::lower_bound(elements_set_.begin(), elements_set_.end(), std::pair(elem, uid));
  auto it2 = std::lower_bound(tomb_set_.begin(), tomb_set_.end(), std::pair(elem, uid));
  if (it2 == tomb_set_.end() || *it2 != std::pair(elem, uid)) {
    elements_set_.insert(it1, std::pair(elem, uid));
  }
  // elements_set_.insert(std::lower_bound(elements_set_.begin(),elements_set_.end(),std::pair(elem,uid)),std::pair(elem,uid));
}

template <typename T>
void ORSet<T>::Remove(const T &elem) {
  auto it = std::lower_bound(elements_set_.begin(), elements_set_.end(), std::pair(elem, static_cast<uid_t>(0)));
  while (!elements_set_.empty() && it != elements_set_.end() && (*it).first == elem) {
    tomb_set_.insert(std::lower_bound(tomb_set_.begin(), tomb_set_.end(), *it), *it);
    elements_set_.erase(it);
    //++it;
  }
}

template <typename T>
void ORSet<T>::Merge(const ORSet<T> &other) {
  for (auto &elem : other.tomb_set_) {
    auto it = std::lower_bound(elements_set_.begin(), elements_set_.end(), elem);
    if (it != elements_set_.end() && *it == elem) {
      elements_set_.erase(it);
    }
  }
  for (auto &elem : other.elements_set_) {
    auto it1 = std::lower_bound(elements_set_.begin(), elements_set_.end(), elem);
    auto it2 = std::lower_bound(tomb_set_.begin(), tomb_set_.end(), elem);
    if ((it2 == tomb_set_.end() || *it2 != elem) && (it1 == elements_set_.end() || *it1 != elem)) {
      elements_set_.insert(it1, elem);
    }
  }
  for (auto &elem : other.tomb_set_) {
    auto it = std::lower_bound(tomb_set_.begin(), tomb_set_.end(), elem);
    if (it == tomb_set_.end() || *it != elem) {
      tomb_set_.insert(it, elem);
    }
  }
  // throw NotImplementedException("ORSet<T>::Merge is not implemented");
}

template <typename T>
auto ORSet<T>::Elements() const -> std::vector<T> {
  std::vector<T> elements_set_output;
  elements_set_output.reserve(elements_set_.size());
  for (auto &elem : elements_set_) {
    elements_set_output.push_back(elem.first);
  }
  return elements_set_output;
  // TODO(student): Implement this
  // throw NotImplementedException("ORSet<T>::Elements is not implemented");
}

template <typename T>
auto ORSet<T>::ToString() const -> std::string {
  auto elements = Elements();
  std::sort(elements.begin(), elements.end());
  return fmt::format("{{{}}}", fmt::join(elements, ", "));
}

template class ORSet<int>;
template class ORSet<std::string>;

}  // namespace bustub
