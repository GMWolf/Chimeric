
//
// Created by Felix Bridault on 29/01/2019.
//

#ifndef CHIMERIC_EVENTSYSTEM_H
#define CHIMERIC_EVENTSYSTEM_H

#include "../core/System.h"
#include "EventQueue.h"
#include "../core/ResourceManager.h"
#include <vector>
#include <unordered_map>

namespace chimeric {

    template<class T>
    class EventDispatcher {
        std::vector<EventQueue<T>*> queues;
    public:
        void dispatch(const T& event);
        void registerQueue(EventQueue<T>& eq);
    };



    class EventSystem : public System {
        ResourceManager dispatchers;

    public:

        EventSystem(World& world) : System(world) {};
        void update() override;

        template<class T>
        void dispatch(const T& event);

        template<class T>
        void registerQueue(EventQueue<T>& eq);
    };


    template<class T>
    void EventDispatcher<T>::dispatch(const T &event) {
        for(EventQueue<T>* e : queues) {
            e->deq.push_back(event);
        }
    }

    template<class T>
    void EventDispatcher<T>::registerQueue(EventQueue<T> &eq) {
        queues.push_back(& eq);
    }


    template<class T>
    void chimeric::EventSystem::dispatch(const T &event) {
        dispatchers.get<EventDispatcher<T>>().dispatch(event);
    }


    template<class T>
    void chimeric::EventSystem::registerQueue(chimeric::EventQueue<T> &eq) {

        if (!dispatchers.has<EventDispatcher<T>>()) {
            dispatchers.emplace<EventDispatcher<T>>();
        }

        dispatchers.get<EventDispatcher<T>>().registerQueue(eq);
    }


}


#endif //CHIMERIC_EVENTSYSTEM_H
