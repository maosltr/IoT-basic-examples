..
   Copyright(c) 2006 to 2022 ZettaScale Technology and others

   This program and the accompanying materials are made available under the
   terms of the Eclipse Public License v. 2.0 which is available at
   http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
   v. 1.0 which is available at
   http://www.eclipse.org/org/documents/edl-v10.php.

   SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause

HelloWorld in a polling mode
==========

Description
***********

Implementation of a subscriber in a polling mode

Design
******

It consists of 2 units:

- publisher: publishes random messages extacted from a dictionary
- subscriber: polls until a message that matches its configuration is detected

Scenario
********

If the subscriber is a late joigner, it misses all the messages published previously to its creation

Running the example
*******************

It is recommended that you run the subscriber and publisher in separate terminals to avoid mixing the output.

