static ::mlir::Attribute readDIBasicTypeAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t tag;
  StringRef name;
  uint64_t sizeInBits, encoding;
  if (succeeded(reader.readVarInt(tag)) &&
      succeeded(reader.readString(name)) &&
      succeeded(reader.readVarInt(sizeInBits)) &&
      succeeded(reader.readVarInt(encoding))) {
    return get<DIBasicTypeAttr>(context, tag, name, sizeInBits, encoding);
  }
  return DIBasicTypeAttr();
}

static void write(DIBasicTypeAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIBasicTypeAttr */ 0);
  writer.writeVarInt(attribute.getTag());
  writer.writeOwnedString(attribute.getName());
  writer.writeVarInt(attribute.getSizeInBits());
  writer.writeVarInt(attribute.getEncoding());
}

static ::mlir::Attribute readDICompileUnitAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DistinctAttr id;
  uint64_t sourceLanguage;
  DIFileAttr file;
  StringAttr producer;
  bool isOptimized;
  uint64_t _rawEmissionKind;
  DIEmissionKind emissionKind;
  uint64_t _rawNameTableKind;
  DINameTableKind nameTableKind;
  if (succeeded(reader.readAttribute(id)) &&
      succeeded(reader.readVarInt(sourceLanguage)) &&
      succeeded(reader.readAttribute(file)) &&
      succeeded(reader.readOptionalAttribute(producer)) &&
      succeeded(reader.readBool(isOptimized)) &&
      succeeded(reader.readVarInt(_rawEmissionKind)) &&
      ((emissionKind = (DIEmissionKind)_rawEmissionKind), true) &&
      succeeded(reader.readVarInt(_rawNameTableKind)) &&
      ((nameTableKind = (DINameTableKind)_rawNameTableKind), true)) {
    return get<DICompileUnitAttr>(context, id, sourceLanguage, file, producer, isOptimized, emissionKind, nameTableKind);
  }
  return DICompileUnitAttr();
}

static void write(DICompileUnitAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DICompileUnitAttr */ 1);
  writer.writeAttribute(attribute.getId());
  writer.writeVarInt(attribute.getSourceLanguage());
  writer.writeAttribute(attribute.getFile());
  writer.writeOptionalAttribute(attribute.getProducer());
  writer.writeOwnedBool(attribute.getIsOptimized());
  writer.writeVarInt((uint64_t)attribute.getEmissionKind());
  writer.writeVarInt((uint64_t)attribute.getNameTableKind());
}

static ::mlir::Attribute readDICompositeTypeAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DistinctAttr recId;
  bool isRecSelf;
  uint64_t tag;
  StringAttr name;
  DIFileAttr file;
  uint64_t line;
  DIScopeAttr scope;
  DITypeAttr baseType;
  uint64_t _rawflags;
  DIFlags flags;
  uint64_t sizeInBits, alignInBits;
  DIExpressionAttr dataLocation, rank, allocated, associated;
  SmallVector<DINodeAttr> elements;
  if (succeeded(reader.readOptionalAttribute(recId)) &&
      succeeded(reader.readBool(isRecSelf)) &&
      succeeded(reader.readVarInt(tag)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readOptionalAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(baseType)) &&
      succeeded(reader.readVarInt(_rawflags)) &&
      ((flags = (DIFlags)_rawflags), true) &&
      succeeded(reader.readVarInt(sizeInBits)) &&
      succeeded(reader.readVarInt(alignInBits)) &&
      succeeded(reader.readOptionalAttribute(dataLocation)) &&
      succeeded(reader.readOptionalAttribute(rank)) &&
      succeeded(reader.readOptionalAttribute(allocated)) &&
      succeeded(reader.readOptionalAttribute(associated)) &&
      succeeded(readOptionalArrayRef<DINodeAttr>(reader, elements))) {
    return get<DICompositeTypeAttr>(context, recId, isRecSelf, tag, name, file, line, scope, baseType, flags, sizeInBits, alignInBits, dataLocation, rank, allocated, associated, elements);
  }
  return DICompositeTypeAttr();
}

