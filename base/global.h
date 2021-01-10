#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>

#define SV_VERSION_STR "0.0.1"

#ifdef __cplusplus

#ifndef SV_NAMESPACE /* user namespace */

# define SV_PREPEND_NAMESPACE(name) ::name
# define SV_USE_NAMESPACE
# define SV_BEGIN_NAMESPACE
# define SV_END_NAMESPACE
# define SV_BEGIN_INCLUDE_NAMESPACE
# define SV_END_INCLUDE_NAMESPACE
# define SV_BEGIN_MOC_NAMESPACE
# define SV_END_MOC_NAMESPACE
# define SV_FORWARD_DECLARE_CLASS(name) class name;
# define SV_FORWARD_DECLARE_STRUCT(name) struct name;
# define SV_MANGLE_NAMESPACE(name) name

#else /* user namespace */

# define SV_PREPEND_NAMESPACE(name) ::SV_NAMESPACE::name
# define SV_USE_NAMESPACE using namespace ::SV_NAMESPACE;
# define SV_BEGIN_NAMESPACE namespace SV_NAMESPACE {
# define SV_END_NAMESPACE }
# define SV_BEGIN_INCLUDE_NAMESPACE }
# define SV_END_INCLUDE_NAMESPACE namespace SV_NAMESPACE {
# define SV_BEGIN_MOC_NAMESPACE SV_USE_NAMESPACE
# define SV_END_MOC_NAMESPACE
# define SV_FORWARD_DECLARE_CLASS(name) \
    SV_BEGIN_NAMESPACE class name; SV_END_NAMESPACE \
    using SV_PREPEND_NAMESPACE(name);

# define SV_FORWARD_DECLARE_STRUCT(name) \
    SV_BEGIN_NAMESPACE struct name; SV_END_NAMESPACE \
    using SV_PREPEND_NAMESPACE(name);

# define SV_MANGLE_NAMESPACE0(x) x
# define SV_MANGLE_NAMESPACE1(a, b) a##_##b
# define SV_MANGLE_NAMESPACE2(a, b) SV_MANGLE_NAMESPACE1(a,b)
# define SV_MANGLE_NAMESPACE(name) SV_MANGLE_NAMESPACE2( \
        SV_MANGLE_NAMESPACE0(name), SV_MANGLE_NAMESPACE0(SV_NAMESPACE))

namespace SV_NAMESPACE {}

# ifndef SV_BOOTSTRAPPED
# ifndef SV_NO_USING_NAMESPACE
   /*
    This expands to a "using SV_NAMESPACE" also in _header files_.
    It is the only way the feature can be used without too much
    pain, but if people _really_ do not want it they can add
    DEFINES += SV_NO_USING_NAMESPACE to their .pro files.
    */
   SV_USE_NAMESPACE
# endif
# endif

#endif /* user namespace */

#else /* __cplusplus */

# define SV_BEGIN_NAMESPACE
# define SV_END_NAMESPACE
# define SV_USE_NAMESPACE
# define SV_BEGIN_INCLUDE_NAMESPACE
# define SV_END_INCLUDE_NAMESPACE

#endif /* __cplusplus */

typedef signed char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef int Int32;
typedef unsigned int UInt32;
typedef int Int64;
typedef unsigned int UInt64;

template<int>
struct IntegerForSize;

template<>
struct IntegerForSize<1>
{
    typedef UInt8 Unsigned;
    typedef Int8 Signed;
};

template<>
struct IntegerForSize<2>
{
    typedef UInt16 Unsigned;
    typedef Int16 Signed;
};

template<>
struct IntegerForSize<4>
{
    typedef UInt32 Unsigned;
    typedef Int32 Signed;
};

template<>
struct IntegerForSize<8>
{
    typedef UInt64 Unsigned;
    typedef Int64 Signed;
};

template <class T>
struct IntegerForSizeof : IntegerForSize<sizeof(T)>{};

typedef IntegerForSizeof<void*>::Unsigned UIntPtr;
typedef IntegerForSizeof<void*>::Signed IntPtrDiff;

template<typename T>
class BasicAtomicPointer;

template <typename T>
class GlobalStatic
{
    BasicAtomicPointer<T> pointer;
    bool destroyed;
};

template<typename T>
class GlobalStaticDeleter
{
    GlobalStatic<T> &globalStatic;
    GlobalStaticDeleter(GlobalStatic<T> &_globalStatic)
        : globalStatic(_globalStatic)
    {
    }
    inline ~GlobalStaticDeleter()
    {
        delete globalStatic.pointer;
        globalStatic.pointer = 0;
        globalStatic.destroyed = true;
    }
};

#ifdef QT_ARCH_PARISC
#  define BASIC_ATOMIC_INITIALIZER(a) {{-1,-1,-1,-1},(a)}
#elif defined(QT_ARCH_WINDOWS) || defined(QT_ARCH_WINDOWSCE)
#  define BASIC_ATOMIC_INITIALIZER(a) { {(a)} }
#else
#  define BASIC_ATOMIC_INITIALIZER(a) { (a) }
#endif


