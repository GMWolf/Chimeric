
//
// Created by Felix Bridault on 29/01/2019.
//

#ifndef CHIMERIC_EVENTQUEUE_H
#define CHIMERIC_EVENTQUEUE_H

#include <deque>


namespace chimeric {

    template<class T> class EventQueue;
    template<class T> class EventDispatcher;

    template<class T>
    class EventQueue {
        friend class EventDispatcher<T>;
        std::deque<T> deq;

    public:

        const T&operator[](size_t index) {
            return deq[index];
        }

        void clear() {
            deq.clear();
        }

        void pop() {
            deq.pop_front();
        }

        const T& front() const {
            return deq.front();
        }

        bool empty() const {
            return deq.empty();
        }



    };

}


#endif //CHIMERIC_EVENTQUEUE_H
