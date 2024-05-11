//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// hash_join_executor.h
//
// Identification: src/include/execution/executors/hash_join_executor.h
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "execution/executor_context.h"
#include "execution/executors/abstract_executor.h"
#include "execution/plans/hash_join_plan.h"
#include "storage/table/tuple.h"
#include "common/util/hash_util.h"

namespace bustub {

struct HashJoinKey {
  /** The left values */
  std::vector<Value> attributes_;

  /**
   * Compares two hashjoin keys for equality.
   * @param other the other hashjoin key to be compared with
   * @return `true` if both hashjoin keys have equivalent attributes_ expressions, `false` otherwise
   */
  auto operator==(const HashJoinKey &other) const -> bool {
    for (uint32_t i = 0; i < other.attributes_.size(); i++) {
      if (attributes_[i].CompareEquals(other.attributes_[i]) != CmpBool::CmpTrue) {
        return false;
      }
    }
    return true;
  }
};

struct HashJoinValue {
  /** The left values */
  std::vector<Tuple> attributes_;
};

} // namespace bustub

namespace std {

  /** Implements std::hash on AggregateKey */
  template <>
  struct hash<bustub::HashJoinKey> {
    auto operator()(const bustub::HashJoinKey &hash_key) const -> std::size_t {
      size_t curr_hash = 0;
      for (const auto &key : hash_key.attributes_) {
        if (!key.IsNull()) {
          curr_hash = bustub::HashUtil::CombineHashes(curr_hash, bustub::HashUtil::HashValue(&key));
        }
      }
      return curr_hash;
    }
  };

}  // namespace std

namespace bustub {

/**
 * HashJoinExecutor executes a nested-loop JOIN on two tables.
 */
class HashJoinExecutor : public AbstractExecutor {
 public:
  /**
   * Construct a new HashJoinExecutor instance.
   * @param exec_ctx The executor context
   * @param plan The HashJoin join plan to be executed
   * @param left_child The child executor that produces tuples for the left side of join
   * @param right_child The child executor that produces tuples for the right side of join
   */
  HashJoinExecutor(ExecutorContext *exec_ctx, const HashJoinPlanNode *plan,
                   std::unique_ptr<AbstractExecutor> &&left_child, std::unique_ptr<AbstractExecutor> &&right_child);

  /** Initialize the join */
  void Init() override;

  /**
   * Yield the next tuple from the join.
   * @param[out] tuple The next tuple produced by the join.
   * @param[out] rid The next tuple RID, not used by hash join.
   * @return `true` if a tuple was produced, `false` if there are no more tuples.
   */
  auto Next(Tuple *tuple, RID *rid) -> bool override;

  /** @return The output schema for the join */
  auto GetOutputSchema() const -> const Schema & override { return plan_->OutputSchema(); };



 private:
  /** The HashJoin plan node to be executed. */
  const HashJoinPlanNode *plan_;
  // std::vector<Tuple> right_tuples_{};
  std::unique_ptr<AbstractExecutor> left_executor_;
  std::unique_ptr<AbstractExecutor> right_executor_;
  std::unordered_map<HashJoinKey,std::vector<Tuple>> ht_{};
  Schema left_schema_{plan_->GetLeftPlan()->OutputSchema()};
  Schema right_schema_{plan_->GetRightPlan()->OutputSchema()};
  uint32_t  left_size_{left_schema_.GetColumnCount()};
  uint32_t  right_size_{right_schema_.GetColumnCount()};
  uint32_t tuple_num_{0};
  uint32_t tuple_size_{0};
  std::vector<Tuple> tuple_vec_{};

  auto MakeHashJoinKey(const Tuple *tuple,const bool is_left) -> HashJoinKey {
    std::vector<Value> keys{};
    if(is_left){
      auto left_expr=plan_->LeftJoinKeyExpressions();
      auto expr_size=left_expr.size();
      keys.reserve(expr_size);
      for(uint32_t i=0;i<expr_size;++i){
        keys.push_back(left_expr[i]->Evaluate(tuple, left_schema_));
      }
    }else{
      auto right_expr=plan_->RightJoinKeyExpressions();
      auto expr_size=right_expr.size();
      keys.reserve(expr_size);
      for(uint32_t i=0;i<expr_size;++i){
        keys.push_back(right_expr[i]->Evaluate(tuple, right_schema_));
      }
    }
    return {keys};
  }


};

}  // namespace bustub

