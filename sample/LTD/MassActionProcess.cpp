#include "libecs.hpp"
#include "Process.hpp"
#include "Util.hpp"
#include "PropertyInterface.hpp"
#include "PropertySlotMaker.hpp"
#include "System.hpp"
#include "Stepper.hpp"
#include "Variable.hpp"
#include "VariableProxy.hpp"

#include "FluxProcess.hpp"
#include "ecell3_dm.hpp"

#define ECELL3_DM_TYPE Process
#define ECELL3_DM_CLASSNAME MassActionProcess

USE_LIBECS;

ECELL3_DM_CLASS
  :  
  public FluxProcess
{

  ECELL3_DM_OBJECT;
  
 public:
  
  ECELL3_DM_CLASSNAME()
    {
      ECELL3_CREATE_PROPERTYSLOT_SET_GET( Real, k );
    }
  
  SIMPLE_SET_GET_METHOD( Real, k );
  
  virtual void process()
  {
    
    Real velocity( k * N_A );
    velocity *= getSuperSystem()->getVolume();

    for( VariableReferenceVectorConstIterator 
	   s( theVariableReferenceVector.begin() );
	 s != theZeroVariableReferenceIterator; ++s )
      {
	VariableReference aVariableReference( *s );
	Int aCoefficient( aVariableReference.getCoefficient() );
	do {
	  ++aCoefficient;
	  velocity *= aVariableReference.getConcentration();
	} while( aCoefficient != 0 );
	
      }
    
    setFlux(velocity);
    
    
    
  }
  
  virtual void initialize()
  {
    FluxProcess::initialize();
    declareUnidirectional();
  }  

 protected:
  
  Real k;
    
};

ECELL3_DM_INIT;
