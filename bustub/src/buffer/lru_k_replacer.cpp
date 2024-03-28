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
#include "common/exception.h"

namespace bustub {

LRUKNode::LRUKNode(std::list<size_t> history, size_t k, frame_id_t fid, bool is_evictable)
    : history_(history), k_(k), fid_(fid), is_evictable_(is_evictable){};

LRUKReplacer::LRUKReplacer(size_t num_frames, size_t k) : replacer_size_(num_frames), k_(k) {}

LRUKReplacer::~LRUKReplacer() {
    std::vector<std::shared_ptr<LRUKNode>> nodes_to_delete;
    for (auto& pair : node_store_) {
        nodes_to_delete.push_back(pair.second);
    }
    for (auto& pair : node_less_k_) {
        nodes_to_delete.push_back(pair);
    }
    for (auto& pair : node_more_k_) {
        nodes_to_delete.push_back(pair);
    }
    for (auto [frame_id_now, node_now] : node_store_) {
      node_now->history_.clear();
    }
    node_store_.clear();
    node_less_k_.clear();
    node_more_k_.clear();
    nodes_to_delete.clear();
}

auto LRUKReplacer::Evict(frame_id_t *frame_id) -> bool {
  std::lock_guard<std::mutex> guard(latch_);
  for (auto node_now : node_less_k_) {
    if (node_now->Is_evictable() == true) {
      *frame_id = node_now->Fid();
      curr_size_--;
      node_store_[*frame_id]->is_evictable_change();
      node_less_k_.erase(node_now);
      node_now->history_.clear();
      node_store_[*frame_id]->history_.clear();
      return true;
    }else break;
  }
  for (auto node_now : node_more_k_) {
    if (node_now->Is_evictable() == true) {
      *frame_id = node_now->Fid();
      curr_size_--;
      node_store_[*frame_id]->is_evictable_change();
      node_more_k_.erase(node_now);
      node_now->history_.clear();
      node_store_[*frame_id]->history_.clear();
      return true;
    }else break;
  }
  // *frame_id=static_cast<frame_id_t>(node_more_k_.size());
  return false;
}

void LRUKReplacer::RecordAccess(frame_id_t frame_id, AccessType access_type) {
  std::lock_guard<std::mutex> guard(latch_);
  if (replacer_size_ < static_cast<size_t>(frame_id)) {
    throw NotImplementedException("para of LRUKReplacer::RecordAccess is not safe");
  }
  current_timestamp_++;
  auto frame_node=std::make_shared<LRUKNode>();
  bool exist_frame_id=node_store_.find(frame_id) == node_store_.end();
  if (!exist_frame_id) {
    frame_node=node_store_[frame_id];
    if (frame_node->history_.size()+1 == frame_node->K()) {
      LRUKNode& tmp=*frame_node;
      node_less_k_.erase(frame_node);
      tmp.history_.push_back(current_timestamp_);
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    } else if (frame_node->history_.size()>= frame_node->K()) {
      LRUKNode& tmp=*frame_node;
      node_more_k_.erase(frame_node);
      tmp.history_.pop_front();
      tmp.history_.push_back(current_timestamp_);
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    } else if (frame_node->history_.size() == 0) {
      frame_node->history_.push_back(current_timestamp_);
      node_less_k_.insert(frame_node);
    }
  } else {
    std::list<size_t> new_history;
    new_history.push_back(current_timestamp_);
    map_size_++;
    std::shared_ptr<LRUKNode> frame_node_new(new LRUKNode(new_history, k_, map_size_, false));
    node_less_k_.insert(frame_node_new);
    node_store_[map_size_] = frame_node_new; 
  }
}

void LRUKReplacer::SetEvictable(frame_id_t frame_id, bool set_evictable) {
  std::lock_guard<std::mutex> guard(latch_);
  bool Exist1=node_store_.find(frame_id) == node_store_.end();
  if (Exist1) {
    return;
  }
  if (set_evictable != node_store_[frame_id]->Is_evictable()) {
    if(node_more_k_.find(node_store_[frame_id])!=node_more_k_.end()){
      LRUKNode& tmp=*node_store_[frame_id];
      node_more_k_.erase(node_store_[frame_id]);
      tmp.is_evictable_=set_evictable;
      node_more_k_.insert(std::make_shared<LRUKNode>(tmp));
    }else if(node_less_k_.find(node_store_[frame_id])!=node_less_k_.end()){
      LRUKNode& tmp=*node_store_[frame_id];
      node_less_k_.erase(node_store_[frame_id]);
      tmp.is_evictable_=set_evictable;
      node_less_k_.insert(std::make_shared<LRUKNode>(tmp));
    }else node_store_[frame_id]->is_evictable_change();
    if (set_evictable)curr_size_++;
    else curr_size_--;
  }
}

void LRUKReplacer::Remove(frame_id_t frame_id) {
  std::lock_guard<std::mutex> guard(latch_);
  if (node_store_.find(frame_id) == node_store_.end()) {
    return;
  }
  if (node_store_[frame_id]->Is_evictable() == false) {
    throw NotImplementedException("para of LRUKReplacer::Remove is not safe");
  }
  if (node_more_k_.find(node_store_[frame_id]) != node_more_k_.end()){
    curr_size_--;
    auto& tmp=*node_store_[frame_id];
    node_more_k_.erase(node_store_[frame_id]);
    tmp.is_evictable_change();
  } 
  if (node_less_k_.find(node_store_[frame_id]) != node_less_k_.end()){
    curr_size_--;
    auto& tmp=*node_store_[frame_id];
    node_less_k_.erase(node_store_[frame_id]);
    tmp.is_evictable_change();
  } 
  node_store_[frame_id]->history_.clear();
}

auto LRUKReplacer::Size() -> size_t { return curr_size_; }

}  // namespace bustub
