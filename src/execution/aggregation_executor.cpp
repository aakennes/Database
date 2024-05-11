//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// aggregation_executor.cpp
//
// Identification: src/execution/aggregation_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include <memory>
#include <vector>

#include "execution/executors/aggregation_executor.h"

namespace bustub {

AggregationExecutor::AggregationExecutor(ExecutorContext *exec_ctx, const AggregationPlanNode *plan,
                                         std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    child_executor_(std::move(child_executor)),
    aht_(plan_->aggregates_,plan_->agg_types_),
    aht_iterator_({}) {}

void AggregationExecutor::Init() {
    child_executor_->Init();
    Tuple child_tuple;
    RID child_rid;
    while(true){
        auto status = child_executor_->Next(&child_tuple, &child_rid);
		if (!status) {
			break;
		}
        aht_.InsertCombine(MakeAggregateKey(&child_tuple), MakeAggregateValue(&child_tuple));
    }
    if(plan_->GetGroupBys().empty()){
        // std::cout<<"HERER\n";
        aht_.GenerateNull();
        // std::cerr<<"HASDASD:"<<(aht_.End()==aht_.Begin())<<'\n';
        // aht_.InsertCombine({}, aht_.GenerateInitialAggregateValue());
    }
    aht_iterator_=aht_.Begin();
}

auto AggregationExecutor::Next(Tuple *tuple, RID *rid) -> bool { 
    // auto aggregate=plan_->;
    // if(plan_->GetGroupBys().empty()){
    //     return false;
    // }
    while(true){
        if(aht_iterator_==aht_.End()){
            return false;
        }
        auto aggregate_key = aht_iterator_.Key();
        auto aggregate_val = aht_iterator_.Val();
        ++aht_iterator_;
        std::vector<Value> aggregate_values{};
        aggregate_values.reserve(aggregate_key.group_bys_.size()+aggregate_val.aggregates_.size());
        aggregate_values.insert(aggregate_values.end(),aggregate_key.group_bys_.begin(),aggregate_key.group_bys_.end());
        aggregate_values.insert(aggregate_values.end(),aggregate_val.aggregates_.begin(),aggregate_val.aggregates_.end());
        // aggregate_values.emplace_back(aggregate_val.aggregates_);
        // puts("ASDaaa");
        // std::cout<<aggregate_key.group_bys_.size()<<" "<<aggregate_val.aggregates_.size()<<'\n';
		*tuple=Tuple(aggregate_values,&plan_->OutputSchema());
        *rid = tuple->GetRid();
        // std::cout<<tuple->ToString(&GetOutputSchema())<<'\n';
        
        return true;
    }
    // std::cout<<"HERE\n";
    return false; 
}

auto AggregationExecutor::GetChildExecutor() const -> const AbstractExecutor * { return child_executor_.get(); }

}  // namespace bustub
