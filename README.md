# GEM Alignment Test

```
cmsrel CMSSW_10_5_X_2019-02-12-1100
cd CMSSW_10_5_X_2019-02-12-1100/src
git cms-merge-topic watson-ij:gem-alignment-rcd
git clone https://github.com/watson-ij/GEMAlignmentDBTester.git
scram b -j4
cd GEMAlignmentDBTester/MyGEMRcdMaker/test
cmsRun MakeDB.py
```
