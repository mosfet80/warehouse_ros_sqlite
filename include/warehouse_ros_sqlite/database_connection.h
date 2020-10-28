// SPDX-License-Identifier: BSD-3-Clause

/*
 * Copyright (c) 2020, Bjarne von Horn
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BJARNE VON HORN BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <warehouse_ros/database_connection.h>
#include <warehouse_ros/message_collection.h>
#include <warehouse_ros_sqlite/utils.h>

namespace warehouse_ros_sqlite
{
class DatabaseConnection : public warehouse_ros::DatabaseConnection
{
  sqlite3_ptr db_;
  std::string uri_;

public:

  /// \brief Set database connection params.
  bool setParams(const std::string& host, unsigned, float = 60.0) override
  {
    uri_ = host;
    return true;
  }

  /// \brief Set database connection params.
  bool setTimeout(float) override
  {
    return true;
  }

  /// Setup the database connection. This call assumes setParams() has been previously called.
  /// Returns true if the connection was succesfully established.
  bool connect() override;

  /// Returns whether the database is connected.
  bool isConnected() override;

  /// \brief Drop a db and all its collections.
  /// A DbClientConnection exception will be thrown if the database is not connected.
  void dropDatabase(const std::string& db_name) override;

  /// \brief Return the ROS Message type of a given collection
  std::string messageType(const std::string& db_name, const std::string& collection_name) override;

protected:
  warehouse_ros::MessageCollectionHelper::Ptr openCollectionHelper(const std::string& db_name,
                                                                   const std::string& collection_name) override;
  void check_dbname(const std::string name) const
  {
    if (name != schema::DBName)
      throw std::runtime_error("only main supported");
  }

  void init_db();
};
}  // namespace warehouse_ros_sqlite
