// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
///
/// \brief Shows how to loop over collisions and tracks of a data frame.
///        Requires V0s to be filled with. Therefore use
///        o2-analysis-weak-decay-indices --aod-file AO2D.root | o2-analysistutorial-collision-tracks-iteration
/// \author
/// \since

#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"

#include <iostream>

using namespace o2;
using namespace o2::framework;

struct TracksPerCollision {
  int iCol{0};
  void process(aod::Collision const& collision, aod::Tracks const& tracks)
  {
    if(iCol>10) return;
    std::cout << "TracksPerCollision::process(),\t iCol = " << iCol << "\n";
    // `tracks` contains tracks belonging to `collision`
    LOGF(info, "Collision index : %d", collision.index());
    LOGF(info, "Number of tracks: %d", tracks.size());

    // process the tracks of a given collision
    int iTr{0};
    for (auto& track : tracks) {
      if(iTr>100) break;
      LOGF(info, "  track pT = %f GeV/c", track.pt());
      ++iTr;
    }
    ++iCol;
  }
};

struct TracksPerDataframe {

  void process(aod::Collisions const& collisions, aod::Tracks const& tracks)
  {
    std::cout << "TracksPerDataframe::process()\n";
    // `tracks` contains all tracks of a data frame
    LOGF(info, "Number of collisions: %d", collisions.size());
    LOGF(info, "Number of tracks    : %d", tracks.size());
  }
};

struct GroupByCollision {

  void process(aod::Collision const& collision, aod::Tracks const& tracks, aod::V0s const& v0s)
  {
    std::cout << "GroupByCollision::process()\n";
    // `tracks` contains tracks belonging to `collision`
    // `v0s`    contains V0s    belonging to `collision`
    LOGF(info, "Collision index : %d", collision.index());
    LOGF(info, "Number of tracks: %d", tracks.size());
//     LOGF(info, "Number of v0s   : %d", v0s.size());
  }
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  std::cout << "defineDataProcessing()\n";
  return WorkflowSpec{
    adaptAnalysisTask<TracksPerCollision>(cfgc),
    adaptAnalysisTask<TracksPerDataframe>(cfgc),
    adaptAnalysisTask<GroupByCollision>(cfgc),
  };
}
