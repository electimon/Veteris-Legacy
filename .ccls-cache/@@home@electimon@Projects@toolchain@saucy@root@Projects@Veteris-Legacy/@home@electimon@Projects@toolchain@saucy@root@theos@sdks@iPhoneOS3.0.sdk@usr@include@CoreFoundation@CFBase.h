/*	CFBase.h
	Copyright (c) 1998-2007, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBASE__)
#define __COREFOUNDATION_CFBASE__ 1

#if (defined(__CYGWIN32__) || defined(_WIN32)) && !defined(__WIN32__)
#define __WIN32__ 1
#endif

#if defined(_MSC_VER) && defined(_M_IX86)
#define __i386__ 1
#endif

#if (defined(__i386__) || defined(__x86_64__)) && !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__ 1
#endif

#if !defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)
#error Do not know the endianess of this architecture
#endif

#if !__BIG_ENDIAN__ && !__LITTLE_ENDIAN__
#error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be false
#endif

#if __BIG_ENDIAN__ && __LITTLE_ENDIAN__
#error Both __BIG_ENDIAN__ and __LITTLE_ENDIAN__ cannot be true
#endif

#if TARGET_OS_WIN32
#include <windows.h>
#include <winsock2.h>
#include <stdint.h>
#include <stdbool.h>
#elif defined(__GNUC__)
#include <stdint.h>
#include <stdbool.h>
#endif
#include <AvailabilityMacros.h>
#include <TargetConditionals.h>

#ifndef CF_OPEN_SOURCE
#if defined(__CF_USE_FRAMEWORK_INCLUDES__) || (((TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) && !defined(__MWERKS__)) 
#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#include <MacTypes.h>
#else
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#endif
#elif defined(__MWERKS__)
#include <MacTypes.h>
#endif
#else // CF_OPEN_SOURCE
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#include <libkern/OSTypes.h>
#endif
#endif // CF_OPEN_SOURCE

#if !defined(__MACTYPES__)
#if !defined(_OS_OSTYPES_H)
    typedef unsigned char           Boolean;
    typedef unsigned char           UInt8;
    typedef signed char             SInt8;
    typedef unsigned short          UInt16;
    typedef signed short            SInt16;
    typedef unsigned int            UInt32;
    typedef signed int              SInt32;
    typedef uint64_t		    UInt64;
    typedef int64_t		    SInt64;
    typedef SInt32                  OSStatus;
#endif
    typedef float                   Float32;
    typedef double                  Float64;
    typedef unsigned short          UniChar;
    typedef unsigned long           UniCharCount;
    typedef unsigned char *         StringPtr;
    typedef const unsigned char *   ConstStringPtr;
    typedef unsigned char           Str255[256];
    typedef const unsigned char *   ConstStr255Param;
    typedef SInt16                  OSErr;
    typedef SInt16                  RegionCode;
    typedef SInt16                  LangCode;
    typedef SInt16                  ScriptCode;
    typedef UInt32                  FourCharCode;
    typedef FourCharCode            OSType;
#endif
#if !defined(__MACTYPES__) || (defined(UNIVERSAL_INTERFACES_VERSION) && UNIVERSAL_INTERFACES_VERSION < 0x0340)
    typedef UInt32                  UTF32Char;
    typedef UInt16                  UTF16Char;
    typedef UInt8                   UTF8Char;
#endif

#if !defined(CF_EXTERN_C_BEGIN)
#if defined(__cplusplus)
#define CF_EXTERN_C_BEGIN extern "C" {
#define CF_EXTERN_C_END   }
#else
#define CF_EXTERN_C_BEGIN
#define CF_EXTERN_C_END
#endif
#endif

CF_EXTERN_C_BEGIN

#if !defined(NULL)
#if defined(__GNUG__)
    #define NULL __null
#elif defined(__cplusplus)
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif
#endif

#if !defined(TRUE)
    #define TRUE	1
#endif

#if !defined(FALSE)
    #define FALSE	0
#endif

#if TARGET_OS_WIN32
    #undef CF_EXPORT
    #if defined(CF_BUILDING_CF)
	#define CF_EXPORT __declspec(dllexport) extern
    #else
	#define CF_EXPORT __declspec(dllimport) extern
    #endif
#elif defined(macintosh)
    #if defined(__MWERKS__)
        #define CF_EXPORT __declspec(export) extern
    #endif
#endif

#if !defined(CF_EXPORT)
    #define CF_EXPORT extern
#endif

#if !defined(CF_INLINE)
    #if defined(__GNUC__) && (__GNUC__ == 4) && !defined(DEBUG)
        #define CF_INLINE static __inline__ __attribute__((always_inline))
    #elif defined(__GNUC__)
        #define CF_INLINE static __inline__
    #elif defined(__MWERKS__) || defined(__cplusplus)
	#define CF_INLINE static inline
    #elif defined(_MSC_VER)
        #define CF_INLINE static __inline
    #elif TARGET_OS_WIN32
	#define CF_INLINE static __inline__
    #endif
#endif


CF_EXPORT double kCFCoreFoundationVersionNumber;

#if TARGET_OS_MAC
#define kCFCoreFoundationVersionNumber10_0	196.40
#define kCFCoreFoundationVersionNumber10_0_3	196.50
#define kCFCoreFoundationVersionNumber10_1	226.00
#define kCFCoreFoundationVersionNumber10_1_1	226.00
/* Note the next three do not follow the usual numbering policy from the base release */
#define kCFCoreFoundationVersionNumber10_1_2	227.20
#define kCFCoreFoundationVersionNumber10_1_3	227.20
#define kCFCoreFoundationVersionNumber10_1_4	227.30
#define kCFCoreFoundationVersionNumber10_2	263.00
#define kCFCoreFoundationVersionNumber10_2_1	263.10
#define kCFCoreFoundationVersionNumber10_2_2	263.10
#define kCFCoreFoundationVersionNumber10_2_3	263.30
#define kCFCoreFoundationVersionNumber10_2_4	263.30
#define kCFCoreFoundationVersionNumber10_2_5	263.50
#define kCFCoreFoundationVersionNumber10_2_6	263.50
#define kCFCoreFoundationVersionNumber10_2_7	263.50
#define kCFCoreFoundationVersionNumber10_2_8	263.50
#define kCFCoreFoundationVersionNumber10_3	299.00
#define kCFCoreFoundationVersionNumber10_3_1	299.00
#define kCFCoreFoundationVersionNumber10_3_2	299.00
#define kCFCoreFoundationVersionNumber10_3_3	299.30
#define kCFCoreFoundationVersionNumber10_3_4	299.31
#define kCFCoreFoundationVersionNumber10_3_5	299.31
#define kCFCoreFoundationVersionNumber10_3_6	299.32
#define kCFCoreFoundationVersionNumber10_3_7	299.33
#define kCFCoreFoundationVersionNumber10_3_8	299.33
#define kCFCoreFoundationVersionNumber10_3_9	299.35
#define kCFCoreFoundationVersionNumber10_4	368.00
#define kCFCoreFoundationVersionNumber10_4_1	368.10
#define kCFCoreFoundationVersionNumber10_4_2	368.11
#define kCFCoreFoundationVersionNumber10_4_3	368.18
#define kCFCoreFoundationVersionNumber10_4_4_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_4_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_5_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_5_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_6_Intel	368.26
#define kCFCoreFoundationVersionNumber10_4_6_PowerPC	368.25
#define kCFCoreFoundationVersionNumber10_4_7	368.27
#define kCFCoreFoundationVersionNumber10_4_8	368.27
#define kCFCoreFoundationVersionNumber10_4_9	368.28
#define kCFCoreFoundationVersionNumber10_4_10	368.28
#define kCFCoreFoundationVersionNumber10_4_11	368.31
#define kCFCoreFoundationVersionNumber10_5	476.00
#define kCFCoreFoundationVersionNumber10_5_1	476.00
#define kCFCoreFoundationVersionNumber10_5_2	476.10
#define kCFCoreFoundationVersionNumber10_5_3	476.13
#define kCFCoreFoundationVersionNumber10_5_4	476.14
#endif

