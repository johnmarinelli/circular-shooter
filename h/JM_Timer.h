/*
* timer class
*/
#ifndef _JM_TIMER
#define _JM_TIMER

#include "JM_SDL.h"

namespace JM_Library
{

struct JM_Timer
{
    bool m_paused, m_running;
    int m_startTicks, m_pausedTicks;

    JM_Timer() 
        : m_paused(false), m_running(false), m_startTicks(0), m_pausedTicks(0)
    {
    };

    void start()
    {
        m_running = true;
        m_paused = false;

        m_startTicks = SDL_GetTicks();
        //printf("START TICKS: %d\n", m_startTicks);
    };

    void pause()
    {
        if(!m_paused && m_running){
            m_running = false;
            m_paused = true;

            m_pausedTicks = SDL_GetTicks() - m_startTicks;
        }
    };

    void unpause()
    {
        if(m_paused && !m_running){
            m_running = true;
            m_paused = false;

            m_startTicks = SDL_GetTicks() - m_pausedTicks;
            m_pausedTicks = 0;
        }
    };

    void stop()
    {
        if(m_running){
            m_running = false;
            m_paused = false;

            m_pausedTicks = 0;
            m_startTicks = 0;
        }
    };

    int getTicks()
    {
        if (m_paused){
            return m_pausedTicks;
        }

        else{
            //printf("GET TICKS: %d\n", SDL_GetTicks());
            return SDL_GetTicks() - m_startTicks;
        }

        return 0;
    };
};

}
#endif