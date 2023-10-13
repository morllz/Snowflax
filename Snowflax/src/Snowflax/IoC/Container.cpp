#include "Container.h"


namespace Snowflax {

    namespace Infrastructure {

        template<NotParameterized T>
        void Container::RegisterFactory(Generator<T> gen) {
            m_factoryMap[typeid(T)] = { State::InstanceGenerator, std::move(gen) };
        }
        template<Parameterized T>
        void Container::RegisterFactory(ParameterizedGenerator<T> gen) {
            m_factoryMap[typeid(T)] = { State::InstanceGenerator, std::move(gen) };
        }
        template<class T>
        void Container::RegisterSingleton(Generator<T> gen) {
            m_factoryMap[typeid(T)] = { State::SingletonGenerator, std::move(gen) };
        }

        template<NotParameterized T>
        std::shared_ptr<T> Container::Resolve() {
            return m_Resolve<T, Generator<T>>();
        }
        template<Parameterized T, class...Ps>
        std::shared_ptr<T> Container::Resolve(Ps&&...arg) {
            return m_Resolve<T, ParameterizedGenerator<T>>(std::forward<Ps>(arg)...);
        }

        template<class T, class G, class...Ps>
        std::shared_ptr<T> Container::m_Resolve(Ps&&...arg) {
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
                        std::any_cast<std::shared_ptr<T>>(entry.content);
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
                    }
                }
            }
            else if (m_useContructor)
            try {
                return std::make_shared<T>(std::forward<Ps>(arg)...);
            }
            catch {
                throw std::runtime_error{
                    std::format(
                        "Could not construct [{}] with [{}] passed as arguments!",
                        typeid(T).name(), ...typeid(T).name
                    )
                }
            }
                
            else {
                throw std::runtime_error{ std::format("Could not find generator for type [{}] in factory map!", typeid(T).name()) };
            }
        }

        Container& Container::Get() {
            static Container c;
            return c;
        }
    }
}