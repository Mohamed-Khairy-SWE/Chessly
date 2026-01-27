1. Purpose of This Module

This module defines:

How the user interacts with Chessly and how the UI reflects the game state

It does not:

Decide chess legality

Manage networking

Implement threading

It:

Renders information

Collects user intent

Displays system feedback

2. Core UX Principles
2.1 Zero Ambiguity

At any moment, the user must know:

Am I connected?

Is it my turn?

Why can’t I move?

What just happened?

No silent failures. No guesswork.

2.2 UI Is a State Machine

The UI reacts to application state, not random events.

Buttons appear, disappear, or disable based on:

Connection state

Game state

Turn state

3. Main Window Structure
Fixed Regions

Menu / Top Controls

Host button

Join button

IP input (only visible for Join)

Central Area

Chess board widget

Side Panel

Chat history

Chat input

Status Bar (Critical)

Real-time feedback

4. Host / Join UX Flow
Host Flow

User clicks Host

UI:

Disables Host / Join buttons

Shows “Waiting for player…”

On connection:

Status → “Opponent connected”

Board becomes interactive

Join Flow

User clicks Join

IP input appears

User submits IP

Outcomes:

Success → board activates

Failure → error shown, buttons re-enabled

UI never blocks during connection attempts.

5. Status Bar Design (Extremely Important)

The status bar is the narrator of the game.

Examples of Messages

“Waiting for opponent…”

“Connected — You are White”

“Your turn”

“Opponent’s turn”

“Invalid move”

“Check”

“Checkmate — You lose”

“Opponent disconnected”

“Network error: connection lost”

Rules:

Only one primary message at a time

Latest message overrides previous

Errors take priority

6. Chess Board Widget Responsibilities

This widget:

Displays pieces

Handles clicks / drags

Displays highlights

It does not:

Validate moves

Decide legality

Know network details

7. Input Handling Rules
Selection Rules

Only allow selecting:

Player’s own pieces

During player’s turn

Clicking opponent pieces does nothing

Move Attempt Flow

User selects piece

Legal destinations are highlighted

User selects destination

Move intent sent to engine

If accepted:

UI updates

Move sent to network

If rejected:

Status bar shows reason

8. Highlighting Strategy (Visual Feedback)
Highlight Types

Selected piece (blue outline)

Legal moves (green)

Illegal / dangerous moves (red)

Check (red king square)

All highlight data comes from:

Engine (legal moves)

Board mapping module

UI never invents highlights.

9. Board Orientation Handling

UI must:

Use Board Mapping module

Never flip engine state

Render based on player color

White:

Bottom = rank 1

Black:

Bottom = rank 8

This is invisible to the engine.

10. Chat UX

Chat panel behavior:

Enabled only when connected

Messages appear in chronological order

Own messages visually distinct (optional)

Chat input disabled when disconnected

Chat never blocks gameplay.

11. Error Presentation Strategy

Errors must be:

Human-readable

Actionable

Examples:

“Could not connect to host”

“Host already has a player”

“Opponent disconnected”

UI must:

Reset to safe state

Re-enable Host / Join buttons

12. Turn Awareness & Locking

UI must:

Disable board input when not your turn

Visually indicate whose turn it is

Prevent double-move attempts

This avoids race conditions.

13. Accessibility & Polish (Optional but Recommended)

Clear piece contrast

Large enough squares

Keyboard shortcuts (later)

Window resizing support

Not required for v1, but design should allow it.

15. Exit Criteria (Module 6 Complete)

Module 6 is complete when:

✔ Host / Join flow is clear
✔ Board is responsive and accurate
✔ Status bar always explains state
✔ Illegal moves are impossible
✔ Chat works independently
✔ Same UX on Linux & Windows