#if TARGET_OS_IPHONE
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_0	478.23
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_1     478.26
#define kCFCoreFoundationVersionNumber_iPhoneOS_2_2     478.29
#endif

typedef unsigned long CFTypeID;
typedef unsigned long CFOptionFlags;
typedef unsigned long CFHashCode;
typedef signed long CFIndex;

/* Base "type" of all "CF objects", and polymorphic functions on them */
typedef const void * CFTypeRef;

typedef const struct __CFString * CFStringRef;
typedef struct __CFString * CFMutableStringRef;

/*
        Type to mean any instance of a property list type;
        currently, CFString, CFData, CFNumber, CFBoolean, CFDate,
        CFArray, and CFDictionary.
*/
typedef CFTypeRef CFPropertyListRef;

/* Values returned from comparison functions */
enum {
    kCFCompareLessThan = -1,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1
};
typedef CFIndex CFComparisonResult;

/* A standard comparison function */
typedef CFComparisonResult (*CFComparatorFunction)(const void *val1, const void *val2, void *context);

/* Constant used by some functions to indicate failed searches. */
/* This is of type CFIndex. */
enum {
    kCFNotFound = -1
};


/* Range type */
typedef struct {
    CFIndex location;
    CFIndex length;
} CFRange;

#if defined(CF_INLINE)
CF_INLINE CFRange CFRangeMake(CFIndex loc, CFIndex len) {
    CFRange range;
    range.location = loc;
    range.length = len;
    return range;
}
#else
#define CFRangeMake(LOC, LEN) __CFRangeMake(LOC, LEN)
#endif

/* Private; do not use */
CF_EXPORT
CFRange __CFRangeMake(CFIndex loc, CFIndex len);


#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
/* Null representant */

typedef const struct __CFNull * CFNullRef;

CF_EXPORT
CFTypeID CFNullGetTypeID(void);

CF_EXPORT
const CFNullRef kCFNull;	// the singleton null instance

#endif


