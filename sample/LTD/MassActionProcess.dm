CLASSNAME = 'MassActionProcess'
BASECLASS = 'FluxProcess'
PROPERTIES = [('Real','k',0.0)]

PROTECTED_AUX ='''
  VariableReference P0;
'''

defineMethod( 'initialize','''
''' )

defineMethod( 'react',
'''
  Real velocity( k * N_A );
  velocity *= getSuperSystem()->getVolume();
  
  for(   VariableReferenceMapIterator s( theVariableReferenceMap.begin() );
       s != theVariableReferenceMap.end(); ++s )
    {
      VariableReference aVariableReference( s->second );
      Int aCoefficient( aVariableReference.getCoefficient() );
      if( aCoefficient < 0 )
        {
          do{
            aCoefficient++;
            velocity *= aVariableReference.getVariable()->getConcentration();
          }while(aCoefficient != 0 );
        }
     }
  process(velocity);
''')

