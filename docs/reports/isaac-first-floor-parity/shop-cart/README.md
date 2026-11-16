# Centered Western shop cart

The user acknowledged D12c and requested its commit, then selected replacing the seller with a Wild West peddler/seller cart centered in the room. D12c is committed as `a8f35fb7`. The cart change is implemented and developer-verified. The user acknowledged the scoped cart delivery on 2026-11-16 (“nice commit now, then continue”); it is included in this checkpoint.

The model is the existing **Frontier `SM_Veh_Wagon_Shop_01`**, already assembled as Fort Mercy's merchant wagon. [Bake script](../../../../scripts/bake_shop_cart.py) extracts its13 existing parts from the baked scene library, preserves their UVs and embedded material, uniformly scales the longest ground dimension to4.4, centers the complete assembly in XZ and grounds it atY0. [Asset manifest](../../../../assets/props/shop-cart/manifest.json) records source/output hashes, bounds and7,256 triangles. No asset download or new generated artwork is involved.

Every shop now draws that wagon at the exact room center through the same mission material/shadow passes as existing imported props. The prior primitive seller/table is removed from shops; specialist service NPCs retain their current appearance. The wagon has a shared solid ground footprint for walking, dodge and navigation. Clicking it approaches a reachable edge; later-floor/legacy shop menus still use their existing interaction. The physical footprint is a conservative box around the full wagon, not per-triangle physics.

Stock selection, prices, effects, payment and sold state are retained. Source slot order and horizontal spacing remain; in small rooms only the forward stock offset is increased as needed for a character to stand clear of the wagon. The direct review starts beside it. Local outcrops that would intrude on the centered cart are filtered after their seeded draws; canyon room outlines/connections remain. Dynamic resizing retains safe player placement. No new gameplay tunable or preset schema is introduced.

Native packaging copies the standalone asset; the browser asset list includes it, but browser runtime is untested. Gameplay saves and broader native shop coverage remain open as documented in [D12c](../d12c-shop-stock/README.md).

## Verification

- [Four core suites](core-tests.log) pass: source stock, heart/key transactions and legacy shop. [Final arrival regression](arrival-tests.log) rechecks both affected suites after correcting the legacy approach distance.
- [Detailed checks](core-details.log) cover27 size/range/route configurations, model-center/stock clearance and key access,16 walking/dodge directions, cart-edge clicks, purchases, sold revisit, Apply, floors and presets. The asset manifest bounds match the shared collider dimensions within0.00001.
- [Main-game input](game-input.log) exercises the imported model and mission shadows, safe direct entry, mouse purchases/discount/revisit, tuning/export/load/retry. [Legacy input](legacy-input.log) checks clicking the actual cart, trade/payment/UI guards and persisted spending in both Mine and Canyon themes.
- Visual inspection: [centered shop cart](shop-stock-before.png) and [purchase/discount](shop-stock-discount.png). The original165% preset hash remains unchanged.

The cart needed its own full-body click target and an arrival check measured against the shop center: the old rule stopped two units before the new cart edge, outside trade range. Both paths are corrected. Diagonal movement can slide around the cart; grounded movement/dodge cannot enter its box or cross straight through it. Native packaging is built; browser execution and broader native shop equivalence remain untested/open.

## Review

```sh
./build/deathward --expedition --seed 7 --review-shop-stock --mute --save /home/kambo/.local/share/deathward/reviews/shop-cart/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Check the centered wagon, walk around it and buy the displayed stock. The accepted165% zoom, walking, shooting, universal dodge and20-coin labelled review setup are retained. The previous D12c checkpoint is committed; this cart change received scoped user acknowledgment and is included in this checkpoint. Broader native shop coverage remains unfinished; the next bounded continuation is ordinary bomb/dynamite stock.
