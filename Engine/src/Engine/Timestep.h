#ifndef __TIMESTEP_H__
#define __TIMESTEP_H__

namespace Engine
{
    class Timestep
    {
        public:
            Timestep(float time = 0.0f)
            :
            m_time(time)
            {}

            const float GetTimeSeconds() const { return m_time; }
            const float GetTimeMilliseonds() const { return m_time * 1000.0f; }
        private:
            float m_time;
    };
}

#endif