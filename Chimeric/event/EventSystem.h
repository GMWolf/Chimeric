
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
#include "../core/World.h"
#include "../core/FamilyBitsets.h"

namespace chimeric {

    template<class T>
    class EventDispatcher {
        std::vector<EventQueue<T>*> globalQueues;

        //Entity Queues
        struct {
            std::vector<FamilyBitsets> bitsets;
            std::vector<EventQueue<T>*> queues;
        } entityQueues;

    public:
        void dispatch(const T& event);
        void dispatch(const T& event,  const dynamic_bitset& aspect);
        void registerQueue(EventQueue<T>& eq);
        void registerQueue(EventQueue<T>& eq, const FamilyBitsets& bs);
    };



    class EventSystem : public System {
        ResourceManager dispatchers;

    public:
        EventSystem(World& world) : System(world) {};
        void update() override;

        template<class T>
        void dispatch(const T& event);

        template<class T>
        void dispatch(const T& event, size_t entity);

        template<class T>
        void registerQueue(EventQueue<T>& eq);

        template<class T>
        void registerQueue(EventQueue<T>& eq, const Family& family);
    };


    template<class T>
    void EventDispatcher<T>::dispatch(const T &event) {
        for(EventQueue<T>* e : globalQueues) {
            e->deq.push_back(event);
        }
    }

    template<class T>
    void EventDispatcher<T>::dispatch(const T &event, const dynamic_bitset& aspect) {
        for(size_t i = 0; i < entityQueues.bitsets.size(); i++) {
            if (entityQueues.bitsets[i].matches(aspect)) {
                entityQueues.queues[i]->deq.push_back(event);
            }
        }
    }

    template<class T>
    void EventDispatcher<T>::registerQueue(EventQueue<T> &eq) {
        globalQueues.push_back(& eq);
    }

    template<class T>
    void EventDispatcher<T>::registerQueue(EventQueue<T> &eq, const FamilyBitsets &bs) {
        entityQueues.bitsets.push_back(bs);
        entityQueues.queues.push_back(&eq);
    }




    template<class T>
    void chimeric::EventSystem::dispatch(const T &event) {
        if (dispatchers.has<EventDispatcher<T>>()) {
            dispatchers.get<EventDispatcher<T>>().dispatch(event);
        }
    }

    template<class T>
    void chimeric::EventSystem::dispatch(const T &event, size_t entity) {
        if (dispatchers.has<EventDispatcher<T>>()) {
            dispatchers.get<EventDispatcher<T>>().dispatch(event, world.entities.getAspect(entity));
        }
    }


    template<class T>
    void chimeric::EventSystem::registerQueue(chimeric::EventQueue<T> &eq) {

        if (!dispatchers.has<EventDispatcher<T>>()) {
            dispatchers.emplace<EventDispatcher<T>>();
        }

        dispatchers.get<EventDispatcher<T>>().registerQueue(eq);
    }

    template<class T>
    void chimeric::EventSystem::registerQueue(chimeric::EventQueue<T> &eq, const chimeric::Family &family) {
        if (!dispatchers.has<EventDispatcher<T>>()) {
            dispatchers.emplace<EventDispatcher<T>>();
        }

        dispatchers.get<EventDispatcher<T>>().registerQueue(eq, FamilyBitsets(world, family));
    }



}


#endif //CHIMERIC_EVENTSYSTEM_H
