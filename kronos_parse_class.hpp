/** Copyright 2015 Daniel Santos
 *  @file     kronos_parse_class.hpp
 *  @author   Daniel Santos (dsantos)
 *  @date     04/15/2016
 *  @version  1.0
 *
 *  @brief    This is the interfaces
 *  of the Boot and Services class.
 * */
#ifndef PS4_KRONOS_PARSE_CLASS_HPP
#define PS4_KRONOS_PARSE_CLASS_HPP

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>
#include <ostream>

class Service {
 public:
  /**
   *  @brief  This is a constructor for the Service class.
   *
   *  @param  std::string service_name, std::string file_name
   * */
  Service(std::string service_name, std::string file_name);
  /**
   *  @brief  This is the operator<< ostream defined as a friend
   *
   *  @param  std::ostream& os, const Service& service
   *
   *  @return std::ostream&
   * */
  friend std::ostream& operator<< (std::ostream &os, const Service &service);
  /**
   *  @breif  Getter for the name of the services
   *
   *  @return std::string
   * */
  std::string getName() const;
  /**
   *  @breif  Getter for the start line of the service
   *
   *  @return int
   * */
  int getStartLine() const;
  /**
   *  @breif  Get a formated version of the start line
   *
   *  @return std::string
   * */
  std::string getFStartLine() const;
  /**
   *  @breif  Setter for the start line
   *
   *  @param  int start_line
   * */
  void setStartLine(int start_line);
  /**
   *  @breif  Getter for end line of the service
   *
   *  @return int
   * */
  int getEndLine() const;
  /**
   *  @breif  Get the formated version of the end line
   *
   *  @return std::string
   * */
  std::string getFEndLine() const;
  /**
   *  @breif  Setter for end line
   *
   *  @param  int end_line
   * */
  void setEndLine(int end_line);
  /**
   *  @breif  Getter for the file name of the log
   *
   *  @return std::string
   * */
  std::string getFileName() const;
  /**
   *  @breif  Getter for the duration with a suffix
   *  of 'ms'.
   *
   *  @return std::string
   * */
  std::string getDuration() const;
  /**
   *  @breif  Setter for the duration. It is a string
   *  because it appear in the log file, so there is
   *  nothing to calculate.
   *
   *  @param  std::string duration
   * */
  void setDuration(std::string duration);
  /**
   *  @breif  Helper function to change the state of
   *  the member completed. If called, it will make
   *  the service as completed.
   * */
  void completed();
  /**
   *  @breif  Helper function to change the state of
   *  the member started. If called, it will make the
   *  service as started.
   * */
  void started();
  /**
   *  @breif  Getter for the completed member
   *
   *  @return bool
   * */
  bool isComplete() const;
  /**
   *  @breif  Getter fot the started member
   *
   *  @return bool
   * */
  bool isStarted() const;

 private:
  std::string name_;        //  < Name of the sevice
  std::string file_name_;   //  < Name of the file
  int start_line_;          //  < Start line of the service
  int end_line_;            //  < End line of the service
  std::string duration_;    //  < Duration of service to start
  bool completed_;          //  < True if the service is completed
  bool started_;            //  < True if the service started
};

