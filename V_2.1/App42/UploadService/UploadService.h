//
//  UploadService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__UploadService__
#define __App42Cocos2dX3_0Sample__UploadService__

#include <iostream>
#include "App42Service.h"

using namespace std;

typedef enum FileType
{
    AUDIO,
    VIDEO,
    IMAGE,
    BINARY,
    TXT,
    XML,
    CSV,
    JSON,
    OTHER
}FileType;

class UploadService : public App42Service
{
    
private:
    UploadService();
	static UploadService* _instance;
    
    inline const char *getUploadFileType(FileType fileType)
    {
        const char *strings[] = {"AUDIO","VIDEO","IMAGE","BINARY","TXT","XML","CSV","JSON","OTHER"};
        
        return strings[fileType];
    }
    
    string BuildGrantAccessBody(string json);
    
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
    static UploadService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static UploadService* getInstance();
    
    void UploadFile(const char *fileName, const char * filePath,FileType fileType, const char * description,const app42CallBack& pSelector);
    
    void UploadFile(const char * fileName, unsigned char* fileData,int fileDataSize,FileType fileType, const char * description,const app42CallBack& pSelector);
    
    void UploadFileForUser(const char * fileName, const char * userName, const char * filePath,FileType fileType, const char * description,const app42CallBack& pSelector);
    
    void UploadFileForUser(const char * fileName, const char * userName, unsigned char* fileData,int fileDataSize,FileType fileType, const char * description,const app42CallBack& pSelector);
    
    void GetAllFiles(const app42CallBack& pSelector);
    
    void GetAllFilesCount(const app42CallBack& pSelector);
    
    void GetAllFiles(int max, int offset, const app42CallBack& pSelector);
    
    void GetFileByUser(const char * fileName, const char * userName, const app42CallBack& pSelector);

    void GetAllFilesByUser(const char * userName, const app42CallBack& pSelector);
    
    void GetAllFilesByUser(const char * userName, int max, int offset, const app42CallBack& pSelector);
    
    void GetAllFilesCountByUser(const char * userName,const app42CallBack& pSelector);
    
    void GetFileByName(const char * fileName,const app42CallBack& pSelector);
    
    void RemoveFileByUser(const char * fileName, const char * userName, const app42CallBack& pSelector);
    
    void RemoveAllFilesByUser(const char * userName, const app42CallBack& pSelector);
    
    void RemoveFileByName(const char * fileName,const app42CallBack& pSelector);

    void RemoveAllFiles(const app42CallBack& pSelector);

    void GetFilesCountByType(FileType fileType,const app42CallBack& pSelector);
    
    void GetFilesByType(FileType fileType,const app42CallBack& pSelector);
    
    void GetFilesByType(FileType fileType, int max, int offset,const app42CallBack& pSelector);
    
    /**
	 *
	 * @param fileName
	 * @param userName
	 * @param App42ACLList
	 * @return void
	 * @throws App42Exception
	 */
	void GrantAccess(const char* fileName, const char* userName,
                    vector<App42ACL> App42ACLList, const app42CallBack& pSelector);
    
    /**
	 *
	 * @param fileName
	 * @param userName
	 * @param App42ACLList
	 * @return void
	 * @throws App42Exception
	 */
	void RevokeAccess(const char* fileName, const char* userName,
                      vector<App42ACL> App42ACLList, const app42CallBack& pSelector);
};

#endif /* defined(__App42Cocos2dX3_0Sample__UploadService__) */
