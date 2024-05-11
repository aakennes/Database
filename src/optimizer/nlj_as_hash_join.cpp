#include <algorithm>
#include <memory>
#include "catalog/column.h"
#include "catalog/schema.h"
#include "common/exception.h"
#include "common/macros.h"
#include "execution/expressions/column_value_expression.h"
#include "execution/expressions/comparison_expression.h"
#include "execution/expressions/constant_value_expression.h"
#include "execution/expressions/logic_expression.h"
#include "execution/plans/abstract_plan.h"
#include "execution/plans/filter_plan.h"
#include "execution/plans/hash_join_plan.h"
#include "execution/plans/nested_loop_join_plan.h"
#include "execution/plans/projection_plan.h"
#include "optimizer/optimizer.h"
#include "type/type_id.h"

namespace bustub {

auto Optimizer::OptimizeNLJAsHashJoin(const AbstractPlanNodeRef &plan) -> AbstractPlanNodeRef {
  // TODO(student): implement NestedLoopJoin -> HashJoin optimizer rule
  // Note for 2023 Fall: You should support join keys of any number of conjunction of equi-condistions:
  // E.g. <column expr> = <column expr> AND <column expr> = <column expr> AND ...
  std::vector<AbstractPlanNodeRef> children;
  for (const auto &child : plan->GetChildren()) {
    children.emplace_back(OptimizeNLJAsHashJoin(child));
  }

  auto optimized_plan = plan->CloneWithChildren(std::move(children));

  std::function<bool(const AbstractExpressionRef,std::vector<AbstractExpressionRef>&,std::vector<AbstractExpressionRef>&)> getkey
  = [&](const AbstractExpressionRef &expr, std::vector<AbstractExpressionRef> &left_keys,std::vector<AbstractExpressionRef> &right_keys) -> bool{
    if (const auto comparison_expr = std::dynamic_pointer_cast<ComparisonExpression>(expr);comparison_expr != nullptr) {
      // if()
      auto left_expr = comparison_expr->GetChildAt(0);
      auto right_expr = comparison_expr->GetChildAt(1);
      return getkey(left_expr, left_keys, right_keys)&&getkey(right_expr, left_keys, right_keys);
    }
    if (const auto logic_expr = std::dynamic_pointer_cast<LogicExpression>(expr); logic_expr != nullptr) {
      bool check=true;
      for (auto &child : logic_expr->GetChildren()) {
        check&= getkey(child, left_keys, right_keys);
      }
      return check;
    }
    if (const auto column_value_expression = std::dynamic_pointer_cast<ColumnValueExpression>(expr); column_value_expression != nullptr) {
      if(column_value_expression->GetTupleIdx() == 0){
        left_keys.push_back(column_value_expression);
      }else{
        right_keys.push_back(column_value_expression);
      }
      return true;
    }
    return false;
  };

  if (optimized_plan->GetType() == PlanType::NestedLoopJoin) {
    const auto &nlj_plan = dynamic_cast<const NestedLoopJoinPlanNode &>(*optimized_plan);
    // Has exactly two children
    BUSTUB_ENSURE(nlj_plan.children_.size() == 2, "NLJ should have exactly 2 children.");
    auto &predicate = nlj_plan.Predicate();
    std::vector<AbstractExpressionRef> left_keys{};
    std::vector<AbstractExpressionRef> right_keys{};
    left_keys.reserve(nlj_plan.OutputSchema().GetColumnCount());
    auto status=getkey(predicate,left_keys,right_keys);
    // getkey(predicate,left_keys,right_keys);
    if(status){
      return std::make_shared<HashJoinPlanNode>(nlj_plan.output_schema_, nlj_plan.GetLeftPlan(), nlj_plan.GetRightPlan(),left_keys, right_keys, nlj_plan.GetJoinType());
    }
  }
  return optimized_plan;
}

}  // namespace bustub
