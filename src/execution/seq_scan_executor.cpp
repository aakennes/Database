//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// seq_scan_executor.cpp
//
// Identification: src/execution/seq_scan_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/seq_scan_executor.h"

namespace bustub {

SeqScanExecutor::SeqScanExecutor(ExecutorContext *exec_ctx, const SeqScanPlanNode *plan) 
:   AbstractExecutor(exec_ctx),
    plan_(plan),
    catalog_(exec_ctx_->GetCatalog()),
    table_info_(catalog_->GetTable(plan_->GetTableOid())),
    table_iter_(std::make_unique<TableIterator>(table_info_->table_->MakeIterator())){}
    //we need to use std::move() to copy table_iter_ ,so that we use unique_ptr
void SeqScanExecutor::Init() { 

    // throw NotImplementedException("SeqScanExecutor is not implemented"); 
}

auto SeqScanExecutor::Next(Tuple *tuple, RID *rid) -> bool { 
    auto filter_expr = plan_->filter_predicate_;
    //copy from filter_executor.cpp
    while(true){
        if(table_iter_->IsEnd()){
            return false;
        }
        *tuple = Tuple(table_iter_->GetTuple().second);
        *rid = table_iter_->GetRID();
        // std::cout<<tuple->ToString(&GetOutputSchema())<<'\n';
        auto tuple_meta = table_iter_->GetTuple().first;
        ++*table_iter_;
        if(tuple_meta.is_deleted_){continue;}
        if(!filter_expr){
            return true;
        }
        //check whether tuple meets the filter or not ,when filter may push down to the seqscan
        auto value = filter_expr->Evaluate(tuple, GetOutputSchema());
        // std::cout<<"HERE\n";
        if (!value.IsNull() && value.GetAs<bool>()) {
            return true;
        }
        // puts("HERE");
    }
    return false; 
}

}  // namespace bustub
