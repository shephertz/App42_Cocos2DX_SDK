# EntityX++ Library built as static library
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := app42SDK_static
LOCAL_MODULE_FILENAME := app42SDK_static

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES :=    \
	V_1.6/App42_Cocos2dX_SDK/PushNotificationService/PushNotificationService.cpp \
	V_1.6/App42_Cocos2dX_SDK/PushNotificationService/App42PushNotificationResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/CustomCodeService/CustomCodeService.cpp \
	V_1.6/App42_Cocos2dX_SDK/CustomCodeService/App42CustomCodeResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/RewardService.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/App42GameResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/App42Score.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/App42RewardResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/ScoreBoardService.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/ScoreService.cpp \
	V_1.6/App42_Cocos2dX_SDK/GameService/GameService.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/App42Friend.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/App42Social.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/SocialService.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/App42FacebookProfile.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/App42PublicProfile.cpp \
	V_1.6/App42_Cocos2dX_SDK/SocialService/App42SocialResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/cJSON/cJSON.c \
	V_1.6/App42_Cocos2dX_SDK/Crypto/urlencode.cpp \
	V_1.6/App42_Cocos2dX_SDK/Crypto/SHA1.cpp \
	V_1.6/App42_Cocos2dX_SDK/Crypto/HMAC_SHA1.cpp \
	V_1.6/App42_Cocos2dX_SDK/Crypto/app42base64.cpp \
	V_1.6/App42_Cocos2dX_SDK/EmailService/EmailService.cpp \
	V_1.6/App42_Cocos2dX_SDK/EmailService/App42EmailResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/Exception/App42Exception.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/JSONDocument.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/App42Response.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/App42Service.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/MetaResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/App42Object.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/App42API.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/ACL.cpp \
	V_1.6/App42_Cocos2dX_SDK/Common/App42GeoPoint.cpp \
	V_1.6/App42_Cocos2dX_SDK/UserService/App42UserResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/UserService/UserService.cpp \
	V_1.6/App42_Cocos2dX_SDK/App42HTTP/App42HttpClient.cpp \
	V_1.6/App42_Cocos2dX_SDK/UploadService/UploadService.cpp \
	V_1.6/App42_Cocos2dX_SDK/UploadService/App42UploadResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/AvatarService/App42AvatarResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/AvatarService/AvatarService.cpp \
	V_1.6/App42_Cocos2dX_SDK/StorageService/StorageService.cpp \
	V_1.6/App42_Cocos2dX_SDK/StorageService/QueryBuilder.cpp \
	V_1.6/App42_Cocos2dX_SDK/StorageService/Query.cpp \
	V_1.6/App42_Cocos2dX_SDK/StorageService/App42StorageResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/SessionService/App42SessionResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/SessionService/SessionService.cpp \
	V_1.6/App42_Cocos2dX_SDK/BuddyService/App42BuddyResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/BuddyService/BuddyService.cpp \
	V_1.6/App42_Cocos2dX_SDK/TimerService/App42TimerResponse.cpp \
	V_1.6/App42_Cocos2dX_SDK/TimerService/TimerService.cpp \

LOCAL_CFLAGS += -fvisibility=hidden

LOCAL_C_INCLUDES := $(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/App42HTTP\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/BuddyService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/cJSON\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Common\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Common/Exception\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Crypto\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/CustomCodeService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/EmailService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/GameService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/SocialService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/AvatarService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/PushNotificationService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/SessionService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/StorageService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/TimerService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/UploadService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/UserService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Util

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/App42HTTP\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/BuddyService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/cJSON\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Common\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Common/Exception\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Crypto\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/CustomCodeService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/EmailService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/GameService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/SocialService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/AvatarService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/PushNotificationService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/SessionService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/StorageService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/TimerService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/UploadService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/UserService\
	$(LOCAL_PATH)/V_1.6/App42_Cocos2dX_SDK/Util

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
	
include $(BUILD_STATIC_LIBRARY)

#we need to import basic cocos for App42.
$(call import-module,.)
$(call import-module,network)
#$(call import-module,extensions)

