#pragma once

#include <unordered_map> 
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>
#include "Snowflax/Core.h"

namespace Snowflax {

    namespace Infrastructure {

        template<class T, class ...Ps>
        concept Parameterized = sizeof...(Ps) > 0;
        template<class T>
        concept NotParameterized = !Parameterized<T>;

        class SNOWFLAX_API Container {
        public:

            template<class T>
            using Generator = std::function<std::shared_ptr<T>()>;
            template<class T, class...Ps>
            using ParameterizedGenerator = std::function<std::shared_ptr<T>(Ps&&...arg)>;

            template<NotParameterized T>
            void RegisterFactory(Generator<T> gen) {
                m_factoryMap[typeid(T)] = { State::InstanceGenerator, std::move(gen) };
            }
            template<Parameterized T>
            void RegisterFactory(ParameterizedGenerator<T> gen) {
                m_factoryMap[typeid(T)] = { State::InstanceGenerator, std::move(gen) };
            }
            template<class T>
            void RegisterSingleton(Generator<T> gen) {
                m_factoryMap[typeid(T)] = { State::SingletonGenerator, std::move(gen) };
            }
            
            template<NotParameterized T>
            std::shared_ptr<T> Resolve() {
                return m_Resolve<T, Generator<T>>();
            }
            template<Parameterized T, class...Ps>
            std::shared_ptr<T> Resolve(Ps&&...arg) {
                return m_Resolve<T, ParameterizedGenerator<T>>(std::forward<Ps>(arg)...);
            }
            
            static Container& Get() {
                static Container c;
                return c;
            }

        private:

            enum class State {
                InstanceGenerator,
                SingletonGenerator,
                SingletonInstance
            };
            struct Entry {
                State state;
                std::any content;
            };

            template<class T, class G, class...Ps>
            std::shared_ptr<T> m_Resolve(Ps&&...arg) {
                if (const auto i = m_factoryMap.find(typeid(T)); i != m_factoryMap.end()) {
                    auto& entry = i->second;
                    if (entry.state != State::InstanceGenerator && sizeof...(Ps) > 0) {
                        throw std::runtime_error{ "Parameter passed in while resolving a singleton!" };
                    }
                    else if (entry.state == State::InstanceGenerator && Parameterized<T> && sizeof...(Ps) == 0) {
                        throw std::runtime_error{ "No parameters passed while resolving an independent instance!" };
                    }
                    try {
                        std::shared_ptr<T> ptr;
                        switch (entry.state) {
                        case State::InstanceGenerator:
                            ptr = std::any_cast<G>(entry.content)(std::forward<Ps>(arg)...);
                            break;
                        case State::SingletonGenerator:
                            ptr = std::any_cast<G>(entry.content)(std::forward<Ps>(arg)...);
                            entry.content = ptr;
                            entry.state = State::SingletonInstance;
                            break;
                        case State::SingletonInstance:
                            ptr = std::any_cast<std::shared_ptr<T>>(entry.content);
                            break;
                        default:
                            break;
                        }
                        return ptr;
                    }
                    catch (const std::bad_any_cast&) {
                        throw std::runtime_error{
                            std::format(
                                "Could not resolve Services mapped type\nfrom: [{}]\n to: [{}]\n",
                                entry.content.type().name(), typeid(G).name()
                            )
                        };
                    }
                    catch (const std::bad_function_call&) {
                        throw std::runtime_error{
                            std::format(
                                "Wrong arguments passed to function: [{}]\n",
                                typeid(G).name()
                            )
                        };
                    }
                }
                else if (m_useContructor) {
                    try {
                        return std::make_shared<T>(std::forward<Ps>(arg)...);
                    }
                    catch (const std::invalid_argument&) {
                        throw std::runtime_error{
                            std::format(
                                "Could not construct [{}]!\n",
                                typeid(T).name()
                            ) // Need to add passed parameters to runtime_error
                        };
                    }
                }
                else {
                    throw std::runtime_error{ std::format("Could not find generator for type [{}] in factory map!", typeid(T).name()) };
                }
            }

            std::unordered_map<std::type_index, Entry> m_factoryMap;
            bool m_useContructor = true;

        };
    }
}