import FWCore.ParameterSet.Config as cms

process = cms.Process("MyGEMAlignmentRcdRetrieveTest")
process.load("Geometry.GEMGeometryBuilder.gemGeometryDB_cfi")
process.GEMGeometryESModule.applyAlignment = cms.bool(True)
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS3', '')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")

process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(
        record = cms.string('GEMAlignmentRcd'),
        tag = cms.string("GEMAlignment_test"),
        connect = cms.string("sqlite:./MyAlignment.db"),
    ),
    # cms.PSet(
    #     record = cms.string('GEMAlignmentErrorRcd'),
    #     tag = cms.string("myGEMAlignment_test"),
    #     connect = cms.string("sqlite:./MyAlignment.db"),
    # ),
    cms.PSet(
        record = cms.string('GEMAlignmentErrorExtendedRcd'),
        tag = cms.string("GEMAlignmentErrorExtended_test"),
        connect = cms.string("sqlite:./MyAlignment.db"),
    ),
    cms.PSet(
        record = cms.string('GEMRecoGeometryRcd'),
        tag = cms.string("GEMRECO_Geometry_10YV4"),
        connect = cms.string("sqlite:./MyGEMGeometry.db"),
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.source = cms.Source("EmptySource")

process.test = cms.EDAnalyzer("GEMTestGeometryAnalyzer")

process.path = cms.Path(process.test)
