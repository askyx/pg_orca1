//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CXformCTEAnchor2Sequence.cpp
//
//	@doc:
//		Implementation of transform
//---------------------------------------------------------------------------

#include "gpopt/xforms/CXformCTEAnchor2Sequence.h"

#include "gpos/base.h"

#include "gpopt/base/COptCtxt.h"
#include "gpopt/operators/CLogicalCTEAnchor.h"
#include "gpopt/operators/CLogicalSequence.h"
#include "gpopt/operators/CPatternLeaf.h"
#include "gpopt/xforms/CXformUtils.h"

using namespace gpopt;

//---------------------------------------------------------------------------
//	@function:
//		CXformCTEAnchor2Sequence::CXformCTEAnchor2Sequence
//
//	@doc:
//		Ctor
//
//---------------------------------------------------------------------------
CXformCTEAnchor2Sequence::CXformCTEAnchor2Sequence(CMemoryPool *mp)
    : CXformExploration(
          // pattern
          GPOS_NEW(mp) CExpression(mp, GPOS_NEW(mp) CLogicalCTEAnchor(mp),
                                   GPOS_NEW(mp) CExpression(mp, GPOS_NEW(mp) CPatternLeaf(mp)))) {}

//---------------------------------------------------------------------------
//	@function:
//		CXformCTEAnchor2Sequence::Exfp
//
//	@doc:
//		Compute promise of xform
//
//---------------------------------------------------------------------------
CXform::EXformPromise CXformCTEAnchor2Sequence::Exfp(CExpressionHandle &exprhdl) const {
  ULONG id = CLogicalCTEAnchor::PopConvert(exprhdl.Pop())->Id();
  const ULONG ulConsumers = COptCtxt::PoctxtFromTLS()->Pcteinfo()->UlConsumers(id);
  GPOS_ASSERT(0 < ulConsumers);

  if (1 == ulConsumers && CXformUtils::FInlinableCTE(id)) {
    return CXform::ExfpNone;
  }

  // If contains outer reference, don't attempt to generate plan with shared scans
  // instead, Orca will generate an inlined plan
  if (exprhdl.HasOuterRefs() > 0) {
    return CXform::ExfpNone;
  }

  return CXform::ExfpHigh;
}

//---------------------------------------------------------------------------
//	@function:
//		CXformCTEAnchor2Sequence::Transform
//
//	@doc:
//		Actual transformation
//
//---------------------------------------------------------------------------
void CXformCTEAnchor2Sequence::Transform(CXformContext *pxfctxt, CXformResult *pxfres, CExpression *pexpr) const {
  GPOS_ASSERT(nullptr != pxfctxt);
  GPOS_ASSERT(FPromising(pxfctxt->Pmp(), this, pexpr));
  GPOS_ASSERT(FCheckPattern(pexpr));

  // ExfExpandFullOuterJoin converts a LogicalFullJoin to a CTE with a UnionAll
  // of an LOJ and LASJ. Even if expansion is disabled by the trace flag, the
  // xform still needs to be triggered, so that the CTE operator generated
  // can be used to compute the statistics for the logical merge join group (see
  // CLogicalFullOuterJoin::Esp()).
  // Instead, we skip the implementation of the CTE, here, if the trace flag is
  // disabled and the CTE op was generated by ExfExpandFullOuterJoin.
  CGroupExpression *pgexprOrigin = pexpr->Pgexpr();
  if (!GPOS_FTRACE(EopttraceExpandFullJoin) && nullptr != pgexprOrigin &&
      CXform::ExfExpandFullOuterJoin == pgexprOrigin->ExfidOrigin()) {
    return;
  }

  CLogicalCTEAnchor *popCTEAnchor = CLogicalCTEAnchor::PopConvert(pexpr->Pop());
  CMemoryPool *mp = pxfctxt->Pmp();

  ULONG id = popCTEAnchor->Id();

  CExpression *pexprProducer = COptCtxt::PoctxtFromTLS()->Pcteinfo()->PexprCTEProducer(id);
  GPOS_ASSERT(nullptr != pexprProducer);

  pexprProducer->AddRef();

  // child of CTE anchor
  CExpression *pexprChild = (*pexpr)[0];
  pexprChild->AddRef();

  // create logical sequence
  CExpression *pexprSequence =
      GPOS_NEW(mp) CExpression(mp, GPOS_NEW(mp) CLogicalSequence(mp), pexprProducer, pexprChild);

  pxfres->Add(pexprSequence);
}

// EOF
