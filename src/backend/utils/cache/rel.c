#include "utils/rel.h"

void
RelationSetIndexSupport(Relation      relation,
                        IndexStrategy strategy,
                        RegProcedure  *support){
  Assert(PointerIsValid(relation));
  Assert(IndexStrategyValid(strategy));

  relation->rd_istrat  = strategy;
  relation->rd_support = support;
}
