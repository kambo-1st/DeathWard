# Expedition heart and dynamite HUD

The user requested removing the numeric heart total and adding dynamite icons to the same HUD bar, in the hearts' style.

The bottom-left bar now contains the existing heart icons and a second row of pixel-art dynamite sticks. Both use an 8×6 grid with three-pixel cells. Each stick represents one charge, up to ten visible sticks; larger inventories show the additional quantity as `+N` (99 charges = ten sticks +89). Zero charges shows one muted empty icon. After acknowledging the icons, the user requested removal of **B / PLACE**: the button and its input-blocking rectangle are removed. **B** still places dynamite. Heart types, half-heart rendering, inventory limits and gameplay are unchanged.

The main-game build passes. A temporary actual Game/Renderer capture checks starting three hearts/three charges, spending a charge through the existing placement action (3 → 2), half-heart/empty inventory, and twelve heart containers/99 charges. Screenshots show the icons fitting the bar and the numeric heart total removed. See `default.png`, `spent.png`, `empty.png`, `capacity.png` and `preview.log`.

The earlier screenshots retain the subsequently removed placement button. The user acknowledged the icon bar and placement-button removal, then selected the additional cleanup below. This is a HUD presentation change; the broader gameplay/native-parity gaps remain in their existing reports.

Button-removal verification: main game and input-test builds pass. `deathward_input_tests --dynamite-only` passes in Mine and Canyon, including B placement, no invisible blocker at the old button, paused input, refill and contact kicks. `no-place-button.png` shows that checkpoint.

## Pause menu and prop cleanup

The expedition HUD no longer shows Pause or Tuning buttons, and their former rectangles no longer intercept world input. Escape still opens the pause menu; Tuning is available there. Closing Tuning returns to the menu, and Escape resumes gameplay. The separate Fort Mercy hub presentation is unchanged.

Fireplaces no longer draw health bars or their hover name, including when damaged or hovered. The user explicitly requested removal of the name after the health-bar cleanup. Flames, damage and extinguishing remain intact; ordinary enemy names and bars are retained. Nearby dung no longer produces `DUNG / BREAKABLE`; other demolition hints and lit-powder warnings are retained.

The build, ordinary-prop suite, actual HUD input checks and full tuning-menu/export/load/retry checks pass. Field-specific tuning fixtures now open the panel by action instead of clicking a removed HUD button; the HUD and balance fixtures exercise the actual Escape/menu/mouse return path. A stale checkpoint-version assertion was updated to verify the current v13 revision suffix. A temporary Game/Renderer capture places the player beside dung and damages both fireplaces: no dung hint or fireplace bars are displayed. See `cleanup-100.png` and `cleanup-review.log`.

The user also selected [vegetation through 500%](../vegetation-500/README.md). Human visual acceptance of this combined cleanup remains pending.

Fireplace-name follow-up: the main-game rebuild passes. An actual Game/Renderer capture deliberately hovers a damaged fireplace and confirms that neither its name nor health bar is rendered; the fire and hover outline remain visible. See `no-fireplace-label.png` and `no-fireplace-label-preview.log`. Human visual review remains pending.
