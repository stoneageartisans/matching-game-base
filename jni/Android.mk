LOCAL_PATH            := $(call my-dir)/..
IRRLICHT_PROJECT_PATH := $(LOCAL_PATH)
STUFF_DRIVE           := $(IRRLICHT_PROJECT_PATH)/../../../../../..
IRRLICHT_LIB_PATH     := $(STUFF_DRIVE)/libraries/irrlicht-ogl-es/source/Irrlicht/Android/obj/local
CRICKET_LIB_PATH      := $(STUFF_DRIVE)/libraries/cricket-1.6.5/lib/android/ndk
#PROJECT_SRC_PATH      := $(STUFF_DRIVE)/projects/irrlicht/matching-game-base
PROJECT_SRC_PATH      := $(STUFF_DRIVE)/projects/irrlicht/matching-game-base/src
PROJECT_ASSETS_PATH   := $(STUFF_DRIVE)/projects/irrlicht/matching-game-base/assets

include $(CLEAR_VARS)
LOCAL_MODULE := Irrlicht
LOCAL_SRC_FILES := $(IRRLICHT_LIB_PATH)/$(TARGET_ARCH_ABI)/libIrrlicht.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ck
LOCAL_SRC_FILES := $(CRICKET_LIB_PATH)/$(TARGET_ARCH_ABI)/release/libck.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := MatchingGameBase

LOCAL_CFLAGS := -pipe -fno-exceptions -fno-rtti -fstrict-aliasing

ifndef NDEBUG
LOCAL_CFLAGS += -g -D_DEBUG
else
LOCAL_CFLAGS += -fexpensive-optimizations -O3
endif

ifeq ($(TARGET_ARCH_ABI),x86)
LOCAL_CFLAGS += -fno-stack-protector
endif

LOCAL_C_INCLUDES := $(STUFF_DRIVE)/libraries/irrlicht-ogl-es/include
LOCAL_C_INCLUDES += $(STUFF_DRIVE)/libraries/cricket-1.6.5/inc

LOCAL_SRC_FILES := $(PROJECT_SRC_PATH)/Tile.cpp
LOCAL_SRC_FILES += $(PROJECT_SRC_PATH)/Sound.cpp
LOCAL_SRC_FILES += $(PROJECT_SRC_PATH)/Application.cpp
LOCAL_SRC_FILES += $(PROJECT_SRC_PATH)/main.cpp
LOCAL_SRC_FILES += $(PROJECT_SRC_PATH)/android_tools.cpp

LOCAL_LDLIBS := -lEGL -llog -lGLESv1_CM -lGLESv2 -lz -landroid

LOCAL_STATIC_LIBRARIES := Irrlicht android_native_app_glue ck cpufeatures

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,android/cpufeatures)

# Copy Irrlicht data to assets

$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/assets)
$(shell mkdir -p $(IRRLICHT_PROJECT_PATH)/src)
$(shell cp $(PROJECT_ASSETS_PATH)/images/*.* $(IRRLICHT_PROJECT_PATH)/assets/)
$(shell cp $(PROJECT_ASSETS_PATH)/meshes/*.* $(IRRLICHT_PROJECT_PATH)/assets/)
$(shell cp $(PROJECT_ASSETS_PATH)/sounds/*.* $(IRRLICHT_PROJECT_PATH)/assets/)
