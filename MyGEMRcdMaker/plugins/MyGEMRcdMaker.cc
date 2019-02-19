// -*- C++ -*-
//
// Package:    MyDB/MyGEMRcdMaker
// Class:      MyGEMRcdMaker
//
/**\class MyGEMRcdMaker MyGEMRcdMaker.cc MyDB/MyGEMRcdMaker/plugins/MyGEMRcdMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Ian James Watson
//         Created:  Wed, 13 Feb 2019 14:29:19 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "CondFormats/AlignmentRecord/interface/GEMAlignmentRcd.h"
#include "CondFormats/AlignmentRecord/interface/GEMAlignmentErrorRcd.h"
#include "CondFormats/AlignmentRecord/interface/GEMAlignmentErrorExtendedRcd.h"

#include "CondFormats/Alignment/interface/Alignments.h"
#include "CondFormats/Alignment/interface/AlignmentErrors.h"
#include "CondFormats/Alignment/interface/AlignmentErrorsExtended.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"

#include "CLHEP/Vector/EulerAngles.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CondFormats/Alignment/interface/AlignTransform.h"

 #include "DataFormats/DetId/interface/DetId.h"
 #include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
 #include "DataFormats/MuonDetId/interface/GEMDetId.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class MyGEMRcdMaker : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MyGEMRcdMaker(const edm::ParameterSet&);
      ~MyGEMRcdMaker();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyGEMRcdMaker::MyGEMRcdMaker(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


MyGEMRcdMaker::~MyGEMRcdMaker()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyGEMRcdMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  Alignments* MyGEMAlignment = new Alignments();
  // AlignmentErrors* MyGEMAlignmentError = new AlignmentErrors();
  AlignmentErrorsExtended* MyGEMAlignmentErrorExtended = new AlignmentErrorsExtended();

  // Form the data here
  for (int re = -1; re <= 1; re = re+2) {
    for (int st=1; st<=GEMDetId::maxStationId; ++st) {
      for (int ri=1; ri<=1; ++ri) {
	for (int la=1; la<=2; ++la) {
	  for (int ch=1; ch<=30; ++ch) {
	    if (ch == 27)
	      MyGEMAlignment->m_align.push_back(AlignTransform(AlignTransform::Translation(-2,0,0),
							       AlignTransform::EulerAngles(0,0,0),
							       GEMDetId(re, ri, st, la, ch, 0)
							       ));
	    else
	      MyGEMAlignment->m_align.push_back(AlignTransform(AlignTransform::Translation(0,0,0),
							       AlignTransform::EulerAngles(0,0,0),
							       GEMDetId(re, ri, st, la, ch, 0)
							       ));	      
	  }
	}
      }
    }
  }

  edm::Service<cond::service::PoolDBOutputService> poolDbService;
  if( poolDbService.isAvailable() ) {
      poolDbService->writeOne( MyGEMAlignment, poolDbService->currentTime(),
                                               "GEMAlignmentRcd"  );
      // poolDbService->writeOne( MyGEMAlignmentError, poolDbService->currentTime(),
      //                                          "GEMAlignmentErrorRcd"  );
      poolDbService->writeOne( MyGEMAlignmentErrorExtended, poolDbService->currentTime(),
                                               "GEMAlignmentErrorExtendedRcd"  );
  }
  else
      throw std::runtime_error("PoolDBService required.");
}


// ------------ method called once each job just before starting event loop  ------------
void
MyGEMRcdMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
MyGEMRcdMaker::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyGEMRcdMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyGEMRcdMaker);
