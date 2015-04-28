/*ckwg +29
 * Copyright 2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "kwiver_logger_factory.h"


namespace kwiver {
namespace logger_ns {

class log4css_logger :
  public kwiver_logger
{
public:
  log4css_logger( logger_ns::logger_factory_default* p, const char* const name )
    : kwiver_logger( p, name ),
    m_loggerImpl( ::log4cxx::Logger::getLogger( realm ) )
  {  }


  // Check to see if level is enabled
  virtual bool is_fatal_enabled() const { return this->m_loggerImpl->isFatalEnabled(); }
  virtual bool is_error_enabled() const { return this->m_loggerImpl->isErrorEnabled(); }
  virtual bool is_warn_enabled() const { return this->m_loggerImpl->isWarnEnabled(); }
  virtual bool is_info_enabled() const { return this->m_loggerImpl->isInfolEnabled(); }
  virtual bool is_debug_enabled() const { return this->m_loggerImpl->isDebugEnabled(); }
  virtual bool is_trace_enabled() const { return this->m_loggerImpl->isTraceEnabled(); }

  // ------------------------------------------------------------------
  virtual void set_level( log_level_t lev )
  {
    log4cxx::LevelPtr lvl;

    switch ( level )
    {
    case LEVEL_TRACE:
      lvl = ::log4cxx::Level::getTrace();
      break;

    case LEVEL_DEBUG:
      lvl = ::log4cxx::Level::getDebug();
      break;

    case LEVEL_INFO:
      lvl = ::log4cxx::Level::getInfo();
      break;

    case LEVEL_WARN:
      lvl = ::log4cxx::Level::getWarn();
      break;

    case LEVEL_ERROR:
      lvl = ::log4cxx::Level::getError();
      break;

    case LEVEL_FATAL:
      lvl = ::log4cxx::Level::getFatal();
      break;

    default:
      // log or throw
      break;
    } // end switch

    this->m_loggerImpl->setLevel( lvl );
  }


  // ------------------------------------------------------------------
  virtual log_level_t get_level() const
  {
    log4cxx::LevelPtr lvl = this->m_loggerImpl->getLevel();

    if ( lvl == ::log4cxx::Level::getTrace() ) { return LEVEL_TRACE; }
    if ( lvl == ::log4cxx::Level::getDebug() ) { return LEVEL_DEBUG; }
    if ( lvl == ::log4cxx::Level::getInfo() ) { return LEVEL_INFO; }
    if ( lvl == ::log4cxx::Level::getWarn() ) { return LEVEL_WARN; }
    if ( lvl == ::log4cxx::Level::getError() ) { return LEVEL_ERROR; }
    if ( lvl == ::log4cxx::Level::getFatal() ) { return LEVEL_FATAL; }
    return LEVEL_NONE;
  }


  // ------------------------------------------------------------------
  virtual void log_fatal( std::string const& msg )
  {
    this->m_loggerImpl->fatal( msg );
  }


  virtual void log_fatal( std::string const&                      msg,
                          kwiver::logger_ns::location_info const& location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->fatal( msg, cxx_location );
  }


  // ------------------------------------------------------------------
  virtual void log_error( std::string const& msg )
  {
    this->m_loggerImpl->error( msg );
  }


  virtual void log_error( std::string const&                      msg,
                          kwiver::logger_ns::location_info const& location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->error( msg, cxx_location );
  }


  // ------------------------------------------------------------------
  virtual void log_warn( std::string const& msg )
  {
    this->m_loggerImpl->warn( msg );
  }

  virtual void log_warn( std::string const&                       msg,
                         kwiver::logger_ns::location_info const&  location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->warn( msg, cxx_location );
  }

  // ------------------------------------------------------------------
  virtual void log_info( std::string const& msg )
  {
    this->m_loggerImpl->info( msg );
  }


  virtual void log_info( std::string const&                       msg,
                         kwiver::logger_ns::location_info const&  location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->info( msg, cxx_location );
  }


  // ------------------------------------------------------------------
  virtual void log_debug( std::string const& msg )
  {
    this->m_loggerImpl->debug( msg );
  }


  virtual void log_debug( std::string const&                      msg,
                          kwiver::logger_ns::location_info const& location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->debug( msg, cxx_location );
  }


  // ------------------------------------------------------------------
  virtual void log_trace( std::string const& msg )
  {
    this->m_loggerImpl->trace( msg );
  }


  virtual void log_trace( std::string const&                      msg,
                          kwiver::logger_ns::location_info const& location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    this->m_loggerImpl->trace( msg, cxx_location );
  }


  // ------------------------------------------------------------------
  virtual void log_message( log_level_t level, std::string const& msg )
  {
    log4cxx::LevelPtr lvl;

    switch ( level )
    {
    case LEVEL_TRACE: lvl = ::log4cxx::Level::getTrace();  break;
    case LEVEL_DEBUG: lvl = ::log4cxx::Level::getDebug(); break;
    case LEVEL_INFO: lvl = ::log4cxx::Level::getInfo(); break;
    case LEVEL_WARN: lvl = ::log4cxx::Level::getWarn(); break;
    case LEVEL_ERROR: lvl = ::log4cxx::Level::getError(); break;
    case LEVEL_FATAL: lvl = ::log4cxx::Level::getFatal(); break;
    default:
      break;
    } // end switch

    this->m_loggerImpl->log( lvl, msg );
  }


  virtual void log_message( log_level_t level, std::string const& msg,
                            kwiver::logger_ns::location_info const& location )
  {
    log4cxx::spi::LocationInfo cxx_location( location.get_file_name_ptr(),
                                             location.get_method_name_ptr(),
                                             location.get_line_number() );

    log4cxx::LevelPtr lvl;

    switch ( level )
    {
    case LEVEL_TRACE: lvl = ::log4cxx::Level::getTrace(); break;
    case LEVEL_DEBUG: lvl = ::log4cxx::Level::getDebug(); break;
    case LEVEL_INFO: lvl = ::log4cxx::Level::getInfo(); break;
    case LEVEL_WARN: lvl = ::log4cxx::Level::getWarn(); break;
    case LEVEL_ERROR: lvl = ::log4cxx::Level::getError(); break;
    case LEVEL_FATAL: lvl = ::log4cxx::Level::getFatal(); break;
    default:
      break;
    } // end switch

    this->m_loggerImpl->log( lvl, msg, cxx_location );
  }


  // -- extended interface --
  log4cxx::LoggerPtr get_logger_impl()
  {
    return m_loggerImpl;
  }


protected:
  log4cxx::LoggerPtr m_loggerImpl;
}; // end class


// ----------------------------------------------------------------
/** Factory for underlying logger.
 *
 * This class represents the factory for the mini_logger logging service.
 *
 * An object of this type can be created early in the program
 * execution (i.e. static initializer time), which is before the
 * initialize method is called.
 */
class log4cxx_factory
  : public kwiver_logger_factory
{
public:
  log4cxx_factory()
    : kwiver_logger_factory( "log4cxx factory" )
  { }

  virtual ~log4cxx_factory() { }

  virtual logger_handle_t get_logger( const char * const name )
  {
    return boost::make_shared<default_logger>( this, name );
  }

}; // end class logger_factory

} // end namespace
} // end namespace

// ------------------------------------------------------------------
/*
 * Shared object bootstrap function
 */
extern "C"
{
  void* KWIVER_LOGGER_EXPORT kwiver_logger_factory()
  {
    kwiver::logger_ns::log4cxx_factory* ptr =  new kwiver::logger_ns::log4cxx_factory;
    return ptr;
  }

}