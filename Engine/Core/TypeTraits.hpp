namespace Azgard {
  template<typename T>
    struct removeConst
    { typedef T     type; };

  template<typename T>
    struct removeConst<T const>
    { typedef T     type; };

  /// removeVolatile
  template<typename T>
    struct removeVolatile
    { typedef T     type; };

  template<typename T>
    struct removeVolatile<T volatile>
    { typedef T     type; };

  /// removeCv
  template<typename T>
    struct removeCv
    {
      typedef typename
      removeConst<typename removeVolatile<T>::type>::type     type;
    };
  
  /// integralConstant
  template<typename T, T v>
    struct integralConstant
    {
      static constexpr T                  value = v;
      typedef T                           valuetype;
      typedef integralConstant<T, v>   type;
      constexpr operator valuetype() const noexcept { return value; }
    };

  template<typename T, T v>
    constexpr T integralConstant<T, v>::value;

  /// The type used as a compile-time boolean with true value.
  typedef integralConstant<bool, true>     trueType;

  /// The type used as a compile-time boolean with false value.
  typedef integralConstant<bool, false>    falseType;

  template<bool v>
    using boolConstant = integralConstant<bool, v>;


  // Meta programming helper types.

  template<bool, typename, typename>
    struct conditional;

  template<typename...>
    struct Or;

  template<>
    struct Or<>
    : public falseType
    { };

  template<typename B1>
    struct Or<B1>
    : public B1
    { };

  template<typename B1, typename B2>
    struct Or<B1, B2>
    : public conditional<B1::value, B1, B2>::type
    { };

  template<typename B1, typename B2, typename B3, typename... Bn>
    struct Or<B1, B2, B3, Bn...>
    : public conditional<B1::value, B1, Or<B2, B3, Bn...>>::type
    { };

  template<typename...>
    struct And;

  template<>
    struct And<>
    : public trueType
    { };

  template<typename B1>
    struct And<B1>
    : public B1
    { };

  template<typename B1, typename B2>
    struct And<B1, B2>
    : public conditional<B1::value, B2, B1>::type
    { };

  template<typename B1, typename B2, typename B3, typename... Bn>
    struct And<B1, B2, B3, Bn...>
    : public conditional<B1::value, And<B2, B3, Bn...>, B1>::type
    { };

  template<typename T>
    struct Not
    : public boolConstant<!bool(T::value)>
    { };


  // Primary type categories.
  template<typename>
    struct removeCv;

  template<typename>
    struct isVoidHelper
    : public falseType { };

  template<>
    struct isVoidHelper<void>
    : public trueType { };

  /// isVoid
  template<typename T>
    struct isVoid
    : public isVoidHelper<typename removeCv<T>::type>::type
    { };

  template<typename>
    struct isIntegerHelper
    : public falseType { };

  template<>
    struct isIntegerHelper<bool>
    : public trueType { };

  template<>
    struct isIntegerHelper<char>
    : public trueType { };

  template<>
    struct isIntegerHelper<signed char>
    : public trueType { };

  template<>
    struct isIntegerHelper<unsigned char>
    : public trueType { };
  template<>
    struct isIntegerHelper<char16_t>
    : public trueType { };

  template<>
    struct isIntegerHelper<char32_t>
    : public trueType { };

  template<>
    struct isIntegerHelper<short>
    : public trueType { };

  template<>
    struct isIntegerHelper<unsigned short>
    : public trueType { };

  template<>
    struct isIntegerHelper<int>
    : public trueType { };

  template<>
    struct isIntegerHelper<unsigned int>
    : public trueType { };

  template<>
    struct isIntegerHelper<long>
    : public trueType { };

  template<>
    struct isIntegerHelper<unsigned long>
    : public trueType { };

  template<>
    struct isIntegerHelper<long long>
    : public trueType { };

  template<>
    struct isIntegerHelper<unsigned long long>
    : public trueType { };


  /// isInteger
  template<typename T>
    struct isInteger
    : public isIntegerHelper<typename removeCv<T>::type>::type
    { };

  template<typename>
    struct isFloatingPointHelper
    : public falseType { };

  template<>
    struct isFloatingPointHelper<float>
    : public trueType { };

  template<>
    struct isFloatingPointHelper<double>
    : public trueType { };

  template<>
    struct isFloatingPointHelper<long double>
    : public trueType { };


  /// isFloatingPoint
  template<typename T>
    struct isFloatingPoint
    : public isFloatingPointHelper<typename removeCv<T>::type>::type
    { };

  /// isArray
  template<typename>
    struct isArray
    : public falseType { };

  template<typename T, unsigned long Size>
    struct isArray<T[Size]>
    : public trueType { };

  template<typename T>
    struct isArray<T[]>
    : public trueType { };

  template<typename>
    struct isPointerHelper
    : public falseType { };

  template<typename T>
    struct isPointerHelper<T*>
    : public trueType { };

  /// isPointer
  template<typename T>
    struct isPointer
    : public isPointerHelper<typename removeCv<T>::type>::type
    { };

  /// isLvalueReference
  template<typename>
    struct isLvalueReference
    : public falseType { };

  template<typename T>
    struct isLvalueReference<T&>
    : public trueType { };

  /// isRvalueReference
  template<typename>
    struct isRvalueReference
    : public falseType { };

  template<typename T>
    struct isRvalueReference<T&&>
    : public trueType { };

  template<typename>
    struct isFunction;

  template<typename>
    struct isMember0bjectPointerHelper
    : public falseType { };

  template<typename T, typename Cp>
    struct isMember0bjectPointerHelper<T Cp::*>
    : public Not<isFunction<T>>::type { };

  /// isMember0bjectPointer
  template<typename T>
    struct isMember0bjectPointer
    : public isMember0bjectPointerHelper<
				typename removeCv<T>::type>::type
    { };

  template<typename>
    struct isMemberFunctionPointerHelper
    : public falseType { };

  template<typename T, typename Cp>
    struct isMemberFunctionPointerHelper<T Cp::*>
    : public isFunction<T>::type { };

  /// isMemberFunctionPointer
  template<typename T>
    struct isMemberFunctionPointer
    : public isMemberFunctionPointerHelper<
				typename removeCv<T>::type>::type
    { };


  /// isFunction
  template<typename>
    struct isFunction
    : public falseType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...)>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......)>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) volatile>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) volatile &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) volatile &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) volatile>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) volatile &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) volatile &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const volatile>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const volatile &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes...) const volatile &&>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const volatile>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const volatile &>
    : public trueType { };

  template<typename Res, typename... ArgTypes>
    struct isFunction<Res(ArgTypes......) const volatile &&>
    : public trueType { };


  template<typename>
    struct isNullPointerHelper
    : public falseType { };

    typedef decltype(nullptr)	nullptr_t;

  template<>
    struct isNullPointerHelper<nullptr_t>
    : public trueType { };

  /// isNullPointer (LWG 2247).
  template<typename T>
    struct isNullPointer
    : public isNullPointerHelper<typename removeCv<T>::type>::type
    { };


  // Composite type categories.

  /// isReference
  template<typename T>
    struct isReference
    : public Or<isLvalueReference<T>,
                   isRvalueReference<T>>::type
    { };

  /// isArithmetic
  template<typename T>
    struct isArithmetic
    : public Or<isInteger<T>, isFloatingPoint<T>>::type
    { };

  /// is_fundamental
  template<typename T>
    struct is_fundamental
    : public Or<isArithmetic<T>, isVoid<T>,
		   isNullPointer<T>>::type
    { };

  /// isObject
  template<typename T>
    struct isObject
    : public Not<Or<isFunction<T>, isReference<T>,
                          isVoid<T>>>::type
    { };

  template<typename>
    struct isMemberPointer;

  template<typename T>
    struct isMemberPointerHelper
    : public falseType { };

  template<typename T, typename Cp>
    struct isMemberPointerHelper<T Cp::*>
    : public trueType { };

  template<typename T>
    struct isMemberPointer
    : public isMemberPointerHelper<typename removeCv<T>::type>::type
    { };


  template<typename T>
    struct isReferenceable
    : public Or<isObject<T>, isReference<T>>::type
    { };

  template<typename Res, typename... Args>
    struct isReferenceable<Res(Args...)>
    : public trueType
    { };

  template<typename Res, typename... Args>
    struct isReferenceable<Res(Args......)>
    : public trueType
    { };

  /// isConst
  template<typename>
    struct isConst
    : public falseType { };

  template<typename T>
    struct isConst<T const>
    : public trueType { };

  /// isVolatile
  template<typename>
    struct isVolatile
    : public falseType { };

  template<typename T>
    struct isVolatile<T volatile>
    : public trueType { };


  template<bool B, class T = void>
  struct enableIf {};
  
  template<class T>
  struct enableIf<true, T> { typedef T type; };


  // Conditional expression for types. If true, first, if false, second.
  template<bool Cond, typename Iftrue, typename IfFalse>
    struct conditionalType
    { typedef Iftrue type; };

  template<typename Iftrue, typename IfFalse>
    struct conditionalType<false, Iftrue, IfFalse>
    { typedef IfFalse type; };
}


