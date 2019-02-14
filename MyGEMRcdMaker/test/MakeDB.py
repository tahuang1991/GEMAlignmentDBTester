import FWCore.ParameterSet.Config as cms

process = cms.Process("MyGEMAlignmentRcdWriter")

# Load CondDB service
process.load("CondCore.CondDB.CondDB_cfi")

# output database (in this case local sqlite file)
process.CondDB.connect = 'sqlite_file:MyAlignment.db'

# A data source must always be defined. We don't need it, so here's a dummy one.
process.source = cms.Source("EmptyIOVSource",
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(1),
    lastValue = cms.uint64(1),
    interval = cms.uint64(1)
)

# We define the output service.
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDB,
    timetype = cms.untracked.string('runnumber'),
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('GEMAlignmentRcd'),
        tag = cms.string('GEMAlignment_test')
    ),
    # cms.PSet(
    #     record = cms.string('GEMAlignmentErrorRcd'),
    #     tag = cms.string('myGEMAlignment_test')
    # ),
    cms.PSet(
        record = cms.string('GEMAlignmentErrorExtendedRcd'),
        tag = cms.string('GEMAlignmentErrorExtended_test')
    ))
)

process.gem_maker = cms.EDAnalyzer("MyGEMRcdMaker",
    loggingOn= cms.untracked.bool(True),
    SinceAppendMode=cms.bool(True),
    Source=cms.PSet(
        IOVRun=cms.untracked.uint32(1)
    )
)

process.path = cms.Path(process.gem_maker)
