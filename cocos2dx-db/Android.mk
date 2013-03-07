# macros to include all files with same extension

define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "$(2)" -and -not -name ".*") \
 )
endef

define all-cpp-files-under
$(call all-files-under,$(1),*.cpp)
endef

# module

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx-db
LOCAL_SRC_FILES := $(call all-cpp-files-under,../src)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../include/platform/android
LOCAL_EXPORT_LDLIBS := -L$(LOCAL_PATH)/libs/$(TARGET_ARCH) -lsqlite -llog
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)
LOCAL_LDLIBS := $(LOCAL_EXPORT_LDLIBS)
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
