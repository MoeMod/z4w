module;

#include <type_traits>
#include <functional>
#include <concepts>

export module amxx.convert;
import hlsdk.types;
import hlsdk.extdll;
import hlsdk.util;

using namespace hlsdk;

export namespace amxx {
    namespace convert {
        // forward decl
        template<class From, class To> struct ConvertFunc;
        template<class T> concept EntType_c = requires (const T & ent) { ConvertFunc<typename std::decay<T>::type, edict_t*>()(ent); };
        template<EntType_c To> struct Converter;
        template<EntType_c TargetType> struct auto_ent;
        template<EntType_c TargetType>
        constexpr auto ent_cast = [](const auto& x) { return Converter<typename std::decay<TargetType>::type>()(x); };
        template<EntType_c T>
        constexpr auto make_auto_ent = [](const auto& x) { return auto_ent<T>(x); };

        // impl
        namespace detail {
            template<class From, class...Dest> struct AdapterFunc;
            template<class From> struct AdapterFunc<From> : std::identity {};
            template<class From, class To> struct AdapterFunc<From, To> : ConvertFunc<From, To> {};
            template<class From, class Mid, class...To> struct AdapterFunc<From, Mid, To...>
            {
                auto operator()(From in) const
                {
                    return AdapterFunc<Mid, To...>()(AdapterFunc<From, Mid>()(in));
                };
            };

            template<class From, class To, class = void> struct ConvertFuncSingle;
            template<class T> struct ConvertFuncSingle<T, T> : std::identity {};
            template<> struct ConvertFuncSingle<int, edict_t*> { edict_t* operator()(int id) const { return INDEXENT(id); } };
            template<> struct ConvertFuncSingle<entvars_t*, edict_t*> { edict_t* operator()(entvars_t* pev) const { return ENT(pev); } };
            template<> struct ConvertFuncSingle<edict_t*, int> { int operator()(edict_t* edict) const { return ENTINDEX(edict); } };
            template<> struct ConvertFuncSingle<edict_t*, entvars_t*> { entvars_t* operator()(edict_t* edict) const { return VARS(edict); } };

            // use adapters
            template<> struct ConvertFuncSingle<int, entvars_t*> : AdapterFunc<int, edict_t*, entvars_t*> {};
            template<> struct ConvertFuncSingle<entvars_t*, int> : AdapterFunc<entvars_t*, edict_t*, int> {};

            // covariant
            /*
            template<class CBaseEntitySubClass> struct ConvertFuncSingle<CBaseEntitySubClass*, CBaseEntity*, typename std::enable_if<std::is_base_of<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity, CBaseEntitySubClass>::value>::type>
            {
                CBaseEntity* operator()(CBaseEntitySubClass* in) const {
                    return static_cast<CBaseEntity*>(in);
                }
            };
            template<class CBaseEntitySubClass> struct ConvertFuncSingle<CBaseEntity*, CBaseEntitySubClass*, typename std::enable_if<std::is_base_of<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity, CBaseEntitySubClass>::value>::type>
            {
                CBaseEntitySubClass* operator()(CBaseEntity* in) const {
                    return static_cast<CBaseEntitySubClass*>(in); // down-cast!!! no checked.
                }
            };
            template<class From, class CBaseEntitySubClass> struct ConvertFuncSingle<From, CBaseEntitySubClass*, typename std::enable_if<std::is_base_of<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity*, From>::value>::type>
                : AdapterFunc<From, CBaseEntity*, CBaseEntitySubClass*> {};
            template<class CBaseEntitySubClass, class To> struct ConvertFuncSingle<CBaseEntitySubClass*, To, typename std::enable_if<std::is_base_of<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity, CBaseEntitySubClass>::value && !std::is_same<CBaseEntity*, To>::value>::type>
                : AdapterFunc<CBaseEntitySubClass*, CBaseEntity*, To> {};
            */

            // auto type
            template<class From, class To> struct ConvertFuncSingle<auto_ent<From>, To> : ConvertFuncSingle<From, To> {};
            template<class From, class To> struct ConvertFuncSingle<From, auto_ent<To>> : ConvertFuncSingle<From, To> {};
            template<class From, class To> struct ConvertFuncSingle<auto_ent<From>, auto_ent<To>> : ConvertFuncSingle<From, To> {};

            template<class FromList, class To> struct ConverterGenerator;
            template<class To, template<class...> class TypeList, class...Froms> struct ConverterGenerator<TypeList<Froms...>, To> : ConvertFunc<Froms, To>... {};
        }

        template<class From, class To> struct ConvertFunc : detail::ConvertFuncSingle<From, To> {};
        template<EntType_c To> struct Converter
        {
            template<class InputType> To operator()(InputType&& in) const {
                return ConvertFunc<typename std::decay<InputType>::type, To>()(std::forward<InputType>(in));
            }
        };

#if 1
        namespace test 
        {
            using AllEntTypeList = std::tuple<edict_t*, entvars_t*, int>;
            template<class From, class To> struct ConverterUnitTest3 : std::is_invocable_r<To, ConvertFunc<From, To>, From> {};
            template<class FromList, class To> struct ConverterUnitTest2;
            template<class To, template<class...> class TypeList, class...Froms> struct ConverterUnitTest2<TypeList<Froms...>, To> : std::conjunction<ConverterUnitTest3<Froms, To>...> {};
            template<class EntTypeList> struct ConverterUnitTest1;
            template<template<class...> class TypeList, class...T> struct ConverterUnitTest1<TypeList<T...>> : std::conjunction<ConverterUnitTest2<TypeList<T...>, T>...> {};
            static_assert(ConverterUnitTest1<AllEntTypeList>::value);
        }
#endif

        template<EntType_c TargetType> struct auto_ent
        {
            template<class InputType> auto_ent(InputType&& in) : value(Converter<TargetType>()(std::forward<InputType>(in))) {}
            operator TargetType() const { return value; }
            template<class Ret = TargetType> decltype(&*std::declval<Ret>()) operator->() { return &*value; }
            TargetType value;
        };
        template<class TargetType> struct auto_ent<auto_ent<TargetType>> : auto_ent<TargetType> {};
        template<class TargetType> auto_ent(TargetType) -> auto_ent<TargetType>;
        template<class TargetType> auto_ent(auto_ent<TargetType>) -> auto_ent<TargetType>;
    }

    using convert::auto_ent;
    using convert::ent_cast;
}