static void write(DICompositeTypeAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DICompositeTypeAttr */ 2);
  writer.writeOptionalAttribute(attribute.getRecId());
  writer.writeOwnedBool(attribute.getIsRecSelf());
  writer.writeVarInt(attribute.getTag());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeOptionalAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getBaseType());
  writer.writeVarInt((uint64_t)attribute.getFlags());
  writer.writeVarInt(attribute.getSizeInBits());
  writer.writeVarInt(attribute.getAlignInBits());
  writer.writeOptionalAttribute(attribute.getDataLocation());
  writer.writeOptionalAttribute(attribute.getRank());
  writer.writeOptionalAttribute(attribute.getAllocated());
  writer.writeOptionalAttribute(attribute.getAssociated());
  writeOptionalArrayRef<DINodeAttr>(writer, attribute.getElements());
}

static ::mlir::Attribute readDIDerivedTypeAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t tag;
  StringAttr name;
  DITypeAttr baseType;
  uint64_t sizeInBits, alignInBits, offsetInBits;
  std::optional<unsigned> dwarfAddressSpace;
  uint64_t _rawflags;
  DIFlags flags;
  DINodeAttr extraData;
  if (succeeded(reader.readVarInt(tag)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(baseType)) &&
      succeeded(reader.readVarInt(sizeInBits)) &&
      succeeded(reader.readVarInt(alignInBits)) &&
      succeeded(reader.readVarInt(offsetInBits)) &&
      succeeded(readOptionalInt(reader, dwarfAddressSpace)) &&
      succeeded(reader.readVarInt(_rawflags)) &&
      ((flags = (DIFlags)_rawflags), true) &&
      succeeded(reader.readOptionalAttribute(extraData))) {
    return get<DIDerivedTypeAttr>(context, tag, name, baseType, sizeInBits, alignInBits, offsetInBits, dwarfAddressSpace, flags, extraData);
  }
  return DIDerivedTypeAttr();
}

static void write(DIDerivedTypeAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIDerivedTypeAttr */ 3);
  writer.writeVarInt(attribute.getTag());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getBaseType());
  writer.writeVarInt(attribute.getSizeInBits());
  writer.writeVarInt(attribute.getAlignInBits());
  writer.writeVarInt(attribute.getOffsetInBits());
  writeOptionalInt(writer, attribute.getDwarfAddressSpace());
  writer.writeVarInt((uint64_t)attribute.getFlags());
  writer.writeOptionalAttribute(attribute.getExtraData());
}

static ::mlir::Attribute readDIExpressionAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  SmallVector<DIExpressionElemAttr> operations;
  if (succeeded(readOptionalArrayRef<DIExpressionElemAttr>(reader, operations))) {
    return get<DIExpressionAttr>(context, operations);
  }
  return DIExpressionAttr();
}

static void write(DIExpressionAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIExpressionAttr */ 5);
  writeOptionalArrayRef<DIExpressionElemAttr>(writer, attribute.getOperations());
}

static ::mlir::Attribute readDIExpressionElemAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t opcode;
  SmallVector<uint64_t> arguments;
  if (succeeded(reader.readVarInt(opcode)) &&
      succeeded(readOptionalArrayRef<uint64_t>(reader, arguments))) {
    return get<DIExpressionElemAttr>(context, opcode, arguments);
  }
  return DIExpressionElemAttr();
}

static void write(DIExpressionElemAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIExpressionElemAttr */ 4);
  writer.writeVarInt(attribute.getOpcode());
  writeOptionalArrayRef<uint64_t>(writer, attribute.getArguments());
}

static ::mlir::Attribute readDIFileAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  StringRef name, directory;
  if (succeeded(reader.readString(name)) &&
      succeeded(reader.readString(directory))) {
    return get<DIFileAttr>(context, name, directory);
  }
  return DIFileAttr();
}

static void write(DIFileAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIFileAttr */ 6);
  writer.writeOwnedString(attribute.getName());
  writer.writeOwnedString(attribute.getDirectory());
}

