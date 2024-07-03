//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2014 VMware, Inc. or its affiliates.
//
//	@filename:
//		CParseHandlerPhysicalAbstractBitmapScan.h
//
//	@doc:
//		SAX parse handler parent class for parsing bitmap scan operator nodes
//---------------------------------------------------------------------------

#include "naucrates/dxl/parser/CParseHandlerPhysicalAbstractBitmapScan.h"

#include "naucrates/dxl/operators/CDXLPhysicalAbstractBitmapScan.h"
#include "naucrates/dxl/operators/CDXLPhysicalBitmapTableScan.h"
#include "naucrates/dxl/operators/CDXLPhysicalDynamicBitmapTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerFactory.h"
#include "naucrates/dxl/parser/CParseHandlerFilter.h"
#include "naucrates/dxl/parser/CParseHandlerMetadataIdList.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalBitmapTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerPhysicalDynamicBitmapTableScan.h"
#include "naucrates/dxl/parser/CParseHandlerProjList.h"
#include "naucrates/dxl/parser/CParseHandlerProperties.h"
#include "naucrates/dxl/parser/CParseHandlerScalarBitmapIndexProbe.h"
#include "naucrates/dxl/parser/CParseHandlerTableDescr.h"
#include "naucrates/dxl/parser/CParseHandlerUtils.h"
#include "naucrates/dxl/xml/dxltokens.h"

using namespace gpdxl;