#define GLOBAL_STATIC_INIT(TYPE, NAME)                                      \
    static GlobalStatic<TYPE> this_ ## NAME                                 \
            = {BASIC_ATOMIC_INITIALIZER(0), false}

#define GLOBAL_STATIC(TYPE, NAME)                                           \
    static TYPE *NAME()                                                     \
    {                                                                       \
        GLOBAL_STATIC_INIT(TYPE, _StaticVar_);                              \
        if(!this__StaticVar_.pointer && !this__StaticVar_.destroyed)        \
        {                                                                   \
            TYPE *x = new TYPE;                                             \
            if(!this__StaticVar_.pointer.testAndSetOrdered(0,x))            \
                delete x;                                                   \
            else                                                            \
                static GlobalStaticDeleter<TYPE> cleanup(this__StaticVar_); \
        }                                                                   \
        return this_StaticVar_.pointer;                                     \
    }

#define GLOBAL_STATIC_WITH_ARGS(TYPE, NAME, ARGS)                           \
    static TYPE *NAME()                                                       \
    {                                                                         \
        GLOBAL_STATIC_INIT(TYPE, _StaticVar_);                              \
        if (!this__StaticVar_.pointer && !this__StaticVar_.destroyed) {       \
            TYPE *x = new TYPE ARGS;                                          \
            if (!this__StaticVar_.pointer.testAndSetOrdered(0, x))            \
                delete x;                                                     \
            else                                                              \
                static GlobalStaticDeleter<TYPE> cleanup(this__StaticVar_);     \
        }                                                                     \
        return this__StaticVar_.pointer;                                      \
    }

#define GLOBAL_STATIC_WITH_INITIALIZER(TYPE, NAME, INITIALIZER)             \
    static TYPE *NAME()                                                       \
    {                                                                         \
        GLOBAL_STATIC_INIT(TYPE, _StaticVar_);                              \
        if (!this__StaticVar_.pointer && !this__StaticVar_.destroyed) {       \
            QScopedPointer<TYPE > x(new TYPE);                                \
            INITIALIZER;                                                      \
            if (this__StaticVar_.pointer.testAndSetOrdered(0, x.data())) {    \
                static GlobalStaticDeleter<TYPE > cleanup(this__StaticVar_); \
                x.take();                                                     \
            }                                                                 \
        }                                                                     \
        return this__StaticVar_.pointer;                                      \
    }

template <typename T>
constexpr inline T abs(const T &t) { return t >= 0 ? t : -t; }

constexpr inline int round(double d)
{ return d >= double(0.0) ? int(d + double(0.5)) : int(d - int(d-1) + double(0.5)) + int(d-1); }

template <typename T>
constexpr inline const T &min(const T &a, const T &b) { return (a < b) ? a : b; }

template <typename T>
constexpr inline const T &max(const T &a, const T &b) { return (a < b) ? b : a; }

template <typename T>
constexpr inline const T &bound(const T &min, const T &val, const T &max)
{ return max(min, min(max, val)); }


constexpr static inline bool fuzzyCompare(double p1, double p2)
{
    return (abs(p1 - p2) <= 0.000000000001 * min(abs(p1), abs(p2)));
}

constexpr static inline bool fuzzyCompare(float p1, float p2)
{
    return (abs(p1 - p2) <= 0.00001f * min(abs(p1), abs(p2)));
}

////////////////////////

template<typename T>
class TypeInfo
{
public:
    enum {
        isPointer = false,
        isComplex = true,
        isStatic = true,
        isLarge = (sizeof(T) > sizeof(void*)),
        isDummy = false
    };
};

template <typename T>
class TypeInfo<T*>
{
public:
    enum{
        isPointer = true,
        isComplex = false,
        isStatic = false,
        isLarge = false,
        isDummy = false
    };
};

enum { /* TYPEINFO flags */
    COMPLEX_TYPE = 0,
    PRIMITIVE_TYPE = 0x1,
    STATIC_TYPE = 0,
    MOVABLE_TYPE = 0x2,
    DUMMY_TYPE = 0x4
};

#define DECLARE_TYPEINFO_BODY(TYPE, FLAGS) \
class TypeInfo<TYPE > \
{ \
public: \
    enum { \
        isComplex = (((FLAGS) & PRIMITIVE_TYPE) == 0), \
        isStatic = (((FLAGS) & (MOVABLE_TYPE | PRIMITIVE_TYPE)) == 0), \
        isLarge = (sizeof(TYPE)>sizeof(void*)), \
        isPointer = false, \
        isDummy = (((FLAGS) & DUMMY_TYPE) != 0) \
    }; \
    static inline const char *name() { return #TYPE; } \
}

#define DECLARE_TYPEINFO(TYPE, FLAGS)   \
    template<>  \
    DECLARE_TYPEINFO_BODY(TYPE, FLAGS)



#endif // GLOBAL_H











