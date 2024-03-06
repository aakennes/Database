#include "primer/orset.h"
#include <algorithm>
#include <string>
#include <vector>
#include "common/exception.h"
#include "fmt/format.h"

namespace bustub {

template <typename T>
auto ORSet<T>::Contains(const T &elem) const -> bool {
  for(auto ELEM:Elements_set){
    if(elem==ELEM.first)return true;
  }
  return false;
}

template <typename T>
void ORSet<T>::Add(const T &elem, uid_t uid) {
  auto it1=std::lower_bound(Elements_set.begin(),Elements_set.end(),std::pair(elem,uid));
  auto it2=std::lower_bound(Tomb_set.begin(),Tomb_set.end(),std::pair(elem,uid));
  if(it2==Tomb_set.end()||*it2!=std::pair(elem,uid)){
    Elements_set.insert(it1,std::pair(elem,uid));
  }
  //Elements_set.insert(std::lower_bound(Elements_set.begin(),Elements_set.end(),std::pair(elem,uid)),std::pair(elem,uid));
}

template <typename T>
void ORSet<T>::Remove(const T &elem) {
  auto it=std::lower_bound(Elements_set.begin(),Elements_set.end(),std::pair(elem,(uid_t)0));
  while(!Elements_set.empty()&&it!=Elements_set.end()&&(*it).first==elem){
    Tomb_set.insert(std::lower_bound(Tomb_set.begin(),Tomb_set.end(),*it),*it);
    Elements_set.erase(it);
    //++it;
  }
}

template <typename T>
void ORSet<T>::Merge(const ORSet<T> &other) {
  for(auto ELEM:other.Tomb_set){
    auto it=std::lower_bound(Elements_set.begin(),Elements_set.end(),ELEM);
    if(it!=Elements_set.end()&&*it==ELEM){
      Elements_set.erase(it);
    }
  }
  for(auto ELEM:other.Elements_set){
    auto it1=std::lower_bound(Elements_set.begin(),Elements_set.end(),ELEM);
    auto it2=std::lower_bound(Tomb_set.begin(),Tomb_set.end(),ELEM);
    if((it2==Tomb_set.end()||*it2!=ELEM)&&(it1==Elements_set.end()||*it1!=ELEM)){
      Elements_set.insert(it1,ELEM);
    }
  }
  for(auto ELEM:other.Tomb_set){
    auto it=std::lower_bound(Tomb_set.begin(),Tomb_set.end(),ELEM);
    if(it==Tomb_set.end()||*it!=ELEM){
      Tomb_set.insert(it,ELEM);
    }
  }
  // for(auto ELEM:other.Tomb_set){
  //   auto it1=std::lower_bound(Elements_set.begin(),Elements_set.end(),ELEM);
  //   auto it2=std::lower_bound(Tomb_set.begin(),Tomb_set.end(),ELEM);
  //   if(it1!=Elements_set.end()&&*it1==ELEM){
  //     Elements_set.erase(it1);
  //   }
  //   if(it2==Tomb_set.end()||*it2!=ELEM){
  //     Tomb_set.insert(it2,ELEM);
  //   }
  // }
  // for(auto it=Elements_set.begin();it!=Elements_set.end();++it){
  //   if(*it==*(--it))Elements_set.erase(it),it--;
  // }
  //throw NotImplementedException("ORSet<T>::Merge is not implemented");
}

template <typename T>
auto ORSet<T>::Elements() const -> std::vector<T> {
  std::vector<T> Elements_set_output;
  for(auto ELEM:Elements_set){
    Elements_set_output.push_back(ELEM.first);
  }
  return Elements_set_output;
  // TODO(student): Implement this
  //throw NotImplementedException("ORSet<T>::Elements is not implemented");
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
