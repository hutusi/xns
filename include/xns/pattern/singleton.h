
#pragma once

#define DEFINE_SINGLETON(class_name) \
	   class_name* get_instance(){  \
	   static class_name* instance_ = 0; \
	   if (!instance_) { instance_ = new class_name(); }   \
	   return instance_;                  \
	}
