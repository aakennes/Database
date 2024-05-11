//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_loop_join_executor.cpp
//
// Identification: src/execution/nested_loop_join_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_loop_join_executor.h"
#include "binder/table_ref/bound_join_ref.h"
#include "common/exception.h"
#include "type/value_factory.h"

namespace bustub {

NestedLoopJoinExecutor::NestedLoopJoinExecutor(ExecutorContext *exec_ctx, const NestedLoopJoinPlanNode *plan,
                                               std::unique_ptr<AbstractExecutor> &&left_executor,
                                               std::unique_ptr<AbstractExecutor> &&right_executor)
    : AbstractExecutor(exec_ctx),
    plan_(plan), 
    left_executor_(std::move(left_executor)),
    right_executor_(std::move(right_executor)){
  if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER)) {
    // Note for 2023 Fall: You ONLY need to implement left join and inner join.
    throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
  }
}

void NestedLoopJoinExecutor::Init() { 
  left_executor_->Init();
  right_executor_->Init();
  while(true){
    Tuple right_tuple;
		RID right_rid;
		auto status = right_executor_->Next(&right_tuple, &right_rid);
		if (!status) {
			break;
		}
    // std::cout<<"SDADSA\n";
    right_tuples_.push_back(right_tuple);
  }
  // std::cout<<right_tuples_.size()<<'\n';
  // throw NotImplementedException("NestedLoopJoinExecutor is not implemented"); 
}

auto NestedLoopJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool { 
  while(true){
    Tuple left_tuple;
		RID left_rid;
    std::cout<<right_tuples_.size()<<'\n';
    if(!is_first_||last_right_id_>=right_tuples_.size()){
      last_right_id_=0;
      is_first_=true;
      auto status = left_executor_->Next(&left_tuple, &left_rid);
      if (!status) {
        break;
      }
      right_executor_->Init();
      // Init();
      is_find_=false;
    }
    else{
      left_tuple=last_left_tuple_;
      left_rid=left_tuple.GetRid();
      // std::cout<<left_tuple.ToString(&plan_->GetLeftPlan()->OutputSchema())<<'\n';
    }
    last_left_tuple_=left_tuple;
    
    // std::cout<<left_tuple.ToString(&plan_->GetLeftPlan()->OutputSchema())<<" "<<right_tuples_.size()<<'\n';
    for(uint32_t i=last_right_id_;i<right_tuples_.size();++i){
      auto &right_tuple=right_tuples_[i];
      auto value=plan_->predicate_->EvaluateJoin(&left_tuple, left_executor_->GetOutputSchema(), &right_tuple, right_executor_->GetOutputSchema());
      if (!value.IsNull() && value.GetAs<bool>()) {
        std::vector<Value> join_values{};
        auto left_schema=plan_->GetLeftPlan()->OutputSchema();
        auto right_schema=plan_->GetRightPlan()->OutputSchema();
        auto left_size=left_schema.GetColumnCount();
        auto right_size=right_schema.GetColumnCount();
        join_values.reserve(left_executor_->GetOutputSchema().GetColumnCount()+right_executor_->GetOutputSchema().GetColumnCount());
        for(uint32_t i=0;i<left_size;++i){
          join_values.push_back(left_tuple.GetValue(&left_schema,i));
        }
        for(uint32_t i=0;i<right_size;++i){
          join_values.push_back(right_tuple.GetValue(&right_schema,i));
        }
        *tuple=Tuple(join_values,&plan_->OutputSchema());
        *rid=tuple->GetRid();
        last_right_id_=i+1;
        is_find_=true;
        return true;
      }
    }
    last_right_id_=right_tuples_.size()+1;
    if(!is_find_&&plan_->GetJoinType() == JoinType::LEFT){
      std::vector<Value> join_values{};
      auto left_schema=plan_->GetLeftPlan()->OutputSchema();
      auto right_schema=plan_->GetRightPlan()->OutputSchema();
      auto left_size=left_schema.GetColumnCount();
      auto right_size=right_schema.GetColumnCount();
      join_values.reserve(left_executor_->GetOutputSchema().GetColumnCount()+right_executor_->GetOutputSchema().GetColumnCount());
      for(uint32_t i=0;i<left_size;++i){
        join_values.push_back(left_tuple.GetValue(&left_schema,i));
      }
      // std::cout<<left_tuple.ToString(&left_schema)<<" "<<right_tuple.ToString(&right_schema)<<'\n';
      for(uint32_t i=0;i<right_size;++i){
        join_values.push_back(ValueFactory::GetNullValueByType(INTEGER));
      }
      *tuple=Tuple(join_values,&plan_->OutputSchema());
      *rid=tuple->GetRid();
      return true;
    }
  }
  return false; 
}
  
}  // namespace bustub
