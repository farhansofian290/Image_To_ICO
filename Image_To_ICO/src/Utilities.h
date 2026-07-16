#pragma once

#ifdef ICO_DEBUG==2
#define ICO_ERROR(msg) std::cout<<msg<<std::endl;
#define ICO_LOG(msg) std::cout<<msg<<std::endl;
#elif ICO_DEBUG==1
#define ICO_ERROR(msg) std::cout<<msg<<std::endl;
#define ICO_LOG(msg)
#else
#define ICO_ERROR(msg)
#define ICO_LOG(msg)
#endif

