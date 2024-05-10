#include <vector>
#include "optimizer/optimizer.h"
#include "execution/plans/seq_scan_plan.h"
#include "execution/plans/index_scan_plan.h"
#include "execution/expressions/column_value_expression.h"
#include "execution/expressions/comparison_expression.h"
#include "execution/expressions/logic_expression.h"
#include "execution/expressions/constant_value_expression.h"
// #include "planner/planner.h"

namespace bustub {

auto Optimizer::OptimizeSeqScanAsIndexScan(const bustub::AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  // TODO(student): implement seq scan with predicate -> index scan optimizer rule
  // The Filter Predicate Pushdown has been enabled for you in optimizer.cpp when forcing starter rule
  std::vector<AbstractPlanNodeRef> children;
  for (const auto &child : plan->GetChildren()) {
    children.emplace_back(OptimizeMergeFilterScan(child));
  }

  auto optimized_plan = plan->CloneWithChildren(std::move(children));
  std::string table_name{};
  // std::function<std::vector<Value>(index_oid_t&,const bustub::AbstractPlanNodeRef)>
  std::function<std::vector<Value>(index_oid_t&,const bustub::AbstractExpressionRef)> getvalue = [&](index_oid_t &index_oid,const bustub::AbstractExpressionRef &root_expr) -> std::vector<Value> {
    std::vector<Value> value{};
    if (const auto *expr = dynamic_cast<const ComparisonExpression *>(root_expr.get()); expr != nullptr) {
      value.reserve(1);
      if (expr->comp_type_ == ComparisonType::Equal) {
        if (const auto *left_expr = dynamic_cast<const ColumnValueExpression *>(expr->children_[0].get());left_expr != nullptr) {
          if (const auto *pred_keys = dynamic_cast<const ConstantValueExpression *>(expr->children_[1].get());pred_keys != nullptr) {
            if (auto index = MatchIndex(table_name, left_expr->GetColIdx());index != std::nullopt) {
                value.push_back(pred_keys->val_);
                index_oid = left_expr->GetColIdx();
                return value;
            }
          }
        }
        if (const auto *right_expr = dynamic_cast<const ColumnValueExpression *>(expr->children_[1].get());right_expr != nullptr) {
          if (const auto *pred_keys = dynamic_cast<const ConstantValueExpression *>(expr->children_[0].get());pred_keys != nullptr) {
            if (auto index = MatchIndex(table_name, right_expr->GetColIdx());index != std::nullopt) {
                value.push_back(pred_keys->val_);
                index_oid = right_expr->GetColIdx();
                return value;
            }
          }
        }
      }
    }
    else if(const auto *expr = dynamic_cast<const LogicExpression *>(root_expr.get()); expr != nullptr){
      
      index_oid_t left_index_oid=INVALID_TXN_ID;
      // auto left_plan=;
      puts("_________________");
      const auto &left_expr = expr->GetChildAt(0);
      puts("_________________");
      auto left_val=getvalue(left_index_oid,left_expr);
      if(left_val.empty()){
        return {};
      }
      
      index_oid_t right_index_oid=INVALID_TXN_ID;
      const auto &right_expr = expr->GetChildAt(1);
      auto right_val=getvalue(right_index_oid,right_expr);
      if(right_val.empty()||right_index_oid!=left_index_oid){
        return {};
      }
      index_oid=left_index_oid;
      if(expr->logic_type_==LogicType::And){
        value.reserve(std::min(left_val.size(),right_val.size()));
        for(auto &lval:left_val){
          for(auto &rval:right_val){
            if (lval.CompareEquals(rval) == CmpBool::CmpTrue) {
              value.push_back(lval);
              break;
            }
          }
        }
      }else if(expr->logic_type_==LogicType::Or){
        value.reserve(left_val.size()+right_val.size());
        for(auto &lval:left_val){
          value.push_back(lval);
        }
        for(auto &rval:right_val){
          value.push_back(rval);
          for(auto &lval:left_val){
            if (rval.CompareEquals(lval) == CmpBool::CmpTrue) {
              value.pop_back();
              break;
            }
          }
        }
        
      }
    }
    return value;
  };
  if (optimized_plan->GetType() == PlanType::SeqScan) {
    const auto &seqscan_plan = dynamic_cast<const SeqScanPlanNode &>(*optimized_plan);
    // BUSTUB_ENSURE(seqscan_plan.children_.size() == 1, "seqscan should have exactly 1 children.");
    if(seqscan_plan.filter_predicate_.get()==nullptr){
      return optimized_plan;
    }
    const auto &filter_predicate = seqscan_plan.filter_predicate_;
    index_oid_t index_oid=INVALID_TXN_ID;
    table_name=seqscan_plan.table_name_;
    // std::cout<<"HERE: "<<optimized_plan->ToString()<<'\n';
    std::vector<Value> value=getvalue(index_oid,filter_predicate);
    // std::cout<<"HERE: "<<value.empty()<<'\n';
    if(!value.empty()){
      std::vector<AbstractExpressionRef> pred_vec;
      pred_vec.reserve(value.size());
      for(auto v:value){
        // std::cerr<<v.ToString()<<" "<<"BreakpointHere\n";
        pred_vec.push_back(std::make_shared<ConstantValueExpression>(v));
      }
      return std::make_shared<IndexScanPlanNode>(
        optimized_plan->output_schema_, seqscan_plan.GetTableOid(),
          index_oid, filter_predicate, pred_vec);
    }
  }
  return optimized_plan;
}

}  // namespace bustub
