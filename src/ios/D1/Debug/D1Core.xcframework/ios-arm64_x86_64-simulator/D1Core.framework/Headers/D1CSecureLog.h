//
//
// Copyright © 2023 THALES. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "D1CError.h"
#import <SecureLogAPI/SecureLogAPI.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SecureLog;

@class SecureLogConfig;
typedef NS_ENUM(NSInteger, SecureLogLevel);

typedef NS_ENUM(NSInteger, D1CSecureLogTag) {
    D1CSecureLogTagD1Error   = 0,
    D1CSecureLogTagRasp    = 1,
    D1CSecureLogTagD1Task  = 2,
    D1CSecureLogTagD1TPC   = 3,
    D1CSecureLogTagD1IDC   = 4
};

/**
 * Secure Logs class. Responsible with handling Secure Logs instances, writing logs for D1 and D1Core SDKs and log file management for all SDKs.
 */
__attribute__((visibility("default")))
@interface D1CSecureLog : NSObject <SecureLog>

- (instancetype)init NS_UNAVAILABLE;

/**
 * Reset shared instance. TESTING ONLY.
 */
+(void)resetSharedInstance;
/**
 * Configuration function for the Secure Logs service. Has to be called once in order to use Secure Logs. Subsequent calls do nothing.
 */
+ (void)configureSharedInstance;

/**
 * Secure Logs shared instance.
 * @return D1CSecureLog instance or NULL if configureSharedInstance has not been called before (ie. app isn't configured to use Secure Logs).
 */
+ (instancetype _Nullable)sharedInstance;

/**
 * Return the first part of a SHA 256 fingerpting of the given string, ONLY if SecureLog has been enabled. Skip otherwise.
 * @param string the string to hash.
 */
+ (NSString*)hashForLog:(NSString* _Nullable)string;

/**
 * Write a message with sensitive string hash in Secure Logs for the D1 SDK module.
 * @param messages List of messages to log. All will be logged as one entry separated with '/'
 * @param level The log level from SecureLogLevel
 * @param tag The tag for this log entry
 * @param string The string to hash. Only first part of the hash is logged. (SHA 256 as hex, first 8 bytes).
 */
+ (void)writeMessages:(NSArray<NSString*>*)messages level:(SecureLogLevel)level tag:(D1CSecureLogTag)tag sensitiveString:(NSString* _Nullable)string;

/**
 * Write a message in Secure Logs for the given module.
 * @param message The log message
 * @param moduleID A unique ID of the module that write log.
 * @param level The log level from SecureLogLevel
 * @param tag The tag for this log entry
 */
- (void)writeMessage:(NSString *)message moduleID:(NSString *)moduleID level:(SecureLogLevel)level tag:(D1CSecureLogTag)tag;

/**
 * Get the Secure Logs configuration object to use within other SDK.
 * @return SecureLogConfig object use to initialize the Secure Logs object.
 */
- (SecureLogConfig*) getConfiguration;

/**
 * Set the secure log level to write in log file.
 * @param level log level.
*/
- (void)setLevel:(SecureLogLevel)level;

/**
 * Return array of log files that logged by secure log.
 * @return array of log files.
*/
- (NSArray<NSURL *> *)files;

/**
 * Delete all logs that logged by secure log.
 *
*/
- (void)deleteFiles;

/**
 * Add secure log instance. This method intends to add an external secure log instance
 * (eg: from other SDK) to the global secure log client.
 *
 * @param secureLog The secure log instance to add.
 * @param moduleID  A unique ID to identify the secure log instance.
 *
 */
- (void)addSecureLogModule:(id<SecureLog>)secureLog moduleID:(NSString*)moduleID;

@end

NS_ASSUME_NONNULL_END

