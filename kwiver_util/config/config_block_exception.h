/*ckwg +29
 * Copyright 2013-2014 by Kitware, Inc.
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

/**
 * \file
 * \brief config_block related exceptions interface
 */

#ifndef KWIVER_CONFIG_EXCEPTIONS_CONFIG_H
#define KWIVER_CONFIG_EXCEPTIONS_CONFIG_H

#include <config/kwiver_config_export.h>
#include <kwiver-config.h>

#include "config_block_types.h"

#include <exception>
#include <string>

namespace kwiver {

// ------------------------------------------------------------------
/**
 * \brief The base class for all exceptions thrown from \ref config_block
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT config_block_exception :
  public std::exception
{
public:
  /// Constructor.
  config_block_exception() KWIVER_NOTHROW;
  /// Destructor.
  virtual ~config_block_exception() KWIVER_NOTHROW;

  /// Description of the exception
  /**
   * \returns A string describing what went wrong.
   */
  char const* what() const KWIVER_NOTHROW;


protected:
  /// descriptive string as to what happened to cause the exception.
  std::string m_what;

};

// ------------------------------------------------------------------
/**
 * \brief The inner exception thrown when casting fails.
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT bad_config_block_cast :
  public config_block_exception
{
public:
  /**
   * \brief Constructor.
   * \param reason The reason for the bad cast.
   */
  bad_config_block_cast( std::string const& reason ) KWIVER_NOTHROW;
  /// Destructor.
  virtual ~bad_config_block_cast() KWIVER_NOTHROW;
};

// ------------------------------------------------------------------
/**
 * \brief Thrown when a value cannot be converted to the requested type.
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT bad_config_block_cast_exception :
  public config_block_exception
{
public:
  /**
   * \brief Constructor.
   *
   * \param key The key that was requested.
   * \param value The value that was failed to cast.
   * \param type The type that was requested.
   * \param reason The reason for the bad cast.
   */
  bad_config_block_cast_exception( config_block_key_t const&    key,
                                   config_block_value_t const&  value,
                                   std::string const&           type,
                                   std::string const&           reason ) KWIVER_NOTHROW;
  /// Destructor.
  virtual ~bad_config_block_cast_exception() KWIVER_NOTHROW;

  /// The requested key name.
  config_block_key_t const m_key;
  /// The value of the requested key.
  config_block_value_t const m_value;
  /// The type requested for the cast.
  std::string const m_type;
  /// The reason for the failed cast.
  std::string const m_reason;
};

// ------------------------------------------------------------------
/**
 * \brief Thrown when a value is requested for a value which does not exist.
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT no_such_configuration_value_exception :
  public config_block_exception
{
public:
  /**
   * \brief Constructor.
   * \param key The key that was requested from the configuration.
   */
  no_such_configuration_value_exception( config_block_key_t const& key ) KWIVER_NOTHROW;
  /// Destructor.
  virtual ~no_such_configuration_value_exception() KWIVER_NOTHROW;

  /// The requested key name.
  config_block_key_t const m_key;
};

// ------------------------------------------------------------------
/**
 * \brief Thrown when a value is set but is marked as read-only.
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT set_on_read_only_value_exception :
  public config_block_exception
{
public:
  /**
   * \brief Constructor.
   *
   * \param key The key that was requested from the configuration.
   * \param value The current read-only value of \p key.
   * \param new_value The value that was attempted to be set.
   */
  set_on_read_only_value_exception( config_block_key_t const&   key,
                                    config_block_value_t const& value,
                                    config_block_value_t const& new_value ) KWIVER_NOTHROW;
  /**
   * \brief Destructor.
   */
  virtual ~set_on_read_only_value_exception() KWIVER_NOTHROW;

  /// The requested key name.
  config_block_key_t const m_key;
  /// The existing value.
  config_block_value_t const m_value;
  /// The new value.
  config_block_value_t const m_new_value;
};

// ------------------------------------------------------------------
/**
 * \brief Thrown when a value is unset but is marked as read-only.
 * \ingroup exceptions
 */
class KWIVER_CONFIG_EXPORT unset_on_read_only_value_exception :
  public config_block_exception
{
public:
  /**
   * \brief Constructor.
   *
   * \param key The key that was requested from the configuration.
   * \param value The current value for \p key.
   */
  unset_on_read_only_value_exception( config_block_key_t const&   key,
                                      config_block_value_t const& value ) KWIVER_NOTHROW;
  /**
   * \brief Destructor.
   */
  virtual ~unset_on_read_only_value_exception() KWIVER_NOTHROW;

  /// The requested key name.
  config_block_key_t const m_key;
  /// The existing value.
  config_block_value_t const m_value;
};


// ------------------------------------------------------------------
/// Base config_io exception class
class KWIVER_CONFIG_EXPORT config_block_io_exception :
  public config_block_exception
{
public:
  ///Constructor
  /**
   * \param file_path The path to the file related to this error.
   * \param reason    Reason for the exception.
   */
  config_block_io_exception( config_path_t const& file_path,
                             std::string const&   reason ) KWIVER_NOTHROW;
  /// Deconstructor
  virtual ~config_block_io_exception() KWIVER_NOTHROW;

  /// Path to file this exception revolves around.
  config_path_t m_file_path;
  /// Reason for exception
  std::string m_reason;
};


// ------------------------------------------------------------------
/// Exception for when a file could not be found
class KWIVER_CONFIG_EXPORT file_not_found_exception :
  public config_block_io_exception
{
public:
  /// Constructor
  /**
   * \param file_path The file path that was looked for.
   * \param reason    The reason the file wasn't found.
   */
  file_not_found_exception( config_path_t const&  file_path,
                            std::string const&    reason ) KWIVER_NOTHROW;
  /// Deconstructor
  virtual ~file_not_found_exception() KWIVER_NOTHROW;
};


// ------------------------------------------------------------------
/// Exception for when a file could not be read for whatever reason.
class KWIVER_CONFIG_EXPORT file_not_read_exception :
  public config_block_io_exception
{
public:
  ///Constructor
  /**
   * \param file_path The file path on which the read was attempted.
   * \param reason    The reason for the read exception.
   */
  file_not_read_exception( config_path_t const& file_path,
                           std::string const&   reason ) KWIVER_NOTHROW;
  /// Deconstructor
  virtual ~file_not_read_exception() KWIVER_NOTHROW;
};


// ------------------------------------------------------------------
/// Exception for when a file could not be parsed after being read in
class KWIVER_CONFIG_EXPORT file_not_parsed_exception :
  public config_block_io_exception
{
public:
  /// Constructor
  /**
   * \param file_path The file path to which the parsing exception occurred.
   * \param reason    The reason for the parsing exception.
   */
  file_not_parsed_exception( config_path_t const& file_path,
                             std::string const&   reason ) KWIVER_NOTHROW;
  /// Deconstructor
  virtual ~file_not_parsed_exception() KWIVER_NOTHROW;
};


// ------------------------------------------------------------------
/// Exception for when a file was not able to be written
class KWIVER_CONFIG_EXPORT file_write_exception :
  public config_block_io_exception
{
public:
  /// Constructor
  /**
   * \param file_path The file path to which the write was attempted.
   * \param reason    The reason for the write exception
   */
  file_write_exception( config_path_t const&  file_path,
                        std::string const&    reason ) KWIVER_NOTHROW;
  /// Deconstructor
  virtual ~file_write_exception() KWIVER_NOTHROW;
};


} // end namespace

#endif // KWIVER_CONFIG_EXPORT