static ::mlir::Attribute readDIGlobalVariableAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIScopeAttr scope;
  StringAttr name, linkageName;
  DIFileAttr file;
  uint64_t line;
  DITypeAttr type;
  bool isLocalToUnit, isDefined;
  uint64_t alignInBits;
  if (succeeded(reader.readOptionalAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(linkageName)) &&
      succeeded(reader.readAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readAttribute(type)) &&
      succeeded(reader.readBool(isLocalToUnit)) &&
      succeeded(reader.readBool(isDefined)) &&
      succeeded(reader.readVarInt(alignInBits))) {
    return get<DIGlobalVariableAttr>(context, scope, name, linkageName, file, line, type, isLocalToUnit, isDefined, alignInBits);
  }
  return DIGlobalVariableAttr();
}

static void write(DIGlobalVariableAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIGlobalVariableAttr */ 7);
  writer.writeOptionalAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getLinkageName());
  writer.writeAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeAttribute(attribute.getType());
  writer.writeOwnedBool(attribute.getIsLocalToUnit());
  writer.writeOwnedBool(attribute.getIsDefined());
  writer.writeVarInt(attribute.getAlignInBits());
}

static ::mlir::Attribute readDIGlobalVariableExpressionAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIGlobalVariableAttr var;
  DIExpressionAttr expr;
  if (succeeded(reader.readAttribute(var)) &&
      succeeded(reader.readOptionalAttribute(expr))) {
    return get<DIGlobalVariableExpressionAttr>(context, var, expr);
  }
  return DIGlobalVariableExpressionAttr();
}

static void write(DIGlobalVariableExpressionAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIGlobalVariableExpressionAttr */ 8);
  writer.writeAttribute(attribute.getVar());
  writer.writeOptionalAttribute(attribute.getExpr());
}

static ::mlir::Attribute readDIImportedEntityAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t tag;
  DIScopeAttr scope;
  DINodeAttr entity;
  DIFileAttr file;
  uint64_t line;
  StringAttr name;
  SmallVector<DINodeAttr> elements;
  if (succeeded(reader.readVarInt(tag)) &&
      succeeded(reader.readAttribute(scope)) &&
      succeeded(reader.readAttribute(entity)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(readOptionalArrayRef<DINodeAttr>(reader, elements))) {
    return get<DIImportedEntityAttr>(context, tag, scope, entity, file, line, name, elements);
  }
  return DIImportedEntityAttr();
}

static void write(DIImportedEntityAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DIImportedEntityAttr */ 9);
  writer.writeVarInt(attribute.getTag());
  writer.writeAttribute(attribute.getScope());
  writer.writeAttribute(attribute.getEntity());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeOptionalAttribute(attribute.getName());
  writeOptionalArrayRef<DINodeAttr>(writer, attribute.getElements());
}

static ::mlir::Attribute readDILabelAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIScopeAttr scope;
  StringAttr name;
  DIFileAttr file;
  uint64_t line;
  if (succeeded(reader.readAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line))) {
    return DILabelAttr::get(context, scope, name, file, line);
  }
  return DILabelAttr();
}

static void write(DILabelAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DILabelAttr */ 10);
  writer.writeAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
}

static ::mlir::Attribute readDILexicalBlockAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIScopeAttr scope;
  DIFileAttr file;
  uint64_t line, column;
  if (succeeded(reader.readAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readVarInt(column))) {
    return get<DILexicalBlockAttr>(context, scope, file, line, column);
  }
  return DILexicalBlockAttr();
}

static void write(DILexicalBlockAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DILexicalBlockAttr */ 11);
  writer.writeAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeVarInt(attribute.getColumn());
}

static ::mlir::Attribute readDILexicalBlockFileAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIScopeAttr scope;
  DIFileAttr file;
  uint64_t discriminator;
  if (succeeded(reader.readAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(discriminator))) {
    return get<DILexicalBlockFileAttr>(context, scope, file, discriminator);
  }
  return DILexicalBlockFileAttr();
}

