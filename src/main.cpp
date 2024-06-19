#include <iostream>
#include <string_view>
#include <string>
#include <format>
#include <vector>
#include <memory>
#include <algorithm>

// An Interface for EvenListeners(Event-consumers, they need to listen for events from producers)
struct IEventListener
{
    // Implement the behaivor when an event has published from the broker
    virtual void OnEvent(std::string_view msg) = 0;
};

// Event consumer class
class EventConsumer : public IEventListener
{
public:
    EventConsumer(std::string_view name) : m_Name(name) {}

public:
    // For sake of simplicity, this consumer(event listener) just logs message when getting a new event
    void OnEvent(std::string_view msg) override
    {
        std::cout << std::format(">> {} got new message : {}\n", m_Name, msg);
    }

    std::string GetName() const { return m_Name; }

private:
    std::string m_Name; // Consumers's name
};

// Event broker - sits between event publishers and event subscribers
class EventBroker
{
public:
    // add event listers to the subscriber list, just like youtube channels
    void Subscribe(IEventListener *listener) { subscribers.push_back(listener); }

    // remove subscriber from the list, finds by the original subscriber object
    void Unsubscribe(IEventListener *listener)
    {
        auto findIt = std::find(subscribers.begin(), subscribers.end(),listener);
        if (findIt != subscribers.end())
        {
            subscribers.erase(findIt);
        }
        else
        {
            std::cout << "Subsciber not found..." << std::endl;
        }
    }

    // Sends event(message) to all of subscribers
    // Event publishers use this member function(method)
    void Publish(std::string_view msg) const
    {
        std::cout << "----------------" << std::endl;
        std::cout << "< Publishing new event to all subscribers... >\n";

        for (size_t i = 0; i < subscribers.size(); ++i)
        {
            subscribers[i]->OnEvent(msg);
        }
    }

private:
    std::vector<IEventListener*> subscribers;
};

// Event producer class
class EventProducer
{
public:
    // Event producer should have a reference to brokers so that they can properly send events(messages) to subscribers
    EventProducer(EventBroker *broker) : m_Broker(broker) {}

public:
    // produce an event = pass the event to the broker, let broker to publish the event.
    void ProduceEvent(std::string_view msg) { m_Broker->Publish(msg); }

private:
    EventBroker *m_Broker;
};

int main()
{
    // Broker and Producer
    EventBroker broker;
    EventProducer producer{ &broker };

    // Consumer 1, 2 subscribes to the broker
    EventConsumer consumer1 {"consumer1"};
    EventConsumer consumer2 {"consumer2"};
    broker.Subscribe(&consumer1);
    broker.Subscribe(&consumer2);

    // Producer creates an event "Hello world!"
    producer.ProduceEvent("Hello world!");

    // New consumer 3 has appeared, subscribes
    EventConsumer consumer3 {"consumer3"};
    broker.Subscribe(&consumer3);
    broker.Unsubscribe(&consumer2); // good bye consumer 2

    // Another event from the producer
    producer.ProduceEvent("Goodbye!");
}