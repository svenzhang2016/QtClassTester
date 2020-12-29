#ifndef GLOBAL_H
#define GLOBAL_H

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


#endif // GLOBAL_H