static void write(DILexicalBlockFileAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DILexicalBlockFileAttr */ 12);
  writer.writeAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getDiscriminator());
}

static ::mlir::Attribute readDILocalVariableAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DIScopeAttr scope;
  StringAttr name;
  DIFileAttr file;
  uint64_t line, arg, alignInBits;
  DITypeAttr type;
  uint64_t _rawflags;
  DIFlags flags;
  if (succeeded(reader.readAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readVarInt(arg)) &&
      succeeded(reader.readVarInt(alignInBits)) &&
      succeeded(reader.readOptionalAttribute(type)) &&
      succeeded(reader.readVarInt(_rawflags)) &&
      ((flags = (DIFlags)_rawflags), true)) {
    return DILocalVariableAttr::get(context, scope, name, file, line, arg, alignInBits, type, flags);
  }
  return DILocalVariableAttr();
}

static void write(DILocalVariableAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DILocalVariableAttr */ 13);
  writer.writeAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeVarInt(attribute.getArg());
  writer.writeVarInt(attribute.getAlignInBits());
  writer.writeOptionalAttribute(attribute.getType());
  writer.writeVarInt((uint64_t)attribute.getFlags());
}

static ::mlir::Attribute readDINamespaceAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  StringAttr name;
  DIScopeAttr scope;
  bool exportSymbols;
  if (succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(scope)) &&
      succeeded(reader.readBool(exportSymbols))) {
    return get<DINamespaceAttr>(context, name, scope, exportSymbols);
  }
  return DINamespaceAttr();
}

static void write(DINamespaceAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DINamespaceAttr */ 14);
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getScope());
  writer.writeOwnedBool(attribute.getExportSymbols());
}

static ::mlir::Attribute readDISubprogramAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  DistinctAttr recId;
  bool isRecSelf;
  DistinctAttr id;
  DICompileUnitAttr compileUnit;
  DIScopeAttr scope;
  StringAttr name, linkageName;
  DIFileAttr file;
  uint64_t line, scopeLine, _rawflags;
  DISubprogramFlags subprogramFlags;
  DISubroutineTypeAttr type;
  SmallVector<DINodeAttr> retainedNodes, annotations;
  if (succeeded(reader.readOptionalAttribute(recId)) &&
      succeeded(reader.readBool(isRecSelf)) &&
      succeeded(reader.readOptionalAttribute(id)) &&
      succeeded(reader.readOptionalAttribute(compileUnit)) &&
      succeeded(reader.readOptionalAttribute(scope)) &&
      succeeded(reader.readOptionalAttribute(name)) &&
      succeeded(reader.readOptionalAttribute(linkageName)) &&
      succeeded(reader.readOptionalAttribute(file)) &&
      succeeded(reader.readVarInt(line)) &&
      succeeded(reader.readVarInt(scopeLine)) &&
      succeeded(reader.readVarInt(_rawflags)) &&
      ((subprogramFlags = (DISubprogramFlags)_rawflags), true) &&
      succeeded(reader.readOptionalAttribute(type)) &&
      succeeded(readOptionalArrayRef<DINodeAttr>(reader, retainedNodes)) &&
      succeeded(readOptionalArrayRef<DINodeAttr>(reader, annotations))) {
    return get<DISubprogramAttr>(context, recId, isRecSelf, id, compileUnit, scope, name, linkageName, file, line, scopeLine, subprogramFlags, type, retainedNodes, annotations);
  }
  return DISubprogramAttr();
}

static void write(DISubprogramAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DISubprogramAttr */ 15);
  writer.writeOptionalAttribute(attribute.getRecId());
  writer.writeOwnedBool(attribute.getIsRecSelf());
  writer.writeOptionalAttribute(attribute.getId());
  writer.writeOptionalAttribute(attribute.getCompileUnit());
  writer.writeOptionalAttribute(attribute.getScope());
  writer.writeOptionalAttribute(attribute.getName());
  writer.writeOptionalAttribute(attribute.getLinkageName());
  writer.writeOptionalAttribute(attribute.getFile());
  writer.writeVarInt(attribute.getLine());
  writer.writeVarInt(attribute.getScopeLine());
  writer.writeVarInt((uint64_t)attribute.getSubprogramFlags());
  writer.writeOptionalAttribute(attribute.getType());
  writeOptionalArrayRef<DINodeAttr>(writer, attribute.getRetainedNodes());
  writeOptionalArrayRef<DINodeAttr>(writer, attribute.getAnnotations());
}

