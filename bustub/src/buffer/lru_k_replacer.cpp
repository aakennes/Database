//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_k_replacer.cpp
//
// Identification: src/buffer/lru_k_replacer.cpp
//
// Copyright (c) 2015-2022, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_k_replacer.h"
#include <utility>
#include "common/exception.h"

namespace bustub {

LRUKNode::LRUKNode(std::list<size_t> history, size_t k, frame_id_t fid, bool is_evictable)
    : history_(std::move(history)), k_(k), fid_(fid), is_evictable_(is_evictable){};

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : replacer_size_(num_frames), k_(k) {}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool {
  std::scoped_lock<std::mutex> guard(latch_);
  ++current_timestamp_;
  for (const auto& node_now : node_less_k_) {
    if (node_now->Isevictable()) {
      *frame_id = node_now->Fid();
      node_less_k_.erase(node_store_[*frame_id]);
      // node_store_[*frame_id]->is_evictable_=false;
      node_store_[*frame_id]->history_.clear();
      curr_size_--;
      return true;
    }
    break;
    
  }
  for (const auto& node_now : node_more_k_) {
    if (node_now->Isevictable()) {
      *frame_id = node_now->Fid();
      node_more_k_.erase(node_store_[*frame_id]);
      // node_store_[*frame_id]->is_evictable_=false;
      node_store_[*frame_id]->history_.clear();
      curr_size_--;
      return true;
    }
    break;
  }
  return false;
}

void LRUKReplacer::RecordAccess(frame_id_t frame_id, AccessType access_type) {
  std::scoped_lock<std::mutex> guard(latch_);
  BUSTUB_ASSERT(static_cast<size_t>(frame_id) < replacer_size_, "Invalid frame_id");
  current_timestamp_++;
  bool exist_frame_id = node_store_.find(frame_id) == node_store_.end();
  if (!exist_frame_id) {
    auto frame_node = node_store_[frame_id];
    if (frame_node->history_.size() + 1 == frame_node->K()) {
      LRUKNode &tmp = *node_store_[frame_id];
      node_less_k_.erase(frame_node);
      tmp.history_.push_back(current_timestamp_);
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    } else if (frame_node->history_.size() >= frame_node->K()) {
      LRUKNode &tmp = *node_store_[frame_id];
      node_more_k_.erase(frame_node);
      tmp.history_.pop_front();
      tmp.history_.push_back(current_timestamp_);
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    } else if (frame_node->history_.empty()) {
      frame_node->history_.push_back(current_timestamp_);
      node_less_k_.insert(frame_node);
    }
  } else {
    if(replacer_size_==node_store_.size()){
      return;
    }
    std::list<size_t> new_history(1, current_timestamp_);
    std::shared_ptr<LRUKNode> frame_node_new(new LRUKNode(std::move(new_history), k_, frame_id, false));
    node_less_k_.insert(frame_node_new);
    node_store_[frame_id] = frame_node_new;
  }
} 

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable) {
  std::scoped_lock<std::mutex> guard(latch_);
  if (node_store_.find(frame_id) == node_store_.end()) {
    return;
  }
  if (set_evictable != node_store_[frame_id]->Isevictable()) {
    if (node_more_k_.find(node_store_[frame_id]) != node_more_k_.end()) {
      LRUKNode &tmp = *node_store_[frame_id];
      node_more_k_.erase(node_store_[frame_id]);
      tmp.is_evictable_ = set_evictable;
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    } else if (node_less_k_.find(node_store_[frame_id]) != node_less_k_.end()) {
      LRUKNode &tmp = *node_store_[frame_id];
      node_less_k_.erase(node_store_[frame_id]);
      tmp.is_evictable_ = set_evictable;
      node_less_k_.insert(std::make_shared<LRUKNode>(tmp));
    }
    node_store_[frame_id]->is_evictable_=set_evictable;
    if (set_evictable){
      curr_size_++;
    }else{
      curr_size_--;
    }
  }
  // guard.unlock();
}

void LRUKReplacer::Remove(frame_id_t frame_id) {
  std::scoped_lock<std::mutex> guard(latch_);
  if (node_store_.find(frame_id) == node_store_.end()) {
    return;
  }
  if (!node_store_[frame_id]->Isevictable()) {
    throw Exception("Attempted to remove a non-evictable frame");
  }
  if (node_more_k_.find(node_store_[frame_id]) != node_more_k_.end()) {
    node_more_k_.erase(node_store_[frame_id]);
  }
  if (node_less_k_.find(node_store_[frame_id]) != node_less_k_.end()) {
    node_less_k_.erase(node_store_[frame_id]);
  }
  curr_size_--;
  node_store_[frame_id]->is_evictable_=false;
  node_store_[frame_id]->history_.clear();
  node_store_.erase(frame_id);
}

auto LRUKReplacer::Size() -> size_t { return curr_size_; }

}  // namespace bustub