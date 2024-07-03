//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		parsehandlers.h
//
//	@doc:
//		collective include file for all parse handlers
//---------------------------------------------------------------------------

#ifndef GPDXL_parsehandlers_H
#define GPDXL_parsehandlers_H

#include "naucrates/dxl/parser/CParseHandlerAgg.h"
#include "naucrates/dxl/parser/CParseHandlerAppend.h"
#include "naucrates/dxl/parser/CParseHandlerArray.h"
#include "naucrates/dxl/parser/CParseHandlerAssert.h"
#include "naucrates/dxl/parser/CParseHandlerBroadcastMotion.h"
#include "naucrates/dxl/parser/CParseHandlerCTEConfig.h"
#include "naucrates/dxl/parser/CParseHandlerCTEList.h"
#include "naucrates/dxl/parser/CParseHandlerColDescr.h"
#include "naucrates/dxl/parser/CParseHandlerColStats.h"
#include "naucrates/dxl/parser/CParseHandlerColStatsBucket.h"
#include "naucrates/dxl/parser/CParseHandlerCondList.h"
#include "naucrates/dxl/parser/CParseHandlerCost.h"
#include "naucrates/dxl/parser/CParseHandlerCostModel.h"
#include "naucrates/dxl/parser/CParseHandlerCostParam.h"
#include "naucrates/dxl/parser/CParseHandlerCostParams.h"
#include "naucrates/dxl/parser/CParseHandlerCtasStorageOptions.h"
#include "naucrates/dxl/parser/CParseHandlerDXL.h"
#include "naucrates/dxl/parser/CParseHandlerDirectDispatchInfo.h"
#include "naucrates/dxl/parser/CParseHandlerDistinctComp.h"
#include "naucrates/dxl/parser/CParseHandlerDynamicForeignScan.h"
#include "naucrates/dxl/parser/CParseHandlerDynamicIndexOnlyScan.h"
#include "naucrates/dxl/parser/CParseHandlerDynamicIndexScan.h"
#include "naucrates/dxl/parser/CParseHandlerDynamicTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerEnumeratorConfig.h"
#include "naucrates/dxl/parser/CParseHandlerExtStats.h"
#include "naucrates/dxl/parser/CParseHandlerExtStatsDependencies.h"
#include "naucrates/dxl/parser/CParseHandlerExtStatsDependency.h"
#include "naucrates/dxl/parser/CParseHandlerExtStatsInfo.h"
#include "naucrates/dxl/parser/CParseHandlerExtStatsNDistinct.h"
#include "naucrates/dxl/parser/CParseHandlerExtStatsNDistinctList.h"
#include "naucrates/dxl/parser/CParseHandlerFactory.h"
#include "naucrates/dxl/parser/CParseHandlerFilter.h"
#include "naucrates/dxl/parser/CParseHandlerForeignScan.h"
#include "naucrates/dxl/parser/CParseHandlerGatherMotion.h"
#include "naucrates/dxl/parser/CParseHandlerGroupingColList.h"
#include "naucrates/dxl/parser/CParseHandlerHashExpr.h"
#include "naucrates/dxl/parser/CParseHandlerHashExprList.h"
#include "naucrates/dxl/parser/CParseHandlerHashJoin.h"
#include "naucrates/dxl/parser/CParseHandlerHint.h"
#include "naucrates/dxl/parser/CParseHandlerIndexCondList.h"
#include "naucrates/dxl/parser/CParseHandlerIndexDescr.h"
#include "naucrates/dxl/parser/CParseHandlerIndexOnlyScan.h"
#include "naucrates/dxl/parser/CParseHandlerIndexScan.h"
#include "naucrates/dxl/parser/CParseHandlerLimit.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalCTAS.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalCTEAnchor.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalCTEConsumer.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalCTEProducer.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalConstTable.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalDelete.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalForeignGet.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalGet.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalGroupBy.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalInsert.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalJoin.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalLimit.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalOp.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalProject.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalSelect.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalSetOp.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalTVF.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalUpdate.h"
#include "naucrates/dxl/parser/CParseHandlerLogicalWindow.h"
#include "naucrates/dxl/parser/CParseHandlerMDArrayCoerceCast.h"
#include "naucrates/dxl/parser/CParseHandlerMDCast.h"
#include "naucrates/dxl/parser/CParseHandlerMDGPDBAgg.h"
#include "naucrates/dxl/parser/CParseHandlerMDGPDBCheckConstraint.h"
#include "naucrates/dxl/parser/CParseHandlerMDGPDBFunc.h"
#include "naucrates/dxl/parser/CParseHandlerMDGPDBScalarOp.h"
#include "naucrates/dxl/parser/CParseHandlerMDIndex.h"
#include "naucrates/dxl/parser/CParseHandlerMDIndexInfoList.h"
#include "naucrates/dxl/parser/CParseHandlerMDRelation.h"
#include "naucrates/dxl/parser/CParseHandlerMDRelationCtas.h"
#include "naucrates/dxl/parser/CParseHandlerMDRequest.h"
#include "naucrates/dxl/parser/CParseHandlerMDScCmp.h"
#include "naucrates/dxl/parser/CParseHandlerMDType.h"
#include "naucrates/dxl/parser/CParseHandlerMaterialize.h"
#include "naucrates/dxl/parser/CParseHandlerMergeJoin.h"
#include "naucrates/dxl/parser/CParseHandlerMetadata.h"
#include "naucrates/dxl/parser/CParseHandlerMetadataColumn.h"
#include "naucrates/dxl/parser/CParseHandlerMetadataColumns.h"
#include "naucrates/dxl/parser/CParseHandlerMetadataIdList.h"
#include "naucrates/dxl/parser/CParseHandlerNLJIndexParam.h"
#include "naucrates/dxl/parser/CParseHandlerNLJIndexParamList.h"
#include "naucrates/dxl/parser/CParseHandlerNLJoin.h"
#include "naucrates/dxl/parser/CParseHandlerOptimizerConfig.h"
#include "naucrates/dxl/parser/CParseHandlerPartitionSelector.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalBitmapTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalCTAS.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalCTEConsumer.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalCTEProducer.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalDML.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalDynamicBitmapTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalOp.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalSplit.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalTVF.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalWindow.h"
#include "naucrates/dxl/parser/CParseHandlerPlan.h"
#include "naucrates/dxl/parser/CParseHandlerPlanHint.h"
#include "naucrates/dxl/parser/CParseHandlerProjElem.h"
#include "naucrates/dxl/parser/CParseHandlerProjList.h"
#include "naucrates/dxl/parser/CParseHandlerProperties.h"
#include "naucrates/dxl/parser/CParseHandlerQuery.h"
#include "naucrates/dxl/parser/CParseHandlerQueryOutput.h"
#include "naucrates/dxl/parser/CParseHandlerRandomMotion.h"
#include "naucrates/dxl/parser/CParseHandlerRedistributeMotion.h"
#include "naucrates/dxl/parser/CParseHandlerRelStats.h"
#include "naucrates/dxl/parser/CParseHandlerRelationExtendedStats.h"
#include "naucrates/dxl/parser/CParseHandlerResult.h"
#include "naucrates/dxl/parser/CParseHandlerRoutedMotion.h"
#include "naucrates/dxl/parser/CParseHandlerScalarAggref.h"
#include "naucrates/dxl/parser/CParseHandlerScalarArrayCoerceExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarArrayComp.h"
#include "naucrates/dxl/parser/CParseHandlerScalarArrayRef.h"
#include "naucrates/dxl/parser/CParseHandlerScalarArrayRefIndexList.h"
#include "naucrates/dxl/parser/CParseHandlerScalarAssertConstraintList.h"
#include "naucrates/dxl/parser/CParseHandlerScalarBitmapBoolOp.h"
#include "naucrates/dxl/parser/CParseHandlerScalarBitmapIndexProbe.h"
#include "naucrates/dxl/parser/CParseHandlerScalarBoolExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarBooleanTest.h"
#include "naucrates/dxl/parser/CParseHandlerScalarCaseTest.h"
#include "naucrates/dxl/parser/CParseHandlerScalarCast.h"
#include "naucrates/dxl/parser/CParseHandlerScalarCoalesce.h"
#include "naucrates/dxl/parser/CParseHandlerScalarCoerceToDomain.h"
#include "naucrates/dxl/parser/CParseHandlerScalarCoerceViaIO.h"
#include "naucrates/dxl/parser/CParseHandlerScalarComp.h"
#include "naucrates/dxl/parser/CParseHandlerScalarConstValue.h"
#include "naucrates/dxl/parser/CParseHandlerScalarDMLAction.h"
#include "naucrates/dxl/parser/CParseHandlerScalarExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarFieldSelect.h"
#include "naucrates/dxl/parser/CParseHandlerScalarFuncExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarIdent.h"
#include "naucrates/dxl/parser/CParseHandlerScalarIfStmt.h"
#include "naucrates/dxl/parser/CParseHandlerScalarLimitCount.h"
#include "naucrates/dxl/parser/CParseHandlerScalarLimitOffset.h"
#include "naucrates/dxl/parser/CParseHandlerScalarMinMax.h"
#include "naucrates/dxl/parser/CParseHandlerScalarNullIf.h"
#include "naucrates/dxl/parser/CParseHandlerScalarNullTest.h"
#include "naucrates/dxl/parser/CParseHandlerScalarOp.h"
#include "naucrates/dxl/parser/CParseHandlerScalarOpExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarOpList.h"
#include "naucrates/dxl/parser/CParseHandlerScalarParam.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSortGroupClause.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubPlan.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubPlanParam.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubPlanParamList.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubPlanTestExpr.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubquery.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubqueryExists.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSubqueryQuantified.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSwitch.h"
#include "naucrates/dxl/parser/CParseHandlerScalarSwitchCase.h"
#include "naucrates/dxl/parser/CParseHandlerScalarValuesList.h"
#include "naucrates/dxl/parser/CParseHandlerScalarWindowFrameEdge.h"
#include "naucrates/dxl/parser/CParseHandlerScalarWindowRef.h"
#include "naucrates/dxl/parser/CParseHandlerSearchStage.h"
#include "naucrates/dxl/parser/CParseHandlerSearchStrategy.h"
#include "naucrates/dxl/parser/CParseHandlerSequence.h"
#include "naucrates/dxl/parser/CParseHandlerSort.h"
#include "naucrates/dxl/parser/CParseHandlerSortCol.h"
#include "naucrates/dxl/parser/CParseHandlerSortColList.h"
#include "naucrates/dxl/parser/CParseHandlerStacktrace.h"
#include "naucrates/dxl/parser/CParseHandlerStatistics.h"
#include "naucrates/dxl/parser/CParseHandlerStatisticsConfig.h"
#include "naucrates/dxl/parser/CParseHandlerStatsBound.h"
#include "naucrates/dxl/parser/CParseHandlerStatsDerivedColumn.h"
#include "naucrates/dxl/parser/CParseHandlerStatsDerivedRelation.h"
#include "naucrates/dxl/parser/CParseHandlerTableDescr.h"
#include "naucrates/dxl/parser/CParseHandlerTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerTraceFlags.h"
#include "naucrates/dxl/parser/CParseHandlerValuesScan.h"
#include "naucrates/dxl/parser/CParseHandlerWindowFrame.h"
#include "naucrates/dxl/parser/CParseHandlerWindowKey.h"
#include "naucrates/dxl/parser/CParseHandlerWindowKeyList.h"
#include "naucrates/dxl/parser/CParseHandlerWindowOids.h"
#include "naucrates/dxl/parser/CParseHandlerWindowSpec.h"
#include "naucrates/dxl/parser/CParseHandlerWindowSpecList.h"
#include "naucrates/dxl/parser/CParseHandlerXform.h"
#endif  // !GPDXL_parsehandlers_H

// EOF
