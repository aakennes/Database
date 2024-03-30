
//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager.h"

#include "common/exception.h"
#include "common/macros.h"
#include "storage/page/page_guard.h"

namespace bustub {

BufferPoolManager::BufferPoolManager(size_t pool_size, DiskManager *disk_manager, size_t replacer_k,
                                     LogManager *log_manager)
    : pool_size_(pool_size), disk_scheduler_(std::make_unique<DiskScheduler>(disk_manager)), log_manager_(log_manager) {
  // TODO(students): remove this line after you have implemented the buffer pool manager
  // throw NotImplementedException(
  //     "BufferPoolManager is not implemented yet. If you have finished implementing BPM, please remove the throw "
  //     "exception line in `buffer_pool_manager.cpp`.");

  // we allocate a consecutive memory space for the buffer pool
  pages_ = new Page[pool_size_];
  replacer_ = std::make_unique<LRUKReplacer>(pool_size, replacer_k);

  // Initially, every page is in the free list.
  for (size_t i = 0; i < pool_size_; ++i) {
    free_list_.emplace_back(static_cast<int>(i));
  }
}

BufferPoolManager::~BufferPoolManager() { delete[] pages_; }

auto BufferPoolManager::NewPage(page_id_t *page_id) -> Page * {
  std::unique_lock<std::mutex> guard(latch_);
  frame_id_t frame_now;
  if (!free_list_.empty()) {
    frame_now = free_list_.front();
    free_list_.pop_front();
  } else {
    bool check_evict = replacer_->Evict(&frame_now);
    if (check_evict) {
      auto page_old = &pages_[frame_now];
      auto page_old_id = page_old->GetPageId();
      if (page_old->IsDirty()) {
        guard.unlock();
        FlushPage(page_old_id);
        guard.lock();
      }
      page_table_.erase(page_old_id);
    } else {
      return nullptr;
    }
  }
  *page_id = AllocatePage();
  page_table_[*page_id] = frame_now;
  auto page_new = &pages_[frame_now];
  page_new->ResetMemory();
  page_new->page_id_ = *page_id;
  page_new->is_dirty_ = true;
  page_new->pin_count_ = 1;
  guard.unlock();
  replacer_->RecordAccess(frame_now);
  replacer_->SetEvictable(frame_now, false);
  guard.lock();
  return page_new;
}

auto BufferPoolManager::FetchPage(page_id_t page_id, [[maybe_unused]] AccessType access_type) -> Page * {
  std::unique_lock<std::mutex> guard(latch_);
  frame_id_t frame_tofetch;
  if (page_table_.find(page_id) != page_table_.end()) {
    frame_tofetch = page_table_[page_id];
  }else if (!free_list_.empty()) {
    frame_tofetch = free_list_.front();
    free_list_.pop_front();
  } else {
    bool check_evict = replacer_->Evict(&frame_tofetch);
    if (check_evict) {
      auto page_old = &pages_[frame_tofetch];
      auto page_old_id = page_old->GetPageId();
      if (page_old->IsDirty()) {
        guard.unlock();
        FlushPage(page_old_id);
        guard.lock();
      }
      page_table_.erase(page_old_id);
    } else {
      return nullptr;
    }
  }
  page_table_[page_id] = frame_tofetch;
  auto page_tofetch = &pages_[frame_tofetch];
  disk_scheduler_->disk_manager_->ReadPage(page_id, page_tofetch->data_);
  page_tofetch->page_id_ = page_id;
  page_tofetch->is_dirty_ = true;
  page_tofetch->pin_count_++;
  guard.unlock();
  replacer_->RecordAccess(frame_tofetch);
  replacer_->SetEvictable(frame_tofetch, false);
  guard.lock();
  return page_tofetch;
}

auto BufferPoolManager::UnpinPage(page_id_t page_id, bool is_dirty, [[maybe_unused]] AccessType access_type) -> bool {
  std::unique_lock<std::mutex> guard(latch_);
  if (page_table_.find(page_id) == page_table_.end()) {
    return false;
  }
  frame_id_t frame_target = page_table_[page_id];
  auto page_toschedule = &pages_[frame_target];
  if (page_toschedule->GetPinCount() <= 0) {
    return false;
  }
  if (--page_toschedule->pin_count_ == 0) {
    guard.unlock();
    replacer_->SetEvictable(page_table_[page_id], true);
    guard.lock();
  }
  page_toschedule->is_dirty_ = is_dirty;
  return true;
}

auto BufferPoolManager::FlushPage(page_id_t page_id) -> bool {
  std::unique_lock<std::mutex> guard(latch_);
  if (page_table_.find(page_id) == page_table_.end()) {
    return false;
  }
  frame_id_t frame_target = page_table_[page_id];
  auto page_target = &pages_[frame_target];
  disk_scheduler_->disk_manager_->WritePage(page_id, page_target->data_);
  page_target->is_dirty_ = false;
  return true;
}

void BufferPoolManager::FlushAllPages() {
  std::unique_lock<std::mutex> guard(latch_);
  for (auto [page_id_now, frame_id_now] : page_table_) {
    guard.unlock();
    FlushPage(page_id_now);
    guard.lock();
  }
  // guard.unlock();
}

auto BufferPoolManager::DeletePage(page_id_t page_id) -> bool {
  std::unique_lock<std::mutex> guard(latch_);
  if (page_table_.find(page_id) == page_table_.end()) {
    // guard.unlock();
    return true;
  }
  frame_id_t frame_target = page_table_[page_id];
  auto page_target = &pages_[frame_target];
  if (page_target->GetPinCount() > 0) {
    // guard.unlock();
    return false;
  }
  page_table_.erase(page_id);
  guard.unlock();
  replacer_->Remove(frame_target);
  guard.lock();
  free_list_.push_back(frame_target);
  page_target->ResetMemory();
  // guard.unlock();
  DeallocatePage(page_id);
  // guard.lock();
  // guard.unlock();
  return true;
}

auto BufferPoolManager::AllocatePage() -> page_id_t { return next_page_id_++; }

auto BufferPoolManager::FetchPageBasic(page_id_t page_id) -> BasicPageGuard { return {this, nullptr}; }

auto BufferPoolManager::FetchPageRead(page_id_t page_id) -> ReadPageGuard { return {this, nullptr}; }

auto BufferPoolManager::FetchPageWrite(page_id_t page_id) -> WritePageGuard { return {this, nullptr}; }

auto BufferPoolManager::NewPageGuarded(page_id_t *page_id) -> BasicPageGuard { return {this, nullptr}; }

}  // namespace bustub
