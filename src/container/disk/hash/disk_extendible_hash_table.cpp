//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// disk_extendible_hash_table.cpp
//
// Identification: src/container/disk/hash/disk_extendible_hash_table.cpp
//
// Copyright (c) 2015-2023, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "common/config.h"
#include "common/exception.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/rid.h"
#include "common/util/hash_util.h"
#include "container/disk/hash/disk_extendible_hash_table.h"
#include "storage/index/hash_comparator.h"
#include "storage/page/b_plus_tree_page.h"
#include "storage/page/extendible_htable_bucket_page.h"
#include "storage/page/extendible_htable_directory_page.h"
#include "storage/page/extendible_htable_header_page.h"
#include "storage/page/page_guard.h"

namespace bustub {

template <typename K, typename V, typename KC>
DiskExtendibleHashTable<K, V, KC>::DiskExtendibleHashTable(const std::string &name, BufferPoolManager *bpm,
                                                           const KC &cmp, const HashFunction<K> &hash_fn,
                                                           uint32_t header_max_depth, uint32_t directory_max_depth,
                                                           uint32_t bucket_max_size)
    : bpm_(bpm),
      cmp_(cmp),
      hash_fn_(std::move(hash_fn)),
      header_max_depth_(header_max_depth),
      directory_max_depth_(directory_max_depth),
      bucket_max_size_(bucket_max_size) {
  index_name_ = name;
  BasicPageGuard header_guard = bpm_->NewPageGuarded(&header_page_id_);
  auto header_page = header_guard.AsMut<ExtendibleHTableHeaderPage>();
  header_page->Init(header_max_depth_);
  header_guard.Drop();
}

/*****************************************************************************
 * SEARCH
 *****************************************************************************/
template <typename K, typename V, typename KC>
auto DiskExtendibleHashTable<K, V, KC>::GetValue(const K &key, std::vector<V> *result, Transaction *transaction) const
    -> bool {
  auto hash = Hash(key);
  auto header_guard = bpm_->FetchPageRead(header_page_id_);
  auto header_page = header_guard.As<ExtendibleHTableHeaderPage>();
  page_id_t directory_page_id = INVALID_PAGE_ID;
  directory_page_id = header_page->GetDirectoryPageId(header_page->HashToDirectoryIndex(hash));
  // std::cout<<"DEBUG:"<<directory_page_id<<" "<<Hash(key)<<' ';
  if (directory_page_id == INVALID_PAGE_ID) {
    return false;
  }
  header_guard.Drop();
  auto directory_guard = bpm_->FetchPageRead(directory_page_id);
  auto directory_page = directory_guard.As<ExtendibleHTableDirectoryPage>();
  // std::cout<<"DEBUG:"<<hash<<" "<<directory_page_id<<'\n';
  // directory_page->PrintDirectory();
  page_id_t bucket_page_id = INVALID_PAGE_ID;
  bucket_page_id = directory_page->GetBucketPageId(directory_page->HashToBucketIndex(hash));
  // std::cout<<bucket_page_id<<" "<<Hash(key)<<'\n';
  if (bucket_page_id == INVALID_PAGE_ID) {
    return false;
  }
  
  directory_guard.Drop();
  auto bucket_guard = bpm_->FetchPageRead(bucket_page_id);
  auto bucket_page = bucket_guard.As<ExtendibleHTableBucketPage<K, V, KC>>();
  V value;
  bool exist = bucket_page->Lookup(key, value, cmp_);
  // std::cout<<bucket_page_id<<" "<<directory_page->HashToBucketIndex(hash)<<'\n';
  if (!exist) {
    return false;
  }
  // bucket_guard.Drop();
  result->push_back(value);
  // directory_page->PrintDirectory();
  // bucket_page->PrintBucket();
  // std::cout << directory_page->Size() << '\n';
  return true;
}

/*****************************************************************************
 * INSERTION
 *****************************************************************************/

template <typename K, typename V, typename KC>
auto DiskExtendibleHashTable<K, V, KC>::Insert(const K &key, const V &value, Transaction *transaction) -> bool {
  auto header_guard = bpm_->FetchPageWrite(header_page_id_);
  auto header_page = header_guard.AsMut<ExtendibleHTableHeaderPage>();
  auto hash = Hash(key);
  auto directory_page_index = header_page->HashToDirectoryIndex(hash);
  page_id_t directory_page_id = INVALID_PAGE_ID;
  directory_page_id = header_page->GetDirectoryPageId(directory_page_index);
  if (directory_page_id == INVALID_PAGE_ID) {
    auto insert_success = InsertToNewDirectory(header_page, directory_page_index, hash, key, value);
    return insert_success;
  }
  header_guard.Drop();
  auto directory_guard = bpm_->FetchPageWrite(directory_page_id);
  auto directory_page = directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
  auto bucket_idx = directory_page->HashToBucketIndex(hash);
  page_id_t bucket_page_id = INVALID_PAGE_ID;
  bucket_page_id = directory_page->GetBucketPageId(bucket_idx);
  if (bucket_page_id == INVALID_PAGE_ID) {
    auto insert_success = InsertToNewBucket(directory_page, bucket_idx, key, value);
    return insert_success;
  }
  // directory_guard.Drop();
  // std::cout<<key<<" "<<directory_page_index<<'\n';
  auto bucket_guard = bpm_->FetchPageWrite(bucket_page_id);
  auto bucket_page = bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
  while (bucket_page->IsFull()) {
    auto local_depth = directory_page->GetLocalDepth(bucket_idx);
    auto global_depth = directory_page->GetGlobalDepth();
    // std::cout<<key<<" "<<local_depth<<" "<<global_depth<<'\n';
    if (local_depth == global_depth) {
      if (global_depth == directory_max_depth_) {
        return false;
      }
      // directory_page->PrintDirectory();
      directory_page->IncrGlobalDepth();
      directory_guard.Drop();
      directory_guard = bpm_->FetchPageWrite(directory_page_id);
      directory_page = directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
      bucket_idx = directory_page->HashToBucketIndex(hash);
      bucket_page_id = INVALID_PAGE_ID;
      bucket_page_id = directory_page->GetBucketPageId(bucket_idx);
      if (bucket_page_id == INVALID_PAGE_ID) {
        auto insert_success = InsertToNewBucket(directory_page, bucket_idx, key, value);
        // bucket_guard.Drop();
        return insert_success;
      }
    }
    auto local_mask = directory_page->GetLocalDepthMask(bucket_idx);
    directory_page->IncrLocalDepth(bucket_idx);
    page_id_t new_bucket_page_id = INVALID_PAGE_ID;
    auto new_bucket_guard = bpm_->NewPageGuarded(&new_bucket_page_id);
    auto new_bucket_page = new_bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
    new_bucket_page->Init(bucket_max_size_);
    auto new_bucket_idx = bucket_idx ^ local_mask;
    // auto new_bucket_idx = directory_page->GetSplitImageIndex(bucket_idx);
    for (uint32_t i = 0; i < bucket_page->Size(); ++i) {
      auto new_key = bucket_page->KeyAt(i);
      auto new_hash = Hash(new_key);
      if (new_hash & local_mask) {
        new_bucket_page->Insert(new_key, bucket_page->ValueAt(i), cmp_);
      }
    }
    for (uint32_t i = 0; i < bucket_page->Size(); ++i) {
      auto old_key = bucket_page->KeyAt(i);
      auto old_value = bucket_page->ValueAt(i);
      if (new_bucket_page->Lookup(old_key, old_value, cmp_)) {
        bucket_page->Remove(old_key, cmp_);
        i--;
      }
    }
    new_bucket_guard.Drop();
    // std::cout<<key<<" "<<new_bucket_idx<<" "<<new_bucket_page_id<<'\n';
    directory_page->SetBucketPageId(new_bucket_idx, new_bucket_page_id);
    // UpdateDirectoryMapping(directory_page,new_bucket_idx,new_bucket_page_id,directory_page->GetLocalDepth(),local_mask);
    bucket_guard.Drop();
    bucket_page_id = INVALID_PAGE_ID;
    bucket_page_id = directory_page->GetBucketPageId(bucket_idx);
    bucket_guard = bpm_->FetchPageWrite(bucket_page_id);
    bucket_page = bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
    // std::cout<<key<<" "<<bucket_idx<<' '<<bucket_page_id<<'\n';
    directory_page->SetBucketPageId(bucket_idx, bucket_page_id);
  }
  // bucket_page->PrintBucket();
  // std::cout<<"Insert:"<<key<<" "<<value<<" "<<bucket_idx<<'\n';
  auto insert_success = bucket_page->Insert(key, value, cmp_);
  // std::cout<<key<<" "<<bucket_idx<<' '<<bucket_page_id<<'\n';
  if (insert_success) {
    directory_page->SetBucketPageId(bucket_idx, bucket_page_id);
  }
  // directory_page->PrintDirectory();
  // bucket_page->PrintBucket();
  // bucket_guard.Drop();
  // directory_guard.Drop();
  return insert_success;
}

template <typename K, typename V, typename KC>
auto DiskExtendibleHashTable<K, V, KC>::InsertToNewDirectory(ExtendibleHTableHeaderPage *header, uint32_t directory_idx,
                                                             uint32_t hash, const K &key, const V &value) -> bool {
  page_id_t directory_page_id = INVALID_PAGE_ID;
  auto directory_guard = bpm_->NewPageGuarded(&directory_page_id);
  auto directory_page = directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
  directory_page->Init(directory_max_depth_);
  header->SetDirectoryPageId(directory_idx, directory_page_id);
  auto bucket_idx = directory_page->HashToBucketIndex(hash);
  auto insert_success = InsertToNewBucket(directory_page, bucket_idx, key, value);
  // directory_guard.Drop();
  return insert_success;
}

template <typename K, typename V, typename KC>
auto DiskExtendibleHashTable<K, V, KC>::InsertToNewBucket(ExtendibleHTableDirectoryPage *directory, uint32_t bucket_idx,
                                                          const K &key, const V &value) -> bool {
  page_id_t bucket_page_id = INVALID_PAGE_ID;
  auto bucket_guard = bpm_->NewPageGuarded(&bucket_page_id);
  auto bucket_page = bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
  bucket_page->Init(bucket_max_size_);
  directory->SetBucketPageId(bucket_idx, bucket_page_id);
  auto insert_success = bucket_page->Insert(key, value, cmp_);
  // bucket_guard.Drop();
  return insert_success;
}

template <typename K, typename V, typename KC>
void DiskExtendibleHashTable<K, V, KC>::UpdateDirectoryMapping(ExtendibleHTableDirectoryPage *directory,
                                                               uint32_t new_bucket_idx, page_id_t new_bucket_page_id,
                                                               uint32_t new_local_depth, uint32_t local_depth_mask) {
  directory->SetBucketPageId(new_bucket_idx, new_bucket_page_id);
}

/*****************************************************************************
 * REMOVE
 *****************************************************************************/
template <typename K, typename V, typename KC>
auto DiskExtendibleHashTable<K, V, KC>::Remove(const K &key, Transaction *transaction) -> bool {
  auto header_guard = bpm_->FetchPageWrite(header_page_id_);
  auto header_page = header_guard.AsMut<ExtendibleHTableHeaderPage>();
  auto hash = Hash(key);
  auto directory_page_index = header_page->HashToDirectoryIndex(Hash(key));
  page_id_t directory_page_id = INVALID_PAGE_ID;
  directory_page_id = header_page->GetDirectoryPageId(directory_page_index);
  if (directory_page_id == INVALID_PAGE_ID) {
    return false;
  }
  // header_guard.Drop();
  auto directory_guard = bpm_->FetchPageWrite(directory_page_id);
  auto directory_page = directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
  auto bucket_idx = directory_page->HashToBucketIndex(hash);
  page_id_t bucket_page_id = INVALID_PAGE_ID;
  bucket_page_id = directory_page->GetBucketPageId(bucket_idx);
  if (bucket_page_id == INVALID_PAGE_ID) {
    return false;
  }
  auto bucket_guard = bpm_->FetchPageWrite(bucket_page_id);
  auto bucket_page = bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
  auto remove_success = bucket_page->Remove(key, cmp_);
  if (!remove_success) {
    return false;
  }
  while (bucket_page->IsEmpty()) {
    auto global_depth = directory_page->GetGlobalDepth();
    if (global_depth == 0) {
      directory_page->SetBucketPageId(bucket_idx, INVALID_PAGE_ID);
      // header_page->SetDirectoryPageId(directory_page_index, INVALID_PAGE_ID);
      return true;
      // break;
    }
    auto new_bucket_idx = directory_page->GetSplitImageIndex(bucket_idx);
    page_id_t new_bucket_page_id = INVALID_PAGE_ID;
    new_bucket_page_id = directory_page->GetBucketPageId(new_bucket_idx);
    if (new_bucket_idx > bucket_idx) {
      auto new_bucket_guard = bpm_->FetchPageWrite(new_bucket_page_id);
      auto new_bucket_page = new_bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
      auto new_bucket_page_size = new_bucket_page->Size();
      for (uint32_t i = 0; i < new_bucket_page_size; ++i) {
        auto new_key = new_bucket_page->KeyAt(i);
        auto new_value = new_bucket_page->ValueAt(i);
        bucket_page->Insert(new_key, new_value, cmp_);
      }
      for (uint32_t i = 0; i < new_bucket_page_size; ++i) {
        auto new_key = new_bucket_page->KeyAt(0);
        new_bucket_page->Remove(new_key, cmp_);
      }
      new_bucket_guard.Drop();
      // for (uint32_t i = 0; i < directory_page->Size(); ++i) {
      //   page_id_t change_directory_page_id = INVALID_PAGE_ID;
      //   change_directory_page_id = header_page->GetDirectoryPageId(i);
      //   if (change_directory_page_id == new_bucket_page_id) {
      //     auto change_directory_guard = bpm_->FetchPageWrite(directory_page_id);
      //     auto change_directory_page = change_directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
      //     change_directory_page->SetBucketPageId(change_directory_page->HashToBucketIndex(hash), bucket_page_id);
      //     change_directory_guard.Drop();
      //   }
      // }
      bpm_->DeletePage(new_bucket_page_id);
    } else {
      // for (uint32_t i = 0; i < directory_page->Size(); ++i) {
      //   page_id_t change_directory_page_id = INVALID_PAGE_ID;
      //   change_directory_page_id = header_page->GetDirectoryPageId(i);
      //   if (change_directory_page_id == bucket_page_id) {
      //     auto change_directory_guard = bpm_->FetchPageWrite(directory_page_id);
      //     auto change_directory_page = change_directory_guard.AsMut<ExtendibleHTableDirectoryPage>();
      //     change_directory_page->SetBucketPageId(change_directory_page->HashToBucketIndex(hash), new_bucket_page_id);
      //     change_directory_guard.Drop();
      //   }
      // }
      bpm_->DeletePage(bucket_page_id);
      bucket_idx = new_bucket_idx;
    }
    directory_page->DecrLocalDepth(bucket_idx);
    if (directory_page->CanShrink()) {
      directory_page->DecrGlobalDepth();
      // std::cout<<directory_page->GetLocalDepth(bucket_idx)<<" "<<bucket_page->Size()<<'\n';
      // for(uint32_t i=1<<(global_depth-1);i<(1<<global_depth);++i){
      // }
    }
    bucket_page_id = INVALID_PAGE_ID;
    bucket_page_id = directory_page->GetBucketPageId(bucket_idx);
    bucket_guard.Drop();
    bucket_guard = bpm_->FetchPageWrite(bucket_page_id);
    bucket_page = bucket_guard.AsMut<ExtendibleHTableBucketPage<K, V, KC>>();
  }
  return true;
}

template class DiskExtendibleHashTable<int, int, IntComparator>;
template class DiskExtendibleHashTable<GenericKey<4>, RID, GenericComparator<4>>;
template class DiskExtendibleHashTable<GenericKey<8>, RID, GenericComparator<8>>;
template class DiskExtendibleHashTable<GenericKey<16>, RID, GenericComparator<16>>;
template class DiskExtendibleHashTable<GenericKey<32>, RID, GenericComparator<32>>;
template class DiskExtendibleHashTable<GenericKey<64>, RID, GenericComparator<64>>;
}  // namespace bustub