/* Allocator API

   Most of the time when specifying an allocator to Create functions, the NULL
   argument indicates "use the default"; this is the same as using kCFAllocatorDefault
   or the return value from CFAllocatorGetDefault().  This assures that you will use
   the allocator in effect at that time.

   You should rarely use kCFAllocatorSystemDefault, the default default allocator.
*/
typedef const struct __CFAllocator * CFAllocatorRef;

/* This is a synonym for NULL, if you'd rather use a named constant. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorDefault;

/* Default system allocator; you rarely need to use this. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorSystemDefault;

/* This allocator uses malloc(), realloc(), and free(). This should not be
   generally used; stick to kCFAllocatorDefault whenever possible. This
   allocator is useful as the "bytesDeallocator" in CFData or
   "contentsDeallocator" in CFString where the memory was obtained as a
   result of malloc() type functions.
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorMalloc;

/* This allocator explicitly uses the default malloc zone, returned by
   malloc_default_zone(). It should only be used when an object is
   safe to be allocated in non-scanned memory.
 */
CF_EXPORT
const CFAllocatorRef kCFAllocatorMallocZone AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Null allocator which does nothing and allocates no memory. This allocator
   is useful as the "bytesDeallocator" in CFData or "contentsDeallocator"
   in CFString where the memory should not be freed. 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorNull;

/* Special allocator argument to CFAllocatorCreate() which means
   "use the functions given in the context to allocate the allocator
   itself as well". 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorUseContext;

typedef const void *	(*CFAllocatorRetainCallBack)(const void *info);
typedef void		(*CFAllocatorReleaseCallBack)(const void *info);
typedef CFStringRef	(*CFAllocatorCopyDescriptionCallBack)(const void *info);
typedef void *		(*CFAllocatorAllocateCallBack)(CFIndex allocSize, CFOptionFlags hint, void *info);
typedef void *		(*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize, CFOptionFlags hint, void *info);
typedef void		(*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef CFIndex		(*CFAllocatorPreferredSizeCallBack)(CFIndex size, CFOptionFlags hint, void *info);
typedef struct {
    CFIndex				version;
    void *				info;
    CFAllocatorRetainCallBack		retain;
    CFAllocatorReleaseCallBack		release;        
    CFAllocatorCopyDescriptionCallBack	copyDescription;
    CFAllocatorAllocateCallBack		allocate;
    CFAllocatorReallocateCallBack	reallocate;
    CFAllocatorDeallocateCallBack	deallocate;
    CFAllocatorPreferredSizeCallBack	preferredSize;
} CFAllocatorContext;

CF_EXPORT
CFTypeID	CFAllocatorGetTypeID(void);

/*
	CFAllocatorSetDefault() sets the allocator that is used in the current
	thread whenever NULL is specified as an allocator argument. This means
	that most, if not all allocations will go through this allocator. It
	also means that any allocator set as the default needs to be ready to
	deal with arbitrary memory allocation requests; in addition, the size
	and number of requests will change between releases.

	An allocator set as the default will never be released, even if later
	another allocator replaces it as the default. Not only is it impractical
	for it to be released (as there might be caches created under the covers
	that refer to the allocator), in general it's also safer and more
	efficient to keep it around.

	If you wish to use a custom allocator in a context, it's best to provide
	it as the argument to the various creation functions rather than setting
	it as the default. Setting the default allocator is not encouraged.

	If you do set an allocator as the default, either do it for all time in
	your app, or do it in a nested fashion (by restoring the previous allocator
	when you exit your context). The latter might be appropriate for plug-ins
	or libraries that wish to set the default allocator.
*/
CF_EXPORT
void CFAllocatorSetDefault(CFAllocatorRef allocator);

CF_EXPORT
CFAllocatorRef CFAllocatorGetDefault(void);

CF_EXPORT
CFAllocatorRef CFAllocatorCreate(CFAllocatorRef allocator, CFAllocatorContext *context);

CF_EXPORT
void *CFAllocatorAllocate(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void *CFAllocatorReallocate(CFAllocatorRef allocator, void *ptr, CFIndex newsize, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorDeallocate(CFAllocatorRef allocator, void *ptr);

CF_EXPORT
CFIndex CFAllocatorGetPreferredSizeForSize(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorGetContext(CFAllocatorRef allocator, CFAllocatorContext *context);


/* Polymorphic CF functions */

CF_EXPORT
CFTypeID CFGetTypeID(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyTypeIDDescription(CFTypeID type_id);

CF_EXPORT
CFTypeRef CFRetain(CFTypeRef cf);

CF_EXPORT
void CFRelease(CFTypeRef cf);

CF_EXPORT
CFIndex CFGetRetainCount(CFTypeRef cf);

CF_EXPORT
CFTypeRef CFMakeCollectable(CFTypeRef cf) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFEqual(CFTypeRef cf1, CFTypeRef cf2);

CF_EXPORT
CFHashCode CFHash(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyDescription(CFTypeRef cf);

CF_EXPORT
CFAllocatorRef CFGetAllocator(CFTypeRef cf);

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFBASE__ */

