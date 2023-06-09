#pragma once
#include "Scene.h"
#include "Component.h"
#include "entt.hpp"



namespace Hazel

{


	class Entity //scene's friend class
	{
	public:
		Entity() = default; //cherno 说空实体也是有效的...   我觉得有点危险
		Entity(const entt::entity& handle,	 Scene* scene);
		Entity(const Entity & other) = default; //as tishi(0.0)
		Entity(Scene* scene);

		template<typename T ,typename... Args>
		//return: reference of the component
		T& AddComponent(Args&&... args) 
		{

			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");

			T& component =  m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
			m_scene->OnComponentAdded<T>(*this,component);
			return component;

		}
		template<typename T ,typename... Args>
		//return: reference of the component
		T& AddOrReplaceComponent(Args&&... args) 
		{
			T& component =  m_scene->m_registry.emplace_or_replace<T>(m_entityHandle, std::forward<Args>(args)...);
			m_scene->OnComponentAdded<T>(*this,component);
			return component;

		}
		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
			return m_scene->m_registry.get<T>(m_entityHandle);
		}


		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.all_of<T>(m_entityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
			m_scene->m_registry.remove<T>(m_entityHandle);
		}

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string&  GetTag() { return GetComponent<TagComponent>().Tag; }

		operator bool() const { return m_entityHandle != entt::null;} //为entity 提供bool转换 ...方便检查空entity
		operator uint32_t() const { return (uint32_t)m_entityHandle; }
		operator entt::entity () const { return m_entityHandle; }
		bool operator==(const Entity& otherentity)const { return m_entityHandle == otherentity.m_entityHandle && m_scene ==otherentity.m_scene; }
		bool operator!=(const Entity& otherentity)const { return !(*this== otherentity); }

	private:
		entt::entity m_entityHandle{entt::null};
		//Ref<Scene> m_scene; entity不应该(强引用)shared own scene .实体不能影响scene的生命周期,而是应该反之
		Scene* m_scene =nullptr;



	};






}