static ::mlir::Attribute readDISubrangeAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  Attribute count, lowerBound, upperBound, stride;
  if (succeeded(reader.readOptionalAttribute(count)) &&
      succeeded(reader.readOptionalAttribute(lowerBound)) &&
      succeeded(reader.readOptionalAttribute(upperBound)) &&
      succeeded(reader.readOptionalAttribute(stride))) {
    return get<DISubrangeAttr>(context, count, lowerBound, upperBound, stride);
  }
  return DISubrangeAttr();
}

static void write(DISubrangeAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DISubrangeAttr */ 16);
  writer.writeOptionalAttribute(attribute.getCount());
  writer.writeOptionalAttribute(attribute.getLowerBound());
  writer.writeOptionalAttribute(attribute.getUpperBound());
  writer.writeOptionalAttribute(attribute.getStride());
}

static ::mlir::Attribute readDISubroutineTypeAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t callingConvention;
  SmallVector<DITypeAttr> types;
  if (succeeded(reader.readVarInt(callingConvention)) &&
      succeeded(readOptionalArrayRef<DITypeAttr>(reader, types))) {
    return get<DISubroutineTypeAttr>(context, callingConvention, types);
  }
  return DISubroutineTypeAttr();
}

static void write(DISubroutineTypeAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* DISubroutineTypeAttr */ 17);
  writer.writeVarInt(attribute.getCallingConvention());
  writeOptionalArrayRef<DITypeAttr>(writer, attribute.getTypes());
}

static ::mlir::Attribute readLoopAnnotationAttr(MLIRContext* context, DialectBytecodeReader &reader) {
  BoolAttr disableNonforced;
  LoopVectorizeAttr vectorize;
  LoopInterleaveAttr interleave;
  LoopUnrollAttr unroll;
  LoopUnrollAndJamAttr unrollAndJam;
  LoopLICMAttr licm;
  LoopDistributeAttr distribute;
  LoopPipelineAttr pipeline;
  LoopPeeledAttr peeled;
  LoopUnswitchAttr unswitch;
  BoolAttr mustProgress, isVectorized;
  FusedLoc startLoc, endLoc;
  SmallVector<AccessGroupAttr> parallelAccesses;
  if (succeeded(reader.readOptionalAttribute(disableNonforced)) &&
      succeeded(reader.readOptionalAttribute(vectorize)) &&
      succeeded(reader.readOptionalAttribute(interleave)) &&
      succeeded(reader.readOptionalAttribute(unroll)) &&
      succeeded(reader.readOptionalAttribute(unrollAndJam)) &&
      succeeded(reader.readOptionalAttribute(licm)) &&
      succeeded(reader.readOptionalAttribute(distribute)) &&
      succeeded(reader.readOptionalAttribute(pipeline)) &&
      succeeded(reader.readOptionalAttribute(peeled)) &&
      succeeded(reader.readOptionalAttribute(unswitch)) &&
      succeeded(reader.readOptionalAttribute(mustProgress)) &&
      succeeded(reader.readOptionalAttribute(isVectorized)) &&
      succeeded(reader.readOptionalAttribute(startLoc)) &&
      succeeded(reader.readOptionalAttribute(endLoc)) &&
      succeeded(readOptionalArrayRef<AccessGroupAttr>(reader, parallelAccesses))) {
    return get<LoopAnnotationAttr>(context, disableNonforced, vectorize, interleave, unroll, unrollAndJam, licm, distribute, pipeline, peeled, unswitch, mustProgress, isVectorized, startLoc, endLoc, parallelAccesses);
  }
  return LoopAnnotationAttr();
}

