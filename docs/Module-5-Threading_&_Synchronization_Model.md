1. Purpose of This Module

This module defines:

How multiple threads coexist without ever stepping on each other

Specifically:

Qt UI thread

ASIO networking thread

Shared game state flow

This module does not:

Define chess rules

Define network protocol

Define UI layout

It defines who runs where and how they talk.

2. The Golden Rule (Absolute)

The Qt UI thread must NEVER block.
The ASIO thread must NEVER touch Qt widgets.

Every decision in this module flows from that.

3. Threads in Chessly
3.1 UI Thread (Qt Main Thread)

Responsibilities:

Event handling

Rendering

User interaction

Status bar updates

Constraints:

Must remain responsive at all times

Cannot wait on network

Cannot lock long mutexes

3.2 Networking Thread (ASIO)

Responsibilities:

Socket I/O

Message send / receive

Connection state changes

Error detection

Constraints:

No UI calls

No long blocking operations

Runs independently of frame rate

4. Ownership of Data (Critical Concept)
Single-Writer Rule

Each piece of data must have one clear owner:

Engine state → owned by UI thread

Socket state → owned by network thread

Messages → transferred via queues

No shared mutable ownership.

5. Communication Model (Message Passing Only)

Threads communicate only by passing messages.

Never by:

Shared raw pointers

Direct function calls across threads

Shared mutable structures

Message passing ensures:

Clear flow

Debuggable behavior

No deadlocks

6. Directional Message Channels
6.1 Network → UI

Used for:

Incoming chat messages

Incoming chess moves

Connection / error events

Opponent disconnects

Flow:

ASIO thread → queue → UI thread processes

6.2 UI → Network

Used for:

Outgoing chess moves

Chat messages

Host / join commands

Disconnect requests

Flow:

UI thread → queue → ASIO thread processes

7. Synchronization Strategy
Minimal Locking Philosophy

Locks only protect queues

Locks are held briefly

No nested locks

Preferred approach:

Lock-free where possible

Otherwise, mutex + condition variable

8. Processing Incoming Messages (UI Side)

UI thread:

Periodically checks message queue

Processes messages one-by-one

Applies effects:

Update engine

Update UI

Update status bar

No background thread mutates engine state.

9. Processing Outgoing Messages (Network Side)

Network thread:

Waits for outgoing messages

Serializes and sends them

Handles failures gracefully

UI never waits for send completion.

10. Thread Lifecycle Management
Startup

UI thread starts first

Network thread starts only when needed

Thread creation is explicit

Shutdown

UI signals shutdown intent

Network thread stops ASIO loop

All sockets closed cleanly

Thread joins safely

No forced termination.

11. Error Propagation Model

Errors flow:

Network thread → UI thread → user

Network thread:

Detects error

Emits structured event

Stops further network activity

UI thread:

Displays message

Resets state

Re-enables buttons

12. Turn Enforcement & Race Safety

To avoid race conditions:

UI disables input when not player’s turn

Incoming move is processed atomically

No two moves are processed concurrently

This guarantees:

No double moves

No desync

13. Long Operations Policy

No long-running tasks on:

UI thread

Network thread

If needed (future):

Dedicated worker thread

Strict message passing

For now, chess logic is fast enough.

15. Debugging Strategy

Good threading design enables:

Logging per-thread

Reproducible bugs

Deterministic state changes

Every message processed should be loggable.

16. Exit Criteria (Module 5 Complete)

This module is complete when:

✔ UI never freezes
✔ Network never blocks UI
✔ No shared mutable state
✔ Clean startup and shutdown
✔ Errors propagate predictably
✔ Same behavior on Linux & Windows