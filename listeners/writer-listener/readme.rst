
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

