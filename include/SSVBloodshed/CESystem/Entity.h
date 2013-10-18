// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVOB_CESYSTEM_ENTITY
#define SSVOB_CESYSTEM_ENTITY

#include "SSVBloodshed/CESystem/Common.h"

namespace ssvces
{
	class Manager;
	class EntityHandle;
	class SystemBase;
	template<typename, typename, typename> class System;

	class Entity
	{
		friend class Manager;
		friend class EntityHandle;
		friend class SystemBase;
		template<typename, typename, typename> friend class System;

		private:
			Manager& manager;
			std::array<Uptr<Component>, maxComponents> components;
			TypeIdsBitset typeIds;
			bool mustDestroy{false}, mustRematch{true};
			GroupBitset groups;
			EntityStat stat;
			std::size_t componentCount{0};

		public:
			inline Entity(Manager& mManager, const EntityStat& mStat) noexcept : manager(mManager), stat(mStat) { }

			template<typename T, typename... TArgs> inline void createComponent(TArgs&&...);
			template<typename T> inline void removeComponent();
			template<typename T> inline bool hasComponent() const noexcept
			{
				static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");
				return typeIds[getTypeIdBitIdx<T>()];
			}
			template<typename T> inline T& getComponent() noexcept
			{
				static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");
				assert(componentCount > 0 && hasComponent<T>());
				return reinterpret_cast<T&>(*components[getTypeIdBitIdx<T>()]);
			}

			inline void destroy() noexcept;

			inline Manager& getManager() noexcept { return manager; }

			// Groups
			inline void addGroups(Group mGroup) noexcept;
			inline void delGroups(Group mGroup) noexcept;
			inline void clearGroups() noexcept;
			template<typename... TGroups> inline void addGroups(Group mGroup, TGroups... mGroups) noexcept	{ addGroups(mGroup); addGroups(mGroups...); }
			template<typename... TGroups> inline void delGroups(Group mGroup, TGroups... mGroups) noexcept	{ delGroups(mGroup); delGroups(mGroups...); }
			inline bool hasGroup(Group mGroup) const noexcept					{ return groups[mGroup]; }
			inline bool hasAnyGroup(const GroupBitset& mGroups) const noexcept	{ return (groups & mGroups).any(); }
			inline bool hasAllGroups(const GroupBitset& mGroups) const noexcept	{ return (groups & mGroups).all(); }
			inline const GroupBitset& getGroups() const noexcept				{ return groups; }
	};

	template<typename T> constexpr inline std::tuple<T*> buildComponentsTuple(Entity& mEntity) { return std::tuple<T*>{&mEntity.getComponent<T>()}; }
	template<typename T1, typename T2, typename... TArgs> constexpr inline std::tuple<T1*, T2*, TArgs*...> buildComponentsTuple(Entity& mEntity) { return std::tuple_cat(buildComponentsTuple<T1>(mEntity), buildComponentsTuple<T2, TArgs...>(mEntity)); }
}

#endif