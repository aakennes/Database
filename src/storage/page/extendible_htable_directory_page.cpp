//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// extendible_htable_directory_page.cpp
//
// Identification: src/storage/page/extendible_htable_directory_page.cpp
//
// Copyright (c) 2015-2023, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "storage/page/extendible_htable_directory_page.h"

#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <iostream>

#include "common/config.h"
#include "common/logger.h"

namespace bustub {

void ExtendibleHTableDirectoryPage::Init(uint32_t max_depth) {
  max_depth_=max_depth;
  global_depth_=0;
  memset(local_depths_,0,sizeof(local_depths_));
  memset(bucket_page_ids_,-1,sizeof(bucket_page_ids_));
  // throw NotImplementedException("ExtendibleHTableDirectoryPage is not implemented");
}

auto ExtendibleHTableDirectoryPage::HashToBucketIndex(uint32_t hash) const -> uint32_t { 
  // uint32_t local_hash=hash&GetGlobalDepthMask();
  // if(hash==3){
  //   std::cout<<local_hash<<" "<<GetLocalDepthMask(hash)<<" "<<(int)local_depths_[3]<<'\n';
  // }
  return hash&GetGlobalDepthMask();
}

auto ExtendibleHTableDirectoryPage::GetBucketPageId(uint32_t bucket_idx) const -> page_id_t {
  return bucket_page_ids_[bucket_idx]; 
}

void ExtendibleHTableDirectoryPage::SetBucketPageId(uint32_t bucket_idx, page_id_t bucket_page_id) {
  bucket_page_ids_[bucket_idx]=bucket_page_id;
  // throw NotImplementedException("ExtendibleHTableDirectoryPage is not implemented");
}

auto ExtendibleHTableDirectoryPage::GetSplitImageIndex(uint32_t bucket_idx) const -> uint32_t {
  if(local_depths_[bucket_idx]>global_depth_){
    // std::cout<<bucket_idx<<" "<<global_depth_<<" "<<(int)local_depths_[bucket_idx]<<" "<<(bucket_idx^(1<<(global_depth_)))<<'\n';
    return bucket_idx^(1<<global_depth_);
  }
  return bucket_idx^(1<<(global_depth_-1)); 
}

auto ExtendibleHTableDirectoryPage::GetGlobalDepthMask() const -> uint32_t{
  return (1<<global_depth_)-1; 
}

auto ExtendibleHTableDirectoryPage::GetLocalDepthMask(uint32_t bucket_idx) const -> uint32_t{
  return (1<<local_depths_[bucket_idx])-1; 
}

auto ExtendibleHTableDirectoryPage::GetGlobalDepth() const -> uint32_t { 
  return global_depth_; 
}

void ExtendibleHTableDirectoryPage::IncrGlobalDepth() {
  uint32_t directory_size=1<<global_depth_;
  global_depth_++;
  for(uint32_t bucket_id=0;bucket_id<directory_size;bucket_id++){
    if(local_depths_[bucket_id]<global_depth_){
      auto double_id=GetSplitImageIndex(bucket_id);
      if(global_depth_==1){
        std::cout<<bucket_id<<" "<<double_id<<'\n';
      }
      local_depths_[double_id]=local_depths_[bucket_id];
      bucket_page_ids_[double_id]=bucket_page_ids_[bucket_id];
    }
  }
  // global_depth_++;
}

void ExtendibleHTableDirectoryPage::DecrGlobalDepth() {
  uint32_t directory_size=1<<global_depth_;
  // std::cout<<directory_size<<" "<<(directory_size<<1)<<'\n';
  for(uint32_t bucket_id=(directory_size>>1);bucket_id<directory_size;bucket_id++){
    bucket_page_ids_[bucket_id]=-1;
    local_depths_[bucket_id]=0;
    // std::cout<<bucket_id<<" "<<bucket_page_ids_[bucket_id]<<'\n';
  }
  // PrintDirectory();
  global_depth_--;
}

auto ExtendibleHTableDirectoryPage::CanShrink() -> bool { 
  auto directory_size=Size();
  for(uint32_t bucket_id=0;bucket_id<directory_size;bucket_id++){
    if(local_depths_[bucket_id]>=global_depth_){
      return false;
    }
  }
  return true; 
}

auto ExtendibleHTableDirectoryPage::Size() const -> uint32_t { 
  uint32_t directory_size=0;
  // std::cout<<bucket_page_ids_[1]<<'\n';
  while(local_depths_[1<<(directory_size)]>0){
    directory_size++;
  }
  return 1<<directory_size;
}

auto ExtendibleHTableDirectoryPage::GetLocalDepth(uint32_t bucket_idx) const -> uint32_t { 
  return local_depths_[bucket_idx]; 
}

void ExtendibleHTableDirectoryPage::SetLocalDepth(uint32_t bucket_idx, uint8_t local_depth) {
  while(local_depths_[bucket_idx]<local_depth){
    IncrLocalDepth(bucket_idx);
  }
  while(local_depths_[bucket_idx]>local_depth){
    DecrLocalDepth(bucket_idx);
  }
  // PrintDirectory();
}

void ExtendibleHTableDirectoryPage::IncrLocalDepth(uint32_t bucket_idx) {
  // std::cout<<(int)local_depths_[bucket_idx]<<" "<<global_depth_<<" "<<bucket_idx<<" "<<GetSplitImageIndex(bucket_idx)<<'\n';
  
  local_depths_[bucket_idx]++;
  local_depths_[GetSplitImageIndex(bucket_idx)]=local_depths_[bucket_idx];
  // throw NotImplementedException("ExtendibleHTableDirectoryPage is not implemented");
}

void ExtendibleHTableDirectoryPage::DecrLocalDepth(uint32_t bucket_idx) {
  local_depths_[bucket_idx]--;
  local_depths_[GetSplitImageIndex(bucket_idx)]=local_depths_[bucket_idx];
  // throw NotImplementedException("ExtendibleHTableDirectoryPage is not implemented");
}

}  // namespace bustub
