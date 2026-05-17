/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::toy::AddOp,
::toy::ConvOp,
::toy::MulOp,
::toy::ReluOp,
::toy::SubOp
#endif  // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//

namespace toy {

static ::mlir::LogicalResult __mlir_ods_local_type_constraint_ToyOps0(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((true))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any type, but got " << type;
  }
  return ::mlir::success();
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_ToyOps0(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  if (attr && !(((attr.isa<::mlir::IntegerAttr>())) && ((attr.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64))))) {
    return op->emitOpError("attribute '") << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  }
  return ::mlir::success();
}
} // namespace toy
namespace toy {

//===----------------------------------------------------------------------===//
// ::toy::AddOp definitions
//===----------------------------------------------------------------------===//

AddOpAdaptor::AddOpAdaptor(::mlir::ValueRange values, ::mlir::DictionaryAttr attrs, ::mlir::RegionRange regions) : odsOperands(values), odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("toy.add", odsAttrs.getContext());
}

AddOpAdaptor::AddOpAdaptor(AddOp op) : odsOperands(op->getOperands()), odsAttrs(op->getAttrDictionary()), odsRegions(op->getRegions()), odsOpName(op->getName()) {}

::mlir::ValueRange AddOpAdaptor::getOperands() {
  return odsOperands;
}

std::pair<unsigned, unsigned> AddOpAdaptor::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::ValueRange AddOpAdaptor::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(odsOperands.begin(), valueRange.first),
           std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
}

::mlir::Value AddOpAdaptor::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value AddOpAdaptor::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::DictionaryAttr AddOpAdaptor::getAttributes() {
  return odsAttrs;
}

