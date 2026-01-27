1. Purpose of This Module

The Core Chess Engine is the single authority on what is and is not legal chess.

Everything else in the system:

UI

Networking

Chat

Status bar
must trust this module completely.

If this module says a move is illegal, it is illegal — no exceptions.

2. Absolute Boundaries (Very Important)

This module:

Knows nothing about:

Qt

ASIO

Threads

Players being remote or local

UI orientation

Only knows:

Board state

Rules of chess

Whose turn it is

If you ever feel tempted to:

“Just check this in the UI…”

That’s a bug. The engine must do it.

3. Canonical Board Perspective (Critical Concept)

The engine always sees the board from White’s perspective.

Rank 1 = White’s back rank

Rank 8 = Black’s back rank

Files always go a → h

Black’s “reversed board” is never handled here.

This guarantees:

One coordinate system

One rule set

Zero duplication

Visual flipping happens later (Module 2).

4. Core Responsibilities Explained
4.1 Board State Ownership

The engine owns:

What piece is on every square

Which side is to move

Special state (castling rights, en passant)

Nothing outside the engine is allowed to mutate these directly.

4.2 Move Legality (The Golden Rule)

A move is legal if and only if:

The moving piece exists

The piece belongs to the side whose turn it is

The move obeys the piece’s movement rules

The path is not blocked (when applicable)

Special rules are respected

The move does not result in the moving side’s king being in check

All 6 must be true.
Fail one → illegal.

5. King Safety Is Non-Negotiable

The engine must never allow:

Moving into check

Exposing the king to discovered check

Castling through check

Castling while in check

This is enforced by:

Simulating the move internally

Verifying the king’s safety afterward

This concept is key for:

Highlighting “red” moves in the UI

Preventing suicidal king moves

6. Check, Checkmate, and Stalemate
Check

The king is currently attacked by at least one enemy piece

Checkmate

King is in check

No legal move exists that removes the check

Stalemate

King is not in check

No legal move exists

These are engine-level concepts, not UI states.

7. Special Chess Rules (Conceptual Handling)
Castling

The engine must track:

Whether the king has moved

Whether each rook has moved

Castling is legal only if:

Neither king nor rook has moved

No pieces in between

King is not in check

Squares the king passes through are not attacked

En Passant

The engine must:

Remember the square eligible for en passant

Allow capture only immediately after the pawn’s two-square move

Remove the captured pawn correctly

No UI guesswork here.

Promotion

Pawn reaching the final rank must promote

Promotion is mandatory

If no choice is provided, default is Queen

The engine enforces this — UI only asks the user.

8. Invalid Move Prevention Strategy

Instead of:

“Let the user try and reject later”

The engine supports:

Querying all legal moves

Verifying whether a move is legal before execution

This enables:

Greyed-out squares

Red highlights

Turn-based enforcement

Network validation (reject cheating peers)

9. Why This Matters for Networking

Because this module:

Is deterministic

Has no side effects

Both peers can:

Validate moves locally

Detect desync

Reject invalid or malicious moves

This is essential for P2P trust.

10. What This Module Does NOT Do

To be crystal clear, this module does NOT:

Flip the board

Render pieces

Show highlights

Handle turns visually

Show messages

Manage timers

Care who is local or remote

It only answers:

“Is this chess?”

12. Completion Criteria (Module 1 Done)

Module 1 is complete when:

✔ Every illegal move is rejected
✔ Every legal move is allowed
✔ Check/checkmate/stalemate are correct
✔ Engine state never becomes invalid
✔ No external module needs to “double-check” rules