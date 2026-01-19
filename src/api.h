#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define KinovaGravityCompensationController_DLLIMPORT __declspec(dllimport)
#  define KinovaGravityCompensationController_DLLEXPORT __declspec(dllexport)
#  define KinovaGravityCompensationController_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define KinovaGravityCompensationController_DLLIMPORT __attribute__((visibility("default")))
#    define KinovaGravityCompensationController_DLLEXPORT __attribute__((visibility("default")))
#    define KinovaGravityCompensationController_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define KinovaGravityCompensationController_DLLIMPORT
#    define KinovaGravityCompensationController_DLLEXPORT
#    define KinovaGravityCompensationController_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef KinovaGravityCompensationController_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define KinovaGravityCompensationController_DLLAPI
#  define KinovaGravityCompensationController_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef KinovaGravityCompensationController_EXPORTS
#    define KinovaGravityCompensationController_DLLAPI KinovaGravityCompensationController_DLLEXPORT
#  else
#    define KinovaGravityCompensationController_DLLAPI KinovaGravityCompensationController_DLLIMPORT
#  endif // KinovaGravityCompensationController_EXPORTS
#  define KinovaGravityCompensationController_LOCAL KinovaGravityCompensationController_DLLLOCAL
#endif // KinovaGravityCompensationController_STATIC
