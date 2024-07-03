#pragma once

#include <chrono>


namespace Snowflax
{
    class Timer
    {
    public:
        Timer()
    	{
            Reset();
        }

        void Reset()
        {
            m_startTime = std::chrono::high_resolution_clock::now();
        }

        template<std::ratio _ratio = 1>
		float Elapsed() const
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_startTime).count() * (0.001f * 0.001f * 0.001f / _ratio);
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    };
}
