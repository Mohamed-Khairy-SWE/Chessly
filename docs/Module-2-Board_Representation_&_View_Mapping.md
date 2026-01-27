1. Purpose of This Module

This module is the translator between:

The engine’s canonical board (always White-oriented)

The player’s visual board (White view or Black view)

It answers one question only:

“When the engine says square X, which square does the user see and click?”

It does not:

Decide legality

Track game state

Know chess rules

2. The Fundamental Rule (Non-Negotiable)

The engine’s board NEVER flips.
The UI ALWAYS adapts.

This guarantees:

One source of truth

No duplicated rule logic

No color-based bugs

If Claude flips the engine board even once → architecture violation.

3. Canonical vs Visual Coordinate Systems
Canonical (Engine)

Fixed

White at bottom

Files: a → h

Ranks: 1 → 8

This never changes.

Visual (UI)

Depends on player color

White player:

Canonical == Visual

Black player:

Board is rotated 180°

This is purely a view transform.

4. The Core Concept: Square Mapping

This module exists to perform bidirectional mapping:

Engine → UI

Where to draw pieces

UI → Engine

What square the user clicked

These mappings must be:

Invertible

Deterministic

Stateless

5. Mapping Rules (Conceptual, No Math Yet)
White Player View

Engine square = UI square

No transformation

Black Player View

File is mirrored

Rank is mirrored

In plain English:

Top becomes bottom

Left becomes right

This is equivalent to rotating the board 180°.

6. Why Mapping Must Be Centralized

If mapping logic is:

Spread across UI widgets

Reimplemented in event handlers

Mixed into rendering code

You will get:

Wrong move destinations

Broken highlights

Impossible-to-debug desync bugs

This module must be the only place where mapping happens.

7. Responsibilities of This Module
7.1 Engine → UI Responsibilities

Given:

Engine board state

Player color

This module tells the UI:

Which piece goes on which visual square

Which squares are:

Legal

Illegal

Dangerous (king would be attacked)

The UI does not compute this.

7.2 UI → Engine Responsibilities

When a user:

Clicks a square

Drags a piece

The module:

Converts that visual square

Into a canonical engine square

The engine never sees “visual coordinates”.

8. Highlighting Strategy (Very Important)

The engine:

Provides a list of legal moves

Can indicate king-in-check states

This module:

Converts those legal engine squares

Into visual highlights

Highlight Types

Legal move (green)

Illegal / blocked (none)

Dangerous move (red)

Check square (red outline)

Color decisions are UI, but square selection comes from here.

9. King Safety Visualization

When the engine says:

“This move would leave the king in check”

This module ensures:

That destination square is highlighted as invalid

The king’s square is visually marked when in check

The UI must not “guess” danger.

10. Board Orientation & Turn Awareness

This module also answers:

“Whose turn is it?”

“Is this square interactable?”

Rules:

Player can only interact with:

Their own pieces

During their turn

Opponent pieces are:

Rendered

Not selectable

Selection logic must go through mapping first.

11. Drag-and-Drop vs Click-to-Move

Regardless of UI interaction style:

Drag start square → mapped to engine

Drag end square → mapped to engine

The engine only sees:

canonical from → canonical to

13. Testing This Module in Isolation

Even without UI:

Feed canonical squares

Verify correct visual mapping

Verify inverse mapping returns original square

If mapping isn’t reversible → it’s wrong.

14. Exit Criteria (Module 2 Complete)

Module 2 is complete when:

✔ White and Black players see correct orientation
✔ Clicking a square always maps correctly
✔ Highlights match engine legality
✔ King-in-check visuals are accurate
✔ No engine logic is duplicated