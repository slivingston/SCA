/*****************************************************************************
* Product: QF/C
* Last Updated for Version: 3.3.00
* Date of the Last Update:  Jan 22, 2007
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2007 Quantum Leaps, LLC. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Alternatively, this software may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GPL and are specifically designed for licensees interested in
* retaining the proprietary status of their code.
*
* Contact information:
* Quantum Leaps Web site:  http://www.quantum-leaps.com
* e-mail:                  sales@quantum-leaps.com
*****************************************************************************/
#include "qf_pkg.h"
#include "qassert.h"

Q_DEFINE_THIS_MODULE(qf_pool)

/*..........................................................................*/
/** \ingroup qf
* \file qf_pool.c
* \brief QF_pool_[] definition and QF_poolInit() implementation.
*/

/* Package-scope objects ---------------------------------------------------*/
QF_EPOOL_TYPE_ QF_pool_[3];                       /* allocate 3 event pools */
uint8_t QF_maxPool_;                   /* number of initialized event pools */

/*..........................................................................*/
void QF_poolInit(void *poolSto, uint32_t poolSize, QEventSize evtSize) {
                      /* cannot exceed the number of available memory pools */
    Q_REQUIRE(QF_maxPool_ < (uint8_t)Q_DIM(QF_pool_));
            /* please initialize event pools in ascending order of evtSize: */
    Q_REQUIRE((QF_maxPool_ == 0)
              || (QF_EPOOL_EVENT_SIZE_(QF_pool_[QF_maxPool_ - 1]) < evtSize));
                /* perfom the platform-dependent initialization of the pool */
    QF_EPOOL_INIT_(QF_pool_[QF_maxPool_], poolSto, poolSize, evtSize);
    ++QF_maxPool_;                                         /* one more pool */
}
