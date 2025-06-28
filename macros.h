//
//  Macors.h
//  SpooferPro
//
//  Created by Malhar Ambekar on 6/23/25.
//

#ifndef Macors_h
#define Macors_h

#ifdef __OBJC__

#define APP_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]
#define TIME_STAMP [NSString stringWithFormat:@"%f",[[NSDate date] timeIntervalSince1970]]
#define NSSTRING_FROM_BOOL(b) (b ? @"YES" : @"NO")
#define IS_STRING_EMPTY(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

#define SCREEN_WIDTH   [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT  [UIScreen mainScreen].bounds.size.height
#define IS_IPHONE ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPhone)
#define IS_IPAD ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad)
#define DEVICE_NAME [[UIDevice currentDevice] name]
#define DEVICE_MODEL [[UIDevice currentDevice] model]
#define DEVICE_LMODEL [[UIDevice currentDevice] localizedModel]
#define DEVICE_SYSNAME [[UIDevice currentDevice] systemName]
#define DEVICE_SYSVER [[UIDevice currentDevice] systemVersion]
#define VENDOR_ID [[[UIDevice currentDevice] identifierForVendor] UUIDString]
#define ADVERT_ID [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString]

#define DOCUMENTS_PATH [NSHomeDirectory() stringByAppendingString:@"/Documents/"]
#define TEMPORARY_PATH NSTemporaryDirectory()
#define APPSUPPORT_PATH [(NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES)) lastObject]

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

#define PURPLE_COLOR [UIColor colorWithHue:0.74 saturation:0.90 brightness:0.80 alpha:1.00]
#define IS_DARK_MODE \
    ([[UIViewController topMostController].traitCollection userInterfaceStyle] == UIUserInterfaceStyleDark)
#define THEMECOLOR \
    (IS_DARK_MODE ? [UIColor systemOrangeColor] : PURPLE_COLOR)

#ifdef PRIVATE
    #define LOG_ERROR(x,...) NSLog(@"[ERROR]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define LOG_WARNING(x,...) NSLog(@"[WARNING]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define LOG_INFO(x,...) NSLog(@"[INFO]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define LOG_DEBUG(x,...) NSLog(@"[DEBUG]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define LOG_VERBOSE(x,...) NSLog(@"[VERBOSE]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define LOG_TRACE(x,...) NSLog(@"[TRACE]: %@ - [%s]",[NSString stringWithFormat:(x), ##__VA_ARGS__], __PRETTY_FUNCTION__)
    #define NSLog if(1) NSLog

    // Example usage:
    //- (void)exampleFunction {
    //    TRACE_THIS_BLOCK("exampleFunction", ^{
    //        // Your function code here
    //    });
    //}

    //return TRACE_RET_BLOCK(__PRETTY_FUNCTION__, ^{
    //
    //});

    //TRACE_VOID_BLOCK(__PRETTY_FUNCTION__, ^{
    //
    //});

    #define TRACE_RET_BLOCK(blockName, block) ({ \
    LOG_TRACE(@"Starting %s", blockName); \
    CFAbsoluteTime start = CFAbsoluteTimeGetCurrent(); \
    __typeof__(block()) result = block(); \
    CFAbsoluteTime end = CFAbsoluteTimeGetCurrent(); \
    LOG_TRACE(@"Finished %s", blockName); \
    LOG_TRACE(@"Time taken by %s: %f seconds", blockName, end - start); \
    result; \
    })

    #define TRACE_VOID_BLOCK(blockName, block) { \
    LOG_TRACE(@"Starting %s", blockName); \
    CFAbsoluteTime start = CFAbsoluteTimeGetCurrent(); \
    block(); \
    CFAbsoluteTime end = CFAbsoluteTimeGetCurrent(); \
    LOG_TRACE(@"Finished %s", blockName); \
    LOG_TRACE(@"Time taken by %s: %f seconds", blockName, end - start); \
    }
#else
    #define LOG_ERROR(x,...)
    #define LOG_WARNING(x,...)
    #define LOG_INFO(x,...)
    #define LOG_DEBUG(x,...)
    #define LOG_VERBOSE(x,...)
    #define LOG_TRACE(x,...)
    #define LOG_PROTO(x,...)
    #define NSLog if(0) NSLog

    #define TRACE_RET_BLOCK(blockName, block) block()

    #define TRACE_VOID_BLOCK(blockName, block) block()
#endif

#define SWIZZLE_METHOD(isClassMethod, origClass, origSel, swizzledClass, swizzledSel, originalImpVar) \
do { \
    Class targetClass = (isClassMethod ? object_getClass(origClass) : origClass); \
    Method origMethod = class_getInstanceMethod(targetClass, origSel); \
    Method swizzledMethod = class_getInstanceMethod(swizzledClass, swizzledSel); \
    if (origMethod && swizzledMethod) { \
        originalImpVar = (void *)method_getImplementation(origMethod); \
        method_exchangeImplementations(origMethod, swizzledMethod); \
        LOG_INFO(@"Swizzle Success: %@[%@ %@] -> [%@ %@]", \
            isClassMethod ? @"+" : @"-", \
            NSStringFromClass(targetClass), \
            NSStringFromSelector(origSel), \
            NSStringFromClass(swizzledClass), \
            NSStringFromSelector(swizzledSel)); \
    } else { \
        LOG_ERROR(@"Swizzle Failed: %@[%@ %@] or [%@ %@] not found", \
            isClassMethod ? @"+" : @"-", \
            NSStringFromClass(targetClass), \
            NSStringFromSelector(origSel), \
            NSStringFromClass(swizzledClass), \
            NSStringFromSelector(swizzledSel)); \
    } \
} while (0)


#endif /* __OBJC__ */

#endif /* Macors_h */
