//Project created by RohanFernandez
//repository : https://github.com/RohanFernandez/DankeDelegate

#pragma once
#include "action.h"
#include <vector>

namespace ns_fretBuzz
{
	template<typename T> class Delegate;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class Delegate <T_RET_TYPE(T_ARGS...)>
	{
		private:

			using T_ACTION = Action<T_RET_TYPE(T_ARGS...)>;

			///Set to store all the Actions of the same type
			std::vector<T_ACTION> m_vectActions;

		public:

			///Adds a member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_Instance)
			{
				m_vectActions.emplace_back(T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance));
			}

			///Adds a const member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...) const>
			void Add(T_CLASS_TYPE* const a_Instance)
			{
				m_vectActions.emplace_back(T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance));
			}

			///Adds an static or global action into the list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Add()
			{
				m_vectActions.emplace_back(T_ACTION::template GetAction<T_METHOD>());
			}

			T_RET_TYPE operator()(T_ARGS... a_Args)
			{
				return Invoke(a_Args...);
			}

			///Calls all the actions stored within the delegate
			T_RET_TYPE Invoke(T_ARGS... a_Args) throw(std::out_of_range)
			{
				try
				{
					if (m_vectActions.size() == 0)
					{
						throw std::out_of_range("Delegate is empty\n");
					}

					T_RET_TYPE l_tReturn;
					for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
						l_iterator != m_vectActions.end();
						l_iterator++)
					{
						l_tReturn = l_iterator->Invoke(a_Args...);
					}

					if (typeid(T_RET_TYPE) != typeid(void))
					{
						return l_tReturn;
					}
				}
				catch (std::out_of_range& a_Exception)
				{
					std::cout << "Delegate Exception::Cannot invoke::" << a_Exception.what() << "\n";
				}
			}

			///removes a member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
			void Remove(T_CLASS_TYPE* a_Instance)
			{
				for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
					l_iterator != m_vectActions.end();
					l_iterator++)
				{
					if (l_iterator->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_Instance))
					{
						m_vectActions.erase(l_iterator);
						break;
					}
				}
			}

			///removes a const member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
			void Remove(T_CLASS_TYPE* const a_Instance)
			{
				for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
					l_iterator != m_vectActions.end();
					l_iterator++)
				{
					if (l_iterator->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_Instance))
					{
						m_vectActions.erase(l_iterator);
						break;
					}
				}
			}

			///removes an static or global action into the list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Remove()
			{
				for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
					l_iterator != m_vectActions.end();
					l_iterator++)
				{
					if (l_iterator->isActionEqual<T_METHOD>())
					{
						m_vectActions.erase(l_iterator);
						break;
					}
				}
			}

			///Clears the stored actions of type withing the delegate
			void Clear()
			{
				m_vectActions.clear();
			}
	};

}