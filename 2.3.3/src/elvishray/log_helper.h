

#define _s( _log_ )															\
	assert(elvishray::Renderer::m_log.get().is_open());						\
	elvishray::Renderer::m_log.get()<< _log_ <<std::endl;

#define _d( _log_or_call_ )													\
	assert(elvishray::Renderer::m_log.get().is_open());						\
	elvishray::Renderer::m_log.get()<< #_log_or_call_ <<";"<<std::endl;		\
	_log_or_call_ ;

#define _t( _log_or_call_ )													\
	if(0) {																	\
		assert(elvishray::Renderer::m_log.get().is_open());					\
		elvishray::Renderer::m_log.get()<< _log_or_call_ <<std::endl;		\
	} else  {																\
		assert(elvishray::Renderer::m_log.get().is_open());					\
		elvishray::Renderer::m_log.get()<< #_log_or_call_ <<";"<<std::endl;	\
		_log_or_call_ ;														\
	}

// #define _S(_call_)  \
// 	Renderer::m_log.get()<<#_call_<<std::endl; my_##_call_ ; 
#define _S(_call_)  my_##_call_ ; 