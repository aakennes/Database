//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// insert_executor.cpp
//
// Identification: src/execution/insert_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "execution/executors/insert_executor.h"

namespace bustub {

InsertExecutor::InsertExecutor(ExecutorContext *exec_ctx, const InsertPlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    catalog_(exec_ctx_->GetCatalog()),
    table_info_(catalog_->GetTable(plan_->GetTableOid())),
    table_index_(catalog_->GetTableIndexes(table_info_->name_)),
    child_executor_(std::move(child_executor)){}

void InsertExecutor::Init() { 
    // throw NotImplementedException("InsertExecutor is not implemented"); 
}

auto InsertExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool {
    //copy from filter_executor.cpp
    if(is_done_){
        return false;
    }
    int insert_count=0;
    auto child_plan=plan_->GetChildPlan();
    while(true){
        Tuple child_tuple;
        RID child_rid;
        auto status = child_executor_->Next(&child_tuple, &child_rid);
        if (!status) {
            break;
        }
        auto insert_rid=table_info_->table_->InsertTuple(TupleMeta{0, false}, child_tuple);
        if(!insert_rid){
            continue;
        }
        for (auto insert_index : table_index_) {
            insert_index->index_->InsertEntry(child_tuple.KeyFromTuple(table_info_->schema_, insert_index->key_schema_,insert_index->index_->GetKeyAttrs()),insert_rid.value(), exec_ctx_->GetTransaction());
        }
        insert_count++;
    }
    std::vector<Value> values{{TypeId::INTEGER,insert_count}};
    *tuple=Tuple{values,&GetOutputSchema()};
    is_done_=true;
    return true; 
}

}  // namespace bustub
