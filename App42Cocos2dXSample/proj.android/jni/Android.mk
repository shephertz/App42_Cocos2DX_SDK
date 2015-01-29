LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/ResponseScene.cpp \
                   ../../Tests/TestAvatarService.cpp \
                   ../../Tests/TestBuddyService.cpp \
                   ../../Tests/TestCustomCodeService.cpp \
                   ../../Tests/TestEmailService.cpp \
                   ../../Tests/TestGameService.cpp \
                   ../../Tests/TestHome.cpp \
                   ../../Tests/TestPushNotificationService.cpp \
                   ../../Tests/TestRewardService.cpp \
                   ../../Tests/TestScoreboardService.cpp \
                   ../../Tests/TestSessionService.cpp \
                   ../../Tests/TestSocialService.cpp \
                   ../../Tests/TestStorageService.cpp \
                   ../../Tests/TestTimerService.cpp \
                   ../../Tests/TestUploadService.cpp \
                   ../../Tests/TestUserService.cpp \
                   ../../App42/App42HTTP/App42HttpClient.cpp \
                   ../../App42/AvatarService/App42AvatarResponse.cpp \
                   ../../App42/AvatarService/AvatarService.cpp \
                   ../../App42/BuddyService/App42BuddyResponse.cpp \
                   ../../App42/BuddyService/BuddyService.cpp \
                   ../../App42/cJSON/cJSON.cpp \
                   ../../App42/Common/ACL.cpp \
                   ../../App42/Common/App42API.cpp \
                   ../../App42/Common/App42GeoPoint.cpp \
                   ../../App42/Common/App42Object.cpp \
                   ../../App42/Common/App42Response.cpp \
                   ../../App42/Common/App42Service.cpp \
                   ../../App42/Common/App42Exception.cpp \
                   ../../App42/Common/JSONDocument.cpp \
                   ../../App42/Common/MetaResponse.cpp \
                   ../../App42/Crypto/app42base64.cpp \
                   ../../App42/Crypto/HMAC_SHA1.cpp \
                   ../../App42/Crypto/SHA1.cpp \
                   ../../App42/Crypto/urlencode.cpp \
                   ../../App42/CustomCodeService/App42CustomCodeResponse.cpp \
                   ../../App42/CustomCodeService/CustomCodeService.cpp \
                   ../../App42/EmailService/App42EmailResponse.cpp \
                   ../../App42/EmailService/EmailService.cpp \
                   ../../App42/GameService/App42GameResponse.cpp \
                   ../../App42/GameService/App42RewardResponse.cpp \
                   ../../App42/GameService/App42Score.cpp \
                   ../../App42/GameService/GameService.cpp \
                   ../../App42/GameService/RewardService.cpp \
                   ../../App42/GameService/ScoreBoardService.cpp \
                   ../../App42/GameService/ScoreService.cpp \
                   ../../App42/PushNotificationService/App42PushNotificationResponse.cpp \
                   ../../App42/PushNotificationService/PushNotificationService.cpp \
                   ../../App42/SessionService/App42SessionResponse.cpp \
                   ../../App42/SessionService/SessionService.cpp \
                   ../../App42/SocialService/App42FacebookProfile.cpp \
                   ../../App42/SocialService/App42Friend.cpp \
                   ../../App42/SocialService/App42PublicProfile.cpp \
                   ../../App42/SocialService/App42Social.cpp \
                   ../../App42/SocialService/App42SocialResponse.cpp \
                   ../../App42/SocialService/SocialService.cpp \
                   ../../App42/StorageService/App42StorageResponse.cpp \
                   ../../App42/StorageService/Query.cpp \
                   ../../App42/StorageService/QueryBuilder.cpp \
                   ../../App42/StorageService/StorageService.cpp \
                   ../../App42/TimerService/App42TimerResponse.cpp \
                   ../../App42/TimerService/TimerService.cpp \
                   ../../App42/UploadService/App42UploadResponse.cpp \
                   ../../App42/UploadService/UploadService.cpp \
                   ../../App42/UserService/App42UserResponse.cpp \
                   ../../App42/UserService/UserService.cpp \
                   ../../AppWarp/appwarp.cpp \
                   ../../AppWarp/appwarp_extended.cpp \
                   ../../AppWarp/requests.cpp \
                   ../../AppWarp/socket.cpp \
                   ../../AppWarp/udpsocket.cpp \
                   ../../AppWarp/utilities.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../App42/Common \
                    $(LOCAL_PATH)/../../App42/Crypto \
                    $(LOCAL_PATH)/../../App42/cJSON \
                    $(LOCAL_PATH)/../../App42/Util \
                    $(LOCAL_PATH)/../../App42/App42HTTP \
                    $(LOCAL_PATH)/../../App42/UserService \
                    $(LOCAL_PATH)/../../App42/PushNotificationService \
                    $(LOCAL_PATH)/../../App42/TimerService \
                    $(LOCAL_PATH)/../../App42/AvatarService \
                    $(LOCAL_PATH)/../../App42/CustomCodeService \
                    $(LOCAL_PATH)/../../App42/SessionService \
                    $(LOCAL_PATH)/../../App42/UploadService \
                    $(LOCAL_PATH)/../../App42/BuddyService \
                    $(LOCAL_PATH)/../../App42/EmailService \
                    $(LOCAL_PATH)/../../App42/SocialService \
                    $(LOCAL_PATH)/../../App42/GameService \
                    $(LOCAL_PATH)/../../App42/StorageService \
                    $(LOCAL_PATH)/../../Tests \
                    $(LOCAL_PATH)/../../AppWarp
                    

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static


# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,curl/prebuilt/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
