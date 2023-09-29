#pragma once

#include <unordered_map> 
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>

template<class T>
concept Parameterized = requires() {
    { typename T::IoCParams{} };
};
template<class T>
concept NotParameterized = !Parameterized<T>;


class Container {
public:
    

    template<class T>
    using Generator = std::function<std::shared_ptr<T>()>;
    template<class T, class...Ps>
    using ParameterizedGenerator = std::function<std::shared_ptr<T>(Ps&&...arg)>;

    template<NotParameterized T>
    void RegisterFactory(Generator<T> gen) {
        factoryMap[typeid(T)] = gen;
    }
    template<Parameterized T>
    void RegisterFactory(ParameterizedGenerator<T> gen) {
        factoryMap[typeid(T)] = gen;
    }

    template<NotParameterized T>
    std::shared_ptr<T> Resolve() {
        return m_Resolve<T, Generator<T>>();
    }
    template<Parameterized T, class...Ps>
    std::shared_ptr<T> Resolve(Ps&&...arg) {
        return m_Resolve<T, ParameterizedGenerator<T>>(std::forward<Ps>(params)...);
    }

    static Container& Get() {
        static Container c;
        return c;
    }
private:
    template<class T, class G, class...Ps>
    std::shared_ptr<T> m_Resolve(Ps&&...arg) {
        if (const auto i = factoryMap.find(typeid(T); i != factoryMap.end())) {
            try {
                return std::any_cast<G>(i->second)(std::forward<Ps>(arg)...);
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error{
                    std::format(
                        "Could not resolve Services mapped type\nfrom: [{}]\n to: [{}]\n",
                        i->second.type().name(), typeid(G).name()
                    );
                }
            }
        }
        else {
            throw std::runtime_error{ std::format("Could not find generator for type [{}] in factory map!", typeid(T).name()) }; y
        }
    }

    std::unordered_map<std::type_index, std::any> factoryMap;
};