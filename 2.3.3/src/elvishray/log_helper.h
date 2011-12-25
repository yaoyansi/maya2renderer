

#define _s( _log_ ) dummy.get()<< _log_ <<std::endl;

#define _t( _log_or_call_ )  \
	if(0) dummy.get()<< _log_or_call_ <<std::endl; \
	else  dummy.get()<< #_log_or_call_ <<";"<<std::endl; _log_or_call_ ; 

// #define _S(_call_)  \
// 	dummy.get()<<#_call_<<std::endl; my_##_call_ ; 
#define _S(_call_)  my_##_call_ ; 