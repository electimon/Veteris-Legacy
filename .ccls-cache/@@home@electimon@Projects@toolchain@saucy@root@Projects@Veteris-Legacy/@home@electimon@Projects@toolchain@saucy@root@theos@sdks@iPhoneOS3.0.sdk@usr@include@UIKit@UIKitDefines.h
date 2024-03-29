//
//  UIKitDefines.h
//  UIKit
//
//  Copyright 2007-2009 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define UIKIT_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define UIKIT_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define UIKIT_STATIC_INLINE	static inline
#define	UIKIT_EXTERN_CLASS	__attribute__((visibility("default")))
