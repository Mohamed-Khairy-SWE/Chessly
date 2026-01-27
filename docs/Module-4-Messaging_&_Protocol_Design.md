1. Purpose of This Module

This module defines:

What data is exchanged between peers, in what format, and in what order

It is the contract between two running instances of Chessly.

It does not:

Contain chess logic

Care about UI

Manage sockets

Decide threading

It only defines:

Message types

Message structure

Validation rules

Error semantics

2. Core Design Philosophy
2.1 Explicit Is Better Than Implicit

Every message:

Has a type

Has a clearly defined payload

Has exactly one meaning

No “magic strings”, no ambiguous blobs.

2.2 Deterministic Ordering

Messages:

Are processed in the order received

Never re-ordered

Never partially applied

TCP guarantees ordering — the protocol relies on it.

2.3 Versioned from Day One

Even if you never change it:

Every handshake includes a protocol version

Mismatches are rejected

This avoids silent incompatibilities later.

3. Message Categories

All messages fall into one of six categories:

Handshake

System / Error

Game Control

Chess Moves

Chat

Heartbeat / Keepalive (optional)

4. Handshake Messages (Mandatory)

These are exchanged before the game starts.

Responsibilities

Confirm protocol compatibility

Assign colors

Confirm readiness

Rules

No other message types allowed before handshake completes

Failure → immediate disconnect with error

5. Color Assignment Strategy

To avoid conflicts:

Host is always White

Joiner is always Black

This removes:

Negotiation complexity

Race conditions

UI ambiguity

Board orientation is handled later (Module 2).

6. System & Error Messages

Errors are messages, not side effects.

Error Message Responsibilities

Carry an explicit error type

Carry a human-readable reason

Force state transition (e.g., disconnect)

Typical Error Scenarios

Host full

Protocol mismatch

Invalid message format

Unexpected message order

Illegal move received

Errors must never:

Be silent

Crash the app

Leave the game in an undefined state

7. Game Control Messages

These control the lifecycle of the match.

Examples of intent (not structure):

Game start

Game over

Resign

Draw offer / accept (optional later)

Rules:

These messages affect global state

Must be validated before application

Cannot be replayed out of order

8. Chess Move Messages
Philosophy

Peers do not send board states — only moves.

This ensures:

Smaller messages

Deterministic replay

Easier desync detection

Validation Rules

When a move is received:

Validate message format

Convert to engine move

Ask engine if move is legal

Apply or reject

Illegal move received:

Send error

End game (optional strict mode)

9. Chat Messages

Chat is:

Asynchronous

Non-blocking

Never affects game state

Rules:

Chat messages allowed only after handshake

Must not block move processing

Must be safe against malformed content

Chat delivery order matters, but timing does not.

10. Message Validation Rules (Critical)

Every incoming message must be validated for:

Type correctness

Required fields present

Field ranges valid

Logical correctness (given current state)

If validation fails:

Send protocol error

Disconnect cleanly

Never assume peer is well-behaved.

11. Message Size & Framing

Protocol must support:

Clear message boundaries

Length-prefixed messages

No reliance on TCP packet boundaries

This prevents:

Partial reads

Message concatenation bugs

Buffer overruns

12. Message Ordering Constraints

Some messages are illegal in certain states.

Examples:

Chess move before handshake → invalid

Chat before handshake → invalid

Game over move → invalid

Protocol must enforce:

State-aware message acceptance

13. Desynchronization Detection (Soft)

Peers can optionally:

Track move numbers

Detect mismatches

Abort game if detected

This is not anti-cheat — it’s consistency protection.

15. Exit Criteria (Module 4 Complete)

This module is complete when:

✔ All message types are explicitly defined
✔ Handshake fully gates game start
✔ Illegal messages are detected and rejected
✔ Moves and chat are cleanly separated
✔ Errors are explicit and user-friendly
✔ Protocol works identically on Linux & Windows