//---------------------------------------------------------------------------
//	@function:
//		CParseHandlerPhysicalAbstractBitmapScan::StartElementHelper
//
//	@doc:
//		Common StartElement functionality for children of this class
//
//---------------------------------------------------------------------------
void CParseHandlerPhysicalAbstractBitmapScan::StartElementHelper(const XMLCh *const element_local_name,
                                                                 Edxltoken token_type) {
  if (0 != XMLString::compareString(CDXLTokens::XmlstrToken(token_type), element_local_name)) {
    CWStringDynamic *str =
        CDXLUtils::CreateDynamicStringFromXMLChArray(m_parse_handler_mgr->GetDXLMemoryManager(), element_local_name);
    GPOS_RAISE(gpdxl::ExmaDXL, gpdxl::ExmiDXLUnexpectedTag, str->GetBuffer());
  }

  // create child node parsers in reverse order of their expected occurrence
  // parse handler for table descriptor
  CParseHandlerBase *table_descr_parse_handler = CParseHandlerFactory::GetParseHandler(
      m_mp, CDXLTokens::XmlstrToken(EdxltokenTableDescr), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(table_descr_parse_handler);

  CParseHandlerBase *partition_mdids_parse_handler = nullptr;
  if (EdxltokenPhysicalDynamicBitmapTableScan == token_type) {
    partition_mdids_parse_handler = CParseHandlerFactory::GetParseHandler(
        m_mp, CDXLTokens::XmlstrToken(EdxltokenMetadataIdList), m_parse_handler_mgr, this);
    m_parse_handler_mgr->ActivateParseHandler(partition_mdids_parse_handler);
  }

  // parse handler for the bitmap access path
  CParseHandlerBase *bitmap_parse_handler =
      CParseHandlerFactory::GetParseHandler(m_mp, CDXLTokens::XmlstrToken(EdxltokenScalar), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(bitmap_parse_handler);

  // parse handler for the recheck condition
  CParseHandlerBase *recheck_cond_parse_handler = CParseHandlerFactory::GetParseHandler(
      m_mp, CDXLTokens::XmlstrToken(EdxltokenScalarRecheckCondFilter), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(recheck_cond_parse_handler);

  // parse handler for the filter
  CParseHandlerBase *filter_parse_handler = CParseHandlerFactory::GetParseHandler(
      m_mp, CDXLTokens::XmlstrToken(EdxltokenScalarFilter), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(filter_parse_handler);

  // parse handler for the proj list
  CParseHandlerBase *proj_list_parse_handler = CParseHandlerFactory::GetParseHandler(
      m_mp, CDXLTokens::XmlstrToken(EdxltokenScalarProjList), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(proj_list_parse_handler);

  // parse handler for the properties of the operator
  CParseHandlerBase *prop_parse_handler = CParseHandlerFactory::GetParseHandler(
      m_mp, CDXLTokens::XmlstrToken(EdxltokenProperties), m_parse_handler_mgr, this);
  m_parse_handler_mgr->ActivateParseHandler(prop_parse_handler);

  // store child parse handlers in array
  this->Append(prop_parse_handler);
  this->Append(proj_list_parse_handler);
  this->Append(filter_parse_handler);
  this->Append(recheck_cond_parse_handler);
  this->Append(bitmap_parse_handler);
  if (EdxltokenPhysicalDynamicBitmapTableScan == token_type) {
    this->Append(partition_mdids_parse_handler);
  }
  this->Append(table_descr_parse_handler);
}

//---------------------------------------------------------------------------
//	@function:
//		CParseHandlerPhysicalAbstractBitmapScan::EndElementHelper
//
//	@doc:
//		Common EndElement functionality for children of this class
//
//---------------------------------------------------------------------------
void CParseHandlerPhysicalAbstractBitmapScan::EndElementHelper(const XMLCh *const element_local_name,
                                                               Edxltoken token_type, ULongPtrArray *selector_ids) {
  if (0 != XMLString::compareString(CDXLTokens::XmlstrToken(token_type), element_local_name)) {
    CWStringDynamic *str =
        CDXLUtils::CreateDynamicStringFromXMLChArray(m_parse_handler_mgr->GetDXLMemoryManager(), element_local_name);
    GPOS_RAISE(gpdxl::ExmaDXL, gpdxl::ExmiDXLUnexpectedTag, str->GetBuffer());
  }

  int i = 0;
  // construct nodes from the created child nodes
  CParseHandlerProperties *prop_parse_handler = dynamic_cast<CParseHandlerProperties *>((*this)[i++]);
  CParseHandlerProjList *proj_list_parse_handler = dynamic_cast<CParseHandlerProjList *>((*this)[i++]);
  CParseHandlerFilter *filter_parse_handler = dynamic_cast<CParseHandlerFilter *>((*this)[i++]);
  CParseHandlerFilter *recheck_cond_parse_handler = dynamic_cast<CParseHandlerFilter *>((*this)[i++]);
  CParseHandlerScalarOp *bitmap_parse_handler = dynamic_cast<CParseHandlerScalarOp *>((*this)[i++]);
  CParseHandlerMetadataIdList *partition_mdids_parse_handler = nullptr;
  if (EdxltokenPhysicalDynamicBitmapTableScan == token_type) {
    partition_mdids_parse_handler = dynamic_cast<CParseHandlerMetadataIdList *>((*this)[i++]);
  }
  CParseHandlerTableDescr *table_descr_parse_handler = dynamic_cast<CParseHandlerTableDescr *>((*this)[i++]);

  GPOS_ASSERT(nullptr != table_descr_parse_handler->GetDXLTableDescr());

  // set table descriptor
  CDXLTableDescr *table_descr = table_descr_parse_handler->GetDXLTableDescr();
  table_descr->AddRef();
  CDXLPhysical *dxl_op = nullptr;

  if (EdxltokenPhysicalBitmapTableScan == token_type) {
    dxl_op = GPOS_NEW(m_mp) CDXLPhysicalBitmapTableScan(m_mp, table_descr);
  } else {
    GPOS_ASSERT(EdxltokenPhysicalDynamicBitmapTableScan == token_type);
    IMdIdArray *mdid_partitions_array = partition_mdids_parse_handler->GetMdIdArray();
    mdid_partitions_array->AddRef();
    dxl_op = GPOS_NEW(m_mp) CDXLPhysicalDynamicBitmapTableScan(m_mp, table_descr, mdid_partitions_array, selector_ids);
  }
  m_dxl_node = GPOS_NEW(m_mp) CDXLNode(m_mp, dxl_op);

  // set statistics and physical properties
  CParseHandlerUtils::SetProperties(m_dxl_node, prop_parse_handler);

  // add constructed children
  AddChildFromParseHandler(proj_list_parse_handler);
  AddChildFromParseHandler(filter_parse_handler);
  AddChildFromParseHandler(recheck_cond_parse_handler);

  AddChildFromParseHandler(bitmap_parse_handler);

#ifdef GPOS_DEBUG
  dxl_op->AssertValid(m_dxl_node, false /* validate_children */);
#endif  // GPOS_DEBUG

  // deactivate handler
  m_parse_handler_mgr->DeactivateHandler();
}

// EOF
