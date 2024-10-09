LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -fvisibility=hidden
LOCAL_MODULE    := keychain
LOCAL_SRC_FILES := \
keychain.c \
base64.c

include $(BUILD_SHARED_LIBRARY)
