/*	NSPredicate.h
	Copyright (c) 2004-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Availability.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_3_0

// Predicates wrap some combination of expressions and operators and when evaluated return a BOOL.

@interface NSPredicate : NSObject <NSCoding, NSCopying> {
    void *_reserved;
}

// Parse predicateFormat and return an appropriate predicate
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat argumentArray:(NSArray *)arguments;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat, ...;
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat arguments:(va_list)argList;

+ (NSPredicate *)predicateWithValue:(BOOL)value;    // return predicates that always evaluate to true/false

- (NSString *)predicateFormat;    // returns the format string of the predicate

- (NSPredicate *)predicateWithSubstitutionVariables:(NSDictionary *)variables;    // substitute constant values for variables

- (BOOL)evaluateWithObject:(id)object;    // evaluate a predicate against a single object

- (BOOL)evaluateWithObject:(id)object substitutionVariables:(NSDictionary *)bindings __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_3_0); // single pass evaluation substituting variables from the bindings dictionary for any variable expressions encountered

@end

@interface NSArray (NSPredicateSupport)
- (NSArray *)filteredArrayUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and return a filtered array
@end

@interface NSMutableArray (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate;    // evaluate a predicate against an array of objects and filter the mutable array directly
@end


@interface NSSet (NSPredicateSupport)
- (NSSet *)filteredSetUsingPredicate:(NSPredicate *)predicate __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_3_0);    // evaluate a predicate against a set of objects and return a filtered set
@end

@interface NSMutableSet (NSPredicateSupport)
- (void)filterUsingPredicate:(NSPredicate *)predicate __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_3_0);    // evaluate a predicate against a set of objects and filter the mutable set directly
@end

#endif
