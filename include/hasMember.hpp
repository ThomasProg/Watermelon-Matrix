#if defined HAS_MEMBER_STRUCT_NAME && defined HAS_MEMBER_MEMBER_NAME && defined HAS_MEMBER_TYPE

// Primary template
template <typename T, typename = HAS_MEMBER_TYPE>
struct HAS_MEMBER_STRUCT_NAME : std::false_type { };

// Specialization for second typename == HAS_MEMBER_TYPE
template <typename T>
struct HAS_MEMBER_STRUCT_NAME <T, decltype((void) T::HAS_MEMBER_MEMBER_NAME, HAS_MEMBER_TYPE())> : std::true_type { };

#else 
#error HAS_MEMBER_STRUCT_NAME , HAS_MEMBER_MEMBER_NAME , and HAS_MEMBER_TYPE should be defined before including hasMember.hpp .
#endif 

#ifdef HAS_MEMBER_STRUCT_NAME
#undef HAS_MEMBER_STRUCT_NAME
#endif

#ifdef HAS_MEMBER_MEMBER_NAME
#undef HAS_MEMBER_MEMBER_NAME
#endif

#ifdef HAS_MEMBER_TYPE
#undef HAS_MEMBER_TYPE
#endif