class Boot {
 public:
  /**
   *  @breif  A constructor of the Boot class
   *
   *  @param std::string file_name
   * */
  explicit Boot(std::string file_name);
  /**
   *  @breif  Another constructor of the Boot class
   *
   *  @param  std::string file_name, int start_line,
   *          int end_line, boost::posix_time::ptime start_time,
   *          boost::posix_time::time_duration duration
   * */
  Boot(std::string file_name, int start_line, int end_line,
       boost::posix_time::ptime start_time,
       boost::posix_time::time_duration duration);
  /**
   *  @brief  This is the operator<< ostream defined as a friend
   *
   *  @param  std::ostream& os, const Boot& boot
   *
   *  @return std::ostream&
   * */
  friend std::ostream& operator<< (std::ostream &os, Boot &boot);
  /**
   *  @breif  Getter for the file name of the log
   *
   *  @return std::string
   * */
  std::string getFileName() const;
  /**
   *  @breif  Setter for the file name of the log
   *
   *  @param std::string file_name
   * */
  void setFileName(std::string file_name);
  /**
   *  @brief  This is a helper function that construct
   *  the map from a array of strings containing the
   *  services name.
   * */
  void buildMap();
  /**
   *  @breif  Getter for the start line of the service
   *
   *  @return int
   * */
  int getStartLine() const;
  /**
   *  @breif  Setter for the start line
   *
   *  @param  int start_line
   * */
  void setStartLine(int line);
  /**
   *  @breif  Getter for end line of the service
   *
   *  @return int
   * */
  int getEndLine() const;
  /**
   *  @breif  Setter for end line
   *
   *  @param  int line
   * */
  void setEndLine(int line);
  /**
   *  @breif  Getter for the duration member
   *
   *  @return boost::posix_time::time_duration
   * */
  boost::posix_time::time_duration getDuration() const;
  /**
   *  @breif  Getter for a formated duration with a suffix
   *  of 'ms'.
   *
   *  @return std::string
   * */
  std::string getFDuration() const;
  /**
   *  @breif  Setter for the duration.
   *
   *  @param  boost::posix_time::time_duration duration
   * */
  void setDuration(boost::posix_time::time_duration duration);
  /**
   *  @brief  Getter for the date member
   *
   *  @return boost::gregorian::date
   * */
  boost::gregorian::date getDate() const;
  /**
   *  @brief  Setter for the date member
   *
   *  @param  boost::gregorian::date date
   * */
  void setDate(boost::gregorian::date date);
  /**
   *  @brief  Getter for the start_time member
   *
   *  @return boost::posix_time::ptime
   * */
  boost::posix_time::ptime getStartTime() const;
  /**
   *  @brief  Setter for the start_time member
   *
   *  @param  boost::posix_time::ptime start_time
   * */
  void setStartTime(boost::posix_time::ptime start_time);
  /**
   *  @brief  Getter for the end_time member
   *
   *  @return boost::posix_time::ptime
   * */
  boost::posix_time::ptime getEndTime() const;
  /**
   *  @brief  Setter for the end_time member
   *
   *  @param  boost::posix_time::ptime end_time
   * */
  void setEndTime(boost::posix_time::ptime end_time);
  /**
   *  @breif  Getter for the completed member
   *
   *  @return bool
   * */
  bool isComplete() const;
  /**
   *  @brief  This helper method iterate throguh
   *  all the services an check if they are completed.
   *  It returns the new state of the completed member.
   *
   *  @return bool
   * */
  bool checkComplete();
  /**
   *  @breif  Helper function to change the state of
   *  the member completed. If called, it will make
   *  the boot as completed.
   * */
  void completed();
  /**
   *  @brief  Get a service from a given name as arguement
   *
   *  @param  std::string service_name
   *
   *  @return Service&
   * */
  Service& getService(std::string service_name);
  /**
   *  @brief  This return a iterator to the begin of the map
   *
   *  @return std::map<std::string, Service>::iterator
   * */
  std::map<std::string, Service>::iterator begin();
  /**
   *  @brief  This return a iterator to the end of the map
   *
   *  @return std::map<std::string, Service>::iterator
   * */
  std::map<std::string, Service>::iterator end();

 private:
  int start_line_;                              //  < Start line of the boot
  int end_line_;                                //  < End line of the boot
  boost::gregorian::date date_;                 //  < The date of the boot
  boost::posix_time::time_duration duration_;   //  < Duration of the boot
  boost::posix_time::ptime start_time_;         //  < Start time of the boot
  boost::posix_time::ptime end_time_;           //  < End time of the boot
  bool completed_;                              //  < Hold state of the boot
  std::string file_name_;                       //  < File name of the input log
  std::map<std::string, Service> services_;     //  < A map of services
};

#endif  // PS4_KRONOS_PARSE_CLASS_HPP
