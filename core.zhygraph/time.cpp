#include "time.h"
namespace zhygraph {
	namespace core {
		detail::init_time engine_time::init ( engine_time::start );
		time_point engine_time::start;
	}
}