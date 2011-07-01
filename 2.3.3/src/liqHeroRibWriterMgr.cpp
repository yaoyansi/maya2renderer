#include <liqHeroRibWriterMgr.h>

#include <string>

#include <liqGlobalVariable.h>
#include <liqRibTranslator.h>

tHeroRibWriterMgr::tHeroRibWriterMgr()
{

}
//
tHeroRibWriterMgr::~tHeroRibWriterMgr()
{

}
//
TempControlBreak tHeroRibWriterMgr::write(
struct liqGlobalVariable &liqglo___, 
	const structJob &currentJob___ ,
	const long scanTime__,
	const bool m_outputLightsInDeepShadows__
	//,std::vector<structJob>  jobList__
	)
{
#ifndef RENDER_PIPE
	liquidMessage( "Beginning RIB output to '" + std::string( currentJob___.ribFileName.asChar() ) + "'", messageInfo );
	RiBegin( const_cast< RtToken >( currentJob___.ribFileName.asChar() ) );
#else//RENDER_PIPE
	liqglo___.liqglo_ribFP = fopen( currentJob___.ribFileName.asChar(), "w" );
	if( liqglo___.liqglo_ribFP ) 
	{
		RtInt ribFD = fileno( liqglo___.liqglo_ribFP );
		RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
	} 
	else
	{
		liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
	}

	liquidMessage( "Beginning RI output directly to renderer", messageInfo );
	RiBegin( RI_NULL );
#endif//RENDER_PIPE
	// full beauty/shadow rib generation
	//
	/* cout <<"  * build full rib"<<endl; */
	if( liqRibTranslator::getInstancePtr()->ribPrologue__() == MS::kSuccess ) 
	{
		if( liqRibTranslator::getInstancePtr()->framePrologue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->worldPrologue__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( !currentJob___.isShadow || ( currentJob___.isShadow && currentJob___.deepShadows && m_outputLightsInDeepShadows__) ) 
			if( liqRibTranslator::getInstancePtr()->lightBlock__() != MS::kSuccess ) 
				return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->coordSysBlock__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->objectBlock__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->worldEpilogue__() != MS::kSuccess ) 
			return TCB_Break;//break;
		if( liqRibTranslator::getInstancePtr()->frameEpilogue__( scanTime__ ) != MS::kSuccess ) 
			return TCB_Break;//break;
		liqRibTranslator::getInstancePtr()->ribEpilogue__();
		// output info when done with the rib - Alf
		cout <<"Finished RIB generation "<<currentJob___.ribFileName.asChar()<<endl;
	}
	RiEnd();

	return TCB_OK;
}