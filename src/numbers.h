
#ifndef __numbers_h__
#define __numbers_h__

#include "lispenvironment.h"
#include "yacasbase.h"

/// Create a internal number object from an ascii string.
void* AsciiToNumber(LispCharPtr aString,LispInt aPrecision);

/// Convert from internal number format to ascii format
LispStringPtr NumberToAscii(void* aNumber,LispHashTable& aHashTable,
                           LispInt aBase);

/// Whether the numeric library supports 1.0E-10 and such.
LispInt NumericSupportForMantissa();

/// Numeric library name
const LispCharPtr NumericLibraryName();

/// Copy a number class
void* NumberCopy(void* aOriginal);

/// Delete a number object.
void NumberDestroy(void* aNumber);


LispStringPtr GcdInteger(LispCharPtr int1, LispCharPtr int2,
                         LispHashTable& aHashTable);

LispStringPtr MultiplyFloat(LispCharPtr int1, LispCharPtr int2,
                            LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr AddFloat(LispCharPtr int1, LispCharPtr int2,
                       LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr PlusFloat(LispCharPtr int1,LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr SubtractFloat(LispCharPtr int1, LispCharPtr int2,
                            LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr NegateFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr DivideFloat(LispCharPtr int1, LispCharPtr int2,
                          LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr PowerFloat(LispCharPtr int1, LispCharPtr int2,
                         LispHashTable& aHashTable,LispInt aPrecision);

LispStringPtr SinFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr CosFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr TanFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr ArcSinFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr ArcCosFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr ArcTanFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr ExpFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr LnFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);

LispStringPtr SqrtFloat(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr AbsFloat( LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);

LispBoolean GreaterThan(LispCharPtr int1, LispCharPtr int2,
                       LispHashTable& aHashTable,LispInt aPrecision);
LispBoolean LessThan(LispCharPtr int1, LispCharPtr int2,
                       LispHashTable& aHashTable,LispInt aPrecision);

LispStringPtr ShiftLeft( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr ShiftRight( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,LispInt aPrecision);

LispStringPtr FromBase( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,
                        LispInt aPrecision);
LispStringPtr ToBase( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,
                      LispInt aPrecision);

LispStringPtr FloorFloat( LispCharPtr int1, LispHashTable& aHashTable,
                        LispInt aPrecision);
LispStringPtr CeilFloat( LispCharPtr int1, LispHashTable& aHashTable,
                        LispInt aPrecision);
LispStringPtr ModFloat( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,
                        LispInt aPrecision);
LispStringPtr DivFloat( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,
                        LispInt aPrecision);
LispStringPtr PiFloat( LispHashTable& aHashTable, LispInt aPrecision);

LispStringPtr BitAnd(LispCharPtr int1, LispCharPtr int2,
                     LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr BitOr(LispCharPtr int1, LispCharPtr int2,
                     LispHashTable& aHashTable,LispInt aPrecision);
LispStringPtr BitXor(LispCharPtr int1, LispCharPtr int2,
                     LispHashTable& aHashTable,LispInt aPrecision);


LispStringPtr LispFactorial(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision);



/** Base number class. It is recommended that the derived classes add the following 
 *  static method to construct a number type:
 *
 *  static YacasBigNumber* Make(LispCharPtr aString,LispInt aPrecision,LispInt aBase=10);
 *
 */
 
// reference-counting through a smart pointer, so we can do automatic clean up on numbers
class YacasBigNumber;
typedef RefPtr<YacasBigNumber> YacasBigNumberPtr;
// pure abstract class representing a number
class YacasBigNumber : public RefCountedObject
{
public: //constructors
  /// Copy a number class
  virtual const YacasBigNumber* Copy() const = 0;
  /// ToString : return string representation of number in aResult 
  virtual void ToString(LispString& aResult, LispInt aBase) = 0;
public: //base conversions
  virtual YacasBigNumber* FromBase( const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY,  LispInt aPrecision) = 0;
  virtual YacasBigNumber* ToBase( const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY,  LispInt aPrecision) = 0;
public: //information retrieval on library used  
  /// Whether the numeric library supports 1.0E-10 and such.
  virtual LispInt NumericSupportForMantissa() = 0;
  /// Numeric library name
  virtual const LispCharPtr NumericLibraryName() = 0;
  
public://arithmetic
  /// Calculate GCD of this object with another, and return result in aResult
  virtual YacasBigNumber* Gcd(YacasBigNumberPtr aX, YacasBigNumberPtr aY) = 0;
  /// Multiply two numbers, and return result in aResult
  virtual YacasBigNumber* Multiply(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  /** Multiply two numbers, and add to aResult (this is useful and generally efficient to implement).
   * This is most likely going to be used by internal functions only, using aResult as an accumulator.
   */
  virtual YacasBigNumber* MultiplyAdd(YacasBigNumber* aResult,
                const YacasBigNumberPtr& aX, 
                const YacasBigNumberPtr& aY, 
                LispInt aPrecision) = 0;
  /// Add two numbers, and return result in aResult
  virtual YacasBigNumber* Add(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  /// Negate the current number, and return it
  virtual YacasBigNumber* Negate() = 0;
  /// Divide, and return result  
  virtual YacasBigNumber* Divide(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  /// Raise power, and return result
  virtual YacasBigNumber* Power(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY,LispInt aPrecision) = 0;
public: //trigonometric functions
  virtual YacasBigNumber* Sin(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Cos(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Tan(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* ArcSin(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* ArcCos(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* ArcTan(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Exp(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Ln(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
public://other functions  
  virtual YacasBigNumber* Sqrt(const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Abs( const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Factorial(LispCharPtr int1, LispHashTable& aHashTable,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Floor(const YacasBigNumberPtr& aX, LispInt aPrecision) = 0;
  virtual YacasBigNumber* Ceil( const YacasBigNumberPtr& aX,LispInt aPrecision) = 0;
  virtual YacasBigNumber* Mod( const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  virtual YacasBigNumber* Div( const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  virtual YacasBigNumber* Pi(LispInt aPrecision) = 0;
public://comparisons  
  virtual LispBoolean GreaterThan(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  virtual LispBoolean LessThan(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;

public://bitwise operations  
  virtual YacasBigNumber* ShiftLeft( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,LispInt aPrecision) = 0;
  virtual YacasBigNumber* ShiftRight( LispCharPtr int1, LispCharPtr int2, LispHashTable& aHashTable,LispInt aPrecision) = 0;
  virtual YacasBigNumber* BitAnd(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  virtual YacasBigNumber* BitOr(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;
  virtual YacasBigNumber* BitXor(const YacasBigNumberPtr& aX, const YacasBigNumberPtr& aY, LispInt aPrecision) = 0;

protected: // I don't want any one to construct this class any other way!
  YacasBigNumber(){};


};






/*
YacasBigNumberPtr adder = MakeBigNum();
YacasBigNumberPtr result =  adder->Add(
                              MakeBigNum("23",10),
                              MakeBigNum("45.23e3",10)
                                      );
  LispString str;
  result->ToString(str,10);
  aResult.Set(LispAtom::New(iEnvironment.HashTable().Lookup(str.String())));
*/


#endif













