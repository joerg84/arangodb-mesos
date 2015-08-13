///////////////////////////////////////////////////////////////////////////////
/// @brief global defines and configuration objects
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2015 ArangoDB GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2015, ArangoDB GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "Global.h"

#include "CaretakerStandalone.h"

using namespace arangodb;
using namespace std;

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief caretaker
////////////////////////////////////////////////////////////////////////////////

static Caretaker* CARETAKER = nullptr;

////////////////////////////////////////////////////////////////////////////////
/// @brief ArangoDB manager
////////////////////////////////////////////////////////////////////////////////

static ArangoManager* MANAGER = nullptr;

////////////////////////////////////////////////////////////////////////////////
/// @brief state
////////////////////////////////////////////////////////////////////////////////

static ArangoState* STATE = nullptr;

////////////////////////////////////////////////////////////////////////////////
/// @brief scheduler
////////////////////////////////////////////////////////////////////////////////

static ArangoScheduler* SCHEDULER = nullptr;

////////////////////////////////////////////////////////////////////////////////
/// @brief mode
////////////////////////////////////////////////////////////////////////////////

static OperationMode MODE = OperationMode::STANDALONE;

////////////////////////////////////////////////////////////////////////////////
/// @brief asynchronous replication flag
////////////////////////////////////////////////////////////////////////////////

static bool ASYNC_REPL = false;

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for an agent, mesos string specification
////////////////////////////////////////////////////////////////////////////////

static std::string MINRESOURCESAGENT = "mem:512(*); cpus:0.2(*); disk:512(*)";

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for a DBServer, mesos string specification
////////////////////////////////////////////////////////////////////////////////

static std::string MINRESOURCESDBSERVER 
  = "mem:1024(*); cpus:1(*); disk:1024(*)";

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for an coordinator, mesos string specification
////////////////////////////////////////////////////////////////////////////////

static std::string MINRESOURCESCOORDINATOR 
  = "mem:1024(*); cpus:1(*); disk:1024(*)";

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of agents
////////////////////////////////////////////////////////////////////////////////

static int NRAGENTS = 1;

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of DBservers
////////////////////////////////////////////////////////////////////////////////

static int NRDBSERVERS = 2;

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of coordinators
////////////////////////////////////////////////////////////////////////////////

static int NRCOORDINATORS = 1;

////////////////////////////////////////////////////////////////////////////////
/// @brief role
////////////////////////////////////////////////////////////////////////////////

static string ROLE = "arangodb";

////////////////////////////////////////////////////////////////////////////////
/// @brief frameworkName
////////////////////////////////////////////////////////////////////////////////

static string FRAMEWORK_NAME = "cluster";

////////////////////////////////////////////////////////////////////////////////
/// @brief principal
////////////////////////////////////////////////////////////////////////////////

static string PRINCIPAL = "arangodb";

////////////////////////////////////////////////////////////////////////////////
/// @brief master url
////////////////////////////////////////////////////////////////////////////////

static string MASTER_URL = "http://master.mesos:5050/";

////////////////////////////////////////////////////////////////////////////////
/// @brief volume path
////////////////////////////////////////////////////////////////////////////////

static string VOLUME_PATH = "/tmp";

// -----------------------------------------------------------------------------
// --SECTION--                                             static public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief caretaker
////////////////////////////////////////////////////////////////////////////////

