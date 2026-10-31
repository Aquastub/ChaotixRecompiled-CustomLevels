# Campaign Studio (first native integration)

Campaign Studio is available from the title/front-end menu. It creates and
stores ordered campaigns in `Campaigns.txt` in the user's Chaotix Recompiled
data directory.

## Current capabilities

- Create, rename and delete campaigns in-game.
- Select a stage with the existing LEVEL SELECT controls, then add that exact
  place, level, time of day, character pair and player count to a campaign.
- Remove the final stage from a campaign.
- Play the campaign from its first stage. Each stage is launched through the
  existing verified stage-select hand-off; finishing a stage advances to the
  next one. The game returns to Campaign Studio when the playlist is complete.
- Campaign stages use the normal practice/no-save behavior of LEVEL SELECT.

The campaign file is a small line-oriented text format. `CAMPAIGN` starts a
playlist and `LEVEL` stores the game's native stage-select request. It contains
no ROM bytes or game assets.

## Important distinction: custom campaigns vs. custom geometry

This first integration makes genuinely user-authored, playable campaigns from
the levels that Knuckles' Chaotix already contains. It does **not yet** create
new tilemaps, object layouts, collision maps, enemy placements or new stage
IDs. The existing emulator executes the original 32X game code, and its level
engine expects the game's own compressed stage data and object routines. A
tile editor that only saves a picture or JSON map would not make that map
playable.

A true custom-level editor requires a separate reverse-engineering and runtime
implementation phase: identify the ROM's stage-data formats and loaders,
define a validated custom-stage package, and add a game-side loader/renderer
path that can supply custom geometry and object data without corrupting the
emulated machine state. That work is intentionally not faked by this initial
campaign feature.

## Controls

- `CAMPAIGN`: change the selected campaign with left/right or confirm.
- `RENAME CAMPAIGN`: type a name.
- `ADD CURRENT LEVEL`: first configure the desired stage in LEVEL SELECT.
- `PLAY CAMPAIGN`: run the ordered playlist.
