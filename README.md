# GEM Alignment Test

Run Alignment DB creator from from 10_5_0_pre1:
```
cmsrel CMSSW_10_5_0_pre1
cd CMSSW_10_5_0_pre1/src
cmsenv
git cms-merge-topic -u watson-ij:gem-alignment-rcd-1050p1
git clone https://github.com/watson-ij/GEMAlignmentDBTester.git
scram b -j4
cd GEMAlignmentDBTester/MyGEMRcdMaker/test
cmsRun MakeDB.py
```

or from a recent nightly

```
cmsrel CMSSW_10_5_X_2019-02-12-1100
cd CMSSW_10_5_X_2019-02-12-1100/src
git cms-merge-topic -u watson-ij:gem-alignment-rcd
git clone https://github.com/watson-ij/GEMAlignmentDBTester.git
scram b -j4
cd GEMAlignmentDBTester/MyGEMRcdMaker/test
cmsRun MakeDB.py
```