Caretaker& Global::caretaker () {
  return *CARETAKER;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the caretaker
////////////////////////////////////////////////////////////////////////////////

void Global::setCaretaker (Caretaker* caretaker) {
  CARETAKER = caretaker;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief manager
////////////////////////////////////////////////////////////////////////////////

ArangoManager& Global::manager () {
  return *MANAGER;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the manager
////////////////////////////////////////////////////////////////////////////////

void Global::setManager (ArangoManager* manager) {
  MANAGER = manager;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief state
////////////////////////////////////////////////////////////////////////////////

ArangoState& Global::state () {
  return *STATE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the state
////////////////////////////////////////////////////////////////////////////////

void Global::setState (ArangoState* state) {
  STATE = state;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief scheduler
////////////////////////////////////////////////////////////////////////////////

ArangoScheduler& Global::scheduler () {
  return *SCHEDULER;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the scheduler
////////////////////////////////////////////////////////////////////////////////

void Global::setScheduler (ArangoScheduler* scheduler) {
  SCHEDULER = scheduler;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for an agent, mesos string specification
////////////////////////////////////////////////////////////////////////////////

std::string Global::minResourcesAgent () {
  return MINRESOURCESAGENT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the minimal resources for an agent
////////////////////////////////////////////////////////////////////////////////

void Global::setMinResourcesAgent (std::string val) {
  MINRESOURCESAGENT = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for a DBserver, mesos string specification
////////////////////////////////////////////////////////////////////////////////

std::string Global::minResourcesDBServer () {
  return MINRESOURCESDBSERVER;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the role
////////////////////////////////////////////////////////////////////////////////

void Global::setMinResourcesDBServer (std::string val) {
  MINRESOURCESDBSERVER = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief minimal resources for a coordinator, mesos string specification
////////////////////////////////////////////////////////////////////////////////

std::string Global::minResourcesCoordinator () {
  return MINRESOURCESCOORDINATOR;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the minimal resources for a coordinator
////////////////////////////////////////////////////////////////////////////////

void Global::setMinResourcesCoordinator (std::string val) {
  MINRESOURCESCOORDINATOR = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of agents
////////////////////////////////////////////////////////////////////////////////

int Global::nrAgents () {
  return NRAGENTS;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the initial number of agents
////////////////////////////////////////////////////////////////////////////////

void Global::setNrAgents (int val) {
  NRAGENTS = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of DBservers
////////////////////////////////////////////////////////////////////////////////

int Global::nrDBServers () {
  return NRDBSERVERS;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the initial number of DBservers
////////////////////////////////////////////////////////////////////////////////

void Global::setNrDBServers (int val) {
  NRDBSERVERS = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief initial number of coordinators
////////////////////////////////////////////////////////////////////////////////

int Global::nrCoordinators () {
  return NRCOORDINATORS;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the initial number of coordinators
////////////////////////////////////////////////////////////////////////////////

void Global::setNrCoordinators (int val) {
  NRCOORDINATORS = val;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief mode
////////////////////////////////////////////////////////////////////////////////

OperationMode Global::mode () {
  return MODE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief mode in lower case
////////////////////////////////////////////////////////////////////////////////

string Global::modeLC () {
  switch (Global::mode()) {
    case OperationMode::STANDALONE:
      return "standalone";
      break;

    case OperationMode::CLUSTER:
      return "cluster";
      break;
  }

  return "unknown";
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the mode
////////////////////////////////////////////////////////////////////////////////

void Global::setMode (OperationMode mode) {
  MODE = mode;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief asynchronous replication flag
////////////////////////////////////////////////////////////////////////////////

bool Global::asyncReplication () {
  return ASYNC_REPL;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the asynchronous replication flag
////////////////////////////////////////////////////////////////////////////////

void Global::setAsyncReplication (bool flag) {
  ASYNC_REPL = flag;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief role
////////////////////////////////////////////////////////////////////////////////

string Global::role () {
  return ROLE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the role
////////////////////////////////////////////////////////////////////////////////

void Global::setRole (const std::string& role) {
  ROLE = role;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief frameworkName
////////////////////////////////////////////////////////////////////////////////

string Global::frameworkName () {
  return FRAMEWORK_NAME;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the frameworkName
////////////////////////////////////////////////////////////////////////////////

void Global::setFrameworkName (const std::string& frameworkName) {
  FRAMEWORK_NAME = frameworkName;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief principal
////////////////////////////////////////////////////////////////////////////////

#if MESOS_PRINCIPAL

mesos::Resource::ReservationInfo Global::principal () {
  mesos::Resource::ReservationInfo reservation;
  reservation.set_principal(PRINCIPAL);

  return reservation;
}

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the principal
////////////////////////////////////////////////////////////////////////////////

void Global::setPrincipal (const std::string& principal) {
  PRINCIPAL = principal;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief master url
////////////////////////////////////////////////////////////////////////////////

const string& Global::masterUrl () {
  return MASTER_URL;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the master url
////////////////////////////////////////////////////////////////////////////////

void Global::setMasterUrl (const std::string& url) {
  MASTER_URL = url;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief volume path
////////////////////////////////////////////////////////////////////////////////

const std::string& Global::volumePath () {
  return VOLUME_PATH;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sets the volume path
////////////////////////////////////////////////////////////////////////////////

void Global::setVolumePath (const std::string& path) {
  VOLUME_PATH = path;
}

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------
