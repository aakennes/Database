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
#include <cstring>
#include <iostream>
#include <unordered_map>

#include "common/config.h"
#include "common/logger.h"

namespace bustub {

void ExtendibleHTableDirectoryPage::Init(uint32_t max_depth) {
  max_depth_ = max_depth;
  global_depth_ = 0;
  memset(local_depths_, 0, sizeof(local_depths_));
  memset(bucket_page_ids_, -1, sizeof(bucket_page_ids_));
}

auto ExtendibleHTableDirectoryPage::HashToBucketIndex(uint32_t hash) const -> uint32_t {
  // uint32_t local_hash=hash&GetGlobalDepthMask();
  return hash & GetGlobalDepthMask();
}

auto ExtendibleHTableDirectoryPage::GetBucketPageId(uint32_t bucket_idx) const -> page_id_t {
  return bucket_page_ids_[bucket_idx];
}

void ExtendibleHTableDirectoryPage::SetBucketPageId(uint32_t bucket_idx, page_id_t bucket_page_id) {
  bucket_page_ids_[bucket_idx] = bucket_page_id;
}

auto ExtendibleHTableDirectoryPage::GetSplitImageIndex(uint32_t bucket_idx) const -> uint32_t {
  if (local_depths_[bucket_idx] > global_depth_) {
    return bucket_idx ^ (1 << global_depth_);
  }
  return bucket_idx ^ (1 << (global_depth_ - 1));
}

auto ExtendibleHTableDirectoryPage::GetGlobalDepthMask() const -> uint32_t { return (1 << global_depth_) - 1; }

auto ExtendibleHTableDirectoryPage::GetLocalDepthMask(uint32_t bucket_idx) const -> uint32_t {
  return (1 << local_depths_[bucket_idx]);
}

auto ExtendibleHTableDirectoryPage::GetGlobalDepth() const -> uint32_t { return global_depth_; }

void ExtendibleHTableDirectoryPage::IncrGlobalDepth() {
  uint32_t directory_size = 1 << global_depth_;
  global_depth_++;
  for (uint32_t bucket_id = 0; bucket_id < directory_size; bucket_id++) {
    if (local_depths_[bucket_id] < global_depth_) {
      auto double_id = GetSplitImageIndex(bucket_id);
      local_depths_[double_id] = local_depths_[bucket_id];
      bucket_page_ids_[double_id] = bucket_page_ids_[bucket_id];
    }
  }
}

void ExtendibleHTableDirectoryPage::DecrGlobalDepth() {
  uint32_t directory_size = 1 << global_depth_;
  for (uint32_t bucket_id = (directory_size >> 1); bucket_id < directory_size; bucket_id++) {
    bucket_page_ids_[bucket_id] = -1;
    local_depths_[bucket_id] = 0;
  }
  global_depth_--;
}

auto ExtendibleHTableDirectoryPage::CanShrink() -> bool {
  auto directory_size = Size();
  for (uint32_t bucket_id = 0; bucket_id < directory_size; bucket_id++) {
    if (local_depths_[bucket_id] >= global_depth_) {
      return false;
    }
  }
  return true;
}

auto ExtendibleHTableDirectoryPage::Size() const -> uint32_t {
  uint32_t directory_size = 0;
  while (local_depths_[1 << (directory_size)] > 0) {
    directory_size++;
  }
  return 1 << directory_size;
}

auto ExtendibleHTableDirectoryPage::GetLocalDepth(uint32_t bucket_idx) const -> uint32_t {
  return local_depths_[bucket_idx];
}

void ExtendibleHTableDirectoryPage::SetLocalDepth(uint32_t bucket_idx, uint8_t local_depth) {
  while (local_depths_[bucket_idx] < local_depth) {
    IncrLocalDepth(bucket_idx);
  }
  while (local_depths_[bucket_idx] > local_depth) {
    DecrLocalDepth(bucket_idx);
  }
}

void ExtendibleHTableDirectoryPage::IncrLocalDepth(uint32_t bucket_idx) {
  local_depths_[bucket_idx]++;
  local_depths_[GetSplitImageIndex(bucket_idx)] = local_depths_[bucket_idx];
}

void ExtendibleHTableDirectoryPage::DecrLocalDepth(uint32_t bucket_idx) {
  local_depths_[bucket_idx]--;
  local_depths_[GetSplitImageIndex(bucket_idx)] = local_depths_[bucket_idx];
}

}  // namespace bustub
