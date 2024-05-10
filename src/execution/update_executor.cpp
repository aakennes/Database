//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// update_executor.cpp
//
// Identification: src/execution/update_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include <memory>
#include <vector>

#include "execution/executors/update_executor.h"

namespace bustub {

UpdateExecutor::UpdateExecutor(ExecutorContext *exec_ctx, const UpdatePlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx),
    plan_(plan),
    catalog_(exec_ctx_->GetCatalog()),
    table_info_(catalog_->GetTable(plan_->GetTableOid())),
    table_index_(catalog_->GetTableIndexes(table_info_->name_)),
    child_executor_(std::move(child_executor)) {
  // As of Fall 2022, you DON'T need to implement update executor to have perfect score in project 3 / project 4.
}

void UpdateExecutor::Init() { 
	child_executor_->Init();
  // throw NotImplementedException("UpdateExecutor is not implemented"); 
}

auto UpdateExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool { 
  if(is_done_){
    return false;
  }
  int update_count=0;
  while(true){
		Tuple child_tuple;
		RID child_rid;
		auto status = child_executor_->Next(&child_tuple, &child_rid);
		if (!status) {
			break;
		}
		if(child_rid.GetPageId()==INVALID_PAGE_ID){
			continue;
		}
		auto update_tuplemeta=table_info_->table_->GetTupleMeta(child_rid);
		// auto update_tuplemeta=TupleMeta{0,true};
		update_tuplemeta.is_deleted_=true;
		table_info_->table_->UpdateTupleMeta(update_tuplemeta,child_rid);
		for (auto &update_index : table_index_) {
			update_index->index_->DeleteEntry(child_tuple.KeyFromTuple(table_info_->schema_, update_index->key_schema_,update_index->index_->GetKeyAttrs()),child_rid, exec_ctx_->GetTransaction());
		}

		std::vector<Value> update_values{};
		update_values.reserve(child_executor_->GetOutputSchema().GetColumnCount());
		for (const auto &expr : plan_->target_expressions_) {
			update_values.push_back(expr->Evaluate(&child_tuple, child_executor_->GetOutputSchema()));
		}

		Tuple update_tuple{};
		update_tuple=Tuple(update_values,&child_executor_->GetOutputSchema());
		auto insert_rid=table_info_->table_->InsertTuple(TupleMeta{0, false}, update_tuple);
		if(!insert_rid){
			return false;
		}
		for (auto &update_index : table_index_) {
				// std::cout<<update_index->index_->GetKeyAttrs().size()<<'\n';
			update_index->index_->InsertEntry(update_tuple.KeyFromTuple(table_info_->schema_, update_index->key_schema_,update_index->index_->GetKeyAttrs()),insert_rid.value(), exec_ctx_->GetTransaction());
				// std::cout<<exist<<'\n';
		}
		update_count++;
	}
	std::vector<Value> values{{TypeId::INTEGER,update_count}};
	*tuple=Tuple{values,&GetOutputSchema()};
	is_done_=true;
	return true; 
}


}  // namespace bustub
