
Writer listener + Reader in a polling mode
==========

Description
***********

Implementation of a publisher in listening mode against a subscriber in a polling mode

Design
******

It consists of 2 units:

- publisher: publishes random messages extacted from a dictionary (if a subscriber is discovered)
- subscriber: polls until a message that matches its configuration is detected

Scenario
********

If the subscriber is a late joigner, it still receive the topic as the topic is published only when a subscriber is discovered

Running the example
*******************

It is recommended that you run the subscriber and publisher in separate terminals to avoid mixing the output.

