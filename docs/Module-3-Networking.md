1. Purpose of This Module

This module is responsible for one thing only:

Reliably connecting exactly two peers and exchanging messages between them.

It does not:

Understand chess rules

Decide whose turn it is

Update UI directly

Care about board orientation

It only:

Connects

Sends

Receives

Detects failure

2. Core Networking Model
Peer-to-Peer (Direct TCP)

One peer acts as Host

One peer acts as Joiner

Exactly one TCP connection

No spectators

No reconnections mid-game (initially)

This choice simplifies:

Synchronization

State consistency

Debugging

3. Host / Join Flow (User-Level)
Host Flow

User presses Host

Application:

Opens a TCP listening socket

Enters “Waiting for opponent” state

Status bar:

“Waiting for second player…”

First peer connects → accepted

Any additional peers → rejected with error

Join Flow

User presses Join

Enters IP address

Application attempts TCP connection

Outcomes:

Success → handshake starts

Timeout → error

Connection refused → error

No host listening → error

4. Connection State Machine (Very Important)

This module must internally track state.
No “half-connected” ambiguity.

States

Idle

Hosting

Connecting

Connected

Disconnecting

Error

State transitions must be explicit.

5. Single-Client Enforcement (Critical)

Host must enforce:

Accept first connection

Immediately reject:

Second connection

Any connection while already in-game

Rejected peers receive:

Explicit error message

Connection closed cleanly

This avoids:

Zombie sockets

UI confusion

Race conditions

6. Handshake Phase (Before Game Starts)

Once TCP connects:

Both peers must:

Exchange protocol version

Agree on roles (White / Black)

Confirm readiness

Until handshake completes:

No chess moves allowed

No chat allowed

If handshake fails → disconnect with error.

7. Error Handling Philosophy

Errors are first-class events, not exceptions.

Types of Errors

Invalid IP

Timeout

Connection refused

Host full

Protocol mismatch

Unexpected disconnect

Malformed message

Each error:

Has a clear type

Has a user-facing explanation

Forces a clean state reset

8. Network Error → UI Communication

Networking module:

Emits structured events

Never touches UI widgets

UI decides:

What message to show

What button to re-enable

Whether to auto-reset

This separation is mandatory.

9. Disconnect Detection

The module must detect:

Clean disconnects

Abrupt socket drops

Network stalls (timeouts)

When detected:

Notify UI immediately

Stop accepting or sending moves

Transition to Disconnected state

Status bar examples:

“Opponent disconnected”

“Connection lost”

10. Weak / Unstable Connection Handling

Initially:

No reconnection

No rollback

No buffering

Instead:

If socket stalls beyond timeout → error

Fail fast, fail clearly

This keeps the game:

Predictable

Debuggable

Fair

11. Message Direction Rules

Network layer does not interpret message meaning

It only guarantees:

Message arrives in order

Message arrives whole

Message is delivered or failure is reported

All validation happens in:

Messaging module

Engine module

12. Threading Expectations (Preview Only)

This module:

Runs entirely off the UI thread

Never blocks Qt

Communicates via thread-safe queues or signals

(Full design in Module 5)

13. Security & Trust Model

This is friendly peer-to-peer, not adversarial:

No encryption (initially)

No authentication

No NAT traversal

However:

Never trust incoming data blindly

Malformed messages must not crash the app

15. Exit Criteria (Module 3 Complete)

This module is done when:

✔ Host accepts exactly one peer
✔ Join handles wrong IPs cleanly
✔ Errors are clear and recoverable
✔ Disconnects are detected reliably
✔ Network layer is chess-agnostic
✔ Works on Linux and Windows