::mlir::IntegerAttr AddOpAdaptor::tensor_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, AddOp::tensor_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t AddOpAdaptor::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr AddOpAdaptor::workspace_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, AddOp::workspace_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t AddOpAdaptor::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::LogicalResult AddOpAdaptor::verify(::mlir::Location loc) {
  auto namedAttrRange = odsAttrs;
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == AddOp::tensor_sizeAttrName(*odsOpName)) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == AddOp::workspace_sizeAttrName(*odsOpName)) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (tblgen_tensor_size && !(((tblgen_tensor_size.isa<::mlir::IntegerAttr>())) && ((tblgen_tensor_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.add' op ""attribute 'tensor_size' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_workspace_size && !(((tblgen_workspace_size.isa<::mlir::IntegerAttr>())) && ((tblgen_workspace_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.add' op ""attribute 'workspace_size' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AddOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range AddOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value AddOp::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value AddOp::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::MutableOperandRange AddOp::lhsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::mlir::MutableOperandRange AddOp::rhsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> AddOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range AddOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value AddOp::output() {
  return *getODSResults(0).begin();
}

::mlir::IntegerAttr AddOp::tensor_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, tensor_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t AddOp::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr AddOp::workspace_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, workspace_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t AddOp::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

void AddOp::tensor_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(tensor_sizeAttrName(), attr);
}

void AddOp::workspace_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(workspace_sizeAttrName(), attr);
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  odsState.addTypes(output);
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  odsState.addTypes(output);
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void AddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

void AddOp::populateDefaultAttrs(const ::mlir::RegisteredOperationName &opName, ::mlir::NamedAttrList &attributes) {
  auto attrNames = opName.getAttributeNames();
  ::mlir::Builder odsBuilder(attrNames.front().getContext());
  if (!attributes.get(attrNames[0])) {
     attributes.append(attrNames[0], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
  if (!attributes.get(attrNames[1])) {
     attributes.append(attrNames[1], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
}

::mlir::LogicalResult AddOp::verifyInvariantsImpl() {
  auto namedAttrRange = (*this)->getAttrs();
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == tensor_sizeAttrName()) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == workspace_sizeAttrName()) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_tensor_size, "tensor_size")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_workspace_size, "workspace_size")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult AddOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void AddOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace toy
MLIR_DEFINE_EXPLICIT_TYPE_ID(::toy::AddOp)

namespace toy {

//===----------------------------------------------------------------------===//
// ::toy::ConvOp definitions
//===----------------------------------------------------------------------===//

ConvOpAdaptor::ConvOpAdaptor(::mlir::ValueRange values, ::mlir::DictionaryAttr attrs, ::mlir::RegionRange regions) : odsOperands(values), odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("toy.conv", odsAttrs.getContext());
}

ConvOpAdaptor::ConvOpAdaptor(ConvOp op) : odsOperands(op->getOperands()), odsAttrs(op->getAttrDictionary()), odsRegions(op->getRegions()), odsOpName(op->getName()) {}

::mlir::ValueRange ConvOpAdaptor::getOperands() {
  return odsOperands;
}

std::pair<unsigned, unsigned> ConvOpAdaptor::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::ValueRange ConvOpAdaptor::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(odsOperands.begin(), valueRange.first),
           std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ConvOpAdaptor::input() {
  return *getODSOperands(0).begin();
}

::mlir::DictionaryAttr ConvOpAdaptor::getAttributes() {
  return odsAttrs;
}

::mlir::IntegerAttr ConvOpAdaptor::tensor_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, ConvOp::tensor_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t ConvOpAdaptor::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ConvOpAdaptor::workspace_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, ConvOp::workspace_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t ConvOpAdaptor::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::LogicalResult ConvOpAdaptor::verify(::mlir::Location loc) {
  auto namedAttrRange = odsAttrs;
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == ConvOp::tensor_sizeAttrName(*odsOpName)) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == ConvOp::workspace_sizeAttrName(*odsOpName)) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (tblgen_tensor_size && !(((tblgen_tensor_size.isa<::mlir::IntegerAttr>())) && ((tblgen_tensor_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.conv' op ""attribute 'tensor_size' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_workspace_size && !(((tblgen_workspace_size.isa<::mlir::IntegerAttr>())) && ((tblgen_workspace_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.conv' op ""attribute 'workspace_size' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ConvOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range ConvOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ConvOp::input() {
  return *getODSOperands(0).begin();
}

::mlir::MutableOperandRange ConvOp::inputMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ConvOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range ConvOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ConvOp::output() {
  return *getODSResults(0).begin();
}

::mlir::IntegerAttr ConvOp::tensor_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, tensor_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t ConvOp::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ConvOp::workspace_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, workspace_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t ConvOp::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

void ConvOp::tensor_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(tensor_sizeAttrName(), attr);
}

void ConvOp::workspace_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(workspace_sizeAttrName(), attr);
}

void ConvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(input);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  odsState.addTypes(output);
}

void ConvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(input);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void ConvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(input);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  odsState.addTypes(output);
}

void ConvOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(input);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void ConvOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

void ConvOp::populateDefaultAttrs(const ::mlir::RegisteredOperationName &opName, ::mlir::NamedAttrList &attributes) {
  auto attrNames = opName.getAttributeNames();
  ::mlir::Builder odsBuilder(attrNames.front().getContext());
  if (!attributes.get(attrNames[0])) {
     attributes.append(attrNames[0], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
  if (!attributes.get(attrNames[1])) {
     attributes.append(attrNames[1], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
}

::mlir::LogicalResult ConvOp::verifyInvariantsImpl() {
  auto namedAttrRange = (*this)->getAttrs();
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == tensor_sizeAttrName()) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == workspace_sizeAttrName()) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_tensor_size, "tensor_size")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_workspace_size, "workspace_size")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult ConvOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ConvOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace toy
MLIR_DEFINE_EXPLICIT_TYPE_ID(::toy::ConvOp)

namespace toy {

//===----------------------------------------------------------------------===//
// ::toy::MulOp definitions
//===----------------------------------------------------------------------===//

MulOpAdaptor::MulOpAdaptor(::mlir::ValueRange values, ::mlir::DictionaryAttr attrs, ::mlir::RegionRange regions) : odsOperands(values), odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("toy.mul", odsAttrs.getContext());
}

MulOpAdaptor::MulOpAdaptor(MulOp op) : odsOperands(op->getOperands()), odsAttrs(op->getAttrDictionary()), odsRegions(op->getRegions()), odsOpName(op->getName()) {}

::mlir::ValueRange MulOpAdaptor::getOperands() {
  return odsOperands;
}

std::pair<unsigned, unsigned> MulOpAdaptor::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::ValueRange MulOpAdaptor::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(odsOperands.begin(), valueRange.first),
           std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
}

::mlir::Value MulOpAdaptor::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value MulOpAdaptor::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::DictionaryAttr MulOpAdaptor::getAttributes() {
  return odsAttrs;
}

::mlir::IntegerAttr MulOpAdaptor::tensor_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, MulOp::tensor_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t MulOpAdaptor::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr MulOpAdaptor::workspace_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, MulOp::workspace_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t MulOpAdaptor::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::LogicalResult MulOpAdaptor::verify(::mlir::Location loc) {
  auto namedAttrRange = odsAttrs;
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == MulOp::tensor_sizeAttrName(*odsOpName)) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == MulOp::workspace_sizeAttrName(*odsOpName)) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (tblgen_tensor_size && !(((tblgen_tensor_size.isa<::mlir::IntegerAttr>())) && ((tblgen_tensor_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.mul' op ""attribute 'tensor_size' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_workspace_size && !(((tblgen_workspace_size.isa<::mlir::IntegerAttr>())) && ((tblgen_workspace_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.mul' op ""attribute 'workspace_size' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> MulOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range MulOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value MulOp::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value MulOp::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::MutableOperandRange MulOp::lhsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::mlir::MutableOperandRange MulOp::rhsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> MulOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range MulOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value MulOp::output() {
  return *getODSResults(0).begin();
}

::mlir::IntegerAttr MulOp::tensor_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, tensor_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t MulOp::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr MulOp::workspace_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, workspace_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t MulOp::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

void MulOp::tensor_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(tensor_sizeAttrName(), attr);
}

void MulOp::workspace_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(workspace_sizeAttrName(), attr);
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  odsState.addTypes(output);
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  odsState.addTypes(output);
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void MulOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

void MulOp::populateDefaultAttrs(const ::mlir::RegisteredOperationName &opName, ::mlir::NamedAttrList &attributes) {
  auto attrNames = opName.getAttributeNames();
  ::mlir::Builder odsBuilder(attrNames.front().getContext());
  if (!attributes.get(attrNames[0])) {
     attributes.append(attrNames[0], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
  if (!attributes.get(attrNames[1])) {
     attributes.append(attrNames[1], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
}

::mlir::LogicalResult MulOp::verifyInvariantsImpl() {
  auto namedAttrRange = (*this)->getAttrs();
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == tensor_sizeAttrName()) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == workspace_sizeAttrName()) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_tensor_size, "tensor_size")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_workspace_size, "workspace_size")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult MulOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void MulOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace toy
MLIR_DEFINE_EXPLICIT_TYPE_ID(::toy::MulOp)

namespace toy {

//===----------------------------------------------------------------------===//
// ::toy::ReluOp definitions
//===----------------------------------------------------------------------===//

ReluOpAdaptor::ReluOpAdaptor(::mlir::ValueRange values, ::mlir::DictionaryAttr attrs, ::mlir::RegionRange regions) : odsOperands(values), odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("toy.relu", odsAttrs.getContext());
}

ReluOpAdaptor::ReluOpAdaptor(ReluOp op) : odsOperands(op->getOperands()), odsAttrs(op->getAttrDictionary()), odsRegions(op->getRegions()), odsOpName(op->getName()) {}

::mlir::ValueRange ReluOpAdaptor::getOperands() {
  return odsOperands;
}

std::pair<unsigned, unsigned> ReluOpAdaptor::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::ValueRange ReluOpAdaptor::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(odsOperands.begin(), valueRange.first),
           std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ReluOpAdaptor::input() {
  return *getODSOperands(0).begin();
}

::mlir::DictionaryAttr ReluOpAdaptor::getAttributes() {
  return odsAttrs;
}

::mlir::IntegerAttr ReluOpAdaptor::tensor_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, ReluOp::tensor_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t ReluOpAdaptor::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ReluOpAdaptor::workspace_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, ReluOp::workspace_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t ReluOpAdaptor::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::LogicalResult ReluOpAdaptor::verify(::mlir::Location loc) {
  auto namedAttrRange = odsAttrs;
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == ReluOp::tensor_sizeAttrName(*odsOpName)) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == ReluOp::workspace_sizeAttrName(*odsOpName)) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (tblgen_tensor_size && !(((tblgen_tensor_size.isa<::mlir::IntegerAttr>())) && ((tblgen_tensor_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.relu' op ""attribute 'tensor_size' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_workspace_size && !(((tblgen_workspace_size.isa<::mlir::IntegerAttr>())) && ((tblgen_workspace_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.relu' op ""attribute 'workspace_size' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ReluOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range ReluOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ReluOp::input() {
  return *getODSOperands(0).begin();
}

::mlir::MutableOperandRange ReluOp::inputMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ReluOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range ReluOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value ReluOp::output() {
  return *getODSResults(0).begin();
}

::mlir::IntegerAttr ReluOp::tensor_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, tensor_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t ReluOp::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ReluOp::workspace_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, workspace_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t ReluOp::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

void ReluOp::tensor_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(tensor_sizeAttrName(), attr);
}

void ReluOp::workspace_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(workspace_sizeAttrName(), attr);
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(input);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  odsState.addTypes(output);
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(input);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(input);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  odsState.addTypes(output);
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(input);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void ReluOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

void ReluOp::populateDefaultAttrs(const ::mlir::RegisteredOperationName &opName, ::mlir::NamedAttrList &attributes) {
  auto attrNames = opName.getAttributeNames();
  ::mlir::Builder odsBuilder(attrNames.front().getContext());
  if (!attributes.get(attrNames[0])) {
     attributes.append(attrNames[0], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
  if (!attributes.get(attrNames[1])) {
     attributes.append(attrNames[1], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
}

::mlir::LogicalResult ReluOp::verifyInvariantsImpl() {
  auto namedAttrRange = (*this)->getAttrs();
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == tensor_sizeAttrName()) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == workspace_sizeAttrName()) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_tensor_size, "tensor_size")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_workspace_size, "workspace_size")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult ReluOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ReluOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace toy
MLIR_DEFINE_EXPLICIT_TYPE_ID(::toy::ReluOp)

namespace toy {

//===----------------------------------------------------------------------===//
// ::toy::SubOp definitions
//===----------------------------------------------------------------------===//

SubOpAdaptor::SubOpAdaptor(::mlir::ValueRange values, ::mlir::DictionaryAttr attrs, ::mlir::RegionRange regions) : odsOperands(values), odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("toy.sub", odsAttrs.getContext());
}

SubOpAdaptor::SubOpAdaptor(SubOp op) : odsOperands(op->getOperands()), odsAttrs(op->getAttrDictionary()), odsRegions(op->getRegions()), odsOpName(op->getName()) {}

::mlir::ValueRange SubOpAdaptor::getOperands() {
  return odsOperands;
}

std::pair<unsigned, unsigned> SubOpAdaptor::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::ValueRange SubOpAdaptor::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(odsOperands.begin(), valueRange.first),
           std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
}

::mlir::Value SubOpAdaptor::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value SubOpAdaptor::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::DictionaryAttr SubOpAdaptor::getAttributes() {
  return odsAttrs;
}

::mlir::IntegerAttr SubOpAdaptor::tensor_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, SubOp::tensor_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t SubOpAdaptor::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr SubOpAdaptor::workspace_sizeAttr() {
  assert(odsAttrs && "no attributes when constructing adapter");
  auto attr = ::mlir::impl::getAttrFromSortedRange(odsAttrs.begin() + 0, odsAttrs.end() - 0, SubOp::workspace_sizeAttrName(*odsOpName)).dyn_cast_or_null<::mlir::IntegerAttr>();
    if (!attr)
      attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t SubOpAdaptor::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::LogicalResult SubOpAdaptor::verify(::mlir::Location loc) {
  auto namedAttrRange = odsAttrs;
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == SubOp::tensor_sizeAttrName(*odsOpName)) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == SubOp::workspace_sizeAttrName(*odsOpName)) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (tblgen_tensor_size && !(((tblgen_tensor_size.isa<::mlir::IntegerAttr>())) && ((tblgen_tensor_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.sub' op ""attribute 'tensor_size' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_workspace_size && !(((tblgen_workspace_size.isa<::mlir::IntegerAttr>())) && ((tblgen_workspace_size.cast<::mlir::IntegerAttr>().getType().isSignlessInteger(64)))))
    return emitError(loc, "'toy.sub' op ""attribute 'workspace_size' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SubOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range SubOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value SubOp::lhs() {
  return *getODSOperands(0).begin();
}

::mlir::Value SubOp::rhs() {
  return *getODSOperands(1).begin();
}

::mlir::MutableOperandRange SubOp::lhsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::mlir::MutableOperandRange SubOp::rhsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> SubOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range SubOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Value SubOp::output() {
  return *getODSResults(0).begin();
}

::mlir::IntegerAttr SubOp::tensor_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, tensor_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t SubOp::tensor_size() {
  auto attr = tensor_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr SubOp::workspace_sizeAttr() {
  return ::mlir::impl::getAttrFromSortedRange((*this)->getAttrs().begin() + 0, (*this)->getAttrs().end() - 0, workspace_sizeAttrName()).dyn_cast_or_null<::mlir::IntegerAttr>();
}

uint64_t SubOp::workspace_size() {
  auto attr = workspace_sizeAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

void SubOp::tensor_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(tensor_sizeAttrName(), attr);
}

void SubOp::workspace_sizeAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(workspace_sizeAttrName(), attr);
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  odsState.addTypes(output);
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::IntegerAttr tensor_size, ::mlir::IntegerAttr workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (tensor_size) {
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), tensor_size);
  }
  if (workspace_size) {
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), workspace_size);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  odsState.addTypes(output);
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, uint64_t tensor_size, uint64_t workspace_size) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addAttribute(tensor_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), tensor_size));
  odsState.addAttribute(workspace_sizeAttrName(odsState.name), odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), workspace_size));
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SubOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

void SubOp::populateDefaultAttrs(const ::mlir::RegisteredOperationName &opName, ::mlir::NamedAttrList &attributes) {
  auto attrNames = opName.getAttributeNames();
  ::mlir::Builder odsBuilder(attrNames.front().getContext());
  if (!attributes.get(attrNames[0])) {
     attributes.append(attrNames[0], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
  if (!attributes.get(attrNames[1])) {
     attributes.append(attrNames[1], odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0));
  }
}

::mlir::LogicalResult SubOp::verifyInvariantsImpl() {
  auto namedAttrRange = (*this)->getAttrs();
  auto namedAttrIt = namedAttrRange.begin();
  ::mlir::Attribute tblgen_tensor_size;
  ::mlir::Attribute tblgen_workspace_size;
  while (true) {
    if (namedAttrIt == namedAttrRange.end()) {
      break;
    }
    else if (namedAttrIt->getName() == tensor_sizeAttrName()) {
      tblgen_tensor_size = namedAttrIt->getValue();
    }
    else if (namedAttrIt->getName() == workspace_sizeAttrName()) {
      tblgen_workspace_size = namedAttrIt->getValue();
    }
    ++namedAttrIt;
  }

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_tensor_size, "tensor_size")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ToyOps0(*this, tblgen_workspace_size, "workspace_size")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ToyOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult SubOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void SubOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace toy
MLIR_DEFINE_EXPLICIT_TYPE_ID(::toy::SubOp)


#endif  // GET_OP_CLASSES

