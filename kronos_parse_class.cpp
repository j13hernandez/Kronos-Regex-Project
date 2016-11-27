/** Copyright 2015 Daniel Santos
 *  @file     kronos_parse_class.cpp
 *  @author   Daniel Santos (dsantos)
 *  @date     04/15/2016
 *  @version  1.0
 *
 *  @brief    This is the implementation
 *  of the Boot and Services class.
 * */
#include "kronos_parse_class.hpp"
#include <sstream>
#include <utility>
#include <map>
#include <string>
#include <vector>

Service::Service(std::string service_name, std::string file_name) :
    name_(service_name), file_name_(file_name), completed_(false),
    started_(false) {
  // Initialize of the passed arguments
}
std::string Service::getName() const {
  return name_;
}
int Service::getStartLine() const {
  return start_line_;
}
std::string Service::getFStartLine() const {
  std::stringstream ss;
  if (started_)   // If service stated the output is different
    ss << start_line_ << "(" << getFileName() << ")";
  else
    ss << "Not started(" << getFileName() << ")";
  return ss.str();
}
std::string Service::getFileName() const {
  return file_name_;
}
void Service::setStartLine(int start_line) {
  this->start_line_ = start_line;
}
int Service::getEndLine() const {
  return end_line_;
}
std::string Service::getFEndLine() const {
  std::stringstream ss;
  if (completed_)  // If service completed the output is different
    ss << end_line_ << "(" << getFileName() << ")";
  else
    ss << "Not started(" << getFileName() << ")";
  return ss.str();
}
void Service::setEndLine(int end_line) {
  this->end_line_ = end_line;
}
std::string Service::getDuration() const {
  std::stringstream ss;
  ss << duration_ << "ms";  // Add a suffix to the duration
  return ss.str();
}
void Service::started() {
  started_ = true;
}
void Service::completed() {
  completed_ = true;
}
void Service::setDuration(std::string duration) {
  this->duration_ = duration;
}
bool Service::isComplete() const {
  return completed_;
}
bool Service::isStarted() const {
  return started_;
}
std::ostream& operator<<(std::ostream &os, const Service &service) {
  // Format the out of the Service object to be printable
  os << "\t" << service.getName() << std::endl
     << "\t\tStart: " << service.getFStartLine() << std::endl
     << "\t\tCompleted: " << service.getFEndLine() << std::endl
     << "\t\tElapsed Time: " << (service.isStarted() ?
                                 service.getDuration() : "");
  return os;
}
Boot::Boot(std::string file_name) : file_name_(file_name), completed_(false) {
  buildMap();  // Build the map with this helper function
}
Boot::Boot(std::string file_name, int start_line, int end_line,
    boost::posix_time::ptime start_time,
    boost::posix_time::time_duration duration) :
    file_name_(file_name), start_line_(start_line), end_line_(end_line),
    start_time_(start_time),
    duration_(duration), completed_(false) {
  // Initialize all the passed arguments
  buildMap();  // Build the map with this helper function
}
std::map<std::string, Service>::iterator Boot::begin() {
  return services_.begin();
}
void Boot::buildMap() {
  // This is the list of all the services name which are used to
  // construct the map
  std::string SERVICES_NAME_[24] = {
      "Logging", "DatabaseInitialize", "MessagingService",
      "HealthMonitorService", "Persistence", "ConfigurationService",
      "LandingPadService", "PortConfigurationService", "CacheService",
      "ThemingService", "StagingService", "DeviceIOService", "BellService",
      "GateService", "ReaderDataService", "BiometricService", "StateManager",
      "OfflineSmartviewService", "AVFeedbackService", "DatabaseThreads",
      "SoftLoadService", "WATCHDOG", "ProtocolService", "DiagnosticsService"
  };
  // Here we the list from above to construct the map
  for (int i = 0; i < 24; ++i)
    services_.insert(
        std::pair<std::string, Service>(
            SERVICES_NAME_[i], Service(SERVICES_NAME_[i], file_name_)));
}
std::map<std::string, Service>::iterator Boot::end() {
  return services_.end();
}
std::ostream& operator<< (std::ostream& os, Boot& boot) {
  boot.checkComplete();  // Here we check if the boot is completed
  // Get the begin iterator fo the map
  std::map<std::string, Service>::iterator it = boot.begin();
  std::vector<Service> incompleted_services;  // A list of incompleted services

  // Start formatting the output
  os << "=== Device boot ===" << std::endl
     << boot.getStartLine() << "(" << boot.getFileName() << "): "
     << boot.getStartTime() << " Boot Start" << std::endl;
  if (boot.isComplete())  // If boot is completed the output is different
    os << boot.getEndLine() << "(" << boot.getFileName() << "): "
       << boot.getEndTime() << " Boot Completed" << std::endl
       << "\tBoot Time: " << boot.getFDuration() << std::endl;
  else
    os << "**** Incomplete boot ****" << std::endl;

  // Here we print the services
  os << std::endl << "Services" << std::endl;
  for (; it != boot.end(); ++it) {
    // Check if the service is not complete
    if (!(*it).second.isComplete())
      // If so, add it to the list
      incompleted_services.push_back((*it).second);
    os << (*it).second << std::endl;
  }
  // If the list of incomplete is not 0, we output it
  if (incompleted_services.size()) {
    os << std::endl << "\t**** Services not succesfully started: ";
    for (int i = 0; i < incompleted_services.size(); i++) {
      os << incompleted_services.at(i).getName();
      if (i != incompleted_services.size()-1) os << ", ";
    }
    os << std::endl;  // Add a new line to the end of the boot output
  }
  return os;
}
void Boot::completed() {
  completed_ = true;  // Make the completed member = true when called
}
std::string Boot::getFileName() const {
  return file_name_;
}
void Boot::setFileName(std::string file_name) {
  this->file_name_ = file_name;
}
int Boot::getStartLine() const {
  return start_line_;
}
void Boot::setStartLine(int start_line) {
  this->start_line_ = start_line;
}
int Boot::getEndLine() const {
  return end_line_;
}
void Boot::setEndLine(int end_line) {
  this->end_line_ = end_line;
}
boost::posix_time::time_duration Boot::getDuration() const {
  return duration_;
}
std::string Boot::getFDuration() const {
  std::stringstream ss;
  // Add a suffix to the duration
  ss << getDuration().total_milliseconds() << "ms";
  return ss.str();
}
void Boot::setDuration(boost::posix_time::time_duration duration) {
  this->duration_ = duration;
}
boost::gregorian::date Boot::getDate() const {
  return date_;
}
void Boot::setDate(boost::gregorian::date date) {
  this->date_ = date;
}
Service& Boot::getService(std::string key) {
  return services_.at(key);  // Gets a services with a given key from the map
}
boost::posix_time::ptime Boot::getStartTime() const {
  return start_time_;
}
void Boot::setStartTime(boost::posix_time::ptime start_time) {
  this->start_time_ = start_time;
}
boost::posix_time::ptime Boot::getEndTime() const {
  return end_time_;
}
void Boot::setEndTime(boost::posix_time::ptime end_time) {
  this->end_time_ = end_time;
}
bool Boot::isComplete() const {
  return completed_;
}
bool Boot::checkComplete() {
  bool is_completed = true;  // A temp variable to be returned
  if (!completed_) {  // If the state is not complete, avoid the check
    std::map<std::string, Service>::const_iterator it = services_.begin();
    while (it != services_.end()) {  // Iterator throught the map
      Service current = (*it).second;
      // Change to false if find one not completed
      if (!current.isComplete()) is_completed = false;
      ++it;
    }
    completed_ = is_completed;  // Change the state of completed_ member
  }
  return completed_;
}
