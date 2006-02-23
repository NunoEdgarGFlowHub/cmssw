#ifndef TkDetLayers_TOBLayer_h
#define TkDetLayers_TOBLayer_h


#include "TrackingTools/DetLayers/interface/RodBarrelLayer.h"
#include "RecoTracker/TkDetLayers/interface/TOBRod.h"
#include "TrackingTools/DetLayers/interface/PeriodicBinFinderInPhi.h"
#include "RecoTracker/TkDetLayers/interface/SubLayerCrossings.h"

/** A concrete implementation for TOB layer 
 *  built out of TOBRods
 */

class TOBLayer : public RodBarrelLayer{
 public:
  typedef PeriodicBinFinderInPhi<double>   BinFinderType;


  TOBLayer(vector<const TOBRod*>& innerRods,
	   vector<const TOBRod*>& outerRods);
  ~TOBLayer();
  
  // GeometricSearchDet interface
  
  virtual vector<const GeomDet*> basicComponents() const;

  virtual vector<const GeometricSearchDet*> components() const;

  
  virtual pair<bool, TrajectoryStateOnSurface>
  compatible( const TrajectoryStateOnSurface& ts, const Propagator&, 
	      const MeasurementEstimator&) const;

  virtual vector<DetWithState> 
  compatibleDets( const TrajectoryStateOnSurface& startingState,
		  const Propagator& prop, 
		  const MeasurementEstimator& est) const;

  virtual vector<DetGroup> 
  groupedCompatibleDets( const TrajectoryStateOnSurface& startingState,
			 const Propagator& prop,
			 const MeasurementEstimator& est) const;


  virtual bool hasGroups() const {return true;}  

  // DetLayer interface
  virtual Module   module()   const { return silicon;}
  
 

 private:
  vector<const TOBRod*> theRods;
  vector<const TOBRod*> theInnerRods;
  vector<const TOBRod*> theOuterRods;

  BinFinderType    theInnerBinFinder;
  BinFinderType    theOuterBinFinder;
  ReferenceCountingPointer<BoundCylinder>  theInnerCylinder;
  ReferenceCountingPointer<BoundCylinder>  theOuterCylinder;

  // private methods for the implementation of groupedCompatibleDets()

  SubLayerCrossings computeCrossings( const TrajectoryStateOnSurface& tsos,
				      PropagationDirection propDir) const;
  
  bool addClosest( const TrajectoryStateOnSurface& tsos,
		   const Propagator& prop,
		   const MeasurementEstimator& est,
		   const SubLayerCrossing& crossing,
		   vector<DetGroup>& result) const;

  float computeWindowSize( const GeomDet* det, 
			   const TrajectoryStateOnSurface& tsos, 
			   const MeasurementEstimator& est) const;

  void searchNeighbors( const TrajectoryStateOnSurface& tsos,
			const Propagator& prop,
			const MeasurementEstimator& est,
			const SubLayerCrossing& crossing,
			float window, 
			vector<DetGroup>& result,
			bool checkClosest) const;

  BoundCylinder* cylinder( const vector<const TOBRod*>& rods) const ;
};


#endif 
