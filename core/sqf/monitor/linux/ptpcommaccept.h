///////////////////////////////////////////////////////////////////////////////
//
// @@@ START COPYRIGHT @@@
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// @@@ END COPYRIGHT @@@
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PTPCOMMACCEPT_H
#define PTPCOMMACCEPT_H

#include <pthread.h>
#include "lock.h"
#include "comm.h"


class CPtpCommAccept : public CLock
                     , public CComm
{
public:

    CPtpCommAccept();
    virtual ~CPtpCommAccept();

    void commAcceptor( void );
    inline const char * getPtPPort( void ) { return ptpPort_.c_str(); }
    inline int          getPtPSocketPort( void ) { return( ptpSocketPort_ ); }
    bool isAccepting( void ) { CAutoLock lock(getLocker()); return( accepting_ ); }
    void monReqExec( void *req ); //stupid compiler and circular header files

    void processMonReqs( int sockFd );
    void processNewSock( int sockFd );
    inline void setPtPPort( char *ptpPort) { ptpPort_ = ptpPort; }  
    inline void setPtPSocketPort( int ptpSocketPort) { ptpSocketPort_ = ptpSocketPort; }
    void startAccepting( void );
    void stopAccepting( void );
    void start( void );
    void shutdownWork( void );

    typedef struct
    {
        CPtpCommAccept *this_;
        int             pendingFd_;
    } Context;

private:

    void commAcceptorSock( void );
    void connectToCommSelf( void );

    bool   accepting_;
    bool   shutdown_;
    int    ioWaitTimeout_;
    int    ioRetryCount_;
    int    ptpSock_;
    int    ptpSocketPort_;           // point-2-point socket port
    string ptpPort_;
    
    pthread_t   thread_id_;         // ptpCommAccept thread's id
    pthread_t   process_thread_id_; // ptpProcess thread's id
};

#endif
