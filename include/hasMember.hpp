#if defined HAS_MEMBER_STRUCT_NAME && defined HAS_MEMBER_MEMBER_NAME

// Primary template
template <typename T, typename = int>
struct HAS_MEMBER_STRUCT_NAME : std::false_type { };

// Specialization for second typename == int
template <typename T>
struct HAS_MEMBER_STRUCT_NAME <T, decltype((void) T::HAS_MEMBER_MEMBER_NAME, int())> : std::true_type { };

#else 
#error HAS_MEMBER_STRUCT_NAME and HAS_MEMBER_MEMBER_NAME should be defined before including hasMember.hpp .
#endif 

#ifdef HAS_MEMBER_STRUCT_NAME
#undef HAS_MEMBER_STRUCT_NAME
#endif

#ifdef HAS_MEMBER_MEMBER_NAME
#undef HAS_MEMBER_MEMBER_NAME
#endif