static void write(LoopAnnotationAttr attribute, DialectBytecodeWriter &writer) {
  writer.writeVarInt(/* LoopAnnotationAttr */ 18);
  writer.writeOptionalAttribute(attribute.getDisableNonforced());
  writer.writeOptionalAttribute(attribute.getVectorize());
  writer.writeOptionalAttribute(attribute.getInterleave());
  writer.writeOptionalAttribute(attribute.getUnroll());
  writer.writeOptionalAttribute(attribute.getUnrollAndJam());
  writer.writeOptionalAttribute(attribute.getLicm());
  writer.writeOptionalAttribute(attribute.getDistribute());
  writer.writeOptionalAttribute(attribute.getPipeline());
  writer.writeOptionalAttribute(attribute.getPeeled());
  writer.writeOptionalAttribute(attribute.getUnswitch());
  writer.writeOptionalAttribute(attribute.getMustProgress());
  writer.writeOptionalAttribute(attribute.getIsVectorized());
  writer.writeOptionalAttribute(attribute.getStartLoc());
  writer.writeOptionalAttribute(attribute.getEndLoc());
  writeOptionalArrayRef<AccessGroupAttr>(writer, attribute.getParallelAccesses());
}

static Attribute readAttribute(MLIRContext* context, DialectBytecodeReader &reader) {
  uint64_t kind;
  if (failed(reader.readVarInt(kind)))
    return Attribute();
  switch (kind) {
    case 0:
      return readDIBasicTypeAttr(context, reader);
    case 1:
      return readDICompileUnitAttr(context, reader);
    case 2:
      return readDICompositeTypeAttr(context, reader);
    case 3:
      return readDIDerivedTypeAttr(context, reader);
    case 4:
      return readDIExpressionElemAttr(context, reader);
    case 5:
      return readDIExpressionAttr(context, reader);
    case 6:
      return readDIFileAttr(context, reader);
    case 7:
      return readDIGlobalVariableAttr(context, reader);
    case 8:
      return readDIGlobalVariableExpressionAttr(context, reader);
    case 9:
      return readDIImportedEntityAttr(context, reader);
    case 10:
      return readDILabelAttr(context, reader);
    case 11:
      return readDILexicalBlockAttr(context, reader);
    case 12:
      return readDILexicalBlockFileAttr(context, reader);
    case 13:
      return readDILocalVariableAttr(context, reader);
    case 14:
      return readDINamespaceAttr(context, reader);
    case 15:
      return readDISubprogramAttr(context, reader);
    case 16:
      return readDISubrangeAttr(context, reader);
    case 17:
      return readDISubroutineTypeAttr(context, reader);
    case 18:
      return readLoopAnnotationAttr(context, reader);
    default:
      reader.emitError() << "unknown attribute code: " << kind;
      return Attribute();
  }
  return Attribute();
}

static LogicalResult writeAttribute(Attribute attribute,
                                DialectBytecodeWriter &writer) {
  return TypeSwitch<Attribute, LogicalResult>(attribute)
    .Case([&](DIBasicTypeAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DICompileUnitAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DICompositeTypeAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIDerivedTypeAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIExpressionAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIExpressionElemAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIFileAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIGlobalVariableAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIGlobalVariableExpressionAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DIImportedEntityAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DILabelAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DILexicalBlockAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DILexicalBlockFileAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DILocalVariableAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DINamespaceAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DISubprogramAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DISubrangeAttr t) {
      return write(t, writer), success();
    })
    .Case([&](DISubroutineTypeAttr t) {
      return write(t, writer), success();
    })
    .Case([&](LoopAnnotationAttr t) {
      return write(t, writer), success();
    })
    .Default([&](Attribute) { return failure(); });
}

static Type readType(MLIRContext* context, DialectBytecodeReader &reader) {
  return reader.emitError() << "unknown attribute", Type();
}

static LogicalResult writeType(Type type,
                                DialectBytecodeWriter &writer) {
  return TypeSwitch<Type, LogicalResult>(type)
    .Default([&](Type) { return failure(); });
}

