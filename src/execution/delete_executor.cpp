//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// delete_executor.cpp
//
// Identification: src/execution/delete_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "execution/executors/delete_executor.h"

namespace bustub {

DeleteExecutor::DeleteExecutor(ExecutorContext *exec_ctx, const DeletePlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    catalog_(exec_ctx_->GetCatalog()),
    table_info_(catalog_->GetTable(plan_->GetTableOid())),
    table_index_(catalog_->GetTableIndexes(table_info_->name_)),
    child_executor_(std::move(child_executor)){}

void DeleteExecutor::Init() { 
    // throw NotImplementedException("DeleteExecutor is not implemented"); 
}

auto DeleteExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool { 
    if(is_done_){
        return false;
    }
    int delete_count=0;
    while(true){
        Tuple child_tuple;
        RID child_rid;
        auto status = child_executor_->Next(&child_tuple, &child_rid);
        if (!status) {
            break;
        }
        auto delete_rid=child_rid;
        if(delete_rid.GetPageId()==INVALID_PAGE_ID){
            continue;
        }
        auto delete_tuplemeta=table_info_->table_->GetTupleMeta(delete_rid);
        delete_tuplemeta.is_deleted_=true;
        table_info_->table_->UpdateTupleMeta(delete_tuplemeta,delete_rid);
        for (auto delete_index : table_index_) {
            delete_index->index_->DeleteEntry(child_tuple.KeyFromTuple(table_info_->schema_, delete_index->key_schema_,delete_index->index_->GetKeyAttrs()),delete_rid, exec_ctx_->GetTransaction());
        }
        delete_count++;
    }
    std::vector<Value> values{{TypeId::INTEGER,delete_count}};
    *tuple=Tuple{values,&GetOutputSchema()};
    is_done_=true;
    return true; 
}

}  // namespace bustub
