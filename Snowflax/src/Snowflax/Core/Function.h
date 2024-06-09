#pragma once

#include "SFXpch.h"


namespace Snowflax
{
	template <typename Ret, typename... Args>
	class Function {
	public:
	    Function(Ret (*_func)(Args...))
			: m_Invoker(new FunctionPointerInvoker<Ret, Args...>(_func)) {}

	    template <typename T>
	    Function(Ret (T::*_func)(Args...), T* _instance)
			: m_Invoker(new MemberFunctionInvoker<Ret, T, Args...>(_func, _instance)) {}

	    template <typename T>
	    Function(Ret (T::*_func)(Args...) const, const T* _instance)
			: m_Invoker(new ConstMemberFunctionInvoker<Ret, T, Args...>(_func, _instance)) {}

	    template <typename Callable>
	    Function(Callable&& _callable)
			: m_Invoker(new CallableInvoker<Callable>(std::forward<Callable>(_callable))) {}

	    auto operator()(Args&&... _args) -> decltype(auto) {
	        return m_Invoker->Invoke(std::forward<Args>(_args)...);
	    }

	private:
		template<typename... Args>
	    struct InvokerBase {
	        virtual ~InvokerBase() = default;
	        virtual void Invoke(Args...) = 0;
	    };

		template <typename Ret, typename... Args>
	    struct FunctionPointerInvoker : InvokerBase<Args...> {
	        using FuncType = Ret (*)(Args...);

	        FunctionPointerInvoker(FuncType _func) : m_Func(_func) {}

	        void Invoke(Args... _args) override {
	            m_Func(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	    };

		template <typename Ret, typename T,typename... Args>
	    struct MemberFunctionInvoker : InvokerBase<Args...> {
	        using FuncType = Ret (T::*)(Args...);

	        MemberFunctionInvoker(FuncType _func, T* _instance) : m_Func(_func), m_Instance(_instance) {}

	        void Invoke(Args... _args) override {
	            (m_Instance->*m_Func)(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	        T* m_Instance;
	    };

	    template <typename Ret, typename T,typename... Args>
	    struct ConstMemberFunctionInvoker : InvokerBase<Args...> {
	        using FuncType = Ret (T::*)(Args...) const;

	        ConstMemberFunctionInvoker(FuncType _func, const T* _instance) : m_Func(_func), m_Instance(_instance) {}

	        void Invoke(Args... _args) override {
	            (m_Instance->*m_Func)(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	        const T* m_Instance;
	    };

	    template <typename Callable>
	    struct CallableInvoker : InvokerBase<Args...> {
	        CallableInvoker(Callable&& _callable) : m_Callable(std::forward<Callable>(_callable)) {}

	        void Invoke(Args&&... _args) {
	            m_Callable(std::forward<Args>(_args)...);
	        }

	        Callable m_Callable;
	    };

	    std::unique_ptr<InvokerBase<Args...>> m_Invoker;
	};

}