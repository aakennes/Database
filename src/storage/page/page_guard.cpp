#include "storage/page/page_guard.h"
#include <iostream>
#include "buffer/buffer_pool_manager.h"

namespace bustub {

BasicPageGuard::BasicPageGuard(BasicPageGuard &&that) noexcept
    : bpm_(that.bpm_), page_(that.page_), is_dirty_(that.is_dirty_) {
  if (this != &that) {
    that.is_dirty_ = false;
    that.bpm_ = nullptr;
    that.page_ = nullptr;
  }
}

void BasicPageGuard::Drop() {
  if (page_ != nullptr) {
    bpm_->UnpinPage(page_->GetPageId(), is_dirty_);
  }
  is_dirty_ = false;
  bpm_ = nullptr;
  page_ = nullptr;
}

auto BasicPageGuard::operator=(BasicPageGuard &&that) noexcept -> BasicPageGuard & {
  if (this != &that) {
    Drop();
    bpm_ = that.bpm_;
    page_ = that.page_;
    is_dirty_ = that.is_dirty_;
    that.is_dirty_ = false;
    that.bpm_ = nullptr;
    that.page_ = nullptr;
  }
  return *this;
}

BasicPageGuard::~BasicPageGuard() { Drop(); };  // NOLINT

auto BasicPageGuard::UpgradeRead() -> ReadPageGuard {
  page_->RLatch();
  ReadPageGuard read_guard(bpm_, page_);
  is_dirty_ = false;
  bpm_ = nullptr;
  page_ = nullptr;
  return read_guard;
}

auto BasicPageGuard::UpgradeWrite() -> WritePageGuard {
  page_->WLatch();
  WritePageGuard write_guard(bpm_, page_);
  is_dirty_ = false;
  bpm_ = nullptr;
  page_ = nullptr;
  return write_guard;
}

ReadPageGuard::ReadPageGuard(BufferPoolManager *bpm, Page *page) : guard_(bpm, page) {
  // std::cout << "Construction1" << '\n';
}

ReadPageGuard::ReadPageGuard(ReadPageGuard &&that) noexcept
    : guard_(std::move(that.guard_)){
          // std::cout << "Construction2" << '\n';
      };

auto ReadPageGuard::operator=(ReadPageGuard &&that) noexcept -> ReadPageGuard & {
  if (this != &that) {
    if (guard_.page_ != nullptr) {
      guard_.page_->RUnlatch();
    }
    Drop();
    if (guard_.page_ != nullptr) {
      guard_.page_->RLatch();
    }
    guard_ = std::move(that.guard_);
  }
  return *this;
}
void ReadPageGuard::Drop() {
  // std::cout << "Drop() Run Success" << '\n';
  if (guard_.page_ != nullptr) {
    guard_.page_->RUnlatch();
    guard_.Drop();
  }
}

ReadPageGuard::~ReadPageGuard() {
  // std::cout << "~ReadPageGuard() Run Success" << '\n';
  // guard_.page_->RUnlatch();
  Drop();
}  // NOLINT

WritePageGuard::WritePageGuard(BufferPoolManager *bpm, Page *page) : guard_(bpm, page) {}

WritePageGuard::WritePageGuard(WritePageGuard &&that) noexcept : guard_(std::move(that.guard_)){};

auto WritePageGuard::operator=(WritePageGuard &&that) noexcept -> WritePageGuard & {
  if (this != &that) {
    if (guard_.page_ != nullptr) {
      guard_.page_->WUnlatch();
    }
    Drop();
    if (guard_.page_ != nullptr) {
      guard_.page_->WLatch();
    }
    guard_ = std::move(that.guard_);
  }
  return *this;
}

void WritePageGuard::Drop() {
  if (guard_.page_ != nullptr) {
    guard_.page_->WUnlatch();
    guard_.Drop();
  }
}

WritePageGuard::~WritePageGuard() { 
  // guard_.page_->WUnlatch();
  Drop(); 
}  // NOLINT

}  // namespace bustub
