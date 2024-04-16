#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "gui_types.pb.h"
// subscriber callback function
void OnReceive(const char* /*topic_name_*/, const struct eCAL::SReceiveCallbackData* data_)
{
  if (data_->size < 1) return;

  int content(static_cast<int>(static_cast<unsigned char*>(data_->buf)[0]));
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << " Received binary buffer " << content            << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << " Size         : " << data_->size                << std::endl;
  std::cout << " Id           : " << data_->id                  << std::endl;
  std::cout << " Time         : " << data_->time                << std::endl;
  std::cout << " Clock        : " << data_->clock               << std::endl;
  std::cout                                                     << std::endl;
}

void OnPerson(const char* topic_name_, const pb::People::Person& person_, const long long time_, const long long clock_)
{
  std::cout << "------------------------------------------" << std::endl;
  std::cout << " HEAD "                                     << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "topic name   : " << topic_name_             << std::endl;
  std::cout << "topic time   : " << time_                   << std::endl;
  std::cout << "topic clock  : " << clock_                  << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  std::cout << " CONTENT "                                  << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "person id    : " << person_.id()            << std::endl;
  std::cout << "person name  : " << person_.name()          << std::endl;
  std::cout << "person email : " << person_.email()         << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  std::cout                                                 << std::endl;
}

int main(int argc, char **argv)
{
  // initialize eCAL API
  eCAL::Initialize(argc, argv, "minimal_sub");

  // create a subscriber (topic name "foo", type "std::string")
  eCAL::protobuf::CSubscriber<pb::People::Person> sub("person");
  // assign callback
  // add receive callback function (_1 = topic_name, _2 = msg, _3 = time, _4 = clock, _5 = id)
  auto callback = std::bind(OnPerson, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
  sub.AddReceiveCallback(callback);

  // idle main loop
  while (eCAL::Ok()) std::this_thread::sleep_for(std::chrono::milliseconds(500));


  // finalize eCAL API
  eCAL::Finalize();
}