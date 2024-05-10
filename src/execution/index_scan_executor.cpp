//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// index_scan_executor.cpp
//
// Identification: src/execution/index_scan_executor.cpp
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include "execution/executors/index_scan_executor.h"

namespace bustub {
IndexScanExecutor::IndexScanExecutor(ExecutorContext *exec_ctx, const IndexScanPlanNode *plan)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    catalog_(exec_ctx_->GetCatalog()),
    index_info_(catalog_->GetIndex(plan_->index_oid_)),
    table_info_(catalog_->GetTable(index_info_->table_name_)),
    htable_(dynamic_cast<HashTableIndexForTwoIntegerColumn *>(index_info_->index_.get())){}

void IndexScanExecutor::Init() {
    std::unordered_map<RID,Value> vis_rid;
    // std::cout<<plan_->pred_keys_.size()<<'\n';
    for(auto &expr:plan_->pred_keys_){
        std::vector<RID> temp_vec{};
        std::vector<Value> values{};
        auto *pred_keys = dynamic_cast<const ConstantValueExpression *>(expr.get());
        values.push_back(pred_keys->val_);
        // std::cout<<expr->ToString()<<'\n';
        auto now_tuple = Tuple(values, &index_info_->key_schema_);
        htable_->ScanKey(now_tuple,&temp_vec,exec_ctx_->GetTransaction());
        // std::cout<<now_tuple.ToString(&index_info_->key_schema_)<<'\n';
        for(auto rid:temp_vec){
            if(vis_rid.find(rid)==vis_rid.end()){
                vis_rid[rid]=pred_keys->val_;
                RID_vec_.push_back(rid);
            }
        }
    }
    // std::cout<<RID_vec_.size()<<'\n';
}

auto IndexScanExecutor::Next(Tuple *tuple, RID *rid) -> bool {
    while(true){
        if(vec_now_>=RID_vec_.size()){
            return false;
        }
        *rid = RID_vec_[vec_now_];
        *tuple=table_info_->table_->GetTuple(*rid).second;
        
        auto tuple_meta = table_info_->table_->GetTuple(*rid).first;
        vec_now_++;
        if(tuple_meta.is_deleted_){continue;}
        auto &filter_expr = plan_->filter_predicate_;
        // for(auto &index_expr:plan_->pred_keys_){
        //     std::cout<<filter_expr->ToString()<<" "<<index_expr->ToString()<<" HEREasdas\n";
        //     auto value=index_expr->Evaluate(tuple, plan_->OutputSchema());
        //     if (!value.IsNull() && value.GetAs<bool>()) {
        //         return true;
        //     }
        // }
        auto value=filter_expr->Evaluate(tuple, plan_->OutputSchema());
        if (!value.IsNull() && value.GetAs<bool>()) {
            return true;
        }
    }
    return false;
}

}  // namespace bustub
