/*ckwg +5
 * Copyright 2011-2012 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include <vistk/pipeline/stamp.h>

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/module.hpp>

/**
 * \file stamp.cxx
 *
 * \brief Python bindings for \link vistk::stamp\endlink.
 */

using namespace boost::python;

static bool stamp_eq(vistk::stamp_t const& self, vistk::stamp_t const& other);
static bool stamp_lt(vistk::stamp_t const& self, vistk::stamp_t const& other);

BOOST_PYTHON_MODULE(stamp)
{
  def("new_stamp", &vistk::stamp::new_stamp
    , "Creates a new stamp.");
  def("incremented_stamp", &vistk::stamp::incremented_stamp
    , (arg("stamp"))
    , "Creates a stamp that is greater than the given stamp.");

  class_<vistk::stamp_t>("Stamp"
    , "An identifier to help synchronize data within the pipeline."
    , no_init)
    .def("__eq__", stamp_eq)
    .def("__lt__", stamp_lt)
  ;
}

bool
stamp_eq(vistk::stamp_t const& self, vistk::stamp_t const& other)
{
  return (*self == *other);
}

bool
stamp_lt(vistk::stamp_t const& self, vistk::stamp_t const& other)
{
  return (*self < *other);
}
