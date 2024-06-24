#pragma once

#include "SFLXpch.h"


namespace Snowflax
{

	template <typename Ret, typename... Args>
	class Function {
	public:
	    Function(Ret (*_func)(Args...))
			: m_Invoker(new FunctionPointerInvoker(_func)) {}

	    template <typename T>
	    Function(Ret (T::*_func)(Args...), T* _instance)
			: m_Invoker(new MemberFunctionInvoker<T>(_func, _instance)) {}

	    template <typename T>
	    Function(Ret (T::*_func)(Args...) const, const T* _instance)
			: m_Invoker(new ConstMemberFunctionInvoker<T>(_func, _instance)) {}

		template <typename Callable>
		requires (std::is_same_v<std::invoke_result_t<Callable, Args...>, Ret>)
	    Function(Callable&& _callable)
			: m_Invoker(new CallableInvoker<Callable>(std::forward<Callable>(_callable))) {}

	    auto operator()(Args&&... _args) -> decltype(auto) {
	        return m_Invoker->Invoke(std::forward<Args>(_args)...);
	    }

	private:
	    struct InvokerBase {
	        virtual ~InvokerBase() = default;
	        virtual Ret Invoke(Args...) = 0;
	    };

	    struct FunctionPointerInvoker : InvokerBase {
	        using FuncType = Ret (*)(Args...);

	        FunctionPointerInvoker(FuncType _func) : m_Func(_func) {}

	        Ret Invoke(Args... _args) override {
	            return m_Func(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	    };

		template <typename T>
	    struct MemberFunctionInvoker : InvokerBase {
	        using FuncType = Ret (T::*)(Args...);

	        MemberFunctionInvoker(FuncType _func, T* _instance) : m_Func(_func), m_Instance(_instance) {}

	        Ret Invoke(Args... _args) override {
	            return (m_Instance->*m_Func)(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	        T* m_Instance;
	    };

	    template <typename T>
	    struct ConstMemberFunctionInvoker : InvokerBase {
	        using FuncType = Ret (T::*)(Args...) const;

	        ConstMemberFunctionInvoker(FuncType _func, const T* _instance) : m_Func(_func), m_Instance(_instance) {}

	        Ret Invoke(Args... _args) override {
	            return (m_Instance->*m_Func)(std::forward<Args>(_args)...);
	        }

	        FuncType m_Func;
	        const T* m_Instance;
	    };

		template <typename Callable>
		requires (std::is_same_v<std::invoke_result_t<Callable, Args...>, Ret>)
	    struct CallableInvoker : InvokerBase {
	        CallableInvoker(Callable&& _callable) : m_Callable(std::forward<Callable>(_callable)) {}

	        Ret Invoke(Args&&... _args) override {
	            return m_Callable(std::forward<Args>(_args)...);
	        }

	        Callable m_Callable;
	    };

	    std::unique_ptr<InvokerBase> m_Invoker;
	};
	

}