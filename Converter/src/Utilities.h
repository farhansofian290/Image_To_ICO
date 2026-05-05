#pragma once

#ifdef CONVERTER_DEBUG==2
	#define CONVERTER_ERROR(msg) std::cout<<msg<<std::endl;
	#define CONVERTER_LOG(msg) std::cout<<msg<<std::endl;
#elif CONVERTER_DEBUG==1
	#define CONVERTER_ERROR(msg) std::cout<<msg<<std::endl;
	#define CONVERTER_LOG(msg)
#else
	#define CONVERTER_ERROR(msg)
	#define CONVERTER_LOG(msg)
#endif

