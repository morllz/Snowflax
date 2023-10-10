// TODO: Test all this shit!!!!!!


#pragma once

#include <unordered_map> 
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>

namespace Snowflax {

    namespace Infrastructure {

        template<class T, class ...Ps>
        concept Parameterized = sizeof...(Ps) > 0;
        template<class T>
        concept NotParameterized = !Parameterized<T>;

        class Container {
        public:

            template<class T>
            using Generator = std::function<std::shared_ptr<T>()>;
            template<class T, class...Ps>
            using ParameterizedGenerator = std::function<std::shared_ptr<T>(Ps&&...arg)>;

            template<NotParameterized T>
            void RegisterFactory(Generator<T> gen);
            template<Parameterized T>
            void RegisterFactory(ParameterizedGenerator<T> gen);
            template<class T>
            void RegisterSingleton(Generator<T> gen);
            
            template<NotParameterized T>
            std::shared_ptr<T> Resolve();
            template<Parameterized T, class...Ps>
            std::shared_ptr<T> Resolve(Ps&&...arg);
            
            static Container& Get();

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
            std::shared_ptr<T> m_Resolve(Ps&&...arg);

            std::unordered_map<std::type_index, Entry> m_factoryMap;
            bool m_useContructor = false;

        };
    }
}