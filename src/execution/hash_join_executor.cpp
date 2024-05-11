//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// hash_join_executor.cpp
//
// Identification: src/execution/hash_join_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/hash_join_executor.h"
#include "type/value_factory.h"

namespace bustub {

HashJoinExecutor::HashJoinExecutor(ExecutorContext *exec_ctx, const HashJoinPlanNode *plan,
                                   std::unique_ptr<AbstractExecutor> &&left_child,
                                   std::unique_ptr<AbstractExecutor> &&right_child)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    left_executor_(std::move(left_child)),
    right_executor_(std::move(right_child)){
  // ht_={};
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2023 Fall: You ONLY need to implement left join and inner join.
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
  
  
}

void HashJoinExecutor::Init() {
  right_executor_->Init();
  while(true){
    Tuple right_tuple;
		RID right_rid;
		auto status = right_executor_->Next(&right_tuple, &right_rid);
		if (!status) {
			break;
		}
    // std::cout<<right_tuple.ToString(&right_schema_)<<'\n';
    auto right_key=MakeHashJoinKey(&right_tuple,false);
    if(ht_.find(right_key)==ht_.end()){
      // auto right_value=MakeHashJoinValue(&right_tuple);
      ht_[right_key]={right_tuple};
      // ht_.insert({right_key,{right_tuple}});
    }else{
      ht_[right_key].push_back(right_tuple);
    }
  }
  left_executor_->Init();
  while(true){
    Tuple left_tuple;
		RID left_rid;
    auto status = left_executor_->Next(&left_tuple, &left_rid);
    if (!status) {
      break;
    }
    auto left_key=MakeHashJoinKey(&left_tuple,true);
    // std::cout<<"3:"<<left_tuple.ToString(&left_schema_)<<'\n';
    if(ht_.find(left_key)!=ht_.end()){
      // std::cout<<"2:"<<left_tuple.ToString(&left_schema_)<<'\n';
      auto right_tuples=ht_[left_key];
      for(auto &right_tuple:right_tuples){
        std::vector<Value> join_values{};
        join_values.reserve(left_size_+right_size_);
        for(uint32_t i=0;i<left_size_;++i){
          join_values.push_back(left_tuple.GetValue(&left_schema_,i));
        }
        for(uint32_t i=0;i<right_size_;++i){
          join_values.push_back(right_tuple.GetValue(&right_schema_,i));
        }
        auto join_tuple=Tuple(join_values,&plan_->OutputSchema());
        tuple_vec_.emplace_back(join_tuple);
      }
    }else if(plan_->GetJoinType() == JoinType::LEFT){
      // std::cout<<"1:"<<left_tuple.ToString(&left_schema_)<<'\n';
      std::vector<Value> join_values{};
      join_values.reserve(left_size_+right_size_);
      for(uint32_t i=0;i<left_size_;++i){
        join_values.push_back(left_tuple.GetValue(&left_schema_,i));
      }
      for(uint32_t i=0;i<right_size_;++i){
        join_values.push_back(ValueFactory::GetNullValueByType(INTEGER));
      }
      
      auto join_tuple=Tuple(join_values,&plan_->OutputSchema());
      // std::cout<<"1:"<<left_tuple.ToString(&left_schema_)<<'\n';
      tuple_vec_.emplace_back(join_tuple);
    }
  }
  tuple_size_=tuple_vec_.size();
  // throw NotImplementedException("HashJoinExecutor is not implemented"); 
}

auto HashJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool {
  if(tuple_num_>=tuple_size_){
    return false;
  }
  *tuple=tuple_vec_[tuple_num_++];
  std::cout<<tuple->ToString(&plan_->OutputSchema())<<'\n';
  *rid=tuple->GetRid();
  return true; 
}

}  // namespace bustub
